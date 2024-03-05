// Copyright © 2024 Jacob Curlin

#include "gui/imgui_render_window.h"

namespace cgx::gui
{
    ImGuiRenderWindow::ImGuiRenderWindow(std::shared_ptr<cgx::render::Framebuffer> framebuffer) 
        : ImGuiWindow("Render")
        , m_framebuffer(framebuffer)
    {
        uint32_t tex_width, tex_height;
        framebuffer->getSize(tex_width, tex_height);  

        m_texture_size[0] = static_cast<float>(tex_width);
        m_texture_size[1] = static_cast<float>(tex_height);
        m_aspect_ratio = (m_texture_size[1] != 0) ?
            m_texture_size[0] / m_texture_size[1]
            : 1.0f;

        m_enforce_aspect_ratio = true;
        m_window_flags |= ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse; 
    }

    ImGuiRenderWindow::~ImGuiRenderWindow()
    {}

    void ImGuiRenderWindow::OnBegin()
    {
        ImGuiWindow::OnBegin();
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{2.0f, 2.0f});
    }

    void ImGuiRenderWindow::OnEnd()
    {
        ImGui::PopStyleVar(1);
    }

    void ImGuiRenderWindow::Render() 
    {
        ImVec2 window_size = ImGui::GetContentRegionAvail();

        float desired_aspect_ratio = m_texture_size[0] / m_texture_size[1];
        float window_aspect_ratio = window_size.x / window_size.y;

        ImVec2 render_size;
        if (window_aspect_ratio > desired_aspect_ratio)
        {
            render_size.y = window_size.y;
            render_size.x = render_size.y * desired_aspect_ratio;
        }
        else
        {
            render_size.x = window_size.x;
            render_size.y = render_size.x / desired_aspect_ratio;
        }

        render_size.x = std::round(render_size.x);
        render_size.y = std::round(render_size.y);

        ImVec2 cursor_pos = ImGui::GetCursorPos();        

        float offset_x = cursor_pos.x + (window_size.x - render_size.x) * 0.5f;
        float offset_y = cursor_pos.y + (window_size.y - render_size.y) * 0.5f;

        ImGui::SetCursorPos(ImVec2(offset_x, offset_y));

        ImGui::Image((void*)(intptr_t)m_framebuffer->getTextureID(), 
                     render_size,
                     ImVec2(0, 1), ImVec2(1, 0));
    }
}


