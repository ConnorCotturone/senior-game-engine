// Copyright © 2024 Jacob Curlin

// Implements a packed array structure for storage/management of a particular component type's data. 
// reference: https://austinmorlan.com/posts/entity_component_system/

#pragma once

#include "core/common.h"
#include "ecs/ecs_types.h"
#include "ecs/entity_manager.h"

namespace cgx::ecs
{
    class IComponentArray
    {
    public:
        virtual ~IComponentArray() = default;
        virtual void EntityDestroyed(Entity entity) = 0;
    };

    template<typename T>
    class ComponentArray : public IComponentArray
    {
    public:
        // Inserts the data of 'component' associated with 'entity' at the back of the array, updating
        // entity->index and index->entity maps to reflect. Increments array size ('m_size'), effectively
        // incrementing the next insertion index to represent the new back of the array. 
        void InsertData(Entity entity, T component)
        {
            CGX_ASSERT(m_entity_to_index_map.find(entity) == m_entity_to_index_map.end(), "Component added to same entity more than once.");

            size_t new_index = m_size;
            m_entity_to_index_map[entity] = new_index;
            m_index_to_entity_map[new_index] = entity;
            m_component_array[new_index] = component;
            ++m_size;
        }

        // Removes the component data associated with 'entity' from the array. Moves the component data
        // currently located at the back of the array to the position of the now-freed data to maintain
        // a packed structure. Decrements array size and updates entity->index and index->entity maps to reflect. 
        void RemoveData(Entity entity) 
        {
            CGX_ASSERT(m_entity_to_index_map.find(entity) != m_entity_to_index_map.end(), "Removing non-existent component.");
            
            size_t index_of_removed_entity = m_entity_to_index_map[entity];
            size_t index_of_last_element = m_size - 1;
            m_component_array[index_of_removed_entity] = m_component_array[index_of_last_element];

            Entity entity_of_last_element = m_index_to_entity_map[index_of_last_element];
            m_entity_to_index_map[entity_of_last_element] = index_of_removed_entity;
            m_index_to_entity_map[index_of_removed_entity] = entity_of_last_element;

            m_entity_to_index_map.erase(entity);
            m_index_to_entity_map.erase(index_of_last_element);

            --m_size;
        }

        // Returns the component data associated iwth 'entity'. 
        T& GetData(Entity entity)
        {
            CGX_ASSERT(m_entity_to_index_map.find(entity) != m_entity_to_index_map.end(), "Retrieving non-existent component.");

            return m_component_array[m_entity_to_index_map[entity]];
        }


        // Checks if 'entity' corresponds to component data in the array, removing it if present. 
        void EntityDestroyed(Entity entity) override
        {
            if (m_entity_to_index_map.find(entity) != m_entity_to_index_map.end())
            {
                RemoveData(entity);
            }
        }

    private:
        std::array<T, MAX_ENTITIES> m_component_array;

        std::unordered_map<Entity, size_t> m_entity_to_index_map;
        std::unordered_map<size_t, Entity> m_index_to_entity_map;

        size_t m_size = 0;
    };
}
