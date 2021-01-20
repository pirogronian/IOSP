
#pragma once

#include <irrlicht.h>
#include <Utils/LinkedList.h>
#include <BulletWorldSceneNode.h>
#include <BulletDebugDrawer.h>

namespace IOSP
{
    class Simulation
    {
        irr::IrrlichtDevice *m_idevice;
        LinkedPtrList<BulletWorldSceneNode> m_worlds;
        BulletDebugDrawer m_ddrawer;
    public:
        Simulation(irr::IrrlichtDevice *d) : m_idevice{d}, m_ddrawer{m_idevice->getVideoDriver()} {}
        bool addWorld(BulletWorldSceneNode *);
        bool removeWorld(BulletWorldSceneNode *);
        bool hasWorld(const BulletWorldSceneNode *) const;
        void stepSimulation(btScalar);
        void drawDebug();
        BulletDebugDrawer& debugDrawer() { return m_ddrawer; }
        const BulletDebugDrawer& debugDrawer() const { return m_ddrawer; }
    };
}
