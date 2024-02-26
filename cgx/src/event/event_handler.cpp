// Copyright © 2024 Jacob Curlin

#include "event_handler.h"

namespace cgx::event
{

    std::vector<EventHandler::KeyCallback> EventHandler::m_key_callbacks;
    std::vector<EventHandler::MouseCallback> EventHandler::m_mouse_callbacks;

    EventHandler::EventHandler(GLFWwindow* window) : m_window(window)
    {
        m_key_callbacks = std::vector<KeyCallback>();
        m_mouse_callbacks = std::vector<MouseCallback>();

        glfwSetKeyCallback(m_window, GLFWKeyCallback);
        glfwSetCursorPosCallback(m_window, GLFWMouseCallback);
    }

    void EventHandler::RegisterKeyCallback(const KeyCallback& callback)
    {
        m_key_callbacks.push_back(callback);
    }

    void EventHandler::RegisterMouseCallback(const MouseCallback& callback)
    {
        m_mouse_callbacks.push_back(callback);
    }

    void EventHandler::Update() 
    {
        glfwPollEvents();
    }

    /* 
        since this function is registered as glfwKeyCallback, when a keyboard event occurs, GLFW will call this function, 
        passing the arguments window, key, scancode, action, and mods. 
    */
    void EventHandler::GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        for (const auto& callback : m_key_callbacks)     // iterate through registered key callbacks functions 
        {
            callback(key, scancode, action, mods);      // 
        }
    }

    void EventHandler::GLFWMouseCallback(GLFWwindow* window, double xpos, double ypos)
    {
        for (const auto& callback : m_mouse_callbacks)
        {
            callback(xpos, ypos);
        }
    }

}