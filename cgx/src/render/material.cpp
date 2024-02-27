// Copyright © 2024 Jacob Curlin

#include "material.h"


#define AMBIENT_MAP_BIT 1
#define DIFFUSE_MAP_BIT 2
#define SPECULAR_MAP_BIT 4
#define NORMAL_MAP_BIT 8

namespace cgx::graphics
{

    Material::Material(
        std::string id, 
        glm::vec3 ambient_color, 
        glm::vec3 diffuse_color, 
        glm::vec3 specular_color, 
        float shininess, 
        std::shared_ptr<Texture> ambient_map, 
        std::shared_ptr<Texture> diffuse_map, 
        std::shared_ptr<Texture> specular_map, 
        std::shared_ptr<Texture> normal_map
    )
        : m_id(id)
        , m_ambient_color(ambient_color)
        , m_diffuse_color(diffuse_color)
        , m_specular_color(specular_color)
        , m_shininess(shininess)
        , m_ambient_map(ambient_map)
        , m_diffuse_map(diffuse_map)
        , m_specular_map(specular_map)
        , m_normal_map(normal_map) {}
        
    Material::~Material() {};

    void Material::bind(Shader &shader) 
    {
        // TODO!
        shader.use();
        shader.setVec3("material.ambient_color", m_ambient_color);
        shader.setVec3("material.diffuse_color", m_diffuse_color);     
        shader.setVec3("material.specular_color", m_specular_color);
        shader.setFloat("material.shininess", m_shininess);

        int map_bitset = 0;
        if (m_ambient_map != nullptr)
        {
            m_ambient_map->Bind(0);
            shader.setInt("material.ambient_map", 0);
            map_bitset |= AMBIENT_MAP_BIT;
        }
        if (m_diffuse_map != nullptr)   
        { 
            m_diffuse_map->Bind(1); 
            shader.setInt("material.diffuse_map", 1);
            map_bitset |= DIFFUSE_MAP_BIT;
        }
        if (m_specular_map != nullptr)  
        { 
            m_specular_map->Bind(2); 
            shader.setInt("material.specular_map", 2);
            map_bitset |= SPECULAR_MAP_BIT;
        }
        shader.setInt("material.map_bitset", map_bitset);
        
        glActiveTexture(GL_TEXTURE0);
    } 

}