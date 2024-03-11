// Copyright © 2024 Jacob Curlin

#pragma once

#include "ecs/event/i_event_dispatcher.h"
#include <list>

namespace cgx::ecs::event
{
    template<class T>
    class EventDispatcher : public IEventDispatcher
    {
        using EventDelegateList =       std::list<IEventDelegate*>;
        using PendingRemoveDelegates =  std::list<IEventDelegate*>;

        PendingRemoveDelegates m_pending_remove_delegates;

        EventDelegateList m_event_callbacks;

        bool m_locked;

    public:

        EventDispatcher() 
            : m_locked(false)
        {}

        virtual ~EventDispatcher()
        {
            m_pending_remove_delegates.clear();
            m_event_callbacks.clear();
        }

        void Dispatch(IEvent* event) override
        {
            m_locked = true;
            {
                if (m_pending_remove_delegates.empty() == false)
                {
                    for (auto event_callback : m_pending_remove_delegates)
                    {
                        auto result = std::find_if(m_event_callbacks.begin(), m_event_callbacks.end(),
                            [&](const IEventDelegate* other)
                            {
                                return other->operator==(event_callback);
                            });

                        if (result != m_event_callbacks.end())
                        {
                            IEventDelegate* ptr_mem = (IEventDelegate*)(*result);

                            m_event_callbacks.erase(result);

                            delete ptr_mem;
                            ptr_mem = nullptr;
                        }
                    }
                    m_pending_remove_delegates.clear();
                }

                for (auto event_callback : m_event_callbacks)
                {
                    CGX_ASSERT(event_callback != nullptr, "Invalid Event Callback. ")
                    event_callback->Invoke(event);
                }
            }
            m_locked = false;
        }

        virtual void AddEventCallback(IEventDelegate* const event_delegate) override
        {
            auto result = std::find_if(m_pending_remove_delegates.begin(), m_pending_remove_delegates.end(),
                [&](const IEventDelegate* other)
                {
                    return other->operator==(event_delegate);
                });
            if (result != m_pending_remove_delegates.end())
            {
                m_pending_remove_delegates.erase(result);
                return;
            }

            m_event_callbacks.push_back(event_delegate);
        }

        virtual void RemoveEventCallback(IEventDelegate* event_delegate) override
        {
            if (m_locked == false)
            {
                auto result = std::find_if(m_event_callbacks.begin(), m_event_callbacks.end(),
                    [&](const IEventDelegate* other)
                    {
                        return other->operator==(event_delegate);
                    });
                if (result != m_event_callbacks.end())
                {
                    IEventDelegate* ptr_mem = (IEventDelegate*)(result);

                    m_event_callbacks.erase(result);

                    delete ptr_mem;
                    ptr_mem = nullptr;
                }
            }
            else
            {
                auto result = std::find_if(m_event_callbacks.begin(), m_event_callbacks.end(),
                    [&](const IEventDelegate* other)
                    {
                        return other->operator==(event_delegate);
                    });
                CGX_ASSERT(result != m_event_callbacks.end(), "(TODO) Assertion Failed: ecs/event/event_dispatcher.h:112");
                m_pending_remove_delegates.push_back((*result));
            }
        }

        virtual size_t getEventCallbackCount() const override { return m_event_callbacks.size(); }

    }; // class EventDispatcher


} //namespace cgx::ecs::event
