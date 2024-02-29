// Copyright © 2024 Jacob Curlin

#pragma once

#include <GLFW/glfw3.h>

namespace cgx::gui
{
    class ImguiManager
    {
    public:
        void Initialize(GLFWwindow* window);
        void Shutdown();

        void BeginRender();
        void EndRender();
    };
}
