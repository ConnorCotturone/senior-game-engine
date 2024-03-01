// Copyright © 2024 Jacob Curlin

#pragma once

#include "gui/i_imgui_window.h"
#include <glad/glad.h>
#include <imgui.h>

namespace cgx::gui
{

    class ImGuiViewportWindow : public IImguiWindow
    {
    public:
        ImGuiViewportWindow();  
        virtual ~ImGuiViewportWindow() override;

    protected:
        void DrawContents() override;

        GLuint m_texture_id;
        float m_view_width;
        float m_view_height;
    };

}