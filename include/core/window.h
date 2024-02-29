// Copyright © 2024 Jacob Curlin

#pragma once

#include <GLFW/glfw3.h>

namespace cgx::core {

    class Window {
    public:
        Window();

        ~Window();

        void Update();

        // bool ShouldClose() const;
        void SwapBuffers();

        void Initialize(int width, int height, const char *label);

        void Shutdown();

        void setKeyCallback(GLFWkeyfun callback);

        void setCursorPosCallback(GLFWcursorposfun callback);

        [[nodiscard]] GLFWwindow *GetGLFWWindow() const { return m_window; }

    private:
        GLFWwindow *m_window;

        static void FramebufferSizeCallback(GLFWwindow *window, int width, int height);
    };

}