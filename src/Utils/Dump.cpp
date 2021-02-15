
#include <cstdio>

#include "Dump.h"

void IOSP::dump(const irr::SEvent::SKeyInput& ki)
{
    printf("SKeyInput\n{\n   Char: %lc\n   Key: %i\n   Pressed: %i\n   Control: %i\n   Shift: %i\n}\n",
        ki.Char, ki.Key, ki.PressedDown, ki.Control, ki.Shift
    );
}

void IOSP::dump(const btTransform& tr)
{
    auto pos = tr.getOrigin();
    auto rot = tr.getBasis();
    btScalar x, y, z;
    rot.getEulerZYX(z, y, x);
    std::printf("Position: [%f, %f, %f]\n", pos.getX(), pos.getY(), pos.getZ());
    std::printf("Rotation: [%f, %f, %f]\n", x, y, z);
}
