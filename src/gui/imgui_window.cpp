// Copyright © 2024 Jacob Curlin

#include "gui/imgui_window.h"


namespace cgx::gui
{
    void ImGuiWindow::RenderFrame()
    {
        if (!m_active) { return; }

        // ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse; 

        bool is_open = true;
        if (ImGui::Begin(m_title.c_str(), &is_open, window_flags))
        {
            Render();
        }
        ImGui::End();

        if (!is_open) { Hide(); }
    }
}
