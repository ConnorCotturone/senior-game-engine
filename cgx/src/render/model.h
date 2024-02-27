// Copyright © 2024 Jacob Curlin

#ifndef MODEL_H
#define MODEL_H

#include "mesh.h"
#include "shader.h"
#include "model.h"

#include <memory>
#include <string>

namespace cgx::graphics
{

    class Model
    {
    public:
        Model(std::string name, std::vector<std::shared_ptr<Mesh>> meshes);

        inline const std::string& GetName() { return m_name; }
        void draw(Shader& shader);

    private:
        std::string m_name;
        std::vector<std::shared_ptr<Mesh>> m_meshes;
    };

}

#endif // MODEL_H