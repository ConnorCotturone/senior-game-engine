// Copyright © 2024 Jacob Curlin

#pragma once

#include "core/common.h"
#include "render/mesh.h"
#include "render/shader.h"
#include <string>

namespace cgx::render
{
    class Model
    {
    public:
        Model(std::string name, std::vector<std::shared_ptr<Mesh>> meshes);

        void Draw(Shader& shader);
        inline const std::string& getName() { return m_name; }

    private:
        std::string                         m_name;
        std::vector<std::shared_ptr<Mesh>>  m_meshes;
    };
}