// Copyright © 2024 Jacob Curlin

#include "core/common.h"
#include "render/framebuffer.h"


namespace cgx::render
{

    Framebuffer::Framebuffer(uint32_t width, uint32_t height)
        : m_FBO(0)
        , m_texture_id(0)
        , m_render_buffer_id(0)
        , m_width(static_cast<GLsizei>(width))
        , m_height(static_cast<GLsizei>(height))
        , m_CCR(1)
        , m_CCG(1)
        , m_CCB(1)
        , m_CCA(1)
    {
        glGenFramebuffers(1, &m_FBO);  
        glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

        // create color texture
        glGenTextures(1, &m_texture_id);
        glBindTexture(GL_TEXTURE_2D, m_texture_id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture_id, 0);   // attach color texture

        // create depth/stencil renderbuffer
        glGenRenderbuffers(1, &m_render_buffer_id);
        glBindRenderbuffer(GL_RENDERBUFFER, m_render_buffer_id);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_render_buffer_id);

        // check for completeness
        int32_t complete_status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (complete_status != GL_FRAMEBUFFER_COMPLETE)
        {
            CGX_ERROR("Failure to create framebuffer. Complete status: {}", complete_status);
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    Framebuffer::~Framebuffer()
    {
        glDeleteFramebuffers(1, &m_FBO);
        m_FBO = 0;
        m_texture_id = 0;
        m_render_buffer_id = 0;
    }    
}