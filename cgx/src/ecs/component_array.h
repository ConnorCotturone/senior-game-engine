// jacob curlin
// IComponentArray.h
// 01/28/2023

#ifndef COMPONENTARRAY_H
#define COMPONENTARRAY_H

#include "ecs_types.h"
#include "entity_manager.h"
#include "../utility/logging.h"

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
        void InsertData(Entity entity, T component)
        {
            CGX_ASSERT(m_entityToIndexMap.find(entity) == m_entityToIndexMap.end(), "Component added to same entity more than once.");

            size_t newIndex = m_size;
            m_entityToIndexMap[entity] = newIndex;
            m_indexToEntityMap[newIndex] = entity;
            m_componentArray[newIndex] = component;
            ++m_size;
        }

        void RemoveData(Entity entity) 
        {
            CGX_ASSERT(m_entityToIndexMap.find(entity) != m_entityToIndexMap.end(), "Removing non-existent component.");
            
            size_t indexOfRemovedEntity = m_entityToIndexMap[entity];
            size_t indexOfLastElement = m_size - 1;
            m_componentArray[indexOfRemovedEntity] = m_componentArray[indexOfLastElement];

            Entity entityOfLastElement = m_indexToEntityMap[indexOfLastElement];
            m_entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
            m_indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

            m_entityToIndexMap.erase(entity);
            m_indexToEntityMap.erase(indexOfLastElement);

            --m_size;
        }

        T& GetData(Entity entity)
        {
            CGX_ASSERT(m_entityToIndexMap.find(entity) != m_entityToIndexMap.end(), "Retreiving non-existent component.");

            return m_componentArray[m_entityToIndexMap[entity]];
        }

        void EntityDestroyed(Entity entity)
        {
            if (m_entityToIndexMap.find(entity) != m_entityToIndexMap.end())
            {
                RemoveData(entity);
            }
        }

    private:
        std::array<T, MAX_ENTITIES> m_componentArray;

        std::unordered_map<Entity, size_t> m_entityToIndexMap;
        std::unordered_map<size_t, Entity> m_indexToEntityMap;

        size_t m_size;
    };
}

#endif // COMPONENTARRAY_H