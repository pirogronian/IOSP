
#pragma once

#include <irrlicht.h>

#include <Simulation.h>

namespace IOSP
{
    class EventReceiver : public irr::IEventReceiver
    {
        Simulation *m_simulation{nullptr};
    public:
        Simulation *simulation() { m_simulation; }
        const Simulation *simulation() const { m_simulation; }
        void setSimulation(Simulation *s) { m_simulation = s; }
        bool OnEvent(const irr::SEvent&) override;
    };
}
