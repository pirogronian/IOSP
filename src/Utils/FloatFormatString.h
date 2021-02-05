
#pragma once

#include <cstdio>

namespace IOSP
{
    inline void generateFloatFormatString(char *str, unsigned char totalDigits, unsigned char fracDigits)
    {
        std::sprintf(str, "%%%u.%uf", totalDigits, fracDigits);
    }
}
