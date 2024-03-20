// Copyright © 2024 Jacob Curlin

#include "ecs/common.h"


namespace cgx::events
{
    const cgx::ecs::EventId KEY_PRESS = "cgx::events::KEY_PRESS"_hash;
    const cgx::ecs::EventId KEY_RELEASE = "cgx::events::KEY_RELEASE"_hash;

    const cgx::ecs::ParamId KEYCODE = "cgx::events::KEYCODE"_hash;
}