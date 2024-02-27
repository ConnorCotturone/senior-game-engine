// Copyright © 2024 Jacob Curlin

#include "input_handler.h"

InputHandler::InputHandler(GLFWwindow* window) : m_window(window) {
    m_mouseX = 0.0;
    m_mouseY = 0.0;
    m_firstMouse = true;
    ignoreNextMouseUpdate = false;
}

InputHandler::~InputHandler() {}

bool InputHandler::IsKeyPressed(int key) const 
{
    return glfwGetKey(m_window, key) == GLFW_PRESS;
}

void InputHandler::getMouseOffset(double& xoffset, double& yoffset) 
{
    double xpos, ypos;
    glfwGetCursorPos(m_window, &xpos, &ypos);

    if (m_firstMouse)
    {
        m_mouseX = xpos;
        m_mouseY = ypos;
        m_firstMouse = false;
    }

    xoffset = xpos - m_mouseX;
    yoffset = m_mouseY - ypos;

    m_mouseX = xpos;
    m_mouseY = ypos;
}

void InputHandler::resetMouseOffset()
{
    m_firstMouse = true;

    double xpos, ypos;
    glfwGetCursorPos(m_window, &xpos, &ypos);
    m_mouseX = xpos;
    m_mouseY = ypos;
}