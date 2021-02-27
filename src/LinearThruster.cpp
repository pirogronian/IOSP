
#include <BulletBodySceneNode.h>

#include "LinearThruster.h"

using namespace IOSP;
using namespace irr;

void LinearThruster::update(BulletBodySceneNode *node, u32 dtime)
{
    node->applyForceLocal(m_transform * m_vector * m_effectiveThrust);
    Component::update(node, dtime);
}
