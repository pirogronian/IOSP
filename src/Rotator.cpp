
#include <BulletBodySceneNode.h>
#include "Rotator.h"

using namespace IOSP;
using namespace irr;

void Rotator::update(BulletBodySceneNode *node, u32 dtime)
{
    node->applyTorqueLocal(m_vector * m_effectiveThrust);
    Component::update(node, dtime);
}
