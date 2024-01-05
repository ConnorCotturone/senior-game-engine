// jacob curlin
// app.cpp
// 01/05/2023

#include "../include/app.h"
#include <iostream>

App::App() : m_isRunning(false) {}
    
App::~App() {}

// main game loop
void App::Run() {
    Initialize();
    std::cout << "working!" << std::endl;
    m_isRunning = true;

    while (m_isRunning) {
        float deltaTime = 0; // (TODO) 
        Update(deltaTime);
        Render();
    }
    Shutdown();
}

void App::Initialize() {
    // todo
}

void App::Update(float deltaTime) {
    // Poll for user input
    // update object characteristics, for ex. move ball an inch forward
}

void App::Render() {
    // OpenGL Rendering
}

void App::Shutdown() {
    // todo
}
