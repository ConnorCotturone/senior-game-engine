// Copyright © 2024 Jacob Curlin

#pragma once

#include "core/common.h"
#include "gui/imgui_window.h"
#include "render/framebuffer.h"
#include <glad/glad.h>
#include <imgui.h>

namespace cgx::gui
{

    class ImGuiRenderWindow : public ImGuiWindow
    {
    public:
        explicit ImGuiRenderWindow(std::shared_ptr<cgx::render::Framebuffer> framebuffer);  
        virtual ~ImGuiRenderWindow() override;

        void Render() override;
        void OnBegin() override;
        void OnEnd() override;

    protected:
        std::shared_ptr<cgx::render::Framebuffer> m_framebuffer;
        
        float m_texture_size[2];

        GLuint m_texture_id;
    };

}