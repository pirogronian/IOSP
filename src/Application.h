
#pragma once

#include <irrlicht.h>

#include <Utils/InputKeyActionManager.h>
#include <Simulation.h>

namespace IOSP
{
    class Application : public irr::IEventReceiver
    {
    public:
        enum Actions
        {
            TimeFaster = 1,
            TimeSlower
        };
    protected:
        irr::IrrlichtDevice *m_dev{nullptr};
        irr::video::IVideoDriver *m_drv{nullptr};
        irr::scene::ISceneManager *m_smgr{nullptr};
        irr::gui::IGUIEnvironment *m_gui{nullptr};
        Simulation *m_simulation{nullptr};
        irr::gui::IGUIStaticText *m_guiRunStats{nullptr};
        SimpleInputKeyTriggeredActionManager m_trKeyActions;
    public:
        Application();
        ~Application();
        irr::IrrlichtDevice *device() { return m_dev; }
        const irr::IrrlichtDevice *device() const { return m_dev; }
        Simulation *simulation() { m_simulation; }
        const Simulation *simulation() const { m_simulation; }
        void setSimulation(Simulation *s) { m_simulation = s; }
        bool OnEvent(const irr::SEvent&) override;
        void run();
    };
}
