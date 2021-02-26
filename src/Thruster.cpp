
#include <cassert>

#include <BulletBodySceneNode.h>

#include "Thruster.h"

using namespace irr;
using namespace IOSP;

Thruster::Thruster(const btVector3& vec, btScalar maxThr)
{
    m_vector = vec.normalized();
    assert(maxThr >= 0);
    m_maxThrust = maxThr;
}

void Thruster::updateEffectiveThrust()
{
    if (isOn())
        m_effectiveThrust = m_setThrust;
    else m_effectiveThrust = 0;
}

void Thruster::setOn(bool on)
{
    m_on = on;
    updateEffectiveThrust();
}

void Thruster::setThrust(btScalar t)
{
    if (t >= 0)
        m_setThrust = std::max(t, m_maxThrust);
    updateEffectiveThrust();
}

void Thruster::update(BulletBodySceneNode *node, u32 dtime)
{
    node->applyForceLocal(m_transform * m_vector * m_effectiveThrust);
    Component::update(node, dtime);
}
