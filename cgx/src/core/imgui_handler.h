// jacob curlin
// imgui_handler.h
// 01/17/2023

#ifndef IMGUIHANDLER_H
#define IMGUIHANDLER_H

#include <GLFW/glfw3.h>

class ImguiHandler
{

public:
    ImguiHandler() {}
    ~ImguiHandler() {}

    void Initialize(GLFWwindow* window);
    void Shutdown();

    void Render();
};

#endif // IMGUIHANDLER_H