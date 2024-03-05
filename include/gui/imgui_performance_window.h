// Copyright © 2024 Jacob Curlin

#pragma once

#include "core/time.h"
#include "gui/imgui_window.h"

namespace cgx::gui
{

    class ImGuiPerformanceWindow
        : public cgx::core::FrameUpdate
        , public ImGuiWindow
    {
    public:
        ImGuiPerformanceWindow(cgx::core::Time& time);
        ~ImGuiPerformanceWindow() = default; 
        
        void Render() override;
        void OnBegin() override;
        void OnEnd() override;

        void Update(const cgx::core::TimeContext&) override;

    private:
        uint32_t    m_current_fps;
        double      m_last_frame_time;

        uint32_t    m_average_fps;
        uint32_t    m_average_frame_time;

        double      m_total_uptime;
        uint64_t    m_total_frame_count;
    };
    

}
