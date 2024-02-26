// Copyright © 2024 Jacob Curlin

#ifndef IMGUISYSTEM_H
#define IMGUISYSTEM_H

#include "../ecs/ecs_manager.h"
#include"../components/transform_component.h"
//#include "imgui_ecs_system.h"

#include <GLFW/glfw3.h>
#include <vector>

namespace cgx::gui
{
    class ImguiManager
    {
    public:
        ImguiManager() {}
        ~ImguiManager() {}

        void Initialize(GLFWwindow* window);
        void Shutdown();

        void BeginRender();
        void EndRender();

    };
}

#endif // IMGUISYSTEM_H