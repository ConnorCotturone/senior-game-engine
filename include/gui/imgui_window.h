// Copyright © 2024 Jacob Curlin

#pragma once

#include <imgui.h>
#include <string>

namespace cgx::gui
{
    class ImGuiWindow
    {
    public:
        ImGuiWindow(const std::string& title, 
                    std::uint32_t min_width = 150, std::uint32_t min_height = 200, 
                    std::uint32_t max_width = 1920, std::uint32_t max_height = 1920)
            : m_title(title)
            , m_active(true) 
            , m_min_size(ImVec2(static_cast<float>(min_width), static_cast<float>(min_height)))
            , m_max_size(ImVec2(static_cast<float>(max_width), static_cast<float>(max_height))) {}

        virtual ~ImGuiWindow() = default;

        void RenderFrame();
        virtual void Render() = 0;

        void ToggleVisibility() { m_active = !m_active; }
        void Show() { m_active = true; }
        void Hide() { m_active = false; }

        [[nodiscard]] std::string& getTitle() { return m_title; }
        [[nodiscard]] bool isActive() { return m_active; }

        void setMinSize(std::uint32_t width, std::uint32_t height) 
        { 
            m_min_size = ImVec2(static_cast<float>(width), static_cast<float>(height));
        }
        void setMaxSize(std::uint32_t width, std::uint32_t height)
        {
            m_max_size = ImVec2(static_cast<float>(width), static_cast<float>(height));
        }

        void getMinSize(std::uint32_t& width, std::uint32_t& height)
        {
            width = static_cast<std::uint32_t>(m_min_size.x);
            height = static_cast<std::uint32_t>(m_min_size.y);
        }
        void getMaxSize(std::uint32_t& width, std::uint32_t& height)
        {
            width = static_cast<std::uint32_t>(m_max_size.x);
            height = static_cast<std::uint32_t>(m_max_size.y);
        }

    protected:
        std::string m_title;
        bool        m_active;
        ImVec2      m_min_size;
        ImVec2      m_max_size;
    };
}