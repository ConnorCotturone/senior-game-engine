// jacob curlin
// sandbox.cpp
// 02/22/2024

#include "../include/sandbox.h"


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
        m_resource_manager->loadShader(name, m_settings.shader_dir.string());
        //std::filesystem::path vert_path = (m_settings.shader_dir / (name + ".vs")).string();
        //std::filesystem::path frag_path = (m_settings.shader_dir / (name + ".fs")).string();

        // loaded_shaders[name] = std::make_shared<cgx::graphics::Shader>(name, m_settings.shader_dir.string(), vert_path.string(), frag_path.string());
    }

}

void Sandbox::Update()
{
    Engine::Update();
}

void Sandbox::Render()
{
    Engine::Render();


    if (m_imgui_active)
        Sandbox::ImguiRender();
}

void Sandbox::ImguiRender()
{
    m_imgui_manager->BeginRender();

    m_imgui_ecs_system->RenderECSMenu();
    // m_imgui_ecs_system->DisplayEntityDropdown();
    // m_imgui_ecs_system->DisplayComponentEditors();


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