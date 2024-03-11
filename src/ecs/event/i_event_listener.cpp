// Copyright © 2024 Jacob Curlin

#include "ecs/event/i_event_listener.h"

namespace cgx::ecs::event
{

    IEventListener::IEventListener(std::shared_ptr<ECSProvider> ecs_provider)
        : m_ecs_provider(std::move(ecs_provider)) 
    {}

    IEventListener::~IEventListener() {}

    void IEventListener::UnregisterAllEventCallbacks()
    {
        for (auto event_callback : m_registered_callbacks)
        {
            m_ecs_provider->UnsubscribeEvent(event_callback);
        }

        m_registered_callbacks.clear();
    }

} // namespace cgx::ecs::event