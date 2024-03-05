// Copyright © 2024 Jacob Curlin

#include "gui/imgui_window.h"


namespace cgx::gui
{
    void AspectRatioConstraint(ImGuiSizeCallbackData* data)
    {
        float aspect_ratio = *(float*)data->UserData;
        data->DesiredSize.y = data->DesiredSize.x / aspect_ratio;
    }

    ImGuiWindow::ImGuiWindow(const std::string& title)
        : m_title(title) 
    {
        m_window_flags = ImGuiWindowFlags_NoCollapse;
    }

    void ImGuiWindow::Begin()
    {
        OnBegin();
        bool keep_visible{true};
        
        if (m_enforce_aspect_ratio)
        {
            ImGui::SetNextWindowSizeConstraints(
                ImVec2(m_min_size[0], m_min_size[1]),
                ImVec2(m_max_size[0], m_max_size[1]),
                AspectRatioConstraint, &m_aspect_ratio
            );
        }
        else
        {
            ImGui::SetNextWindowSizeConstraints(
                ImVec2(m_min_size[0], m_min_size[1]),
                ImVec2(m_max_size[0], m_max_size[1])
            );
        }

        const bool collapsed = (ImGui::Begin(m_title.c_str(), &keep_visible, m_window_flags));

        if (!keep_visible) { Hide(); }
    }

    void ImGuiWindow::End()
    {
        OnEnd();
        m_is_hovered = ImGui::IsWindowHovered();
        ImGui::End();
    }

    void ImGuiWindow::OnBegin() {}  // (child-defined)

    void ImGuiWindow::OnEnd() {}    // (child-defined)

    void ImGuiWindow::Show()
    {
        m_is_visible = true;
    }

    void ImGuiWindow::Hide()
    {
        m_is_visible = false;
    }

    bool ImGuiWindow::isVisible()
    {
        return m_is_visible;
    }

    const std::string& ImGuiWindow::getTitle()
    {
        return m_title;
    }

    void ImGuiWindow::setMinSize(float width, float height)
    {
        m_min_size[0] = width;
        m_max_size[1] = height;
    }
    
    void ImGuiWindow::setMaxSize(float width, float height)
    {
        m_max_size[0] = width;
        m_max_size[1] = height;
    }

}
