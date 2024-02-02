// jacob curlin
// texture.cpp
// 02/02/2024

#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "glad/glad.h"

namespace cgx::rendering
{
    Texture::Texture(const std::string& path)
        : m_path(path)
        , m_width(0)
        , m_height(0)
        , m_num_channels(0)
        , m_pixels(nullptr)
        , m_filter(TextureFilter::Linear)
    {
        int width, height, num_channels;
        stbi_set_flip_vertically_on_load(1);
        m_pixels = stbi_load(path.c_str(), &width, &height, &num_channels, 0);
        if (m_pixels)
        {
            m_width = (uint32_t) width;
            m_height = (uint32_t) height;
            m_num_channels = (uint32_t) num_channels;
        }

        LoadTexture();
    }

    Texture::~Texture()
    {
        stbi_image_free(m_pixels);
        m_pixels = nullptr;
    }

    void Texture::Bind(uint32_t slot) const
    {
        glActiveTexture(GL_TEXTURE0); 
        glBindTexture(GL_TEXTURE_2D, m_id);
    }

    void Texture::Unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::LoadTexture()
    {
        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);

        GLenum data_format = 0;
        if (m_num_channels == 4)
        {
            data_format = GL_RGBA;
        }
        if (m_num_channels == 3)
        {
            data_format = GL_RGB;
        }
        if (m_pixels && data_format == 0)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, data_format, m_width, m_height, 0, data_format, GL_UNSIGNED_BYTE, m_pixels);
            SetTextureFilter(m_filter);
        }
        else
        {
            // checkerboard default pattern
            float pixels[] = {  
				1.f, 0.f, 1.f,		1.f, 1.f, 1.f,		1.f, 0.f, 1.f,		1.f, 1.f, 1.f,
				1.f, 1.f, 1.f,		1.f, 0.f, 1.f,		1.f, 1.f, 1.f,		1.f, 0.f, 1.f,
				1.f, 0.f, 1.f,		1.f, 1.f, 1.f,		1.f, 0.f, 1.f,		1.f, 1.f, 1.f,
				1.f, 1.f, 1.f,		1.f, 0.f, 1.f,		1.f, 1.f, 1.f,		1.f, 0.f, 1.f
			};    

            m_width = 4;
            m_height = 4;
            m_num_channels = 3;

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_FLOAT, pixels);
            SetTextureFilter(TextureFilter::Nearest);
        }
        glBindTexture(GL_TEXTURE_2D, 0);    // unbind texture
    }

    void Texture::SetTextureFilter(TextureFilter filter)
    {
        m_filter = filter;

        glBindTexture(GL_TEXTURE_2D, m_id);
        switch(m_filter)
        {
            case TextureFilter::Linear:
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                break;
            case TextureFilter::Nearest:
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                break;
        }
        glBindTexture(GL_TEXTURE_2D, 0);    // unbind texture
    }

}