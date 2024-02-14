// jacob curlin
// material.cpp
// 01/16/2023

#include "material.h"

namespace cgx::graphics
{

    Material::Material(std::string id)
        : m_id(id)
        , m_ambientColor()
        , m_diffuseColor()
        , m_specularColor()
        , m_shininess()
        , m_ambientMap()
        , m_diffuseMap()
        , m_specularMap()
        , m_normalMap() {}
        
    Material::~Material() {};

    void Material::bind(Shader &shader) 
    {

        shader.setBool("material.useDiffuseMap", m_useDiffuseMap);
        shader.setBool("material.useSpecularMap", m_useSpecularMap);

        if (m_useDiffuseMap) {
            // diffuse map
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_diffuseMap);             // bind diffuse map to texture unit 0
            shader.setInt("material.diffuseMap", 0);     // set shader's material.diffuseMap to texture unit 0
        }

        if (m_useSpecularMap) {
            // specular map
            glActiveTexture(GL_TEXTURE0 + 1);
            glBindTexture(GL_TEXTURE_2D, m_specularMap);            // bind specular map to texture unit 1
            shader.setInt("material.specularMap", 1);   // set shader's material.specularMap to texture unit 1
        }

        shader.setVec3("material.diffuseColor", m_diffuse);     
        shader.setVec3("material.specularColor", m_specular);

        shader.setFloat("material.shininess", 64.0f);

        glActiveTexture(GL_TEXTURE0);
    } 

}