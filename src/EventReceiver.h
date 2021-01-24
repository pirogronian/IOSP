
#pragma once

#include <irrlicht.h>

#include <Utils/InputKeyActionManager.h>
#include <Simulation.h>

namespace IOSP
{
    class EventReceiver : public irr::IEventReceiver
    {
    public:
        enum Actions
        {
            TimeFaster = 1,
            TimeSlower
        };
    protected:
        Simulation *m_simulation{nullptr};
        SimpleInputKeyTriggeredActionManager m_trKeyActions;
    public:
        EventReceiver();
        Simulation *simulation() { m_simulation; }
        const Simulation *simulation() const { m_simulation; }
        void setSimulation(Simulation *s) { m_simulation = s; }
        bool OnEvent(const irr::SEvent&) override;
    };
}
