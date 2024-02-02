// jacob curlin
// texture.h
// 02/02/2024

// src: https://github.com/progrematic/hippo/blob/master/hippo/include/hippo/graphics/texture.h

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <cstdint>

namespace cgx::rendering
{

    enum class TextureFilter
    {
        Nearest,
        Linear
    };

    class Texture
    {
    public:
        Texture(const std::string& path);
        ~Texture();

        inline uint32_t GetID() const { return m_id; }
        inline uint32_t GetWidth() const { return m_width; }
        inline uint32_t GetHeight() const { return m_height; }
        inline uint32_t GetNumChannels() const { return m_num_channels; }
        inline const std::string& GetPath() const { return m_path; }
        inline TextureFilter GetTextureFilter() const { return m_filter; }

        void Bind(uint32_t slot) const;
        void Unbind();

        void SetTextureFilter(TextureFilter filter);

    private:
        void LoadTexture();

    private:
        TextureFilter m_filter;

        std::string m_path;
        uint32_t m_id;
        uint32_t m_width; 
        uint32_t m_height;
        uint32_t m_num_channels;

        unsigned char* m_pixels;

    };
}

#endif // TEXTURE_H