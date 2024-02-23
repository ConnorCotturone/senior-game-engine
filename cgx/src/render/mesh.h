// jacob curlin
// mesh.h
// 01/06/2023

#ifndef MESH_H
#define MESH_H


#include "shader.h"
#include "material.h"
#include <glad/glad.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>

#include <string>
#include <vector>

namespace cgx::graphics
{
    struct Vertex {
        glm::vec3 position;     // position vector
        glm::vec3 normal;       // normal vector
        glm::vec2 texCoord;    // texture coordinate vector

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
    template<> struct hash<cgx::graphics::Vertex> 
    {
        size_t operator()(cgx::graphics::Vertex const& vertex) const
        {
            return ((hash<glm::vec3>()(vertex.position) ^
                    (hash<glm::vec3>()(vertex.normal) << 1)) >> 1) ^
                    (hash<glm::vec2>()(vertex.texCoord) << 1);
        }
    };
}

namespace cgx::graphics 
{
    class Mesh {
    public:
        std::vector<Vertex>         m_vertices;
        std::vector<unsigned int>   m_indices;
        std::shared_ptr<Material>   m_material;          

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::shared_ptr<Material> material);
        ~Mesh();

        void draw(Shader &shader);

    private:
        // render data
        unsigned int VAO, VBO, EBO;     

        void Initialize();
    };

}

#endif // MESH_H