
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
        bool m_allowNeg{true};
        bool m_on{false};
        virtual void updateEffectiveThrust();
    public:
        Thruster(const btVector3&, btScalar, bool = true);
        void copyFrom(const Thruster&);
        Thruster(const Thruster& other)
        : Component(other)
        { copyFrom(other); }
        Thruster& operator=(const Thruster& other)
        {
            copyFrom(other);
            return *this;
        }
        Component *clone(bool c) override
        {
            return Component::clone<Thruster>(c);
        }
        btScalar getMaxThrust() const { return m_maxThrust; }
        bool allowNegativeThrust() const { return m_allowNeg; }
        void setOn(bool);
        bool isOn() const { return m_on; }
        void setThrust(btScalar);
        btScalar getDemandedThrust() const { return m_setThrust; }
        btScalar getEffectiveThrust() const { return m_effectiveThrust; }
    };
}
