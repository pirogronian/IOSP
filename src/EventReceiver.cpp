
#include <cstdio>

#include <EventReceiver.h>

using namespace IOSP;

using namespace irr;

bool EventReceiver::OnEvent(const SEvent& event)
{
    if (m_simulation)  return m_simulation->OnEvent(event);
//     std::puts("Simulation not set");
    return false;
}
