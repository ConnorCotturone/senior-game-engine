// jacob curlin
// mesh.cpp
// 01/06/2023

#include "../include/mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
    m_vertices = vertices;
    m_indices = indices;
    m_textures = textures;

    Initialize();
}

Mesh::~Mesh() {}

void Mesh::Initialize()
{
    glGenVertexArrays(1, &VAO);         // generate vertex array object
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

    // position vectors
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0); 

    // normal vectors
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, Normal));

    // texture coordinates
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, TexCoords));

    glBindVertexArray(0);       
}


void Mesh::Draw(Shader &shader)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;

    for (unsigned int i = 0; i < m_textures.size(); i++) 
    {
        glActiveTexture(GL_TEXTURE0 + i);          // activate texture unit [i]

        std::string number;
        std::string name = m_textures[i].type;             // recall each texture has a string 'type' (diffuse/ specular)

        if (name == "texture.diffuse")          
        { 
            number = std::to_string(diffuseNr++);       
        }
        else if (name == "texture_specular") 
        { 
            number = std::to_string(specularNr++); 
        }

        // set shader uniform 'material.{[diffuse/specular]}.{unique integer val}' to 
        shader.setInt(("material." + name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}