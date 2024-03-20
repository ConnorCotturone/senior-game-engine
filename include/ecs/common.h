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
    static const Entity MAX_ENTITIES = 5000;

    using ComponentType = std::uint8_t;
    static const ComponentType MAX_COMPONENTS = 32;

    using Signature = std::bitset<MAX_COMPONENTS>;

    using EventId = std::uint32_t;
    using ParamId = std::uint32_t;

} // namespace cgx::ecs 

#define METHOD_LISTENER(EventType, Listener) EventType, std::bind(&Listener, this, std::placeholders::_1)
#define FUNCTION_LISTENER(EventType, Listener) EventType, std::bind(&Listener, std::placeholders::_1)

constexpr std::uint32_t fnv1a_32(char const* s, std::size_t count)
{
	return ((count ? fnv1a_32(s, count - 1) : 2166136261u) ^ s[count]) * 16777619u; // NOLINT (hicpp-signed-bitwise)
}

constexpr std::uint32_t operator "" _hash(char const* s, std::size_t count)
{
	return fnv1a_32(s, count);
}