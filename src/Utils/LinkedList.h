
#pragma once

#include <irrlicht.h>

namespace IOSP
{
    template<typename T>
    class LinkedPtrList : public irr::core::list<T*>
    {
    public:
        const T* findItem(const T* item) const
        {
            if (irr::core::list<T*>::size() == 0)  return nullptr;
            for (auto it = irr::core::list<T*>::begin(); it != irr::core::list<T*>::end(); it++)
                if (*it == item)  return item;
            return nullptr;
        }

        T* findItem(T* item)
        {
            if (irr::core::list<T*>::size() == 0)  return nullptr;
            for (auto it = irr::core::list<T*>::begin(); it != irr::core::list<T*>::end(); it++)
                if (*it == item)  return item;
            return nullptr;
        }

        bool hasItem(const T* item) const
        {
            return findItem(item) == item;
        }

        bool addItem(T* item)
        {
            if (hasItem(item))  return false;
            irr::core::list<T*>::push_back(item);
            return true;
        }

        bool removeItem(T* item)
        {
            if (irr::core::list<T*>::size() == 0)  return false;
            for (auto it = irr::core::list<T*>::begin(); it != irr::core::list<T*>::end(); it++)
            {
                if (*it == item)
                {
                    irr::core::list<T*>::erase(it);
                    return true;
                }
            }
            return false;
        }
    };
}
