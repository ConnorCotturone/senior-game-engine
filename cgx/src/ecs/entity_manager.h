// Copyright © 2024 Jacob Curlin

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

        std::vector<Entity> GetActiveEntities() const;

    private:
        std::queue<Entity> m_available_entities{};
        std::array<Signature, MAX_ENTITIES> m_signatures{};

        uint32_t m_active_entity_count;
    };
}

#endif // ENTITYMANAGER_H