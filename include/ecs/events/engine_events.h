// Copyright © 2024 Jacob Curlin

#pragma once

#include "ecs/common.h"


namespace cgx::events::engine
{
    const cgx::ecs::EventId QUIT = "Events::Engine::QUIT"_hash;
}

namespace cgx::events::camera
{
    const cgx::ecs::EventId MOVE = "cgx::events::camera::move"_hash;

    namespace move
    {
        const cgx::ecs::ParamId DIRECTION = "cgx::events::camera::move::direction"_hash;
    }

}