// Copyright © 2024 Jacob Curlin

#include "core/common.h"
#include "core/window_manager.h"

#include "ecs/common.h"
#include "ecs/event.h"

#include <iostream>

namespace cgx::core
{

    WindowManager::WindowManager() : m_window(nullptr) {}

    WindowManager::~WindowManager()
    {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    void WindowManager::Initialize(int width, int height, const char* label)
    {

        CGX_TRACE("Initializing window : '{}' ({}w x {}h)", label, width, height);
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        m_window = glfwCreateWindow(width, height, label, nullptr, nullptr);
        if (m_window == nullptr) {
            glfwTerminate();
            CGX_CRITICAL("Failed to create GLFW window.");
            throw std::runtime_error("[window] Failed to create GLFW window");
        }

        glfwSetWindowUserPointer(m_window, this);
        setupGLFWCallbacks();

        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        glfwMakeContextCurrent(m_window);
        glfwSetFramebufferSizeCallback(m_window, FramebufferSizeCallback);
    }

    void WindowManager::Update() {
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    void WindowManager::EnableCursor()
    {
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    void WindowManager::DisableCursor()
    {
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    void WindowManager::setKeyCallback(const KeyCallback& cb)
    {
        m_key_callback = cb;
    }

    void WindowManager::setCursorPosCallback(const MouseMoveCallback& cb)
    {
        m_mouse_move_callback = cb;
    }

    void WindowManager::setMouseButtonCallback(const MouseButtonCallback& cb)
    {
        m_mouse_button_callback = cb;
    }

    void WindowManager::setScrollCallback(const ScrollCallback& cb)
    {
        m_scroll_callback = cb;
    }

    void WindowManager::setupGLFWCallbacks()
    {
        glfwSetKeyCallback(m_window, WindowManager::glfwKeyCallback);
        glfwSetCursorPosCallback(m_window, WindowManager::glfwCursorPosCallback);
        glfwSetMouseButtonCallback(m_window, WindowManager::glfwMouseButtonCallback);
        glfwSetScrollCallback(m_window, WindowManager::glfwScrollCallback);
    }

    void WindowManager::glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        auto* instance = static_cast<WindowManager*>(glfwGetWindowUserPointer(window));
        if (instance && instance->m_key_callback)
        {
            instance->m_key_callback(TranslateKeyToInternal(key), TranslateKeyActionToInternal(action));
        }
    }

    void WindowManager::glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        auto* instance = static_cast<WindowManager*>(glfwGetWindowUserPointer(window));
        if (instance && instance->m_mouse_button_callback)
        {
            instance->m_mouse_button_callback(TranslateKeyToInternal(button), TranslateKeyActionToInternal(action));
        }
    }
    
    void WindowManager::glfwCursorPosCallback(GLFWwindow* window, double xpos, double ypos)
    {
        auto* instance = static_cast<WindowManager*>(glfwGetWindowUserPointer(window));
        if (instance && instance->m_mouse_move_callback)
        {
            instance->m_mouse_move_callback(xpos, ypos);
        }
    }

    void WindowManager::glfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
    {
        auto* instance = static_cast<WindowManager*>(glfwGetWindowUserPointer(window));
        if (instance && instance->m_scroll_callback)
        {
            instance->m_scroll_callback(xoffset, yoffset);
        }
    }

    void WindowManager::getMousePosition(double &x_pos, double &y_pos)
    {
        glfwGetCursorPos(m_window, &x_pos, &y_pos);
    }

    void WindowManager::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    bool WindowManager::isKeyPressed(cgx::input::Key key) const
    {
       return glfwGetKey(m_window, TranslateKeyToGLFW(key)) == GLFW_PRESS;
    }

    bool WindowManager::isKeyReleased(cgx::input::Key key) const
    {
        return glfwGetKey(m_window, TranslateKeyToGLFW(key)) == GLFW_RELEASE;
    }

    bool WindowManager::isMouseButtonPressed(cgx::input::Key button) const
    {
        return glfwGetKey(m_window, TranslateMouseButtonToGLFW(button)) == GLFW_PRESS;
    }

    bool WindowManager::isMouseButtonReleased(cgx::input::Key button) const
    {
        return glfwGetKey(m_window, TranslateMouseButtonToGLFW(button)) == GLFW_RELEASE;
    }

    cgx::input::KeyAction WindowManager::TranslateKeyActionToInternal(int glfw_action) 
    {
        switch(glfw_action)
        {
            case GLFW_PRESS:
                return cgx::input::KeyAction::press;
            case GLFW_RELEASE:
                return cgx::input::KeyAction::release;
            default:
                return cgx::input::KeyAction::undefined_key_action;
        };
    }

    cgx::input::Key WindowManager::TranslateMouseButtonToInternal(int glfw_mouse_button) 
    {
        switch(glfw_mouse_button)
        {
            case GLFW_MOUSE_BUTTON_1:
                return cgx::input::Key::mouse_button_1;
            case GLFW_MOUSE_BUTTON_2:
                return cgx::input::Key::mouse_button_2;
            case GLFW_MOUSE_BUTTON_3:
                return cgx::input::Key::mouse_button_3;
            case GLFW_MOUSE_BUTTON_4:
                return cgx::input::Key::mouse_button_4;
            case GLFW_MOUSE_BUTTON_5:
                return cgx::input::Key::mouse_button_5;
            case GLFW_MOUSE_BUTTON_6:
                return cgx::input::Key::mouse_button_6;
            case GLFW_MOUSE_BUTTON_7:
                return cgx::input::Key::mouse_button_7;
            case GLFW_MOUSE_BUTTON_8:
                return cgx::input::Key::mouse_button_8;
            default:
                return cgx::input::Key::undefined_key;
        };
    }

    cgx::input::Key WindowManager::TranslateKeyToInternal(int glfw_key)
    {
        switch (glfw_key)
        {
            // nums
            case GLFW_KEY_0:
                return cgx::input::Key::key_0;
            case GLFW_KEY_1:
                return cgx::input::Key::key_1;
            case GLFW_KEY_2:
                return cgx::input::Key::key_2;
            case GLFW_KEY_3:
                return cgx::input::Key::key_3;
            case GLFW_KEY_4:
                return cgx::input::Key::key_4;
            case GLFW_KEY_5:
                return cgx::input::Key::key_5;
            case GLFW_KEY_6:
                return cgx::input::Key::key_6;
            case GLFW_KEY_7:
                return cgx::input::Key::key_7;
            case GLFW_KEY_8:
                return cgx::input::Key::key_8;
            case GLFW_KEY_9:
                return cgx::input::Key::key_9;

            // letters
            case GLFW_KEY_A:
                return cgx::input::Key::key_a;
            case GLFW_KEY_B:
                return cgx::input::Key::key_b;
            case GLFW_KEY_C:
                return cgx::input::Key::key_c;
            case GLFW_KEY_D:
                return cgx::input::Key::key_d;
            case GLFW_KEY_E:
                return cgx::input::Key::key_e;
            case GLFW_KEY_F:
                return cgx::input::Key::key_f;
            case GLFW_KEY_G:
                return cgx::input::Key::key_g;
            case GLFW_KEY_H:
                return cgx::input::Key::key_h;
            case GLFW_KEY_I:
                return cgx::input::Key::key_i;
            case GLFW_KEY_J:
                return cgx::input::Key::key_j;
            case GLFW_KEY_K:
                return cgx::input::Key::key_k;
            case GLFW_KEY_L:
                return cgx::input::Key::key_l;
            case GLFW_KEY_M:
                return cgx::input::Key::key_m;
            case GLFW_KEY_N:
                return cgx::input::Key::key_n;
            case GLFW_KEY_O:
                return cgx::input::Key::key_o;
            case GLFW_KEY_P:
                return cgx::input::Key::key_p;
            case GLFW_KEY_Q:
                return cgx::input::Key::key_q;
            case GLFW_KEY_R:
                return cgx::input::Key::key_r;
            case GLFW_KEY_S:
                return cgx::input::Key::key_s;
            case GLFW_KEY_T:
                return cgx::input::Key::key_t;
            case GLFW_KEY_U:
                return cgx::input::Key::key_u;
            case GLFW_KEY_V:
                return cgx::input::Key::key_v;
            case GLFW_KEY_W:
                return cgx::input::Key::key_w;
            case GLFW_KEY_X:
                return cgx::input::Key::key_x;
            case GLFW_KEY_Y:
                return cgx::input::Key::key_y;
            case GLFW_KEY_Z:
                return cgx::input::Key::key_z;

            // esc / enter
            case GLFW_KEY_ESCAPE:
                return cgx::input::Key::key_escape;
            case GLFW_KEY_ENTER:
                return cgx::input::Key::key_enter;

            // directional
            case GLFW_KEY_RIGHT:
                return cgx::input::Key::key_right;
            case GLFW_KEY_LEFT:
                return cgx::input::Key::key_left;
            case GLFW_KEY_DOWN:
                return cgx::input::Key::key_down;
            case GLFW_KEY_UP:
                return cgx::input::Key::key_up;

            default:
                return cgx::input::Key::undefined_key;
        };
    }

    int WindowManager::TranslateKeyActionToGLFW(cgx::input::KeyAction action) 
    {
        switch(action)
        {
            case cgx::input::KeyAction::press:
                return GLFW_PRESS;
            case cgx::input::KeyAction::release:
                return GLFW_RELEASE;
            default:
                CGX_ERROR("Invalid GLFW Action")
                return GLFW_RELEASE;
        };
    }

    int WindowManager::TranslateMouseButtonToGLFW(cgx::input::Key key) 
    {
        switch(key)
        {
            case cgx::input::Key::mouse_button_1:
                return GLFW_MOUSE_BUTTON_1;
            case cgx::input::Key::mouse_button_2:
                return GLFW_MOUSE_BUTTON_2;
            case cgx::input::Key::mouse_button_3:
                return GLFW_MOUSE_BUTTON_3;
            case cgx::input::Key::mouse_button_4:
                return GLFW_MOUSE_BUTTON_4;
            case cgx::input::Key::mouse_button_5:
                return GLFW_MOUSE_BUTTON_5;
            case cgx::input::Key::mouse_button_6:
                return GLFW_MOUSE_BUTTON_6;
            case cgx::input::Key::mouse_button_7:
                return GLFW_MOUSE_BUTTON_7;
            case cgx::input::Key::mouse_button_8:
                return GLFW_MOUSE_BUTTON_8;
            default:
                CGX_ERROR("Invalid GLFW key");
                return GLFW_KEY_0; //placeholder
        };
    }

    int WindowManager::TranslateKeyToGLFW(cgx::input::Key key)
    {
        switch (key)
        {
            // nums
            case cgx::input::Key::key_0:
                return GLFW_KEY_0;
            case cgx::input::Key::key_1:
                return GLFW_KEY_1;
            case cgx::input::Key::key_2:
                return GLFW_KEY_2;
            case cgx::input::Key::key_3:
                return GLFW_KEY_3;
            case cgx::input::Key::key_4:
                return GLFW_KEY_4;
            case cgx::input::Key::key_5:
                return GLFW_KEY_5;
            case cgx::input::Key::key_6:
                return GLFW_KEY_6;
            case cgx::input::Key::key_7:
                return GLFW_KEY_7;
            case cgx::input::Key::key_8:
                return GLFW_KEY_8;
            case cgx::input::Key::key_9:
                return GLFW_KEY_9;

            // letters
            case cgx::input::Key::key_a:
                return GLFW_KEY_A;
            case cgx::input::Key::key_b:
                return GLFW_KEY_B;
            case cgx::input::Key::key_c:
                return GLFW_KEY_C;
            case cgx::input::Key::key_d:
                return GLFW_KEY_D;
            case cgx::input::Key::key_e:
                return GLFW_KEY_E;
            case cgx::input::Key::key_f:
                return GLFW_KEY_F;
            case cgx::input::Key::key_g:
                return GLFW_KEY_G;
            case cgx::input::Key::key_h:
                return GLFW_KEY_H;
            case cgx::input::Key::key_i:
                return GLFW_KEY_I;
            case cgx::input::Key::key_j:
                return GLFW_KEY_J;
            case cgx::input::Key::key_k:
                return GLFW_KEY_K;
            case cgx::input::Key::key_l:
                return GLFW_KEY_L;
            case cgx::input::Key::key_m:
                return GLFW_KEY_M;
            case cgx::input::Key::key_n:
                return GLFW_KEY_N;
            case cgx::input::Key::key_o:
                return GLFW_KEY_O;
            case cgx::input::Key::key_p:
                return GLFW_KEY_P;
            case cgx::input::Key::key_q:
                return GLFW_KEY_Q;
            case cgx::input::Key::key_r:
                return GLFW_KEY_R;
            case cgx::input::Key::key_s:
                return GLFW_KEY_S;
            case cgx::input::Key::key_t:
                return GLFW_KEY_T;
            case cgx::input::Key::key_u:
                return GLFW_KEY_U;
            case cgx::input::Key::key_v:
                return GLFW_KEY_V;
            case cgx::input::Key::key_w:
                return GLFW_KEY_W;
            case cgx::input::Key::key_x:
                return GLFW_KEY_X;
            case cgx::input::Key::key_y:
                return GLFW_KEY_Y;
            case cgx::input::Key::key_z:
                return GLFW_KEY_Z;

            // esc / enter
            case cgx::input::Key::key_escape:
                return GLFW_KEY_ESCAPE;
            case cgx::input::Key::key_enter:
                return GLFW_KEY_ENTER;

            // directional
            case cgx::input::Key::key_right:
                return GLFW_KEY_RIGHT;
            case cgx::input::Key::key_left:
                return GLFW_KEY_LEFT;
            case cgx::input::Key::key_down:
                return GLFW_KEY_DOWN;
            case cgx::input::Key::key_up:
                return GLFW_KEY_UP;

            default:
                CGX_ERROR("Invalid GLFW key")
                return GLFW_KEY_0; //placeholder
        };
    }



    void WindowManager::Shutdown() {}
    
    /*
    void WindowManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        auto* self = static_cast<WindowManager*>(glfwGetWindowUserPointer(window));
        if (self->m_input_manager)
        {
            switch (action) {
                case GLFW_PRESS:
                    self->m_input_manager->OnKeyPressed(key);
                    break;
                case GLFW_RELEASE:
                    self->m_input_manager->OnKeyReleased(key);
                default:
                    return;
            };
        }
    }

    
    
    bool Window::ShouldClose() const {
        return glfwWindowShouldClose(m_window);
    }

    */

} // namespace cgx::core
