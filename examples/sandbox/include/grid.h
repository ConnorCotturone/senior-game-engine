// jacob curlin
// grid.h
// 02/01/2024

#ifndef GRID_H
#define GRID_H

#include "cpgx.h"

class VisualGrid
{
public:
    VisualGrid(float extent, glm::mat4 world_transform, 
        float grid_size, float cell_size, 
        glm::vec4 thin_lines_color, glm::vec4 thick_lines_color
    ); 
    ~VisualGrid();

    void Render(Shader* grid_shader, glm::vec3 view_dir, glm::mat4 view_mat, glm::mat4 proj_mat);

private:
    float m_extent;
    float* m_grid_vertices;

    glm::mat4 m_world_transform;
    float m_grid_size;
    float m_cell_size;
    glm::vec4 m_thin_lines_color;
    glm::vec4 m_thick_lines_color;
    
    unsigned int num_vertices;
    unsigned int VAO;
    unsigned int VBO;
};

#endif // GRID_H