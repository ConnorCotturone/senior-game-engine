// Copyright © 2024 Jacob Curlin

#ifndef ECSTYPES_H
#define ECSTYPES_H

#include <bitset>

namespace cgx::ecs
{
    using Entity = std::uint32_t;
    const Entity MAX_ENTITIES = 5000;

    using ComponentType = std::uint8_t;
    const ComponentType MAX_COMPONENTS = 32;

    using Signature = std::bitset<MAX_COMPONENTS>;

}


#endif // ECSTYPES_H
