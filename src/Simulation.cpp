
#include "Simulation.h"

using namespace IOSP;

bool IOSP::Simulation::addWorld(BulletWorldSceneNode *w)
{
    if (m_worlds.addItem(w))
    {
        w->bulletWorld().setDebugDrawer(&m_ddrawer);
        return true;
    }
    return false;
}

bool IOSP::Simulation::removeWorld(BulletWorldSceneNode *w)
{
    if (m_worlds.size() == 0)  return false;
    for (auto it = m_worlds.begin(); it != m_worlds.end(); it++)
    {
        if (*it == w)
        {
            m_worlds.erase(it);
            w->bulletWorld().setDebugDrawer(nullptr);
            return true;
        }
    }
    return false;
}

bool IOSP::Simulation::hasWorld(const BulletWorldSceneNode *w) const
{
    return m_worlds.hasItem(w);
}

void IOSP::Simulation::stepSimulation(btScalar d)
{
    for (auto &w : m_worlds)
        w->stepSimulation(d);
}

void IOSP::Simulation::drawDebug()
{
    auto *drv = m_idevice->getVideoDriver();
    drv->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());
    for (auto &world : m_worlds)
        world->bulletWorld().debugDrawWorld();
}
