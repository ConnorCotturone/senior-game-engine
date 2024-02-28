// Copyright © 2024 Jacob Curlin

#include "../include/cubemap.h"
#include <glad/glad.h>
#include <stb/stb_image.h>

namespace cgx::graphics
{
    Cubemap::Cubemap(std::vector<std::string> face_paths, std::shared_ptr<Shader> shader)
        : m_vertices(s_cube_vertices)
        , m_shader(shader)
    {
        m_texture_id = loadCubemap(face_paths);

        CGX_INFO("Size of cubemap.m_vertices: {}", sizeof(m_vertices));
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), &m_vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

        const int skybox_texture_unit = 11;
        m_shader->use();
        m_shader->setInt("skybox", skybox_texture_unit);

    }

    Cubemap::~Cubemap()
    {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
    }

    void Cubemap::Draw(glm::mat4 view, glm::mat4 proj)
    {
        glDepthFunc(GL_LEQUAL);
        m_shader->use();
        glm::mat4 new_view = glm::mat4(glm::mat3(view));
        m_shader->setMat4("view", new_view);
        m_shader->setMat4("proj", proj);

        glBindVertexArray(m_VAO);
        glActiveTexture(GL_TEXTURE11);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture_id);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS);
    }


    uint32_t Cubemap::loadCubemap(std::vector<std::string> faces)
    {
        uint32_t texture_id;
        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);

        int width, height, num_components;
        for (size_t i = 0; i < faces.size(); i++)
        {
            unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &num_components, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                stbi_image_free(data);
            }
            else
            {
                CGX_ERROR("Cubemap texture failed to load at path: {} ", faces[i]);
                stbi_image_free(data);
            }
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        CGX_INFO("Cubemap Texture ID: {}", texture_id);
        return texture_id;
    }






}