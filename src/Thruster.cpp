
#include <cassert>

#include "Thruster.h"

using namespace irr;
using namespace IOSP;

void Thruster::copyFrom(const Thruster& other)
{
    Component::copyFrom(other);
    m_vector = other.m_vector;
    m_maxThrust = other.m_maxThrust;
    m_setThrust = other.m_setThrust;
    m_effectiveThrust = other.m_effectiveThrust;
    m_allowNeg = other.m_allowNeg;
    m_on = other.m_on;
}

Thruster::Thruster(const btVector3& vec, btScalar maxThr, bool allowNeg)
{
    m_allowNeg = allowNeg;
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
    if (t < 0)
    {
        if (m_allowNeg)
            m_setThrust = std::max(t, -m_maxThrust);
        else
            m_setThrust = 0;
    }
    else
        m_setThrust = std::min(t, m_maxThrust);
    updateEffectiveThrust();
}
