// Copyright © 2024 Jacob Curlin

#pragma once

#include <GLFW/glfw3.h>

namespace cgx::core {

    class InputHandler {

    public:
        explicit InputHandler(GLFWwindow *window);

        ~InputHandler() = default;

        bool IsKeyPressed(int key) const;

        void getMouseOffset(double &x_offset, double &y_offset);

        void resetMouseOffset();

        bool m_ignore_next_mouse_update = false;

    private:
        GLFWwindow *m_window;

        double m_mouse_x = 0.0;
        double m_mouse_y = 0.0;

        bool m_first_mouse = true;
    };

}