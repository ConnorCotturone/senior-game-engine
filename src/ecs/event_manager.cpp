// Copyright © 2024 Jacob Curlin

#include "ecs/event_manager.h"

namespace cgx::ecs
{
    void EventManager::AddListener(EventId event_id, std::function<void(Event&)> const& listener)
    {
        m_listeners[event_id].push_back(listener);
    }

    void EventManager::SendEvent(Event& event)
    {
        uint32_t type = event.getType();

        for (auto const& listener : m_listeners[type])
        {
            listener(event);
        }
    }

    void EventManager::SendEvent(EventId event_id)
    {
        Event event(event_id);

        for (auto const& listener : m_listeners[event_id])
        {
            listener(event);
        }
    }

} // namespace cgx::ecs