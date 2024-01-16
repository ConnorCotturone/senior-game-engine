// jacob curlin
// material.h
// 01/16/2023

#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include "../include/shader.h"

class Material
{
public:
    Material(glm::vec3 diffuse, glm::vec3 specular, GLint diffuseMap, GLint specularMap, bool useDiffuseMap, bool useSpecularMap); 
    ~Material();

    void Bind(Shader &shader);

private:
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;

    GLint m_diffuseMap;
    GLint m_specularMap;

    bool m_useDiffuseMap;
    bool m_useSpecularMap;

};


#endif // MATERIAL_H