// Copyright © 2024 Jacob Curlin

#pragma once

#include "core/common.h"
#include "core/window_manager.h"
#include "ecs/ecs_manager.h"

namespace cgx::core
{
    using ActionCallback = std::function<void()>;
    using InputEventAction = cgx::ecs::EventId;

    struct Action
    {
        std::optional<ActionCallback> callback;
        std::optional<InputEventAction> event;

        Action(ActionCallback cb) : callback(cb) {}
        Action(InputEventAction ev) : event(ev) {}
    };

    class InputAction
    {
        public:
            std::vector<Action> actions;

            void addCallback(ActionCallback cb)
            {
                actions.emplace_back(cb);
            }

            void addEvent(InputEventAction ev)
            {
                actions.emplace_back(ev);
            }

            void execute(cgx::ecs::ECSManager* ecs_manager) 
            {
                for (auto& action : actions)
                {
                    if (action.callback)    { (*action.callback)(); }
                    if (action.event)       { ecs_manager->SendEvent(*action.event); } 
                }
            }
    };

    enum class InputType
    {
        KEYBOARD_KEY,
        MOUSE_BUTTON,
    };

    enum class InputState
    {
        PRESSED,
        RELEASED
    };

    struct InputEventKey
    {
        InputType type;
        InputState state;
        int code;

        bool operator ==(const InputEventKey& other) const 
        {
            return type == other.type &&
                  state == other.state &&
                   code == other.code;
        }
    };

    struct InputEventKeyHash
    {
        std::size_t operator()(const InputEventKey& key) const
        {
            std::size_t h1 = std::hash<int>()(static_cast<int>(key.type));
            std::size_t h2 = std::hash<int>()(static_cast<int>(key.state));
            std::size_t h3 = std::hash<int>()(key.code);
            return h1 ^ (h2 << 1) ^ (h3 << 2);
        }
    };

    class InputManager
    {
    public:
        InputManager(
            std::shared_ptr<cgx::ecs::ECSManager> ecs_manager,
            std::shared_ptr<WindowManager> window_manager
        );
        ~InputManager();

        // need a way to bind any input type (keyboard, mouse, mouse button input), (pressed, released)
        // to an event, AND/OR a callback 
        void BindInputAction(const InputEventKey& key, const InputAction& action);

        // for glfw to call
        void onKeyboardInput(int key, InputState state);
        void onMouseButtonInput(int button, InputState state);

        // keyboard polling
        bool isKeyPressed(int key) const;
        bool isKeyReleased(int key) const;
        
        // mouse button polling
        bool isMouseButtonPressed(int button) const;
        bool isMouseButtonReleased(int button) const;

        // mouse movement polling
        void getMousePosition(double &x_pos, double &y_pos);
        void getMouseOffset(double &x_offset, double &y_offset);

    private:
        std::shared_ptr<cgx::ecs::ECSManager> m_ecs_manager;
        std::shared_ptr<WindowManager> m_window_manager;

        std::unordered_map<InputEventKey, InputAction, InputEventKeyHash> m_input_bindings;

        double  m_mouse_x       = 0.0;
        double  m_mouse_y       = 0.0;
        bool    m_first_mouse   = true;

    }; // class InputManager

} // namespace cgx::core