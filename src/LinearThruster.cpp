
#include <BulletBodySceneNode.h>

#include "LinearThruster.h"

using namespace IOSP;
using namespace irr;

void LinearThruster::update(u32 dtime)
{
    m_node->applyForceLocal(m_transform * m_vector * m_effectiveThrust);
    Component::update(dtime);
}
