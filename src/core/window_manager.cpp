// Copyright © 2024 Jacob Curlin

#include "core/common.h"
#include "core/window_manager.h"

#include "ecs/common.h"
#include "ecs/event.h"

#include <iostream>

namespace cgx::core
{

    WindowManager::WindowManager() : m_window(nullptr) {}

    WindowManager::~WindowManager()
    {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    void WindowManager::Initialize(int width, int height, const char* label)
    {

        CGX_TRACE("Initializing window : '{}' ({}w x {}h)", label, width, height);
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        m_window = glfwCreateWindow(width, height, label, nullptr, nullptr);
        if (m_window == nullptr) {
            glfwTerminate();
            CGX_CRITICAL("Failed to create GLFW window.");
            throw std::runtime_error("[window] Failed to create GLFW window");
        }

        glfwSetWindowUserPointer(m_window, this);
        setupGLFWCallbacks();

        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        glfwMakeContextCurrent(m_window);
        glfwSetFramebufferSizeCallback(m_window, FramebufferSizeCallback);
    }

    void WindowManager::Update() {
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    void WindowManager::setKeyCallback(const KeyCallback& cb)
    {
        m_key_callback = cb;
    }

    void WindowManager::setCursorPosCallback(const MouseMoveCallback& cb)
    {
        m_mouse_move_callback = cb;
    }

    void WindowManager::setMouseButtonCallback(const MouseButtonCallback& cb)
    {
        m_mouse_button_callback = cb;
    }

    void WindowManager::setupGLFWCallbacks()
    {
        glfwSetKeyCallback(m_window, WindowManager::glfwKeyCallback);
        glfwSetCursorPosCallback(m_window, WindowManager::glfwCursorPosCallback);
        glfwSetMouseButtonCallback(m_window, WindowManager::glfwMouseButtonCallback);
    }

    void WindowManager::glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        auto* instance = static_cast<WindowManager*>(glfwGetWindowUserPointer(window));
        if (instance && instance->m_key_callback)
        {
            instance->m_key_callback(key, action);
        }
    }

    void WindowManager::glfwCursorPosCallback(GLFWwindow* window, double xpos, double ypos)
    {
        auto* instance = static_cast<WindowManager*>(glfwGetWindowUserPointer(window));
        if (instance && instance->m_mouse_move_callback)
        {
            instance->m_mouse_move_callback(xpos, ypos);
        }
    }

    void WindowManager::glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        auto* instance = static_cast<WindowManager*>(glfwGetWindowUserPointer(window));
        if (instance && instance->m_mouse_button_callback)
        {
            instance->m_mouse_button_callback(button, action);
        }
    }

    void WindowManager::getMousePosition(double &x_pos, double &y_pos)
    {
        glfwGetCursorPos(m_window, &x_pos, &y_pos);
    }

    void WindowManager::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    bool WindowManager::isKeyPressed(int key) const
    {
       return glfwGetKey(m_window, key) == GLFW_PRESS;
    }

    bool WindowManager::isKeyReleased(int key) const
    {
        return glfwGetKey(m_window, key) == GLFW_RELEASE;
    }

    bool WindowManager::isMouseButtonPressed(int key) const
    {
        return glfwGetKey(m_window, key) == GLFW_PRESS;
    }

    bool WindowManager::isMouseButtonReleased(int key) const
    {
        return glfwGetKey(m_window, key) == GLFW_RELEASE;
    }

    void WindowManager::Shutdown() {}
    
    /*
    void WindowManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        auto* self = static_cast<WindowManager*>(glfwGetWindowUserPointer(window));
        if (self->m_input_manager)
        {
            switch (action) {
                case GLFW_PRESS:
                    self->m_input_manager->OnKeyPressed(key);
                    break;
                case GLFW_RELEASE:
                    self->m_input_manager->OnKeyReleased(key);
                default:
                    return;
            };
        }
    }

    
    
    bool Window::ShouldClose() const {
        return glfwWindowShouldClose(m_window);
    }

    */

} // namespace cgx::core
