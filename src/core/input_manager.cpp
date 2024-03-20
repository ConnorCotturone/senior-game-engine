// Copyright © 2024 Jacob Curlin

#include "core/input_manager.h"
#include "ecs/events/engine_events.h"

namespace cgx::core
{
    InputManager::InputManager(
        std::shared_ptr<cgx::ecs::ECSManager> ecs_manager,
        std::shared_ptr<WindowManager> window_manager
    )
        : m_ecs_manager(ecs_manager)
        , m_window_manager(window_manager) 
    {
        m_window_manager->setKeyCallback([this](int key, int glfw_state)
        {
            InputState state = (glfw_state == GLFW_PRESS) ? InputState::PRESSED :
                               (glfw_state == GLFW_RELEASE) ? InputState::RELEASED :
                               InputState::RELEASED; // todo : fix this placeholder, better error checking
            this->onKeyboardInput(key, state);
        });

        m_window_manager->setMouseButtonCallback([this](int button, int glfw_state)
        {
            InputState state = (glfw_state == GLFW_PRESS) ? InputState::PRESSED :
                               (glfw_state == GLFW_RELEASE) ? InputState::RELEASED :
                               InputState::RELEASED; // todo : fix this placeholder, better error checking
            this->onMouseButtonInput(button, state);
        });
    }

    InputManager::~InputManager() {}


    void InputManager::BindInputAction(const InputEventKey& key, const InputAction& action)
    {
        m_input_bindings[key] = action;
    }

    void InputManager::onKeyboardInput(int key, InputState state) 
    {
        InputEventKey event_key{InputType::KEYBOARD_KEY, state, key};
        auto it = m_input_bindings.find(event_key);
        if (it != m_input_bindings.end())
        {
            it->second.execute(m_ecs_manager.get());
        }
    }

    void InputManager::onMouseButtonInput(int button, InputState state)
    {
        InputEventKey event_key{InputType::MOUSE_BUTTON, state, button};
        auto it = m_input_bindings.find(event_key);
        if (it != m_input_bindings.end())
        {
            it->second.execute(m_ecs_manager.get());
        }
    }

    bool InputManager::isKeyPressed(int key) const
    {
        return m_window_manager->isKeyPressed(key);
    }

    bool InputManager::isKeyReleased(int key) const
    {
        return m_window_manager->isKeyReleased(key);
    }

    bool InputManager::isMouseButtonPressed(int button) const
    {
        return m_window_manager->isMouseButtonPressed(button);
    }

    bool InputManager::isMouseButtonReleased(int button) const
    {
        return m_window_manager->isMouseButtonReleased(button);
    }

    void InputManager::getMousePosition(double &x_pos, double &y_pos)
    {
        m_window_manager->getMousePosition(x_pos, y_pos);
    }

    void InputManager::getMouseOffset(double &x_offset, double &y_offset)
    {
        double x_pos, y_pos;
        getMousePosition(x_pos, y_pos);

        if (m_first_mouse)
        {
            m_mouse_x = x_pos;
            m_mouse_y = y_pos;
            m_first_mouse = false;
        }

        x_offset = x_pos - m_mouse_x;
        y_offset = m_mouse_y - y_pos;

        m_mouse_x = x_pos;
        m_mouse_y = y_pos;
    }

} // namespace cgx::core