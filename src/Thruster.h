
#pragma once

#include <Component.h>

namespace IOSP
{
    class Thruster : public Component
    {
    protected:
        btVector3 m_vector;
        btScalar m_maxThrust;
        btScalar m_setThrust{0};
        btScalar m_effectiveThrust{0};
        bool m_on{false};
        virtual void updateEffectiveThrust();
    public:
        Thruster(const btVector3&, btScalar);
        void setOn(bool);
        bool isOn() const { return m_on; }
        void setThrust(btScalar);
        btScalar getDemandedThrust() const { return m_setThrust; }
        btScalar getEffectiveThrust() const { return m_effectiveThrust; }
        void update(BulletBodySceneNode *, irr::u32) override;
    };
}
