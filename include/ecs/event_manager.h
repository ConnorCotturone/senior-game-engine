// Copyright © 2024 Jacob Curlin

#include "ecs/common.h"
#include "ecs/event.h"

#include <functional>
#include <list>
#include <unordered_map>

namespace cgx::ecs
{
    class EventManager
    {
    public:

        void AddListener(EventId event_id, std::function<void(Event&)> const& listener);

        void SendEvent(Event& event);

        void SendEvent(EventId event_id);

    private:
        std::unordered_map<EventId, std::list<std::function<void(Event&)>>> m_listeners;

    }; // class EventManager

} // namespace cgx::ecs