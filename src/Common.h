
#pragma once

#include <irrTypes.h>

namespace IOSP
{
    typedef double time_t;
    enum SceneNodeType
    {
        ESNT_BULLET_WORLD = MAKE_IRR_ID('s', 'p', 'b', 'w'),
        ESNT_BULLET_BODY = MAKE_IRR_ID('s', 'p', 'b', 'b'),
        ESNT_USER_CONTROL_PANEL = MAKE_IRR_ID('s', 'p', 'u', 'p')
    };
}
