// Copyright © 2024 Jacob Curlin

#include "gui/imgui_render_settings_window.h"


namespace cgx::gui
{
    ImGuiRenderSettingsWindow::ImGuiRenderSettingsWindow(
        std::shared_ptr<RenderSettings> settings)
        : ImGuiWindow("Render Settings")
        , m_render_settings(std::move(settings))
    {}


    void ImGuiRenderSettingsWindow::Render()
    {
        ImGui::Checkbox("MSAA", &(m_render_settings->msaa));
        ImGui::Checkbox("Skybox", &(m_render_settings->skybox));
    }

}