// Copyright © 2024 Jacob Curlin

#include "sandbox.h"

Sandbox::Sandbox() {}

Sandbox::~Sandbox() {}

void Sandbox::Initialize()
{
    Engine::Initialize();

    // model filenames (relative to data directory - 'cgx/cgx/data/')
    model_filenames = {"soccerball/ball.obj", "light_cube/light_cube.obj", "sponza/sponza.obj", "backpack/backpack.obj", "sponza-2/sponza.obj" };
    // shader names (relative to shader directory - 'cgx/cgx/shaders/', extension-less filename of vert & frag shaders)
    shader_names = {"model", "lighting"};   // i.e. "model" -> fetches 'cgx/cgx/shaders/model.vs' and 'cgx/cgx/shaders/model.fs'

    std::vector<std::string> face_paths = {
        "/Users/curlin/dev/cgx/build/cgx_debug/data/assets/skybox_mountains/right.jpg",   // right
        "/Users/curlin/dev/cgx/build/cgx_debug/data/assets/skybox_mountains/left.jpg",    // left
        "/Users/curlin/dev/cgx/build/cgx_debug/data/assets/skybox_mountains/top.jpg",     // top
        "/Users/curlin/dev/cgx/build/cgx_debug/data/assets/skybox_mountains/bottom.jpg",  // bottom
        "/Users/curlin/dev/cgx/build/cgx_debug/data/assets/skybox_mountains/front.jpg",   // front
        "/Users/curlin/dev/cgx/build/cgx_debug/data/assets/skybox_mountains/back.jpg",    // back
    };

    m_skybox = std::make_unique<cgx::render::CubeMap>(face_paths, m_resource_manager->loadShader("skybox", m_settings.shader_dir.string()));

    for (const auto& filename : model_filenames)
    {
        std::filesystem::path model_path = m_settings.asset_dir / filename;
        loaded_models[filename] = m_resource_manager->loadModel(model_path.string());
    }

    for (const auto& name : shader_names)
    {
        m_resource_manager->loadShader(name, m_settings.shader_dir.string());
    }
}

void Sandbox::Update()
{
    Engine::Update();
}

void Sandbox::Render()
{
    Engine::Render();

    glm::mat4 view = m_camera->GetViewMatrix();
    glm::mat4 projection = glm::perspective(
        glm::radians(m_camera->getZoom()), 
        (float)m_settings.window_width / (float)m_settings.window_height, 
        0.1f, 100.0f
    );
    m_skybox->Draw(view, projection);

    if (m_imgui_active)
        Sandbox::ImguiRender();
}

void Sandbox::ImguiRender()
{
    m_imgui_manager->BeginRender();
    m_imgui_ecs_system->RenderECSMenu();
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