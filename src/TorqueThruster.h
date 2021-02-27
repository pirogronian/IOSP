
#pragma once

#include <Thruster.h>

namespace IOSP
{
    class TorqueThruster : public Thruster
    {
    public:
        TorqueThruster(const btVector3 &axis, btScalar max) : Thruster(axis, max) {}
        void update(BulletBodySceneNode *, irr::u32) override;
    };
}
