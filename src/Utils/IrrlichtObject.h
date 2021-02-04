
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
        static irr::IrrlichtDevice *getDefaultDevice() { return s_dev; }
        static irr::video::IVideoDriver *getDefaultDriver()
        {
            if (!s_dev)  return nullptr;
            return s_dev->getVideoDriver();
        }
        static irr::gui::IGUIEnvironment *getDefaultGui()
        {
            if (!s_dev)  return nullptr;
            return s_dev->getGUIEnvironment();
        }
        static irr::scene::ISceneManager *getDefaultSceneManager()
        {
            if (!s_dev)  return nullptr;
            return s_dev->getSceneManager();
        }
        irr::IrrlichtDevice *getDevice() { return m_dev ? m_dev : s_dev; }
        const irr::IrrlichtDevice *getDevice() const { return m_dev ? m_dev : s_dev; }
        void setDevice(irr::IrrlichtDevice *d) { switchOwnership(m_dev, d); }
        irr::video::IVideoDriver *getDriver()
        {
            if (m_dev)  return m_dev->getVideoDriver();
            return getDefaultDriver();
        }
        const irr::video::IVideoDriver *getDriver() const
        {
            if (m_dev)  return m_dev->getVideoDriver();
            return getDefaultDriver();
        }
        irr::gui::IGUIEnvironment *getGui()
        {
            if (m_dev)  return m_dev->getGUIEnvironment();
            return getDefaultGui();
        }
        const irr::gui::IGUIEnvironment *getGui() const
        {
            if (m_dev)  return m_dev->getGUIEnvironment();
            return getDefaultGui();
        }
        irr::scene::ISceneManager *getSeneManager()
        {
            if (m_dev)  return m_dev->getSceneManager();
            return getDefaultSceneManager();
        }
        const irr::scene::ISceneManager *getSceneManager() const
        {
            if (m_dev)  return m_dev->getSceneManager();
            return getDefaultSceneManager();
        }
        irr::ITimer *getDefaultTimer()
        {
            if (s_dev)  return s_dev->getTimer();
            return nullptr;
        }
        const irr::ITimer *getDefaultTimer() const
        {
            if (s_dev)  return s_dev->getTimer();
            return nullptr;
        }
        irr::ITimer *getTimer()
        {
            if (m_dev)  return m_dev->getTimer();
            return getDefaultTimer();
        }
        const irr::ITimer *getTimer() const
        {
            if (m_dev)  return m_dev->getTimer();
            return getDefaultTimer();
        }
        irr::gui::IGUIFont *getFont(irr::gui::EGUI_DEFAULT_FONT f = irr::gui::EGDF_DEFAULT);
        const irr::gui::IGUIFont *getFont(irr::gui::EGUI_DEFAULT_FONT f = irr::gui::EGDF_DEFAULT) const;
    };
}
