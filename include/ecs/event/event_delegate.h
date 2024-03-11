// Copyright © 2024 Jacob Curlin

#pragma once

#include "ecs/common.h"
#include "ecs/event/i_event_delegate.h"

namespace cgx::ecs::event
{

    class IEvent;

    template<class Class, class EventType>
    class EventDelegate : public IEventDelegate
    {
        typedef void(Class::*Callback)(const EventType* const);

        Class* m_receiver;
        Callback m_callback;

    public:

        EventDelegate(Class* receiver, Callback& callback_function)
            : m_receiver(receiver)
            , m_callback(callback_function)
        {}

        virtual IEventDelegate* Clone() override
        {
            return new EventDelegate(m_receiver, m_callback);
        }

        virtual void Invoke(const IEvent* const e) override
        {
            (m_receiver->*m_callback)(reinterpret_cast<const EventType* const>(e));
        }

        virtual EventDelegateId getDelegateId() const override
        {
            static const EventDelegateId s_delegate_id { typeid(Class).hash_code() ^ typeid(Callback).hash_code() };
            return s_delegate_id;
        }

        virtual uint64_t getStaticEventTypeId() const override
        {
            static const uint64_t s_event_type_id { EventType::s_event_type_id };
            return s_event_type_id;
        }

        virtual bool operator==(const IEventDelegate* other) const override
        {
            if (this->getDelegateId() != other->getDelegateId())
            {
                return false;
            }

            EventDelegate* delegate = (EventDelegate*) other;
            if (other == nullptr)
            {
                return false;
            }

            return ((this->m_callback == delegate->m_callback) && (this->m_receiver == delegate->m_receiver));
        }

    }; // class EventDelegate

} // namespace cgx::ecs::event