// Copyright © 2024 Jacob Curlin

// Event Class

#pragma once

#include "core/common.h"
#include "ecs/event/i_event.h"


namespace cgx::ecs::event
{
    template<class T>
    class Event : public IEvent
    {
    public:

        // static event id for runtime type identification 
        static const EventTypeId s_event_type_id;

        Event() : IEvent(s_event_type_id) {}

    }; // class Event<T>

    template<class T>
    const EventTypeId Event<T>::s_event_type_id { typeid(T).hash_code() };

}// namespace cgx::ecs::event