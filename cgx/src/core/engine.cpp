// jacob curlin
// engine.cpp
// 01/05/2023

#define STB_IMAGE_IMPLEMENTATION

#include "engine.h"

#include <assert.h>
#include <filesystem>
#include <iostream>

// temp - remove
#include <unistd.h>
#include <limits.h>


Engine::Engine() {
    m_windowHandler = nullptr;
    m_inputHandler = nullptr;
    m_camera = nullptr;

    m_isRunning = false;
    m_imguiActive = false;

    m_timeData.deltaTime = 0.0;
    m_timeData.lastTime = 0.0;
}
    
Engine::~Engine() {
    // assert(m_windowHandler == nullptr);
    // assert(m_inputHandler == nullptr); 
}

// main game loop
void Engine::Run() {
    Initialize();   // NOTE: INIT FIRST ALWAYS

    m_isRunning = true;

    static double currTime = 0.0;

    while (m_isRunning) {
        while (glfwGetTime() < m_timeData.lastTime + 0.016) { }        // limit fps to 60

        // frame timing
        currTime = static_cast<float>(glfwGetTime());
        m_timeData.deltaTime = currTime - m_timeData.lastTime;
        m_timeData.lastTime = currTime;

        Update();
        Render();

        m_windowHandler->SwapBuffers();
    }
    Shutdown();
}

void Engine::Initialize() {
    LoggingHandler::Initialize();
    PHX_TRACE("engine - initializing")

    m_windowHandler = new Window();
    m_windowHandler->Initialize(settings.WindowWidth,
                                settings.WindowHeight,
                                "engine");

    m_eventHandler = new EventHandler(m_windowHandler->GetGLFWWindow());
    m_eventHandler->RegisterKeyCallback([this](int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            m_isRunning = false;
        if (key == GLFW_KEY_M && action == GLFW_PRESS)
            m_imguiActive = !m_imguiActive;
    });    


    m_imguiHandler = new ImguiHandler();
    m_imguiHandler->Initialize(m_windowHandler->GetGLFWWindow());

    m_inputHandler = new InputHandler(m_windowHandler->GetGLFWWindow());

    // check glad loaded
    PHX_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize GLAD.");
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { exit(1); }

    glEnable(GL_DEPTH_TEST);
    stbi_set_flip_vertically_on_load(true);

    m_camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

    // initialize shader program w/ frag & vert shaders
    std::__fs::filesystem::path shader_dir(SHADER_DIRECTORY);
    std::__fs::filesystem::path data_dir(DATA_DIRECTORY);
    
    std::__fs::filesystem::path model_vs_path = shader_dir / "model.vs";
    std::__fs::filesystem::path model_fs_path = shader_dir / "model.fs";
    std::__fs::filesystem::path light_vs_path = shader_dir / "lighting.vs";
    std::__fs::filesystem::path light_fs_path = shader_dir / "lighting.fs";

    std::__fs::filesystem::path model_obj_path = data_dir / "soccerball/ball.obj";
    std::__fs::filesystem::path light_obj_path = data_dir / "objects/light_cube/light_cube.obj"; 

    // m_objShader = new Shader(model_vs_path.c_str(), model_fs_path.c_str());
    // m_lightShader = new Shader(light_vs_path.c_str(), light_vs_path.c_str());

    // m_subject = new Model(model_obj_path.string());
    // m_lightSrc = new Model(light_obj_path.string());

    m_ecsHandler = new ECS::ECSManager();
    m_ecsHandler->Initialize();

    m_ecsHandler->RegisterComponent<TransformComponent>();
    m_ecsHandler->RegisterComponent<RenderComponent>();

    m_entities = std::vector<ECS::Entity>(2);

    // subject
    m_entities[0] = m_ecsHandler->CreateEntity();
    m_ecsHandler->AddComponent(
        m_entities[0],
        RenderComponent {
            .model = new Model(model_obj_path.string()),
            .shader = new Shader(model_vs_path.c_str(), model_fs_path.c_str())
        });
    m_ecsHandler->AddComponent(
        m_entities[0], 
        TransformComponent {
            .position = glm::vec3(0.0f, 0.0f, 0.0f),
            .rotation = glm::vec3(0.0f, 0.0f, 0.0f),
            .scale =    glm::vec3(1.0f, 1.0f, 1.0f)
        });

    // light source
    m_entities[1] = m_ecsHandler->CreateEntity();
    m_ecsHandler->AddComponent(
        m_entities[1],
        RenderComponent {
            .model = new Model(light_obj_path.string()),
            .shader = new Shader(light_vs_path.c_str(), light_fs_path.c_str())
        });
    m_ecsHandler->AddComponent(
        m_entities[1], 
        TransformComponent {
            .position = glm::vec3(1.0f, 3.0f, 5.0f),
            .rotation = glm::vec3(1.0f, 0.0f, 0.0f),
            .scale =    glm::vec3(0.5f, 0.5f, 0.5f)
        });
}

void Engine::Update() {
    m_eventHandler->Update();

    if (!m_imguiActive)
    {
        glfwSetInputMode(m_windowHandler->GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        double xoffset, yoffset;
        m_inputHandler->getMouseOffset(xoffset, yoffset);
        m_camera->MouseUpdate(xoffset, yoffset, true);

        // keyboard camera updates
        if (m_inputHandler->IsKeyPressed(GLFW_KEY_W))
            m_camera->KeyboardUpdate(FORWARD, m_timeData.deltaTime);
        if (m_inputHandler->IsKeyPressed(GLFW_KEY_A))
            m_camera->KeyboardUpdate(LEFT, m_timeData.deltaTime);
        if (m_inputHandler->IsKeyPressed(GLFW_KEY_S))
            m_camera->KeyboardUpdate(BACKWARD, m_timeData.deltaTime);
        if (m_inputHandler->IsKeyPressed(GLFW_KEY_D))
            m_camera->KeyboardUpdate(RIGHT, m_timeData.deltaTime);
    }
    else
    {
        glfwSetInputMode(m_windowHandler->GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        m_camera->MouseUpdate((double)0.0, (double)0.0, true);
    }

}

void Engine::Render() {
    // window background
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ECS::Entity* e_subject = &m_entities[0];
    ECS::Entity* e_lightSrc = &m_entities[1];
    Model* mod_subject = m_ecsHandler->GetComponent<RenderComponent>(*e_subject).model;
    Model* mod_lightSrc = m_ecsHandler->GetComponent<RenderComponent>(*e_lightSrc).model;
    Shader* s_subject = m_ecsHandler->GetComponent<RenderComponent>(*e_subject).shader;
    Shader* s_lightSrc = m_ecsHandler->GetComponent<RenderComponent>(*e_lightSrc).shader;

    s_subject->use();

    // setup lighting
    s_subject->setVec3("light.position", m_ecsHandler->GetComponent<TransformComponent>(*e_lightSrc).position);
    s_subject->setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
    s_subject->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
    s_subject->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

    glm::mat4 proj_mat, view_mat; 
    glm::mat4 obj_model_mat, light_model_mat;

    // transformation matrix - perspective projection 
    proj_mat = glm::perspective(glm::radians(m_camera->getZoom()), 
                (float) settings.WindowWidth / (float) settings.WindowHeight, 0.1f, 100.0f);

    // transformation matrix - view / camera space
    view_mat = m_camera->GetViewMatrix();

    // model matrix - translate/scale model into world space 
    obj_model_mat = glm::mat4(1.0f);
    obj_model_mat = glm::translate(obj_model_mat, m_ecsHandler->GetComponent<TransformComponent>(*e_subject).position);
    obj_model_mat = glm::scale(obj_model_mat, m_ecsHandler->GetComponent<TransformComponent>(*e_subject).scale);

    s_subject->setMat4("projection", proj_mat);
    s_subject->setMat4("view", view_mat);
    s_subject->setMat4("model", obj_model_mat);  

    mod_subject->Draw(*s_subject);

    s_lightSrc->use();

    light_model_mat = glm::mat4(1.0f);
    s_lightSrc->setMat4("projection", proj_mat);
    s_lightSrc->setMat4("view", view_mat);

    light_model_mat = glm::translate(light_model_mat, m_ecsHandler->GetComponent<TransformComponent>(*e_lightSrc).position);
    light_model_mat = glm::rotate(light_model_mat, glm::radians(140.0f), m_ecsHandler->GetComponent<TransformComponent>(*e_lightSrc).rotation);
    light_model_mat = glm::scale(light_model_mat, m_ecsHandler->GetComponent<TransformComponent>(*e_lightSrc).scale);
    s_lightSrc->setMat4("model", light_model_mat);

    mod_lightSrc->Draw(*s_lightSrc);

    if (m_imguiActive) 
        m_imguiHandler->Render();
}

void Engine::Shutdown() {
    delete m_inputHandler;
    delete m_windowHandler;
}



