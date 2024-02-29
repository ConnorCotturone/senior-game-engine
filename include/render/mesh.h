// Copyright © 2024 Jacob Curlin

#pragma once

#include "render/shader.h"
#include "render/material.h"
#include <glad/glad.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>

#include <string>
#include <vector>

namespace cgx::render
{
    struct Vertex {
        glm::vec3 position{};   // position vector
        glm::vec3 normal{};     // normal vector
        glm::vec2 texCoord{};   // texture coordinate vector

        bool operator==(const Vertex& other) const 
        {
            return position == other.position   && 
                   normal == other.normal       && 
                   texCoord == other.texCoord;
        }
    };
}

namespace std 
{
    template<> struct hash<cgx::render::Vertex>
    {
        size_t operator()(cgx::render::Vertex const& vertex) const
        {
            return ((hash<glm::vec3>()(vertex.position) ^
                    (hash<glm::vec3>()(vertex.normal) << 1)) >> 1) ^
                    (hash<glm::vec2>()(vertex.texCoord) << 1);
        }
    };
}

namespace cgx::render
{
    class Mesh {
    public:
        std::vector<Vertex>         m_vertices;
        std::vector<unsigned int>   m_indices;
        std::shared_ptr<Material>   m_material;          

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::shared_ptr<Material> material);
        ~Mesh();

        void Draw(Shader &shader) const;

    private:
        // render data
        uint32_t m_vao = 0;
        uint32_t m_vbo = 0;
        uint32_t m_ebo = 0;

    };

}