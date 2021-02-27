
#include <BulletBodySceneNode.h>
#include "TorqueThruster.h"

using namespace IOSP;
using namespace irr;

void TorqueThruster::update(BulletBodySceneNode *node, u32 dtime)
{
    node->applyTorqueLocal(m_vector * m_effectiveThrust);
    Component::update(node, dtime);
}
