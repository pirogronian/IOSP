
#pragma once

#include <irrlicht.h>

namespace IOSP
{
    template<typename T>
    inline void setOwnership(T *&own_ptr, T *new_ptr)
    {
        own_ptr = new_ptr;
        if (own_ptr)
            own_ptr->grab();
    }
    template<typename T>
    inline bool clearOwnership(T *&own_ptr)
    {
        bool ret = false;
        if (own_ptr)
        {
            own_ptr->drop();
            ret = true;
        }
        own_ptr = nullptr;
        return ret;
    }
    template<typename T>
    inline bool switchOwnership(T *&own_ptr, T *new_ptr)
    {
        bool ret = false;
        if (own_ptr)
        {
            own_ptr->drop();
            ret = true;
        }
        own_ptr = new_ptr;
        if (own_ptr)
            own_ptr->grab();
        return ret;
    }
}
