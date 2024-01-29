// jacob curlin
// Entity.h
// 01/26/2023

#ifndef OBJECT_H
#define OBJECT_H

#include <bitset>
#include "Component.h"

namespace ECS
{
    const ComponentType MAX_COMPONENTS = 32;

    using Entity = std::uint32_t;
    using Signature = std::bitset<MAX_COMPONENTS>;
}

#endif // OBJECT_H