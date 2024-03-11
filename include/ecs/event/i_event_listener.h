// Copyright © 2024 Jacob Curlin

#pragma once

#include "ecs/ecs_provider.h"
#include "ecs/event/event_delegate.h"
#include <list>

namespace cgx::ecs::event
{

    class IEventListener
    {
        using RegisteredCallbacks = std::list<IEventDelegate*>;
        RegisteredCallbacks m_registered_callbacks;

    public:

        IEventListener(std::shared_ptr<ECSProvider> ecs_provider);
        virtual ~IEventListener();

        void UnregisterAllEventCallbacks();

        template<class E, class C>
        void RegisterEventCallback(void(C::*Callback)(const E* const))
        {
            IEventDelegate* event_delegate = new EventDelegate<C, E>(static_cast<C*>(this), Callback);

            m_registered_callbacks.push_back(event_delegate);
            m_ecs_provider->SubscribeEvent<E>(event_delegate);
        }

        template<class E, class C>
        void UnregisterEventCallback(void(C::*Callback)(const E* const))
        {
            EventDelegate<C, E> delegate(static_cast<C*>(this), Callback);

            for (auto event_callback : m_registered_callbacks)
            {
                if (event_callback->getDelegateId() == delegate.getDelegateId())
                {
                    m_registered_callbacks.remove_if(
                        [&](const IEventDelegate* other)
                        {
                            return other->operator==(event_callback);
                        }
                    );

                    m_ecs_provider->UnsubscribeEvent(&delegate);
                    break;
                }
            }
        }

    private:
        std::shared_ptr<ECSProvider> m_ecs_provider;

    }; // class IEventListener

} // namespace cgx::ecs::event