// Copyright © 2024 Jacob Curlin

#pragma once

#include "core/common.h"
#include "ecs/i_system.h"
#include "ecs/event/i_event_listener.h"

namespace cgx::ecs
{
    class ECSManager;
    class Event;
}

namespace cgx::render
{

    class CameraSystem  
        : public cgx::ecs::System
        , public cgx::ecs::event::IEventListener

    {
    public:
        void Initialize(std::shared_ptr<cgx::ecs::ECSManager> ecs_manager);
        void Update(float dt);

    private:
        std::bitset<8> m_buttons;

        void InputListener(cgx::ecs::Event& event);
    };

}