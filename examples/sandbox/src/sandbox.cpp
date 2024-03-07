// Copyright © 2024 Jacob Curlin

#include "sandbox.h"
#include <imgui.h>


Sandbox::Sandbox() {}

Sandbox::~Sandbox() {}

void Sandbox::Initialize()
{
    Engine::Initialize();
    LoadAssets();   // load models / textures etc. 

    // setup MSAA frame buffer object
    glGenFramebuffers(1, &m_msaa_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_msaa_framebuffer);

    unsigned int msaa_tex_color_buf;
    glGenTextures(1, &msaa_tex_color_buf);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, msaa_tex_color_buf);
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, m_settings.render_width, m_settings.render_height, GL_TRUE);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, msaa_tex_color_buf, 0);

    unsigned int msaa_rbo;
    glGenRenderbuffers(1, &msaa_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, msaa_rbo);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, m_settings.render_width, m_settings.render_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, msaa_rbo);

    CGX_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "MSAA Framebuffer not complete.");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Sandbox::Update()
{
    Engine::Update();
}

void Sandbox::Render()
{
    float r, g, b, a;
    m_framebuffer->getClearColor(r, g, b, a);
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (m_render_settings->msaa)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_msaa_framebuffer);
    }
    else // msaa disabled
    { 
        glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer->getFBO()); 
    }

    // glEnable(GL_DEPTH_TEST);


    glViewport(0, 0, m_settings.render_width, m_settings.render_height);
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Engine::Render();
    if (m_render_settings->skybox) { SkyboxRender(); }
    
    if (m_render_settings->msaa)
    {
        glBindFramebuffer(GL_READ_FRAMEBUFFER, m_msaa_framebuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_framebuffer->getFBO());
        glBlitFramebuffer(0, 0, m_settings.render_width, m_settings.render_height,
                        0, 0, m_settings.render_width, m_settings.render_height, 
                        GL_COLOR_BUFFER_BIT, GL_NEAREST);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

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