
#include "BulletMotionState.h"

#include <Conversions.h>

using namespace IOSP;

void IOSP::BulletMotionState::getWorldTransform(btTransform& tr) const
{
    tr.setOrigin(toBullet(m_node.getPosition()));
    tr.setRotation(toBulletQuaternion(degToRad(m_node.getRotation())));
}

void IOSP::BulletMotionState::setWorldTransform(const btTransform& tr)
{
    m_node.setPosition(fromBullet(tr.getOrigin()));
    m_node.setRotation(radToDeg(toIrrlichtVector(tr.getRotation())));
    m_node.updateAbsolutePosition();
}
