// jacob curlin
// framebuffer.cpp
// 01/30/2024


#include "framebuffer.h"

#include "glad/glad.h"
#include "../utility/logging.h"


namespace cgx::graphics
{
    Framebuffer::Framebuffer(uint32_t width, uint32_t height) :
        m_fbo(0),
        m_textureId(0),
        m_renderbufferId(0),
        m_width(width),
        m_height(height),
        m_CCR(1),
        m_CCG(1),
        m_CCB(1),
        m_CCA(1)
    {
        glGenFramebuffers(1, &m_fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

        // create color texture
        glGenTextures(1, &m_textureId);
        glBindTexture(GL_TEXTURE_2D, m_textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glBindTexture(GL_TEXTURE_2D, 0);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureId, 0);  

        // Create depth/stencil renderbuffer
        glGenRenderbuffers(1, &m_renderbufferId);
        glBindRenderbuffer(GL_RENDERBUFFER, m_renderbufferId);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderbufferId);

        int32_t completeStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (completeStatus != GL_FRAMEBUFFER_COMPLETE)
        {
            PHX_ERROR("Failure to create framebuffer. Complete status: {}", completeStatus)
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    Framebuffer::~Framebuffer()
    {
        glDeleteFramebuffers(1, &m_fbo);
        m_fbo = 0;
        m_textureId = 0;
        m_renderbufferId = 0;
    }

    uint32_t Framebuffer::GetFbo() const
    {
        return m_fbo;
    }

    uint32_t Framebuffer::GetTextureId() const
    {
        return m_textureId;
    }

    uint32_t Framebuffer::GetRenderbufferId() const
    {
        return m_renderbufferId;
    }

    void Framebuffer::GetSize(uint32_t& width, uint32_t& height)
    {
        width = m_width;
        height = m_height;
    }

    void Framebuffer::SetClearColor(float r, float g, float b, float a)
    {
        m_CCR = r; 
        m_CCG = g;
        m_CCB = b;
        m_CCA = a;
    }

    void Framebuffer::GetClearColor(float& r, float& g, float& b, float& a)
    {
        r = m_CCR;
        g = m_CCG;
        b = m_CCB;
        a = m_CCA;
    }





}