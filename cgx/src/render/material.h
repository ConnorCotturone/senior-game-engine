// jacob curlin
// material.h
// 01/16/2023

#ifndef MATERIAL_H
#define MATERIAL_H

#include "shader.h"
#include "texture.h"
#include <glm/glm.hpp>
#include <glad/glad.h>

namespace cgx::graphics
{
    class Material
    {
    public:
        Material(std::string id); 
        ~Material();

        void bind(Shader &shader);

    private:
        std::string m_id;

        glm::vec3 m_ambientColor;
        glm::vec3 m_diffuseColor;
        glm::vec3 m_specularColor;
        float m_shininess;

        std::shared_ptr<Texture> m_ambientMap;
        std::shared_ptr<Texture> m_diffuseMap;
        std::shared_ptr<Texture> m_specularMap;
        std::shared_ptr<Texture> m_normalMap;
    };

}

#endif // MATERIAL_H 