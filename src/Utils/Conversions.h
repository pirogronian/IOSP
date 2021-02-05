
#pragma once

#include <irrlicht.h>
#include <btBulletDynamicsCommon.h>
#include <cstdlib>

namespace IOSP
{
    inline irr::core::dimension2d<irr::u32> toUnsigned(const irr::core::dimension2d<irr::s32>& other)
    {
        return irr::core::dimension2d<irr::u32>(std::abs(other.Width), std::abs(other.Height));
    }

    template<typename T>
    T radToDeg(T a)
    {
        return a * irr::core::RADTODEG;
    }

    template<typename T>
    T degToRad(T a)
    {
        return a * irr::core::DEGTORAD;
    }

    inline btVector3 toBullet(const irr::core::vector3df& v)
    {
        return btVector3(v.X, v.Y, v.Z);
    }

    inline irr::core::vector3df fromBullet(const btVector3& v)
    {
        return irr::core::vector3df(v[0], v[1], v[2]);
    }

    inline irr::core::quaternion fromBullet(const btQuaternion& q)
    {
        return irr::core::quaternion(q.getX(), q.getY(), q.getZ(), q.getW());
    }

    inline irr::core::vector3df toEuler(const irr::core::quaternion& q)
    {
        irr::core::vector3df ret;
        q.toEuler(ret);
        return ret;
    }

    inline irr::core::vector3df toIrrlichtVector(const btQuaternion& q)
    {
        return toEuler(fromBullet(q));
    }

    inline btQuaternion toQuaternion(const btVector3& v)
    {
        return btQuaternion(v.getX(), v.getY(), v.getZ());
    }

    inline btQuaternion toBulletQuaternion(const irr::core::vector3df& v)
    {
        return btQuaternion(v.X, v.Y, v.Z);
    }

    inline btQuaternion toBullet(const irr::core::quaternion& q)
    {
        return btQuaternion(q.X, q.Y, q.Z, q.W);
    }

    inline btTransform toBullet(const irr::core::quaternion& rot, const irr::core::vector3df& tr)
    {
        return btTransform(toBullet(rot), toBullet(tr));
    }

    inline irr::video::SColor toIrrlichtColor(btVector3 v)
    {
        v *= 255;
        return irr::video::SColor(v.getX(), v.getY(), v.getZ(), 255);
    }
}
