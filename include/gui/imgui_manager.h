// Copyright © 2024 Jacob Curlin

#pragma once

#include "core/common.h"
#include "gui/imgui_window.h"

#include <imgui/imgui.h>

#include <GLFW/glfw3.h>

namespace cgx::gui
{
    class ImGuiManager
    {
    public:
        ImGuiManager() = default;
        ~ImGuiManager() = default;

        void Initialize(GLFWwindow* window);
        void Shutdown();

        void RegisterImGuiWindow(ImGuiWindow* window);
        void UnregisterImGuiWindow(ImGuiWindow* window);

        void Render();
        void BeginRender();
        void EndRender();

        void RenderCoreMenu();


    private:
        std::vector<ImGuiWindow*> m_imgui_windows;
    };
}
