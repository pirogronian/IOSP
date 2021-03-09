
#pragma once

#include <Thruster.h>

namespace IOSP
{
    class TorqueThruster : public Thruster
    {
    public:
        TorqueThruster(const btVector3 &axis, btScalar max) : Thruster(axis, max) {}
        TorqueThruster(const TorqueThruster& other) : Thruster(other) {}
        Component *clone(bool c) override
        {
            return Component::clone<TorqueThruster>(c);
        }
        void update(irr::u32) override;
    };
}
