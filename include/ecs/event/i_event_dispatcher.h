// Copyright © 2024 Jacob Curlin

#pragma once

#include "ecs/common.h"
#include "ecs/event/event_delegate.h"

namespace cgx::ecs::event
{
    class IEvent;

    class IEventDispatcher
    {
    public:
        virtual ~IEventDispatcher() = default;

        virtual void Dispatch(IEvent* event) = 0;

        virtual void AddEventCallback(IEventDelegate* const event_delegate) = 0;

        virtual void RemoveEventCallback(IEventDelegate* event_delegate) = 0;

        virtual size_t getEventCallbackCount() const = 0;

    }; // class IEventDispatcher

} // namespace cgx::ecs::event