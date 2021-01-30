
#include <cstdio>

#include "BulletMotionState.h"

#include <Conversions.h>

using namespace IOSP;

void IOSP::BulletMotionState::getWorldTransform(btTransform& tr) const
{
//     std::puts("getWorldTransform");
    tr = m_bTransform;
}

void IOSP::BulletMotionState::setWorldTransform(const btTransform& tr)
{
    m_bTransform = tr;
    m_node.setPosition(fromBullet(tr.getOrigin()));
    m_node.setRotation(radToDeg(toIrrlichtVector(tr.getRotation())));
    m_node.updateAbsolutePosition();
}
