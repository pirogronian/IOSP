
#pragma once

#include <irrlicht.h>
#include <Utils/Ownership.h>

void testRefOp(void *&p);

namespace IOSP
{
    class IrrlichtObject
    {
    protected:
        static irr::IrrlichtDevice *s_dev;
        irr::IrrlichtDevice *m_dev{nullptr};
        irr::video::IVideoDriver *m_drv{nullptr};
    public:
        static bool setDefaultDevice(irr::IrrlichtDevice *d) { return switchOwnership(s_dev, d); }
        static irr::IrrlichtDevice *defaultDevice() { return s_dev; }
        static irr::video::IVideoDriver *defaultDriver()
        {
            if (!s_dev)  return nullptr;
            return s_dev->getVideoDriver();
        }
        static irr::gui::IGUIEnvironment *defaultGui()
        {
            if (!s_dev)  return nullptr;
            return s_dev->getGUIEnvironment();
        }
        static irr::scene::ISceneManager *defaultSceneManager()
        {
            if (!s_dev)  return nullptr;
            return s_dev->getSceneManager();
        }
        irr::IrrlichtDevice *device() { return m_dev ? m_dev : s_dev; }
        const irr::IrrlichtDevice *device() const { return m_dev ? m_dev : s_dev; }
        void setDevice(irr::IrrlichtDevice *d) { switchOwnership(m_dev, d); }
        irr::video::IVideoDriver *driver()
        {
            if (m_dev)  return m_dev->getVideoDriver();
            return defaultDriver();
        }
        const irr::video::IVideoDriver *driver() const
        {
            if (m_dev)  return m_dev->getVideoDriver();
            return defaultDriver();
        }
        irr::gui::IGUIEnvironment *gui()
        {
            if (m_dev)  return m_dev->getGUIEnvironment();
            return defaultGui();
        }
        const irr::gui::IGUIEnvironment *gui() const
        {
            if (m_dev)  return m_dev->getGUIEnvironment();
            return defaultGui();
        }
        irr::scene::ISceneManager *sceneManager()
        {
            if (m_dev)  return m_dev->getSceneManager();
            return defaultSceneManager();
        }
        const irr::scene::ISceneManager *sceneManager() const
        {
            if (m_dev)  return m_dev->getSceneManager();
            return defaultSceneManager();
        }
    };
}
