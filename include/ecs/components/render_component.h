// Copyright © 2024 Jacob Curlin

#pragma once

#include "core/common.h"
#include "render/model.h"
#include "render/shader.h"

struct RenderComponent
{
    std::shared_ptr<cgx::render::Model> model;
    std::shared_ptr<cgx::render::Shader> shader;
};