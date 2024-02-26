// Copyright © 2024 Jacob Curlin

#ifndef ISYSTEM_H
#define ISYSTEM_H

#include "ecs_types.h"
#include <set>

namespace cgx::ecs
{
    class System
    {
    public:
        std::set<Entity> m_entities;
    };
}

#endif // ISYSTEM_H