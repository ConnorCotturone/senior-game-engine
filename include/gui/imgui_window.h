// Copyright © 2024 Jacob Curlin
// source: https://github.com/tksuoran/erhe/blob/main/src/erhe/imgui/erhe_imgui/imgui_window.hpp

#pragma once

#include <imgui.h>
#include <string>

namespace cgx::gui
{
    class ImGuiWindow
    {
    public:
        ImGuiWindow(const std::string& title);
        virtual ~ImGuiWindow() = default;

        void Begin();                   // ImGui::Begin() called (start actual ImGui window)
        void End();                     // ImGui::End() called (end actual ImGui window)

        virtual void Render() = 0;      // child-defined, actual ImGui window UI logic
        virtual void OnBegin();         // child-defined operations before Begin() calls ImGui::Begin()
        virtual void OnEnd();           // child-defined operations before End() calls ImGui::End()

        void Show(); 
        void Hide(); 

        [[nodiscard]] const std::string& getTitle();
        [[nodiscard]] bool isVisible();

        void setMinSize(float width, float height); 
        void setMaxSize(float width, float height);

    protected:
        std::string m_title                 = "Window";
        bool        m_is_visible            = true;
        bool        m_is_hovered            = false;
        bool        m_enforce_aspect_ratio  = false;

        ImGuiWindowFlags m_window_flags;

        float       m_aspect_ratio{1};
        float       m_min_size[2]{240.0f, 180.0f};      // minimum window size
        float       m_max_size[2]{1920.0f, 1080.0f};    // maximum window size
    };
}