// Copyright © 2024 Jacob Curlin

#pragma once

#include "ecs/ecs_types.h"
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

        [[nodiscard]] std::vector<Entity> GetActiveEntities() const;

    private:
        std::deque<Entity> m_available_entities{};
        std::array<Signature, MAX_ENTITIES> m_signatures{};

        uint32_t m_active_entity_count;
    };
}
