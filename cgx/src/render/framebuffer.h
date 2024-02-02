// jacob curlin
// framebuffer.h
// 01/30/2024

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <cstdint>


namespace cgx::graphics
{
    class Framebuffer
    {
    public:

        Framebuffer(uint32_t width, uint32_t height);
        ~Framebuffer();

        uint32_t GetFbo() const;
        uint32_t GetTextureId() const;
        uint32_t GetRenderbufferId() const;

        void GetSize(uint32_t& width, uint32_t& height);
        void SetClearColor(float r, float g, float b, float a);
        void GetClearColor(float& r, float& g, float& b, float& a);

    private:
        uint32_t m_fbo;
        uint32_t m_textureId;
        uint32_t m_renderbufferId;

        uint32_t m_width;
        uint32_t m_height;
        float m_CCR;
        float m_CCG;
        float m_CCB;
        float m_CCA;
    };
}

#endif // FRAMEBUFFER_H