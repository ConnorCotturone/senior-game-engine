// EntityManager.cpp
// jacob curlin
// 01/26/2023


#include "EntityManager.h"
#include "logging.h"

namespace ECS
{

    EntityManager::EntityManager() 
    {
        for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
        {
            m_availableEntities.push(entity);
        }
    }

    Entity EntityManager::CreateEntity()
    {
        PHX_ASSERT(m_activeEntityCount < MAX_ENTITIES, "Too many active entities.")

        Entity id = m_availableEntities.front();
        m_availableEntities.pop();
        ++m_activeEntityCount;

        return id;
    }

    void EntityManager::DestroyEntity(Entity entity)
    {
        PHX_ASSERT(entity < MAX_ENTITIES, "Entity out of range.");

        m_signatures[entity].reset();   // reset entity ID's bitset to 0's

        m_availableEntities.push(entity);
        --m_activeEntityCount;
    }

    void EntityManager::SetSignature(Entity entity, Signature signature)
    {
        PHX_ASSERT(entity < MAX_ENTITIES, "Entity out of range.");

        m_signatures[entity] = signature;
    }

    Signature EntityManager::GetSignature(Entity entity)
    {
        PHX_ASSERT(entity < MAX_ENTITIES, "Entity out of range.");

        return m_signatures[entity];
    }

}