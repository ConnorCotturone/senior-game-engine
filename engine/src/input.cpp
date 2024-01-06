// jacob curlin
// input.cpp
// 01/05/2023

#include "../include/input.h"

Input::Input(GLFWwindow* window) : m_window(window) {}

Input::~Input() {}

bool Input::isKeyPressed(int key) const 
{
    return glfwGetKey(m_window, key) == GLFW_PRESS;
}

void Input::getMousePosition(double& xpos, double& ypos) const
{
    glfwGetCursorPos(m_window, &xpos, &ypos);
}


