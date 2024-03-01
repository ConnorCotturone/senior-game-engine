// Copyright © 2024 Jacob Curlin

#include "gui/imgui_viewport_window.h"

namespace cgx::gui
{
    ImGuiViewportWindow::ImGuiViewportWindow() 
        : IImguiWindow("Viewport")
        , m_texture_id(0)
    {}

    ImGuiViewportWindow::~ImGuiViewportWindow()
    {}

    void ImGuiViewportWindow::DrawContents() 
    {
        ImGui::Text("Drawing the contents of the Viewport Window");
    }
}