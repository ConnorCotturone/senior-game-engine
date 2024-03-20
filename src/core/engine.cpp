// Copyright © 2024 Jacob Curlin

#define STB_IMAGE_IMPLEMENTATION

#include "core/engine.h"
#include "ecs/events/engine_events.h"

#include <iostream>

namespace cgx::core {

    Engine::Engine()
            : m_time_data{0.0, 0.0}, m_is_running(false), m_imgui_active(false) {}

    // main game loop
    void Engine::Run() {
        Initialize();
        m_is_running = true;

        static double curr_time = 0.0;
        while (m_is_running) {
            while (glfwGetTime() < m_time_data.last_time + 0.016) {}        // limit fps to 60

            // frame timing
            curr_time = static_cast<float>(glfwGetTime());
            m_time_data.delta_time = curr_time - m_time_data.last_time;
            m_time_data.last_time = curr_time;

            Update();
            Render();

            m_window_manager->Update();

        }
        Shutdown();
    }

    void Engine::Initialize() {
        cgx::utility::LoggingHandler::Initialize();
        CGX_TRACE("engine - initializing")

        m_time_system = Time();
        m_time_system.Start();

        m_ecs_manager = std::make_shared<cgx::ecs::ECSManager>();
        m_ecs_manager->Initialize();
        m_ecs_manager->RegisterComponent<TransformComponent>();
        m_ecs_manager->RegisterComponent<RenderComponent>();
        m_ecs_manager->RegisterComponent<LightComponent>();
        m_ecs_manager->RegisterComponent<RigidBody>();


        m_window_manager= std::make_shared<cgx::core::WindowManager>();
        m_window_manager->Initialize(m_settings.window_width,
                                     m_settings.window_height,
                                     "engine");

        m_input_manager = std::make_shared<cgx::core::InputManager>(m_ecs_manager, m_window_manager);
        // (temp : remove this)


        auto onEscapePressed = [this]() {
            this->m_is_running = false;
        };
        InputAction escape_action;
        escape_action.addCallback(onEscapePressed);
        InputEventKey escape_key{InputType::KEYBOARD_KEY, InputState::PRESSED, GLFW_KEY_ESCAPE};
        m_input_manager->BindInputAction(escape_key, escape_action);



        m_resource_manager = std::make_unique<cgx::render::ResourceManager>();

        // check glad loaded
        CGX_ASSERT(gladLoadGLLoader((GLADloadproc) glfwGetProcAddress), "Failed to initialize GLAD.");
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) { exit(1); }

        glEnable(GL_DEPTH_TEST);

        m_framebuffer = std::make_shared<cgx::render::Framebuffer>(m_settings.render_width, m_settings.render_height);
        m_framebuffer->setClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        m_camera = std::make_unique<cgx::render::Camera>(m_input_manager, glm::vec3(0.0f, 0.0f, 3.0f));

        // ----- IMGUI ------

        m_imgui_manager = std::make_unique<cgx::gui::ImGuiManager>();
        m_imgui_manager->Initialize(m_window_manager->getGLFWWindow());

        m_imgui_render_window = std::make_unique<cgx::gui::ImGuiRenderWindow>(m_framebuffer);
        m_imgui_manager->RegisterImGuiWindow(m_imgui_render_window.get());

        m_imgui_ecs_window = std::make_unique<cgx::gui::ImGuiECSWindow>(m_ecs_manager, m_resource_manager);
        m_imgui_manager->RegisterImGuiWindow(m_imgui_ecs_window.get());

        m_imgui_performance_window = std::make_unique<cgx::gui::ImGuiPerformanceWindow>(m_time_system);
        m_imgui_manager->RegisterImGuiWindow(m_imgui_performance_window.get());

        m_render_settings = std::make_shared<cgx::gui::RenderSettings>();
        m_render_settings->msaa = false;
        m_render_settings->skybox = true;

        m_physics_system = m_ecs_manager->RegisterSystem<PhysicsSystem>();
        {
            cgx::ecs::Signature signature;
            signature.set(m_ecs_manager->GetComponentType<RigidBody>());
            signature.set(m_ecs_manager->GetComponentType<TransformComponent>());
            m_ecs_manager->SetSystemSignature<PhysicsSystem>(signature);
        }
        m_physics_system->Initialize(m_ecs_manager);

        m_imgui_render_settings_window = std::make_unique<cgx::gui::ImGuiRenderSettingsWindow>(m_render_settings);
        m_imgui_manager->RegisterImGuiWindow(m_imgui_render_settings_window.get());
    }

    void Engine::Update() {
        m_time_system.Update();
        TimeContext& update_time_data = m_time_system.getLastUpdate();
        double& delta_time = update_time_data.frame_time;
        
        m_physics_system->Update(static_cast<float>(delta_time));
        m_camera->Update(delta_time);


        // m_event_handler->Update();

        /*
        if (!m_imgui_active) {
            if (m_input_handler->m_ignore_next_mouse_update) {
                m_input_handler->resetMouseOffset();
                m_input_handler->m_ignore_next_mouse_update = false;
            }

            glfwSetInputMode(m_window_manager->getGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            double x_offset, y_offset;
            m_input_handler->getMouseOffset(x_offset, y_offset);
            m_camera->MouseUpdate(x_offset, y_offset, true);

            // keyboard camera updates
            if (m_input_handler->IsKeyPressed(GLFW_KEY_W))
                m_camera->KeyboardUpdate(cgx::render::kForward, delta_time);
            if (m_input_handler->IsKeyPressed(GLFW_KEY_A))
                m_camera->KeyboardUpdate(cgx::render::kLeft, delta_time);
            if (m_input_handler->IsKeyPressed(GLFW_KEY_S))
                m_camera->KeyboardUpdate(cgx::render::kBackward, delta_time);
            if (m_input_handler->IsKeyPressed(GLFW_KEY_D))
                m_camera->KeyboardUpdate(cgx::render::kRight, delta_time);
        } else {
            m_input_handler->m_ignore_next_mouse_update = true;
            glfwSetInputMode(m_window_manager->getGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            m_camera->MouseUpdate((double) 0.0, (double) 0.0, true);
        }
        */
    }

    void Engine::Render() {

        // glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        /// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // model, view, projection matrices
        glm::mat4 view_mat = m_camera->getViewMatrix();
        glm::mat4 proj_mat = glm::perspective(
                glm::radians(m_camera->getZoom()),
                (float) m_settings.render_width / (float) m_settings.render_height,
                0.1f, 100.0f
        );

        // iterate through active entities present in the ecs manager
        for (auto &entity: m_ecs_manager->getActiveEntities()) {
            glm::mat4 model_mat(1.0f);

            // skip rendering of entity if it has no RenderComponent
            if (!m_ecs_manager->HasComponent<RenderComponent>(entity)) { continue; }

            std::shared_ptr<cgx::render::Model> model = m_ecs_manager->GetComponent<RenderComponent>(entity).model;
            std::shared_ptr<cgx::render::Shader> shader = m_ecs_manager->GetComponent<RenderComponent>(entity).shader;

            // skip rendering of entity if either RenderComponent.model or RenderComponent.shader uninitialized
            if (!(model && shader)) { continue; }

            // if entity has a TransformComponent, apply transformations to model matrix
            if (m_ecs_manager->HasComponent<TransformComponent>(entity)) {
                auto &transform = m_ecs_manager->GetComponent<TransformComponent>(entity);

                // apply rotations transformations around each axis
                model_mat = glm::rotate(model_mat, glm::radians(transform.rotation.x),
                                        glm::vec3(1.0f, 0.0f, 0.0f)); // X-axis
                model_mat = glm::rotate(model_mat, glm::radians(transform.rotation.y),
                                        glm::vec3(0.0f, 1.0f, 0.0f)); // Y-axis
                model_mat = glm::rotate(model_mat, glm::radians(transform.rotation.z),
                                        glm::vec3(0.0f, 0.0f, 1.0f)); // Z-axis

                model_mat = glm::translate(model_mat, transform.position);  // apply position transformation

                model_mat = glm::scale(model_mat, transform.scale); // apply scale transformation
            }

            // activate shader program, set shader data, draw
            shader->use();

            // shader->setVec3("light.position", (m_ecsHandler->GetComponent<TransformComponent>(light))) /TODO
            shader->setVec3("light.position", 1.0f, 1.0f, 1.0f);
            shader->setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
            shader->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
            shader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

            shader->setMat4("proj", proj_mat);
            shader->setMat4("view", view_mat);
            shader->setMat4("model", model_mat);

            model->Draw(*shader);
        }
    }

    void Engine::Shutdown() {}
}