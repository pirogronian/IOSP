
#pragma once

#include <stdexcept>

#include <irrlicht.h>

namespace IOSP
{
    class IrrCommonObject
    {
        static irr::IrrlichtDevice *s_dev;
        static bool s_throwOnNull;
    public:
        static bool getThrowOnNull() { return s_throwOnNull; }
        static void setThrowOnNull(bool on) { s_throwOnNull = on; }
        static irr::IrrlichtDevice *getDevice() {
            if (!s_dev && s_throwOnNull) throw std::runtime_error("Common Irrlicht device is null!");
            return s_dev;
        }
        static void setDevice(irr::IrrlichtDevice *dev) { s_dev = dev; }
        static irr::IEventReceiver *getEventReceiver();
        static irr::ITimer* getTimer();
        static irr::gui::ICursorControl *getCursorControl();
        static irr::io::IFileSystem *getFileSystem();
        static irr::gui::IGUIEnvironment *getGUIEnvironment();
        static irr::ILogger *getLogger();
        static irr::IOSOperator *getOSOperator();
        static irr::IRandomizer *getRandomizer();
        static irr::scene::ISceneManager *getSceneManager();
        static irr::video::IVideoDriver *getVideoDriver();
        static irr::gui::IGUISkin *getSkin();
        static irr::gui::IGUIFont *getFont(irr::gui::EGUI_DEFAULT_FONT f = irr::gui::EGDF_DEFAULT);
    };
}
