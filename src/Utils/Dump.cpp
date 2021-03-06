
#include <cstdio>

#include "Dump.h"

using namespace irr;
using namespace IOSP;

void IOSP::dump(const btTransform& tr)
{
    auto pos = tr.getOrigin();
    auto rot = tr.getBasis();
    btScalar x, y, z;
    rot.getEulerZYX(z, y, x);
    std::printf("Position: [%f, %f, %f]\n", pos.getX(), pos.getY(), pos.getZ());
    std::printf("Rotation: [%f, %f, %f]\n", x, y, z);
}

void IOSP::dump(const btDiscreteDynamicsWorld& world)
{
    std::printf("BulletWold: {%i}\n", world.getNumCollisionObjects());
    auto objs = world.getCollisionObjectArray();
    for (int i = 0; i < objs.size(); i++)
    {
        auto obj = objs[i];
        std::printf(" ptr: %p, user index: %i\n", obj, obj->getUserIndex());
    }
}

void IOSP::dump(const video::SColor& c)
{
    std::printf("SColor(A: %i, R: %i, G: %i, B: %i)\n", c.getAlpha(), c.getRed(), c.getGreen(), c.getBlue());
}

void IOSP::dump(const irr::core::recti& rect)
{
    auto ulc = rect.UpperLeftCorner;
    auto lrc = rect.LowerRightCorner;
    std::printf("Rect(%i, %i, %i, %i)\n", ulc.X, ulc.Y, lrc.X, lrc.Y);
}

void IOSP::dump(const core::vector3df& v)
{
    std::printf("vector3df(%f, %f, %f)\n", v.X, v.Y, v.Z);
}

void IOSP::dump(const irr::SEvent::SKeyInput& ki)
{
    printf("SKeyInput\n{\n   Char: %lc\n   Key: %i\n   Pressed: %i\n   Control: %i\n   Shift: %i\n}\n",
        ki.Char, ki.Key, ki.PressedDown, ki.Control, ki.Shift
    );
}
