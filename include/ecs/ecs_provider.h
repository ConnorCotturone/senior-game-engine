// Copyright © 2024 Jacob Curlin

#pragma once

// Implements an interface for managing entities and their associated components. 

#include "core/time.h"

#include "ecs/common.h"
#include "ecs/component_registry.h"
#include "ecs/entity_registry.h"
#include "ecs/system_registry.h"

#include "ecs/event/event_handler.h"
#include "ecs/event/event_delegate.h"

namespace cgx::ecs::event
{
    class IEventListener;
}

namespace cgx::ecs
{
    

    class ECSProvider
        : public cgx::core::FixedStepUpdate
    {
        friend class cgx::ecs::event::EventHandler;
        friend class cgx::ecs::event::IEventListener;

    public:
        // Initializes the ECS registry, creating and initializing instances of the component, 
        // entity, and system registries.
        ECSProvider(cgx::core::Time& time);
        ~ECSProvider();

        // Creates and return an Entity (i.e. a uint32_t identifier).
        Entity CreateEntity();

        // Destroys 'entity'. 
        void DestroyEntity(Entity entity);

        // Returns a vector of currently active Entities.
        [[nodiscard]] std::vector<Entity> getActiveEntities() const;

        Signature GetSignature(Entity entity);

        // Registers a new component type with the component registry.
        template<typename T>
        void RegisterComponent() 
        { 
            m_component_registry->RegisterComponent<T>(); 
        }

        // Associates the component type 'T' data 'component' with entity 'entity'. Updates the 
        // signature (a std::bitset) of 'entity' to reflect its additional component association. 
        template<typename T>
        void AddComponent(Entity entity, T component)
        {
            m_component_registry->AddComponent<T>(entity, component);

            auto signature = m_entity_registry->GetSignature(entity);
            signature.set(m_component_registry->GetComponentType<T>(), true);
            m_entity_registry->SetSignature(entity, signature);

            m_system_registry->EntitySignatureChanged(entity, signature);
        }

        // Removes the data associated with 'entity' for component type 'T'. Updates the 
        // signautre (std::bitset) of 'entity' to reflect the component's removal. 
        template<typename T>
        void RemoveComponent(Entity entity)
        {
            m_component_registry->RemoveComponent<T>(entity);

            auto signature = m_entity_registry->GetSignature(entity);
            signature.set(m_component_registry->GetComponentType<T>(), false);
            m_entity_registry->SetSignature(entity, signature);

            m_system_registry->EntitySignatureChanged(entity, signature);
        }

        // Returns the component type 'T' data associated with 'entity. 
        template<typename T>
        T& GetComponent(Entity entity)
        {
            return m_component_registry->GetComponent<T>(entity);
        }

        template<typename T>
        bool HasComponent(Entity entity)
        {
            ComponentType component_type = GetComponentType<T>();
            Signature signature = GetSignature(entity);
            return signature.test(component_type);
        }

        // Returns the unique ID (uint8_t) associated with component type 'T'.
        template<typename T>
        ComponentType GetComponentType()
        {
            return m_component_registry->GetComponentType<T>();
        }

        // Registers a new system within the ECS System registry. 
        template<typename T>
        std::shared_ptr<T> RegisterSystem()
        {
            return m_system_registry->RegisterSystem<T>();
        }

        // Sets the 'signature' associated with a system of type 'T'.
        template<typename T>
        void SetSystemSignature(Signature signature)
        {
            m_system_registry->SetSignature<T>(signature);
        }

        template<class E, class... Args>
        void SendEvent(Args&&... event_args)
        {
            m_event_handler->Send<E>(std::forward<Args>(event_args)...);
        }

        void Update(const cgx::core::TimeContext&) override;

    private:
        std::unique_ptr<ComponentRegistry>      m_component_registry;
        std::unique_ptr<EntityRegistry>         m_entity_registry;
        std::unique_ptr<SystemRegistry>         m_system_registry;

        std::unique_ptr<event::EventHandler>    m_event_handler;


        template<class E>
        void SubscribeEvent(event::IEventDelegate* const event_delegate)
        {
            m_event_handler->AddEventCallback<E>(event_delegate);
        }

        void UnsubscribeEvent(event::IEventDelegate* event_delegate);

    }; // class ECSProvider

} // namespace cgx::ecs
