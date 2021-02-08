
#include "IrrCommonObject.h"

using namespace irr;
using namespace IOSP;

IrrlichtDevice *IrrCommonObject::s_dev{nullptr};
bool IrrCommonObject::s_throwOnNull{false};

#define getObjectType(Type, Name) \
Type *IrrCommonObject::Name() { \
    auto dev = getDevice(); \
    if (!dev)  return nullptr; \
    auto m = dev->Name(); \
    if (!m && s_throwOnNull)  throw std::runtime_error(#Type " pointer is null!"); \
    return m; \
}

getObjectType(IEventReceiver, getEventReceiver)

getObjectType(ITimer, getTimer)

getObjectType(gui::ICursorControl, getCursorControl)

getObjectType(io::IFileSystem, getFileSystem)

getObjectType(gui::IGUIEnvironment, getGUIEnvironment)

getObjectType(ILogger, getLogger)

getObjectType(IOSOperator, getOSOperator)

getObjectType(IRandomizer, getRandomizer)

getObjectType(scene::ISceneManager, getSceneManager)

getObjectType(video::IVideoDriver, getVideoDriver)

gui::IGUISkin *IrrCommonObject::getSkin()
{
    auto gui = getGUIEnvironment();
    if (!gui)  return nullptr;
    auto s = gui->getSkin();
    if (!s && s_throwOnNull)  throw std::runtime_error("IGUISkin pointer is null!");
    return s;
}

gui::IGUIFont *IrrCommonObject::getFont(irr::gui::EGUI_DEFAULT_FONT f)
{
    auto skin = getSkin();
    if (!skin)  return nullptr;
    auto font = skin->getFont(f);
    if (!font && s_throwOnNull)  throw std::runtime_error("IGUIFont pointer is null!");
    return font;
}
