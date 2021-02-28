
#pragma once

// #include <memory>
#include <irrlicht.h>

#include <Common.h>
#include <Utils/IrrCommonObject.h>
#include <Utils/InputKeyActionManager.h>
#include <Utils/IntervalTimer.h>
#include <BulletBodySceneNode.h>

namespace IOSP
{
    class ControlPanelSceneNode : public irr::scene::ISceneNode, public irr::IEventReceiver, public IrrCommonObject
    {
    protected:
        irr::core::aabbox3d<irr::f32> m_bbox;
        irr::gui::IGUIElement *m_rootGui{nullptr};
        BulletBodySceneNode *m_controlTarget{nullptr};
        SimpleInputKeyTriggeredActionManager m_trKeyActions;
        InputKeyStateActionManager m_stKeyActions;
    public:
        ControlPanelSceneNode(
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
        virtual void update() = 0;
        virtual void drawUI() = 0;
        virtual void updateImGui();
        void setVisible(bool v) override;
        bool OnEvent(const irr::SEvent&) override;
        void grabEvents() { getDevice()->setEventReceiver(this); }
        virtual void setTarget(BulletBodySceneNode *);
        BulletBodySceneNode *getControlTarget() { return m_controlTarget; }
        const BulletBodySceneNode *getControlTarget() const { return m_controlTarget; }
        SimpleInputKeyTriggeredActionManager& triggeredActionManager()
        {
            return m_trKeyActions;
        }
        const SimpleInputKeyTriggeredActionManager& triggeredActionManager() const
        {
            return m_trKeyActions;
        }
        InputKeyStateActionManager& stateActionManager()
        {
            return m_stKeyActions;
        }
        const InputKeyStateActionManager& stateActionManager() const
        {
            return m_stKeyActions;
        }
    };
}
