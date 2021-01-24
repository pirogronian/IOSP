
#include <cstdio>

#include <EventReceiver.h>

using namespace IOSP;

using namespace irr;

EventReceiver::EventReceiver()
{
    m_trKeyActions.bind(TimeFaster, irr::KEY_PRIOR);
    m_trKeyActions.bind(TimeSlower, irr::KEY_NEXT);
}

bool EventReceiver::OnEvent(const SEvent& event)
{
    if (m_simulation)
    {
        if (m_simulation->OnEvent(event))  return true;
    }
//     if (event.EventType == irr::EET_KEY_INPUT_EVENT)
//     {
//         if (event.KeyInput.PressedDown)
//             std::printf("Pressed key: %i\n", event.KeyInput.Key);
//     }
    if (m_trKeyActions.OnEvent(event))
    {
        if (m_trKeyActions.isTriggered(TimeFaster))  m_simulation->setTimeMultiplier(m_simulation->timeMultiplier() + 1);
        if (m_trKeyActions.isTriggered(TimeSlower))  m_simulation->setTimeMultiplier(m_simulation->timeMultiplier() - 1);
            m_trKeyActions.reset();
        return true;
    }

    return false;
}
