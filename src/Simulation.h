
#pragma once

#include <irrlicht.h>
#include <Utils/LinkedList.h>
// #include <Utils/AutoIndexer.h>
#include <BulletWorldSceneNode.h>
#include <BulletDebugDrawer.h>
#include <ControlPanelSceneNode.h>
// #include <Updatable.h>

namespace IOSP
{
    class Simulation : public irr::IEventReceiver
    {
        irr::IrrlichtDevice *m_idev;
        LinkedPtrList<BulletWorldSceneNode> m_worlds;
        BulletDebugDrawer m_ddrawer;
        ControlPanelSceneNode *m_activePanel{nullptr};
        irr::u32 
            m_timeMult{1},
            m_timeLast{0},
            m_timeCurrent{0},
            m_timeLastDelta{0},
            m_timePassed{0},
            m_maxTimeMult{100};
    public:
        Simulation(irr::IrrlichtDevice *d) : m_idev{d}, m_ddrawer{m_idev->getVideoDriver()} {}
        bool addWorld(BulletWorldSceneNode *);
        bool removeWorld(BulletWorldSceneNode *);
        bool hasWorld(const BulletWorldSceneNode *) const;
        void init();
        void stepSimulation(btScalar);
        void update();
        void drawDebug();
        BulletDebugDrawer& debugDrawer() { return m_ddrawer; }
        const BulletDebugDrawer& debugDrawer() const { return m_ddrawer; }
        ControlPanelSceneNode *activePanel() { return m_activePanel; }
        const ControlPanelSceneNode *activePanel() const { return m_activePanel; }
        void setActivePanel(ControlPanelSceneNode *);
        bool OnEvent(const irr::SEvent&) override;
        irr::u32 lastDelta() const { return m_timeLastDelta; }
        irr::u32 timeMultiplier() const { return m_timeMult; }
        void setTimeMultiplier(irr::u32 tm)
        {
            if (tm > m_maxTimeMult)  return;
            m_timeMult = tm;
        }
    };
}
