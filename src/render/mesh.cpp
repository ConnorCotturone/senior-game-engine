// Copyright © 2024 Jacob Curlin

#include "render/mesh.h"

namespace cgx::render
{

    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::shared_ptr<Material> material)
        : m_vertices(std::move(vertices)), m_indices(std::move(indices)), m_material(std::move(material))
    {
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        glGenBuffers(1, &m_ebo);

        glBindVertexArray(m_vao);

        // setup vertex buffer object
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(m_vertices.size() * sizeof(Vertex)), &m_vertices[0], GL_STATIC_DRAW);

        // setup element array object (indices)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(m_indices.size() * sizeof(unsigned int)), &m_indices[0], GL_STATIC_DRAW);

        // vertex data : position vectors
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, position));

        // vertex data : normal vectors
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, normal));

        // vertex data: texture coordinates
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, texCoord));

        glBindVertexArray(0);   // unbind any bound vertex arrays
    }

    Mesh::~Mesh() {
        glDeleteVertexArrays(1, &m_vao);    // free VAO
        glDeleteBuffers(1, &m_vbo);
        glDeleteBuffers(1, &m_ebo);
    }

    void Mesh::Draw(Shader& shader) const
    {
        m_material->bind(shader);    

        glBindVertexArray(m_vao);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }

}
