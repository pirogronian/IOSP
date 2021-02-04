
#include "IntervalTimer.h"

using namespace irr;
using namespace IOSP;

bool IOSP::IntervalTimer::update(u32 ctime)
{
    if (ctime - m_lastTime > m_interval)
    {
        m_lastTime = ctime;
        return true;
    }
    return false;
}
