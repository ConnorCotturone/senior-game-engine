// Copyright © 2024 Jacob Curlin

#include "sandbox.h"
#include <imgui.h>


Sandbox::Sandbox() {}

Sandbox::~Sandbox() {}

void Sandbox::Initialize()
{
    Engine::Initialize();
    LoadAssets();   // load models / textures etc. 


}

void Sandbox::Update()
{
    Engine::Update();
}

void Sandbox::Render()
{
    float r, g, b, a;
    m_framebuffer->getClearColor(r, g, b, a);
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer->getFBO());

    glViewport(0, 0, m_settings.render_width, m_settings.render_height);
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Engine::Render();
    SkyboxRender();

    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);   // unbind framebuffer
    glViewport(0, 0, m_settings.window_width, m_settings.window_height);

    // if (m_imgui_active)
    Sandbox::ImguiRender();
}

void Sandbox::ImguiRender()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_imgui_manager->Render();
}

void Sandbox::LoadAssets()
{
    model_filenames = {"soccerball/ball.obj", "light_cube/light_cube.obj", "sponza/sponza.obj", "backpack/backpack.obj"};
    // shader names (relative to shader directory - 'cgx/cgx/shaders/', extension-less filename of vert & frag shaders)
    shader_names = {"model", "lighting"};   // i.e. "model" -> fetches 'cgx/cgx/shaders/model.vs' and 'cgx/cgx/shaders/model.fs'

    std::vector<std::string> face_paths = {
        "/Users/curlin/dev/senior-game-engine/out/build/x64-Debug/data/assets/skybox_mountains/right.jpg",   // right
        "/Users/curlin/dev/senior-game-engine/out/build/x64-Debug/data/assets/skybox_mountains/left.jpg",    // left
        "/Users/curlin/dev/senior-game-engine/out/build/x64-Debug/data/assets/skybox_mountains/top.jpg",     // top
        "/Users/curlin/dev/senior-game-engine/out/build/x64-Debug/data/assets/skybox_mountains/bottom.jpg",  // bottom
        "/Users/curlin/dev/senior-game-engine/out/build/x64-Debug/data/assets/skybox_mountains/front.jpg",   // front
        "/Users/curlin/dev/senior-game-engine/out/build/x64-Debug/data/assets/skybox_mountains/back.jpg",    // back
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

void Sandbox::SkyboxRender()
{
    glm::mat4 view = m_camera->GetViewMatrix();
    glm::mat4 projection = glm::perspective(
        glm::radians(m_camera->getZoom()), 
        (float)m_settings.render_width / (float)m_settings.render_height, 
        0.1f, 100.0f
    );
    m_skybox->Draw(view, projection);
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