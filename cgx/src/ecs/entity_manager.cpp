// entity_manager.cpp
// jacob curlin
// 01/26/2023

#include "entity_manager.h"
#include "../utility/logging.h"

namespace cgx::ecs
{

    EntityManager::EntityManager() : m_activeEntityCount(0)  // initialize vector of MAX_ENTITIES   
    {
        for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
        {
            m_availableEntities.push(entity);
        }
    }

    Entity EntityManager::CreateEntity()    // fetch first unused entity from entity vector
    {
        CGX_ASSERT(m_activeEntityCount < MAX_ENTITIES, "Too many active entities."); 
        if (!(m_activeEntityCount < MAX_ENTITIES)) { CGX_INFO("Active Entity Count : {}", m_activeEntityCount); } 
        if (!(m_activeEntityCount < MAX_ENTITIES)) { CGX_INFO("MAX_ENTITIES : {}", MAX_ENTITIES); }

        Entity id = m_availableEntities.front();        // fetch 
        m_availableEntities.pop();
        ++m_activeEntityCount;

        return id;
    }

    void EntityManager::DestroyEntity(Entity entity)
    {
        CGX_ASSERT(entity < MAX_ENTITIES, "Entity out of range.");
        CGX_INFO("Destroying Entity {}", entity);

        m_signatures[entity].reset();   // reset entity's signature (bitset) 

        m_availableEntities.push(entity);
        --m_activeEntityCount;
    }

    void EntityManager::SetSignature(Entity entity, Signature signature)
    {
        CGX_ASSERT(entity < MAX_ENTITIES, "Entity out of range.");

        m_signatures[entity] = signature;
    }

    Signature EntityManager::GetSignature(Entity entity)
    {
        CGX_ASSERT(entity < MAX_ENTITIES, "Entity out of range.");

        return m_signatures[entity];
    }

}