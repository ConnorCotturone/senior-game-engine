// Copyright © 2024 Jacob Curlin
// source: https://github.com/tksuoran/erhe/blob/aa0cc8dbd3edf0aea0f0f8a4512505a4eb6887f0/src/editor/time.hpp

#pragma once

#include "core/common.h"
#include <chrono>

namespace cgx::core
{
    class Time; // fwd. decl. 

    class TimeContext
    {
    public:
        double dt               = 0.0;
        double frame_time       = 0.0;
        double time             = 0.0;
        uint64_t frame_number   = 0;
    };

    class UpdateTimeBase
    {
    public:
        explicit UpdateTimeBase(Time& time);
        virtual ~UpdateTimeBase() noexcept;
    
    protected:
        Time& m_time;
    };

    class FixedStepUpdate : public virtual UpdateTimeBase
    {
    public:
        FixedStepUpdate();
        ~FixedStepUpdate() noexcept override;

        virtual void Update(const TimeContext&) = 0;
    };

    class FrameUpdate: public virtual UpdateTimeBase
    {
    public:
        FrameUpdate();
        ~FrameUpdate() noexcept override;

        virtual void Update(const TimeContext&) = 0;
    };

    class Time
    {
    public:
        [[nodiscard]] double getTime();
        uint64_t getFrameNumber() const;

        void Start();
        void Update();

        void UpdatePerFixedStep(const TimeContext& time_context);
        void UpdatePerFrame();

        void RegisterFixedStepUpdate(FixedStepUpdate* entry);
        void UnregisterFixedStepUpdate(FixedStepUpdate* entry);
        void RegisterFrameUpdate(FrameUpdate* entry);
        void UnregisterFrameUpdate(FrameUpdate* entry);

        TimeContext& getLastUpdate(); 

    private:
        std::chrono::steady_clock::time_point   m_current_time;

        double          m_time_accumulator  = 0.0;
        double          m_time              = 0.0;
        uint64_t        m_frame_number      = 0;
        TimeContext     m_last_update;

        std::vector<FixedStepUpdate*>        m_fixed_step_updates;
        std::vector<FrameUpdate*>            m_frame_updates;
    };
}