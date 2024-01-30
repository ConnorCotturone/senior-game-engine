// jacob curlin
// mesh.h
// 01/06/2023

#ifndef MESH_H
#define MESH_H

#include "shader.h"
#include "material.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>



struct Vertex {
    glm::vec3 Position;     // position vector
    glm::vec3 Normal;       // normal vector
    glm::vec2 TexCoords;    // texture coordinate vector
    // glm::vec3 Tangent;
    // glm::vec3 Bitangent;
};

struct Texture {
    unsigned int id;        // texture id
    std::string type;       // texture type (diffuse / specular)
    std::string path;       // texture path
};

class Mesh {
public:
    std::vector<Vertex>         m_vertices;
    std::vector<unsigned int>   m_indices;
    Material                    m_material;          
    // std::vector<Texture>        m_textures;  ( deprecated -- remove )

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material material);
    ~Mesh();

    void Draw(Shader &shader);

private:
    // render data
    unsigned int VAO, VBO, EBO;     

    void Initialize();
};

#endif // MESH_H