// Copyright © 2024 Jacob Curlin

#pragma once

#include "render/shader.h"
#include "render/texture.h"
#include <glm/glm.hpp>
#include <glad/glad.h>

namespace cgx::render
{
    class Material
    {
    public:
        Material(
            std::string id, 
            glm::vec3 ambient_color, 
            glm::vec3 diffuse_color, 
            glm::vec3 specular_color, 
            float m_shininess, 
            std::shared_ptr<Texture> ambient_map,
            std::shared_ptr<Texture> diffuse_map,
            std::shared_ptr<Texture> specular_map,
            std::shared_ptr<Texture> normal_map
        ); 
        ~Material() = default;

        void setAmbientMap(const std::shared_ptr<Texture>& map) { m_ambient_map = map; }
        void setDiffuseMap(const std::shared_ptr<Texture>& map) { m_diffuse_map = map; }
        void setSpecularMap(const std::shared_ptr<Texture>& map) { m_specular_map = map; }
        void setNormalMap(const std::shared_ptr<Texture>& map) { m_normal_map = map; }

        void bind(Shader &shader);

    private:
        std::string m_id;

        glm::vec3 m_ambient_color;
        glm::vec3 m_diffuse_color;
        glm::vec3 m_specular_color;
        float m_shininess;

        std::shared_ptr<Texture> m_ambient_map;
        std::shared_ptr<Texture> m_diffuse_map;
        std::shared_ptr<Texture> m_specular_map;
        std::shared_ptr<Texture> m_normal_map;
    };

}