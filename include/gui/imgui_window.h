// Copyright © 2024 Jacob Curlin

#pragma once

#include <imgui.h>
#include <string>

namespace cgx::gui
{
    class ImGuiWindow
    {
    public:
        ImGuiWindow(const std::string& title)
            : m_title(title)
            , m_is_visible(true) {}

        virtual ~ImGuiWindow() = default;

        virtual void Render() = 0;

        [[nodiscard]] std::string& getTitle() { return m_title; }
        [[nodiscard]] bool isVisible() { return m_is_visible; }


    protected:
        std::string m_title;
        bool        m_is_visible;
    };
}