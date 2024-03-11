// Copyright © 2024 Jacob Curlin

#pragma once

#include "utility/logging.h"

#include <bitset>
#include <cstdint>
#include <limits>
#include <memory>
#include <vector>

namespace cgx::ecs
{
    // ecs
    using Entity = std::uint32_t;
    static const Entity s_max_entities = 5000;

    using ComponentType = std::uint8_t;
    static const ComponentType s_max_components = 32;

    using Signature = std::bitset<s_max_components>;

    // event
    using TypeId = size_t;
    static const TypeId s_invalid_type_id = std::numeric_limits<TypeId>::max();

    using TimeStamp = double;


} // namespace cgx::ecs