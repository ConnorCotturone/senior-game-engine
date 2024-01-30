// jacob curlin
// event_handler.cpp
// 01/25/2023


#include "event_handler.h"


std::vector<EventHandler::KeyCallback> EventHandler::m_keyCallbacks;
std::vector<EventHandler::MouseCallback> EventHandler::m_mouseCallbacks;

EventHandler::EventHandler(GLFWwindow* window) : m_window(window)
{
    m_keyCallbacks = std::vector<KeyCallback>();
    m_mouseCallbacks = std::vector<MouseCallback>();

    glfwSetKeyCallback(m_window, GLFWKeyCallback);
    glfwSetCursorPosCallback(m_window, GLFWMouseCallback);
}

void EventHandler::RegisterKeyCallback(const KeyCallback& callback)
{
    m_keyCallbacks.push_back(callback);
}

void EventHandler::RegisterMouseCallback(const MouseCallback& callback)
{
    m_mouseCallbacks.push_back(callback);
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
    for (const auto& callback : m_keyCallbacks)     // iterate through registered key callbacks functions 
    {
        callback(key, scancode, action, mods);      // 
    }
}

void EventHandler::GLFWMouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    for (const auto& callback : m_mouseCallbacks)
    {
        callback(xpos, ypos);
    }
}