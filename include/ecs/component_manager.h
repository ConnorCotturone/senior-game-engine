// Copyright © 2024 Jacob Curlin

// Implements an interface for managing components within the ECS, allowing for registration 
// of component types and management of each type's corresponding component array. 

#pragma once

#include "core/common.h"
#include "ecs/ecs_types.h"
#include "ecs/component_array.h"
#include "utility/logging.h"

#include <unordered_map>

namespace cgx::ecs
{
    class ComponentManager
    {
    public:
        // Registers a new component type T. Associates string name representation of component type
        // with a unique ID within the 'm_component_types' map, a new corresponding component 
        // array within the 'm_component_arrays'.
        template<typename T>
        void RegisterComponent()
        {
            const char* type_name = typeid(T).name();

            CGX_ASSERT(m_component_types.find(type_name) == m_component_types.end(), "Registering component type more than once.");

            // add {component type name : component type id} mapping to m_component_types{}
            ComponentType type_id = m_next_component_type;
            m_component_types.insert({type_name, type_id});

            auto component_array = std::make_shared<ComponentArray<T>>();

            // add {component type name : component array} mapping to m_component_arrays{}
            m_component_arrays.insert({type_name, component_array});

            // add {component type id : component array} mapping to m_type_id_to_arrays{}
            m_type_id_to_arrays.insert({type_id, component_array});


            ++m_next_component_type;    
        }

        // Returns the unique ID (uint8_t) associated with a component type 'T'.
        template<typename T>
        ComponentType GetComponentType()
        {
            const char* type_name = typeid(T).name();

            CGX_ASSERT(m_component_types.find(type_name) != m_component_types.end(), "Component not registered before use.");

            return m_component_types[type_name];
        }

        // Adds the component data 'component' associated with 'entity' to its corresponding component array. 
        template<typename T>
        void AddComponent(Entity entity, T component)
        {
            GetComponentArray<T>()->InsertData(entity, component);
        }

        // Removes the component data associated with 'entity' for from the component array associated with
        // component type 'T'.
        template<typename T>
        void RemoveComponent(Entity entity)
        {
            GetComponentArray<T>()->RemoveData(entity);
        }

        // Returns the data associated with 'entity' stored in the component array for component type 'T' 
        template<typename T>
        T& GetComponent(Entity entity)
        {
            return GetComponentArray<T>()->GetData(entity);
        }

        // Removes any data associated with 'entity' from the component arrays. 
        void EntityDestroyed(Entity entity);

    private:
        std::unordered_map<const char*, ComponentType> m_component_types{};
        std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_component_arrays{};
        std::unordered_map<ComponentType, std::shared_ptr<IComponentArray>> m_type_id_to_arrays{};
        ComponentType m_next_component_type{};

        // Returns a shared pointer to the component array associated with component type 'T'
        template<typename T>
        std::shared_ptr<ComponentArray<T>> GetComponentArray()
        {
            const char* type_name = typeid(T).name();

            CGX_ASSERT(m_component_types.find(type_name) != m_component_types.end(), "Component not registered before use.");

            return std::static_pointer_cast<ComponentArray<T>>(m_component_arrays[type_name]);
        }

    };

}
