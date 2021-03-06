
#pragma once

#include <btBulletDynamicsCommon.h>

namespace IOSP
{
    btCollisionObject &copyFrom(btCollisionObject&, btCollisionObject&);
    btRigidBody &copyFrom(btRigidBody&, btRigidBody&);
}
