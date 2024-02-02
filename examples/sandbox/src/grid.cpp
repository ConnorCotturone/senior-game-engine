// jacob curlin
// grid.cpp
// 02/01/2024

#include "../include/grid.h"

VisualGrid::VisualGrid(
    float extent, glm::mat4 world_transform, 
    float grid_size, float cell_size, 
    glm::vec4 thin_lines_color, glm::vec4 thick_lines_color) 
    : m_extent(extent), m_world_transform(world_transform), 
    m_grid_size(grid_size), m_cell_size(cell_size),
    m_thin_lines_color(thin_lines_color), m_thick_lines_color(thick_lines_color)
{

    num_vertices = 6;
    m_grid_vertices = new float[3 * num_vertices];

    m_grid_vertices[0] =  -extent; m_grid_vertices[1] =  0.0f, m_grid_vertices[2] =  -extent;
    m_grid_vertices[3] =   extent; m_grid_vertices[4] =  0.0f, m_grid_vertices[5] =  -extent;
    m_grid_vertices[6] =  -extent; m_grid_vertices[7] =  0.0f, m_grid_vertices[8] =   extent;
    m_grid_vertices[9] =  -extent; m_grid_vertices[10] = 0.0f, m_grid_vertices[11] =  extent;
    m_grid_vertices[12] =  extent; m_grid_vertices[13] = 0.0f, m_grid_vertices[14] = -extent;
    m_grid_vertices[15] =  extent; m_grid_vertices[16] = 0.0f, m_grid_vertices[17] =  extent;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_grid_vertices), m_grid_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

VisualGrid::~VisualGrid()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    delete[] m_grid_vertices;       // cleanup allocated memory
}

void VisualGrid::Render(Shader* grid_shader, glm::vec3 view_dir, glm::mat4 view_mat, glm::mat4 proj_mat)
{
    grid_shader->use();

    grid_shader->setMat4("model", m_world_transform);
    grid_shader->setMat4("view", view_mat);
    grid_shader->setMat4("proj", proj_mat);

    grid_shader->setMat4("world_transform", m_world_transform);
    grid_shader->setFloat("grid_size", m_grid_size);
    grid_shader->setFloat("cell_size", m_cell_size);
    grid_shader->setVec4("thin_lines_color", m_thin_lines_color);
    grid_shader->setVec4("thick_lines_color", m_thick_lines_color);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, num_vertices);
    glBindVertexArray(0);
}