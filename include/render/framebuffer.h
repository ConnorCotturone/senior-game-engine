// Copyright © 2024 Jacob Curlin

// source: (yt:progrematic) https://www.youtube.com/watch?v=czQpF0Q7cgo

#pragma once

#include "core/common.h"
#include "glad/glad.h"

namespace cgx::render
{
    class Framebuffer
    {
    public:
        Framebuffer(uint32_t width, uint32_t height);
        ~Framebuffer();

        [[nodiscard]] inline uint32_t getFBO() const { return m_FBO; }
        [[nodiscard]] inline uint32_t getTextureID() const { return m_texture_id; }
        [[nodiscard]] inline uint32_t getRenderBufferID() const { return m_render_buffer_id; }

        inline void getSize(uint32_t& width, uint32_t& height) const { width = m_width; height = m_height; }

        inline void setClearColor(float r, float g, float b, float a) { m_CCR = r; m_CCG = g; m_CCB = b; m_CCA = a; }
        inline void getClearColor(float& r, float& g, float& b, float& a) const { r = m_CCR; g = m_CCG; b = m_CCB; a = m_CCA; }

    private:
        GLuint m_FBO;
        GLuint m_texture_id;
        GLuint m_render_buffer_id;

        GLsizei m_width;
        GLsizei m_height;
        float m_CCR, m_CCG, m_CCB, m_CCA;
    };
}