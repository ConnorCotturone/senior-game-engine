// Copyright © 2024 Jacob Curlin

#include "texture.h"
#include "../utility/logging.h"
#include "stb/stb_image.h"

namespace cgx::graphics
{
    Texture::Texture(std::string id, uint32_t width, uint32_t height, uint32_t num_channels, GLenum format, unsigned char* pixels)
        : m_id(id)
        , m_width(width)
        , m_height(height)
        , m_num_channels(num_channels)
        , m_format(format) 
        , m_pixels(pixels)
    {
        Initialize();
    }

    Texture::~Texture() 
    {
        glDeleteTextures(1, &m_texture_id);
        stbi_image_free(m_pixels);
    }

    void Texture::Initialize()
    {
        glGenTextures(1, &m_texture_id);
        glBindTexture(GL_TEXTURE_2D, m_texture_id);
        glTexImage2D(GL_TEXTURE_2D, 0, m_format, m_width, m_height, 0, m_format, GL_UNSIGNED_BYTE, m_pixels);

        glBindTexture(GL_TEXTURE_2D, 0);    // unbind texture

        SetTextureFilter(TextureFilter::Linear);
    }

    void Texture::Bind(uint32_t slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot); 
        glBindTexture(GL_TEXTURE_2D, m_texture_id);
    }

    void Texture::SetTextureFilter(TextureFilter filter)
    {
        m_filter = filter;

        glBindTexture(GL_TEXTURE_2D, m_texture_id);
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