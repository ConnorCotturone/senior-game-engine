// Copyright © 2024 Jacob Curlin

#pragma once

#include "ecs/common.h"

namespace cgx::ecs::event
{
    class IEvent;

    using EventDelegateId = size_t;

    class IEventDelegate
    {
    public:
        
        virtual ~IEventDelegate() = default;

        virtual void Invoke(const IEvent* const e) = 0;

        virtual EventDelegateId getDelegateId() const = 0;

        virtual uint64_t getStaticEventTypeId() const = 0;

        virtual bool operator==(const IEventDelegate* other) const = 0;

        virtual IEventDelegate* Clone() = 0;


    }; // class IEventDelegate

} // namespace cgx::ecs::event