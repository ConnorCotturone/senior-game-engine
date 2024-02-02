// jacob curlin
// entity_manager.h
// 01/28/2023


#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "ecs_types.h"
#include <array>
#include <bitset>
#include <queue>
#include <vector>


namespace cgx::ecs
{
    class EntityManager {
    public:
        EntityManager();

        Entity CreateEntity();
        void DestroyEntity(Entity entity);
        void SetSignature(Entity entity, Signature signature);
        Signature GetSignature(Entity entity);

    private:
        std::queue<Entity> m_availableEntities{};
        std::array<Signature, MAX_ENTITIES> m_signatures{};

        uint32_t m_activeEntityCount;
    };
}

#endif // ENTITYMANAGER_H