
#pragma once

#include <irrlicht.h>

namespace IOSP
{
    class IntervalTimer
    {
    protected:
        irr::u32 m_lastTime{0};
        irr::u32 m_interval{0};
    public:
        IntervalTimer() = default;
        IntervalTimer(irr::u32 i) : m_interval(i) {}
        irr::u32 getInterval() const { return m_interval; }
        void setInterval(irr::u32 i) { m_interval = i; }
        bool update(irr::u32 ctime);
    };
}
