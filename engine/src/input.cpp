// jacob curlin
// input.cpp
// 01/05/2023

#include "../include/input.h"

Input::Input(GLFWwindow* window) : m_window(window) {
    mouseX = 0.0;
    mouseY = 0.0;
    firstMouse = true;
}

Input::~Input() {}

bool Input::isKeyPressed(int key) const 
{
    return glfwGetKey(m_window, key) == GLFW_PRESS;
}

void Input::getMouseOffset(double& xoffset, double& yoffset) 
{
    double xpos, ypos;
    glfwGetCursorPos(m_window, &xpos, &ypos);

    if (firstMouse)
    {
        mouseX = xpos;
        mouseY = ypos;
        firstMouse = false;
    }

    xoffset = xpos - mouseX;
    yoffset = mouseY - ypos;

    mouseX = xpos;
    mouseY = ypos;
}

