// jacob curlin
// material.cpp
// 01/16/2023

#include "material.h"

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

        shader.setVec3("material.diffuseColor", m_diffuse_color);     
        shader.setVec3("material.specularColor", m_specular_color);
        shader.setFloat("material.shininess", 64.0f);

        if (m_diffuse_map != nullptr)   
        { 
            m_diffuse_map->Bind(0); 
            shader.setInt("material.diffuseMap", 0);
        }
        if (m_specular_map != nullptr)  
        { 
            m_specular_map->Bind(1); 
            shader.setInt("material.specularMap", 1);
        }
        
        glActiveTexture(GL_TEXTURE0);
    } 

}