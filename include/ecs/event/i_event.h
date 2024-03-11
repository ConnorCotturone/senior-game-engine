// Copyright © 2024 Jacob Curlin

#pragma once

#include "core/common.h"

namespace cgx::ecs::event
{
    using EventTypeId       =  std::size_t;
    using EventTimestamp    =  double;

    static const EventTypeId s_invalid_event_type = std::numeric_limits<std::size_t>::max();

    class IEvent
    {
    public:
        IEvent(EventTypeId type_id);

        const EventTypeId getEventTypeId() const     { return m_type_id; }
        const EventTimestamp getTimeCreated() const  { return m_time_created; }

    private:
        EventTypeId     m_type_id;
        EventTimestamp  m_time_created;

    }; // class IEvent

} // namespace cgx::ecs::event