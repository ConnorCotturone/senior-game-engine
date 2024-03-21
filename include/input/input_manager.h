// Copyright © 2024 Jacob Curlin

#pragma once

#include "input/input_types.h"

#include "core/common.h"
#include "core/window_manager.h"
#include "ecs/ecs_manager.h"

namespace cgx::input
{
    class InputManager
    {
    public:
        InputManager(
            std::shared_ptr<cgx::ecs::ECSManager> ecs_manager,
            std::shared_ptr<cgx::core::WindowManager> window_manager
        );
        ~InputManager();

        // bind an event to a specific input
        void BindKeyInputEvent(Key key, KeyAction action, cgx::ecs::Event event);

        // for glfw to call
        void onKeyboardInput(Key key, KeyAction action);
        void onMouseButtonInput(Key key, KeyAction action);

        // keyboard polling
        bool isKeyPressed(Key key) const;
        bool isKeyReleased(Key key) const;
        
        // mouse button polling
        bool isMouseButtonPressed(Key key) const;
        bool isMouseButtonReleased(Key key) const;

        // mouse movement polling
        void getMousePosition(double &x_pos, double &y_pos);
        void getMouseOffset(double &x_offset, double &y_offset);

    private:
        std::shared_ptr<cgx::ecs::ECSManager> m_ecs_manager;
        std::shared_ptr<cgx::core::WindowManager> m_window_manager;

        std::unordered_map<KeyInput, cgx::ecs::Event, KeyInputHash> m_event_bindings;

        double  m_mouse_x       = 0.0;
        double  m_mouse_y       = 0.0;
        bool    m_first_mouse   = true;

    }; // class InputManager

} // namespace cgx::input

