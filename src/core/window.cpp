// Copyright © 2024 Jacob Curlin

#include "core/common.h"
#include "core/window.h"
#include <iostream>

namespace cgx::core
{

    Window::Window() : m_window(nullptr) {}

    Window::~Window()
    {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    void Window::Initialize(int width, int height, const char* title)
    {
        CGX_TRACE("Initializing window : '{}' ({}w x {}h)", title, width, height);
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (m_window == nullptr) {
            glfwTerminate();
            CGX_CRITICAL("Failed to create GLFW window.");
            throw std::runtime_error("[window] Failed to create GLFW window");
        }

        glfwMakeContextCurrent(m_window);
        glfwSetFramebufferSizeCallback(m_window, FramebufferSizeCallback);
    }

    void Window::Update() {
        glfwPollEvents();
    }

    /*
    bool Window::ShouldClose() const {
        return glfwWindowShouldClose(m_window);
    }
    */

    void Window::SwapBuffers() {
        glfwSwapBuffers(m_window);
    }

    void Window::setKeyCallback(GLFWkeyfun callback)
    {
        glfwSetKeyCallback(m_window, callback);
    }

    void Window::setCursorPosCallback(GLFWcursorposfun callback)
    {
        glfwSetCursorPosCallback(m_window, callback);
    }

    void Window::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void Window::Shutdown() {}


}
