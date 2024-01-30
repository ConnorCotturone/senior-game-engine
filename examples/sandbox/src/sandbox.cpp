// jacob curlin
// sandbox_app.cpp
// 12/30/2023 

#include "../include/sandbox.h"

// temp
#include <iostream>

Sandbox::Sandbox() {}

Sandbox::~Sandbox() {}

void Sandbox::Initialize() {
    Engine::Initialize();
}

void Sandbox::Update() {
    Engine::Update();
}

void Sandbox::Render() {
    Engine::Render();
}

void Sandbox::Shutdown() {
    Engine::Shutdown();
}

int main() {
    Sandbox app;
    app.Run();
    return 0;
}