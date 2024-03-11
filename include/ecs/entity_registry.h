// Copyright © 2024 Jacob Curlin

#pragma once

#include "ecs/common.h"
#include <array>
#include <queue>

namespace cgx::ecs
{
    class EntityRegistry {
    public:
        EntityRegistry();

        Entity CreateEntity();
        void DestroyEntity(Entity entity);

        void SetSignature(Entity entity, Signature signature);
        Signature GetSignature(Entity entity);

        [[nodiscard]] std::vector<Entity> GetActiveEntities() const;

    private:
        std::queue<Entity>                      m_available_entities{};
        std::array<Signature, s_max_entities>   m_signatures{};

        uint32_t m_active_entity_count;
    };
}
