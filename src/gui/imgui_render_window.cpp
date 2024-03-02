// Copyright © 2024 Jacob Curlin

#include "gui/imgui_render_window.h"

namespace cgx::gui
{
    ImGuiRenderWindow::ImGuiRenderWindow(std::shared_ptr<cgx::render::Framebuffer> framebuffer) 
        : ImGuiWindow("Render", 200, 150, 1920, 1200)
        , m_framebuffer(framebuffer)
    {
        
    }

    ImGuiRenderWindow::~ImGuiRenderWindow()
    {}

    void ImGuiRenderWindow::Render() 
    {
        uint32_t tex_width, tex_height;
        m_framebuffer->getSize(tex_width, tex_height);

        ImVec2 avail = ImGui::GetContentRegionAvail();
        float aspect_ratio = static_cast<float>(tex_width) / static_cast<float>(tex_height);

        ImVec2 image_size = avail;
        if (avail.x / avail.y > aspect_ratio)
        {
            image_size.x = avail.y * aspect_ratio;
        }
        else
        {
            image_size.y = avail.x / aspect_ratio;
        }


        ImGui::Image((void*)(intptr_t)m_framebuffer->getTextureID(), 
                     image_size,
                     ImVec2(0, 1), ImVec2(1, 0));
    }
}