// Copyright © 2024 Jacob Curlin

#pragma once

// Implements an interface for managing entities and their associated components. 

#include "ecs/entity_manager.h"
#include "ecs/system_manager.h"
#include "ecs/component_manager.h"

namespace cgx::ecs
{
    class ECSManager
    {
    public:
        // Initializes the ECS Manager, creating and initializing instances of the component, 
        // entity, and system managers.
        void Initialize();

        // Creates and return an Entity (i.e. a uint32_t identifier).
        Entity CreateEntity();

        // Destroys 'entity'. 
        void DestroyEntity(Entity entity);

        // Returns a vector of currently active Entities.
        [[nodiscard]] std::vector<Entity> getActiveEntities() const;

        Signature GetSignature(Entity entity);

        // Registers a new component type with the component manager.
        template<typename T>
        void RegisterComponent() 
        { 
            m_component_manager->RegisterComponent<T>(); 
        }

        // Associates the component type 'T' data 'component' with entity 'entity'. Updates the 
        // signature (a std::bitset) of 'entity' to reflect its additional component association. 
        template<typename T>
        void AddComponent(Entity entity, T component)
        {
            m_component_manager->AddComponent<T>(entity, component);

            auto signature = m_entity_manager->GetSignature(entity);
            signature.set(m_component_manager->GetComponentType<T>(), true);
            m_entity_manager->SetSignature(entity, signature);

            m_system_manager->EntitySignatureChanged(entity, signature);
        }

        // Removes the data associated with 'entity' for component type 'T'. Updates the 
        // signautre (std::bitset) of 'entity' to reflect the component's removal. 
        template<typename T>
        void RemoveComponent(Entity entity)
        {
            m_component_manager->RemoveComponent<T>(entity);

            auto signature = m_entity_manager->GetSignature(entity);
            signature.set(m_component_manager->GetComponentType<T>(), false);
            m_entity_manager->SetSignature(entity, signature);

            m_system_manager->EntitySignatureChanged(entity, signature);
        }

        // Returns the component type 'T' data associated with 'entity. 
        template<typename T>
        T& GetComponent(Entity entity)
        {
            return m_component_manager->GetComponent<T>(entity);
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
            return m_component_manager->GetComponentType<T>();
        }

        // Registers a new system within the ECS System manager. 
        template<typename T>
        std::shared_ptr<T> RegisterSystem()
        {
            return m_system_manager->RegisterSystem<T>();
        }

        // Sets the 'signature' associated with a system of type 'T'.
        template<typename T>
        void SetSystemSignature(Signature signature)
        {
            m_system_manager->SetSignature<T>(signature);
        }

    private:
        std::unique_ptr<ComponentManager> m_component_manager;
        std::unique_ptr<EntityManager> m_entity_manager;
        std::unique_ptr<SystemManager> m_system_manager;
    };
}
