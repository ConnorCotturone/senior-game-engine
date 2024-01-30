// entity_manager.cpp
// jacob curlin
// 01/26/2023

#include "entity_manager.h"
#include "../utility/logging.h"

namespace ECS
{

    EntityManager::EntityManager()   // initialize vector of MAX_ENTITIES   
    {
        for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
        {
            m_availableEntities.push(entity);
        }
    }

    Entity EntityManager::CreateEntity()    // fetch first unused entity from entity vector
    {
        PHX_ASSERT(m_activeEntityCount < MAX_ENTITIES, "Too many active entities.")

        Entity id = m_availableEntities.front();        // fetch 
        m_availableEntities.pop();
        ++m_activeEntityCount;

        return id;
    }

    void EntityManager::DestroyEntity(Entity entity)
    {
        PHX_ASSERT(entity < MAX_ENTITIES, "Entity out of range.");

        m_signatures[entity].reset();   // reset entity's signature (bitset) 

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