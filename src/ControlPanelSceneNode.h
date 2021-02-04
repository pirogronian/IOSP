
#pragma once

#include <memory>
#include <irrlicht.h>

#include <Common.h>
#include <Utils/IrrlichtObject.h>
#include <Utils/InputKeyActionManager.h>
#include <ThirdPersonCamera.h>
#include <Utils/IntervalTimer.h>

namespace IOSP
{
    class ControlPanelSceneNode : public irr::scene::ISceneNode, public irr::IEventReceiver, public IrrlichtObject
    {
    protected:
        irr::core::aabbox3d<irr::f32> m_bbox;
        irr::IrrlichtDevice *m_dev{nullptr};
        irr::gui::IGUIElement *m_rootGui{nullptr};
        irr::scene::ISceneNode *m_controlTarget{nullptr};
        std::shared_ptr<AbstractInputKeyTriggeredActionManager> m_trKeyActions;
        std::shared_ptr<InputKeyStateActionManager> m_stKeyActions;
        IntervalTimer m_uiTimer{100};
    public:
        static ThirdPersonCamera thirdPersonCamera;
        ControlPanelSceneNode(
            irr::IrrlichtDevice *,
            irr::scene::ISceneNode *,
            irr::scene::ISceneManager *,
            irr::s32 id = -1,
            const irr::core::vector3df& pos = irr::core::vector3df(0, 0, 0),
            const irr::core::vector3df& rot = irr::core::vector3df(0, 0, 0));
        ~ControlPanelSceneNode();
        const irr::core::aabbox3d<irr::f32>& getBoundingBox() const
        {
            return m_bbox;
        }
        virtual void update();
        virtual void updateUI() = 0;
        void setVisible(bool v) override;
        bool OnEvent(const irr::SEvent&) override;
        void grabEvents() { m_dev->setEventReceiver(this); }
        void setTarget(irr::scene::ISceneNode *t)
        {
            if (m_controlTarget)
                m_controlTarget->drop();
            m_controlTarget = t;
            m_controlTarget->grab();
        }
        irr::scene::ISceneNode *controlTarge() { return m_controlTarget; }
        const irr::scene::ISceneNode *controlTarge() const { return m_controlTarget; }
        std::shared_ptr<AbstractInputKeyTriggeredActionManager>& triggeredActionManager()
        {
            return m_trKeyActions;
        }
        const std::shared_ptr<AbstractInputKeyTriggeredActionManager>& triggeredActionManager() const
        {
            return m_trKeyActions;
        }
        void setTriggeredActionManager(std::shared_ptr<AbstractInputKeyTriggeredActionManager>& manager)
        {
            m_trKeyActions = manager;
        }
        std::shared_ptr<InputKeyStateActionManager>& stateActionManager()
        {
            return m_stKeyActions;
        }
        const std::shared_ptr<InputKeyStateActionManager>& stateActionManager() const
        {
            return m_stKeyActions;
        }
        void setStateActionManager(std::shared_ptr<InputKeyStateActionManager>& manager)
        {
            m_stKeyActions = manager;
        }
    };
}
