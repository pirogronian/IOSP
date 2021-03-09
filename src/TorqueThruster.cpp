
#include <BulletBodySceneNode.h>
#include "TorqueThruster.h"

using namespace IOSP;
using namespace irr;

void TorqueThruster::update(u32 dtime)
{
    m_node->applyTorqueLocal(m_vector * m_effectiveThrust);
    Component::update(dtime);
}
