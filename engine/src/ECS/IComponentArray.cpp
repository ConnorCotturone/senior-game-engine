// jacob curlin
// IComponentArray.cpp
// 01/28/2024

#include "IComponentArray.h"
#include "logging.h"

namespace ECS
{
    template<typename T>
    void ComponentArray<T>::InsertData(Entity entity, T component)
    {
        PHX_ASSERT(m_entityToIndexMap.find(entity) == m_entityToIndexMap.end(), "Component added to same entity more than once.");

        size_t newIndex = m_size;
        m_entityToIndexMap[entity] = newIndex;
        m_indexToEntityMap[newIndex] = entity;
        m_componentArray[newIndex] = component;
        ++m_size;
    }

    template<typename T>
    void ComponentArray<T>::RemoveData(Entity entity) 
    {
        PHX_ASSERT(m_entityToIndexMap.find(entity) != m_entityToIndexMap.end(), "Removing non-existent component.");
        
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

    template<typename T>
    T& ComponentArray<T>::GetData(Entity entity)
    {
        PHX_ASSERT(m_entityToIndexMap.find(entity) != m_entityToIndexMap.end(), "Retreiving non-existent component.");

        return m_componentArray[m_entityToIndexMap[entity]];
    }

    template<typename T>
    void ComponentArray<T>::EntityDestroyed(Entity entity)
    {
        if (m_entityToIndexMap.find(entity) != m_entityToIndexMap.end())
        {
            RemoveData(entity);
        }
    }
}