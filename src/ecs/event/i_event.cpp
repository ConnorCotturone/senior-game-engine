// Copyright © 2024 Jacob Curlin

#include "ecs/event/i_event.h"

namespace cgx::ecs::event
{
    IEvent::IEvent(EventTypeId type_id)
        : m_type_id(type_id)
    {
        // (TODO) m_time_created = 
    }

} // namespace cgx::ecs::event