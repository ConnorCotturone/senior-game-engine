// Copyright © 2024 Jacob Curlin

#include "core/input_handler.h"

namespace cgx::core {

    InputHandler::InputHandler(GLFWwindow *window)
            : m_window(window), m_mouse_x(0.0), m_mouse_y(0.0), m_first_mouse(true),
              m_ignore_next_mouse_update(false) {}

    bool InputHandler::IsKeyPressed(int key) const {
        return glfwGetKey(m_window, key) == GLFW_PRESS;
    }

    void InputHandler::getMouseOffset(double &x_offset, double &y_offset) {
        double x_pos, y_pos;
        glfwGetCursorPos(m_window, &x_pos, &y_pos);

        if (m_first_mouse) {
            m_mouse_x = x_pos;
            m_mouse_y = y_pos;
            m_first_mouse = false;
        }

        x_offset = x_pos - m_mouse_x;
        y_offset = m_mouse_y - y_pos;

        m_mouse_x = x_pos;
        m_mouse_y = y_pos;
    }

    void InputHandler::resetMouseOffset() {
        m_first_mouse = true;

        double x_pos, y_pos;
        glfwGetCursorPos(m_window, &x_pos, &y_pos);
        m_mouse_x = x_pos;
        m_mouse_y = y_pos;
    }

}