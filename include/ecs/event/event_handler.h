// Copyright © 2024 Jacob Curlin

#pragma once

#include "ecs/common.h"
#include "ecs/event/i_event.h"
#include "ecs/event/event_dispatcher.h"

namespace cgx::ecs
{
    class ECSProvider;
}

namespace cgx::ecs::event
{

    class EventHandler  
    {
        friend class cgx::ecs::ECSProvider;   // allow EventHandler to access private ECSProvider add/remove callback methods

        using EventDispatcherMap = std::unordered_map<EventTypeId, IEventDispatcher*>;
        using EventStorage = std::vector<IEvent*>;


    public:
        EventHandler();
        ~EventHandler();

        void ClearEventBuffer();
        void ClearEventDispatcher();
        void DispatchEvents();

        template<class E, class... Args>
        void Send(Args&&... event_args)
        {
            CGX_ASSERT(std::is_trivially_copyable<E>::value, "Event is not trivially copyable.");

            // temporarily using std::vector until allocator implementation decided upon
            try
            {
                auto event = new E(std::forward<Args>(event_args)...);
                m_event_storage.push_back(event);
            }
            catch(const std::exception& e)
            {
                CGX_WARN("Memory allocation for event failed: {}", e.what());
            }
        }


    private:
        EventHandler(const EventHandler&);
        EventHandler& operator=(EventHandler&);

        std::unordered_map<EventTypeId, IEventDispatcher*>  m_event_dispatcher_map;
        std::vector<IEvent*>                                m_event_storage;

        template<class E>
        void AddEventCallback(IEventDelegate* const event_delegate)
        {
            EventTypeId event_type_id = E::s_event_type_id;

            EventDispatcherMap::const_iterator iter = m_event_dispatcher_map.find(event_type_id);
            if (iter == m_event_dispatcher_map.end())
            {
                std::pair<EventTypeId, IEventDispatcher*> keyval_pair(event_type_id, new EventDispatcher<E>());

                keyval_pair.second->AddEventCallback(event_delegate);

                m_event_dispatcher_map.insert(keyval_pair);
            }
            else
            {
                m_event_dispatcher_map[event_type_id]->AddEventCallback(event_delegate);
            }
        }

        void RemoveEventCallback(IEventDelegate* event_delegate)
        {
            auto type_id = event_delegate->getStaticEventTypeId();
            EventDispatcherMap::const_iterator iter = m_event_dispatcher_map.find(type_id);
            if (iter != m_event_dispatcher_map.end())
            {
                m_event_dispatcher_map[type_id]->RemoveEventCallback(event_delegate);
            }
        }        






    };








}