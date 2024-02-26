// jacob curlin
// sandbox.cpp
// 02/22/2024

#include "../include/sandbox.h"

#include <glm/gtc/type_ptr.hpp>

Sandbox::Sandbox() {}

Sandbox::~Sandbox() {}

void Sandbox::Initialize()
{
    Engine::Initialize();

    model_filenames = {"soccerball/ball.obj", "objects/light_cube/light_cube.obj", "sponza/sponza.obj", "objects/backpack/backpack.obj" };
    shader_names = {"model", "lighting"};

    for (const auto& filename : model_filenames)
    {
        std::filesystem::path model_path = m_settings.asset_dir / filename;
        loaded_models[filename] = m_resource_manager->loadModel(model_path.string());
    }

    for (const auto& name : shader_names)
    {
        std::filesystem::path vert_path = (m_settings.shader_dir / (name + ".vs")).string();
        std::filesystem::path frag_path = (m_settings.shader_dir / (name + ".fs")).string();

        loaded_shaders[name] = std::make_shared<cgx::graphics::Shader>(name, m_settings.shader_dir.string(), vert_path.string(), frag_path.string());
    }

    m_entities = std::vector<cgx::ecs::Entity>();

}

void Sandbox::Update()
{
    Engine::Update();
}

void Sandbox::Render()
{
    Engine::Render();

    glm::mat4 proj_mat, view_mat;

    view_mat = m_camera->GetViewMatrix();
    proj_mat = glm::perspective(
        glm::radians(m_camera->getZoom()),
        (float) m_settings.window_width / (float) m_settings.window_height,
        0.1f, 100.0f
    );

    glm::mat4 model_mat;
    for (auto& entity : m_entities)
    {
        model_mat = glm::mat4(1.0f);        

        std::shared_ptr<cgx::graphics::Model> model = m_ecs_handler->GetComponent<RenderComponent>(entity).model;
        std::shared_ptr<cgx::graphics::Shader> shader = m_ecs_handler->GetComponent<RenderComponent>(entity).shader;

        if (model && shader)
        {
            shader->use();
            // shader->setVec3("light.position", (m_ecsHandler->GetComponent<TransformComponent>(light))) /TODO
            shader->setVec3("light.position", 1.0f, 1.0f, 1.0f);
            shader->setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
            shader->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
            shader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

            model_mat = glm::rotate(model_mat, glm::radians(140.0f), m_ecs_handler->GetComponent<TransformComponent>(entity).rotation);
            model_mat = glm::translate(model_mat, m_ecs_handler->GetComponent<TransformComponent>(entity).position);
            model_mat = glm::scale(model_mat, m_ecs_handler->GetComponent<TransformComponent>(entity).scale);

            shader->setMat4("projection", proj_mat);
            shader->setMat4("view", view_mat);
            shader->setMat4("model", model_mat);

            model->draw(*shader);
        }
    }

    if (m_imgui_active)
        Sandbox::ImguiRender();
}

void Sandbox::ImguiRender()
{
    m_imgui_manager->BeginRender();


    m_imgui_ecs_system->DisplayEntityDropdown();
    m_imgui_ecs_system->DisplayComponentEditors();


    m_imgui_manager->EndRender();
}



void Sandbox::Shutdown() 
{
    Engine::Shutdown();
}

int main()
{
    Sandbox app;
    app.Run();
    return 0;
}