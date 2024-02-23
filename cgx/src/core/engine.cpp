// jacob curlin
// engine.cpp
// 01/05/2023

#define STB_IMAGE_IMPLEMENTATION

#include "engine.h"

#include <assert.h>
#include <filesystem>
#include <iostream>

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
    Initialize();  

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
    cgx::utility::LoggingHandler::Initialize();
    CGX_TRACE("engine - initializing")

    m_windowHandler = new Window();
    m_windowHandler->Initialize(m_settings.WindowWidth,
                                m_settings.WindowHeight,
                                "engine");


    m_inputHandler = new InputHandler(m_windowHandler->GetGLFWWindow());

    m_eventHandler = new cgx::event::EventHandler(m_windowHandler->GetGLFWWindow());
    m_eventHandler->RegisterKeyCallback([this](int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            m_isRunning = false;
        if (key == GLFW_KEY_M && action == GLFW_PRESS)
            m_imguiActive = !m_imguiActive;
    });    

    m_ecsHandler = new cgx::ecs::ECSManager();
    m_ecsHandler->Initialize();
    m_ecsHandler->RegisterComponent<TransformComponent>();
    m_ecsHandler->RegisterComponent<RenderComponent>();

    m_resource_manager = new cgx::graphics::ResourceManager();

    m_imguiHandler = new ImguiHandler();
    m_imguiHandler->Initialize(m_windowHandler->GetGLFWWindow());

    // check glad loaded
    CGX_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize GLAD.");
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { exit(1); }

    glEnable(GL_DEPTH_TEST);

    m_camera = new cgx::graphics::Camera(glm::vec3(0.0f, 0.0f, 3.0f));

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
            m_camera->KeyboardUpdate(cgx::graphics::FORWARD, m_timeData.deltaTime);
        if (m_inputHandler->IsKeyPressed(GLFW_KEY_A))
            m_camera->KeyboardUpdate(cgx::graphics::LEFT, m_timeData.deltaTime);
        if (m_inputHandler->IsKeyPressed(GLFW_KEY_S))
            m_camera->KeyboardUpdate(cgx::graphics::BACKWARD, m_timeData.deltaTime);
        if (m_inputHandler->IsKeyPressed(GLFW_KEY_D))
            m_camera->KeyboardUpdate(cgx::graphics::RIGHT, m_timeData.deltaTime);
    }
    else
    {
        glfwSetInputMode(m_windowHandler->GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        m_camera->MouseUpdate((double)0.0, (double)0.0, true);
    }

}

void Engine::Render() 
{
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}


void Engine::Shutdown() {
    delete m_inputHandler;
    delete m_windowHandler;
}



