
#pragma once

#include <Thruster.h>

namespace IOSP
{
    class Rotator : public Thruster
    {
    public:
        Rotator(const btVector3 &axis, btScalar max) : Thruster(axis, max) {}
        void update(BulletBodySceneNode *, irr::u32) override;
    };
}
