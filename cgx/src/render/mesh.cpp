// jacob curlin
// mesh.cpp
// 01/06/2023

#include "mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material material)
    : m_vertices(vertices), m_indices(indices), m_material(material)
{
    Initialize();
}

Mesh::~Mesh() {}


void Mesh::Initialize()
{
    /* setup mesh vertex array object (VAO) */

    glGenVertexArrays(1, &VAO);     
    glGenBuffers(1, &VBO);          
    glGenBuffers(1, &EBO);          

    glBindVertexArray(VAO);

    // setup vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

    // setup element array object (indices)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

    // vertex data : position vectors
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0); 

    // vertex data : normal vectors
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, Normal));

    // vertex data: texture coordinates
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, TexCoords));

    glBindVertexArray(0);   // unbind any bound vertex arrays
}


void Mesh::Draw(Shader &shader)
{
    m_material.Bind(shader);    

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}