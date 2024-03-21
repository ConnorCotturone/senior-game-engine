// Copyright © 2024 Jacob Curlin

#pragma once

#include "ecs/common.h"


namespace cgx::events::engine
{
    const cgx::ecs::EventId QUIT = "Events::Engine::QUIT"_hash;
    const cgx::ecs::EventId ENABLE_CAMERA_CONTROL = "Events::Engine::ENABLE_CAMERA_CONTROL"_hash;
    const cgx::ecs::EventId DISABLE_CAMERA_CONTROL = "Events::Engine::DISABLE_CAMERA_CONTROL"_hash;
}

namespace cgx::events::camera
{
    const cgx::ecs::EventId MOVE = "cgx::events::camera::move"_hash;

    namespace move
    {
        const cgx::ecs::ParamId DIRECTION = "cgx::events::camera::move::direction"_hash;
    }

}

namespace cgx::events::ecs
{
    const cgx::ecs::EventId ENTITY_CREATED = "cgx::events::ecs::ENTITY_CREATED"_hash;
    const cgx::ecs::EventId ENTITY_DESTROYED = "cgx::events::ecs::ENTITY_DESTROYED"_hash;
    const cgx::ecs::ParamId ENTITY_ID = "cgx::events::ecs::ENTITY_ID"_hash;
}