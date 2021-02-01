
#pragma once

namespace IOSP
{
    template<typename T>
    inline T nestedRangeRelativeBegin(T begin, T end, T nestedRange, float alignment)
    {
        return ((end - begin) - nestedRange) * alignment;
    }
}
