// jacob curlin
// material.cpp
// 01/16/2023

#include "../include/material.h"

Material::Material(glm::vec3 diffuse, glm::vec3 specular, GLint diffuseMap, GLint specularMap, bool useDiffuseMap, bool useSpecularMap) 
    : m_diffuse(diffuse), m_specular(specular), m_diffuseMap(diffuseMap), m_specularMap(specularMap), 
      m_useDiffuseMap(useDiffuseMap), m_useSpecularMap(useSpecularMap) {}
    
Material::~Material() {};

void Material::Bind(Shader &shader) 
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
