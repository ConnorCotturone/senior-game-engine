// jacob curlin
// texture.h
// 02/02/2024

// src: https://github.com/progrematic/hippo/blob/master/hippo/include/hippo/graphics/texture.h

#ifndef TEXTURE_H
#define TEXTURE_H


#include "glad/glad.h"

#include <string>
#include <cstdint>

namespace cgx::graphics
{
    enum class TextureFilter
    {
        Nearest,
        Linear
    };

    class Texture
    {
    public:
        Texture(std::string id, uint32_t width, uint32_t height, uint32_t num_channels, GLenum format, unsigned char* pixels); 
        ~Texture();

        void Initialize();
        void Bind(uint32_t slot) const;

        inline std::string GetID() const { return m_id; }
        inline uint32_t GetWidth() const { return m_width; }
        inline uint32_t GetHeight() const { return m_height; }
        inline uint32_t GetNumChannels() const { return m_num_channels; }


        inline TextureFilter GetTextureFilter() const { return m_filter; }
        void SetTextureFilter(TextureFilter filter);

    private:

        std::string m_id;
        uint32_t m_width; 
        uint32_t m_height;
        uint32_t m_num_channels;
        uint32_t m_texture_id;

        unsigned char* m_pixels;
        GLenum m_format;


        TextureFilter m_filter;
    };
}

#endif // TEXTURE_H