
#pragma once

#include <irrlicht.h>

namespace IOSP
{
    struct TTF
    {
        irr::core::stringw file;
        unsigned int size{0};
        TTF() = default;
        TTF(const irr::core::stringw& f, unsigned int s) : file(f), size(s) {}
    };
}
