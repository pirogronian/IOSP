
#pragma once

#include <irrlicht.h>

namespace IOSP
{
    class EventReceiver : public irr::IEventReceiver
    {
    public:
        bool OnEvent(const irr::SEvent&) override;
    };
}
