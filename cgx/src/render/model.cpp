// Copyright © 2024 Jacob Curlin

#include "shader.h"
#include "mesh.h"
#include "model.h"

#include <glm/glm.hpp>
#include <filesystem>
#include <unordered_map>


namespace cgx::graphics
{

    Model::Model(std::string name, std::vector<std::shared_ptr<Mesh>> meshes)
        : m_name(name)
        , m_meshes(meshes) {}

    void Model::draw(Shader& shader)
    {
        for (unsigned int i = 0; i < m_meshes.size(); i++)
        {
            m_meshes[i]->draw(shader);
        }
    }

}