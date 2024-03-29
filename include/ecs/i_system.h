// Copyright © 2024 Jacob Curlin

#pragma once

#include "ecs/ecs_types.h"
#include <set>

namespace cgx::ecs
{
    class System
    {
    public:
        std::set<Entity> m_entities;
    };
}