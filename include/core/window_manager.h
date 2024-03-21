// Copyright © 2024 Jacob Curlin

#pragma once

#include "core/common.h"
#include "input/input_types.h"
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

    using KeyCallback           = std::function<void(cgx::input::Key, cgx::input::KeyAction)>;
    using MouseButtonCallback   = std::function<void(cgx::input::Key, cgx::input::KeyAction)>;
    using MouseMoveCallback     = std::function<void(double x_pos, double y_pos)>;
    using ScrollCallback        = std::function<void(double x_offset, double y_offset)>;

    class WindowManager {
    public:
        WindowManager();
        ~WindowManager();

        void Initialize(int width, int height, const char *label); 
        void Update();
        void Shutdown();
        
        [[nodiscard]] GLFWwindow *getGLFWWindow() const { return m_window; }

        void EnableCursor();
        void DisableCursor();

        void getMousePosition(double &x_pos, double &y_pos);

        bool isKeyPressed(cgx::input::Key key) const;
        bool isKeyReleased(cgx::input::Key key) const;

        bool isMouseButtonPressed(cgx::input::Key button) const;
        bool isMouseButtonReleased(cgx::input::Key button) const;

        void setKeyCallback(const KeyCallback& cb);          
        void setCursorPosCallback(const MouseMoveCallback& cb);
        void setMouseButtonCallback(const MouseButtonCallback& cb);
        void setScrollCallback(const ScrollCallback& cb);

        
        
        // bool ShouldClose() const;

    private:
        GLFWwindow *m_window;

        KeyCallback         m_key_callback;
        MouseMoveCallback   m_mouse_move_callback;
        MouseButtonCallback m_mouse_button_callback;
        ScrollCallback      m_scroll_callback;

        static void FramebufferSizeCallback(GLFWwindow *window, int width, int height);

        static void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void glfwCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
        static void glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        static void glfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
        void setupGLFWCallbacks();

        static cgx::input::KeyAction    TranslateKeyActionToInternal(int glfw_action);
        static cgx::input::Key          TranslateKeyToInternal(int glfw_key);
        static cgx::input::Key          TranslateMouseButtonToInternal(int glfw_mouse_button);
        static int                      TranslateKeyActionToGLFW(cgx::input::KeyAction action);
        static int                      TranslateKeyToGLFW(cgx::input::Key key);
        static int                      TranslateMouseButtonToGLFW(cgx::input::Key key);

    }; // class WindowManager

} // namespace cgx::core