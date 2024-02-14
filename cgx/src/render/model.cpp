// jacob curlin
// model.cpp
// 02/09/2024


#include "shader.h"
#include "mesh.h"
#include "model.h"

#include <glm/glm.hpp>
#include <filesystem>
#include <unordered_map>


namespace cgx::graphics
{

    Model::Model(std::vector<std::shared_ptr<Mesh>> meshes)
        : m_meshes(meshes) {}

    void Model::draw(Shader& shader)
    {
        for (unsigned int i = 0; i < m_meshes.size(); i++)
        {
            m_meshes[i]->draw(shader);
        }
    }

}