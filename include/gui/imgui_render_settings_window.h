// Copyright © 2024 Jacob Curlin

#pragma once

#include "core/common.h"
#include "gui/imgui_window.h"


namespace cgx::gui
{
    // temporarily defining this here, to be removed / properly implemented
    struct RenderSettings
    {
        bool msaa;      // multisampled anti-alisasing 
        bool skybox;    // skybox
    };

    class ImGuiRenderSettingsWindow : public ImGuiWindow
    {
    public:
        ImGuiRenderSettingsWindow(std::shared_ptr<RenderSettings> settings);

        void Render() override;

    private:
        std::shared_ptr<RenderSettings> m_render_settings;

    };





}