
#pragma once

#include <Thruster.h>

namespace IOSP
{
    class LinearThruster : public Thruster
    {
    public:
        LinearThruster(const btVector3& v, btScalar max) : Thruster(v, max, false) {}
        void update(BulletBodySceneNode *, irr::u32) override;
    };
}
