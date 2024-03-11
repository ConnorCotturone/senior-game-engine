// Copyright © 2024 Jacob Curlin

#include "ecs/common.h"
#include "ecs/event/event_handler.h"

namespace cgx::ecs::event
{

    void EventHandler::ClearEventBuffer()
    {
        m_event_storage.clear();
    }

    void EventHandler::ClearEventDispatcher()
    {
        m_event_dispatcher_map.clear();
    }

    void EventHandler::DispatchEvents()
    {
        size_t last_index = m_event_storage.size();
        size_t i = 0;

        while (i < last_index)
        {
            auto event = m_event_storage[i++];
            if (event == nullptr)
            {
                CGX_ERROR("Skip corruped event: {}", event->getEventTypeId());
                continue;
            }

            auto it = m_event_dispatcher_map.find(event->getEventTypeId());
            if (it == m_event_dispatcher_map.end())
            {
                continue;
            }

            it->second->Dispatch(event);

            last_index = m_event_storage.size();
        }

        for (auto event : m_event_storage)
        {
            delete event;
        }

        ClearEventBuffer();
    }

} // namespace cgx::ecs::event