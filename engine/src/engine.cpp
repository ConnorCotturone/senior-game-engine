// jacob curlin
// app.cpp
// 01/05/2023

#include <iostream>
#include <assert.h>

#include "../include/engine.h"

Engine::Engine() {
    m_windowHandler = nullptr;
    m_inputHandler = nullptr;
    m_isRunning = false;
}
    
Engine::~Engine() {
    assert(m_windowHandler == nullptr);
    assert(m_inputHandler == nullptr); 
}

// main game loop
void Engine::Run() {
    Initialize();

    m_isRunning = true;

    float deltaTime = 0.0f;
    float currentFrame = 0.0f;
    float lastFrame = 0.0f;
    while (m_isRunning) {
        

        // frame timing
        currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;


        Update(deltaTime);
        Render();

        m_windowHandler->SwapBuffers();
    }
    Shutdown();
}

void Engine::Initialize() {
    
    m_windowHandler = new Window(settings.WindowWidth,
                                 settings.WindowHeight,
                                 "engine");

    m_inputHandler = new Input(m_windowHandler->GetGLFWWindow());
    
}

void Engine::Update(float deltaTime) {
    m_windowHandler->Update();
    if (m_inputHandler->isKeyPressed(GLFW_KEY_ESCAPE)) {
        m_isRunning = false;
    }

    // update object characteristics, for ex. move ball an inch forward
}

void Engine::Render() {
    // OpenGL Rendering
}

void Engine::Shutdown() {
    delete m_inputHandler;
    delete m_windowHandler;
}
