
#pragma once

#include <btBulletDynamicsCommon.h>

namespace IOSP
{
    btCollisionObject &copyFrom(btCollisionObject&, btCollisionObject&);
    inline btCollisionObject *copyFrom(btCollisionObject *obj, btCollisionObject *other)
    {
        return &copyFrom(*obj, *other);
    }
    btRigidBody &copyFrom(btRigidBody&, btRigidBody&);
    inline btRigidBody *copyFrom(btRigidBody *obj, btRigidBody *other)
    {
        return &copyFrom(*obj, *other);
    }
}
