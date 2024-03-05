// Copyright © 2024 Jacob Curlin

#include "core/time.h"

namespace cgx::core
{

    UpdateTimeBase::UpdateTimeBase(Time& time)
        : m_time(time)
    {}

    UpdateTimeBase::~UpdateTimeBase() noexcept = default;

    FixedStepUpdate::FixedStepUpdate()
    {
        m_time.RegisterFixedStepUpdate(this);
    }

    FixedStepUpdate::~FixedStepUpdate() noexcept
    {
        m_time.UnregisterFixedStepUpdate(this);
    }

    FrameUpdate::FrameUpdate()
    {
        m_time.RegisterFrameUpdate(this);
    }

    FrameUpdate::~FrameUpdate() noexcept
    {
        m_time.UnregisterFrameUpdate(this);
    }

    void Time::RegisterFixedStepUpdate(FixedStepUpdate* entry)
    {
        m_fixed_step_updates.push_back(entry);
    }

    void Time::UnregisterFixedStepUpdate(FixedStepUpdate* entry)
    {
        m_fixed_step_updates.erase(
            std::remove(m_fixed_step_updates.begin(), m_fixed_step_updates.end(), entry), 
            m_fixed_step_updates.end());
    }

    void Time::RegisterFrameUpdate(FrameUpdate* entry)
    {
        m_frame_updates.push_back(entry);
    }

    void Time::UnregisterFrameUpdate(FrameUpdate* entry)
    {
        m_frame_updates.erase(
            std::remove(m_frame_updates.begin(), m_frame_updates.end(), entry), 
            m_frame_updates.end());
    }

    void Time::Start()
    {
        m_current_time = std::chrono::steady_clock::now();
    }

    void Time::Update()
    {
        const auto new_time = std::chrono::steady_clock::now();
        const auto duration = new_time - m_current_time;
        
        // std::chrono::duration < Rep, Period > (ticks)
        // > Rep    : arithmetic type representing number of ticks
        // > Period : std::ratio representing (# seconds fractions / tick)
        double frame_time = std::chrono::duration<double, std::ratio<1>>(duration).count();

        if (frame_time > 0.25)  { m_time_accumulator += 0.25; }
        else                    { m_time_accumulator += frame_time; }

        m_current_time = new_time;
        m_time_accumulator += frame_time;

        const double dt = 1.0 / 100.0;

        while (m_time_accumulator >= dt)
        {
            UpdatePerFixedStep(
                TimeContext{
                    .dt             = dt,
                    .frame_time     = frame_time,
                    .time           = m_time,
                    .frame_number   = m_frame_number
                }
            );
            m_time_accumulator -= dt;
            m_time += dt;
        }

        m_last_update = TimeContext {
            .dt             = dt,
            .frame_time     = frame_time,
            .time           = m_time,
            .frame_number   = m_frame_number
        };
        UpdatePerFrame();
    }

    void Time::UpdatePerFixedStep(const TimeContext& time_context)
    {
        for (auto* entry : m_fixed_step_updates)
        {
            entry->Update(time_context);
        }
    }

    void Time::UpdatePerFrame()
    {
        for (auto* entry : m_frame_updates)
        {
            entry->Update(m_last_update);
        }
        ++m_frame_number;
    }

    uint64_t Time::getFrameNumber() const
    {
        return m_frame_number;
    }

    double Time::getTime()
    {
        return m_time;
    }

    TimeContext& Time::getLastUpdate()
    {
        return m_last_update;
    }

}
