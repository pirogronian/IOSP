
#pragma once

#include <irrlicht.h>

namespace IOSP
{
    struct Variant
    {
        irr::f32 Float;
        irr::s32 Int;
        const wchar_t *wChar;
    };
}
