// Copyright © 2024 Jacob Curlin

#include "gui/imgui_performance_window.h"

namespace cgx::gui
{

    ImGuiPerformanceWindow::ImGuiPerformanceWindow(cgx::core::Time& time)
        : ImGuiWindow("Performance")
        , UpdateTimeBase(time)
    {}

    void ImGuiPerformanceWindow::OnBegin()
    {
        // any pre-render logic (note: ImGui::Begin() has been called by the ImGuiWindow() base class)
    }

    void ImGuiPerformanceWindow::OnEnd()
    {
        // any post-render implementation (note: ImGui::End() has been called by the ImGuiWindow() base class)
    }

    void ImGuiPerformanceWindow::Render()
    {
        ImGui::Text("Frame Time: %.3f ms", m_last_frame_time * 1000.0); // Convert to milliseconds
        ImGui::Text("Current FPS: %u", m_current_fps);
        ImGui::Text("Average FPS: %u", m_average_fps);
        ImGui::Text("Average Frame Time: %u ms", m_average_frame_time);
        ImGui::Text("Total Uptime: %.2f seconds", m_total_uptime);
        ImGui::Text("Total Frames Rendered: %llu", m_total_frame_count);
    }

    void ImGuiPerformanceWindow::Update(const cgx::core::TimeContext& context)
    {
        // calculate/update display m_current_fps, m_last_frame_time, m_average_fps, m_average_frame_time,
        // m_total_uptime, m_total_frame_count

        m_last_frame_time = context.frame_time;
        m_current_fps = (context.frame_time > 0) ? static_cast<uint32_t>(1.0 / context.frame_time) : 0;

        m_average_fps = m_current_fps;
        m_average_frame_time = static_cast<uint32_t>(m_last_frame_time * 1000);

        m_total_uptime = context.time;
        m_total_frame_count = context.frame_number;
    }
}