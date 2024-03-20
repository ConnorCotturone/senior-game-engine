// Copyright © 2024 Jacob Curlin

#pragma once

#include "core/common.h"
#include <GLFW/glfw3.h>

namespace cgx::core {

    /*
    struct WindowConfig
    {
        uint32_t gl_minor; 
        uint32_t gl_major;
        uint32_t width;
        uint32_t height;
        std::string title;
    }
    */

    using KeyCallback = std::function<void(int key, int state)>;
    using MouseMoveCallback = std::function<void(double x_pos, double y_pos)>;
    using MouseButtonCallback = std::function<void(int button, int state)>;

    class WindowManager {
    public:
        WindowManager();
        ~WindowManager();

        void Initialize(int width, int height, const char *label); 
        void Update();
        void Shutdown();
        
        [[nodiscard]] GLFWwindow *getGLFWWindow() const { return m_window; }

        void getMousePosition(double &x_pos, double &y_pos);

        bool isKeyPressed(int key) const;
        bool isKeyReleased(int key) const;

        bool isMouseButtonPressed(int button) const;
        bool isMouseButtonReleased(int button) const;

        void setKeyCallback(const KeyCallback& cb);          
        void setCursorPosCallback(const MouseMoveCallback& cb);
        void setMouseButtonCallback(const MouseButtonCallback& cb);
        
        // bool ShouldClose() const;

    private:

        GLFWwindow *m_window;

        KeyCallback m_key_callback;
        MouseMoveCallback m_mouse_move_callback;
        MouseButtonCallback m_mouse_button_callback;

        void setupGLFWCallbacks();
        static void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void glfwCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
        static void glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        static void FramebufferSizeCallback(GLFWwindow *window, int width, int height);


    }; // class WindowManager

} // namespace cgx::core