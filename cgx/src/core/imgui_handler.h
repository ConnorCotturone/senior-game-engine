// jacob curlin
// imgui_handler.h
// 01/17/2023

#ifndef IMGUIHANDLER_H
#define IMGUIHANDLER_H


#include "../ecs/ecs_manager.h"
#include"../components/transform_component.h"

#include <GLFW/glfw3.h>
#include <vector>

class ImguiHandler
{

public:
    ImguiHandler() {}
    ~ImguiHandler() {}

    void Initialize(GLFWwindow* window);
    void Shutdown();

    void BeginRender();
    void EndRender();
};

#endif // IMGUIHANDLER_H