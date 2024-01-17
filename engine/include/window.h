// jacob curlin
// window.h
// 01/05/2023

#ifndef WINDOW_H
#define WINDOW_H

#define GL_SILENCE_DEPRECATION

#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include "../include/logging.h"
#include "../include/imguiwindow.h"

class Window {
public:
    Window(int width, int height, const char* label);
    ~Window();

    void Update();
    bool ShouldClose() const;
    void SwapBuffers();

    void setKeyCallback(GLFWkeyfun callback);
    void setCursorPosCallback(GLFWcursorposfun callback);

    GLFWwindow* GetGLFWWindow() const { return m_window; }

private:
    GLFWwindow* m_window;
    ImguiWindow m_imguiWindow;

    void Initialize(int width, int height, const char* label);
    void Shutdown();


    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

};


#endif // WINDOW_H

