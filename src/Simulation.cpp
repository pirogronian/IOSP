
#include <cstdio>

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

void IOSP::Simulation::init()
{
    m_timeCurrent = getTimer()->getTime();
}

void IOSP::Simulation::stepSimulation(irr::u32 d)
{
    for (auto &w : m_worlds)
        w->update(d);

    if (m_activePanel)
        m_activePanel->update();
}

void IOSP::Simulation::update()
{
    m_timeLast = m_timeCurrent;
    m_timeCurrent = getTimer()->getTime();
    m_timeLastDelta = m_timeCurrent - m_timeLast;
    stepSimulation(m_timeMult * m_timeLastDelta);
}

void IOSP::Simulation::drawDebug()
{
    auto *drv = getVideoDriver();
    drv->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());
    for (auto &world : m_worlds)
        world->bulletWorld().debugDrawWorld();
}

void IOSP::Simulation::setActivePanel(ControlPanelSceneNode *p)
{
    if (m_activePanel == p)  return;
    if (m_activePanel)
        m_activePanel->drop();
    m_activePanel = p;
    m_activePanel->grab();
}

bool IOSP::Simulation::OnEvent(const irr::SEvent& event)
{
    if (m_activePanel)  return m_activePanel->OnEvent(event);
//     std::puts("No active control panel!");
    return false;
}
