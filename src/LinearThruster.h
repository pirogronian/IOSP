
#pragma once

#include <Thruster.h>

namespace IOSP
{
    class LinearThruster : public Thruster
    {
    public:
        LinearThruster(const btVector3& v, btScalar max) : Thruster(v, max, false) {}
        LinearThruster(const LinearThruster& other) : Thruster(other) {}
        Component *clone(bool c) override
        {
            return Component::clone<LinearThruster>(c);
        }
        void update(irr::u32) override;
    };
}
