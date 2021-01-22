
#pragma once

#include <memory>
#include <irrlicht.h>

#include <Common.h>
#include <Utils/InputKeyActionManager.h>

namespace IOSP
{
    class AbstractControlPanelSceneNode : public irr::scene::ISceneNode, public irr::IEventReceiver
    {
    protected:
        irr::core::aabbox3d<irr::f32> m_bbox;
        irr::IrrlichtDevice *m_dev{nullptr};
        irr::gui::IGUIElement *m_rootGui{nullptr};
    public:
        AbstractControlPanelSceneNode(
            irr::IrrlichtDevice *,
            irr::scene::ISceneNode *,
            irr::scene::ISceneManager *,
            irr::s32 id = -1,
            const irr::core::vector3df& pos = irr::core::vector3df(0, 0, 0),
            const irr::core::vector3df& rot = irr::core::vector3df(0, 0, 0));
        const irr::core::aabbox3d<irr::f32>& getBoundingBox() const
        {
            return m_bbox;
        }
        virtual void update() = 0;
        void setVisible(bool v) override;
        void grabEvents() { m_dev->setEventReceiver(this); }
        ~AbstractControlPanelSceneNode();
    };

    template<class TT>
    class TargetedAbstractControlPanel : virtual public AbstractControlPanelSceneNode
    {
    protected:
        TT *m_target{nullptr};
    public:
        TargetedAbstractControlPanel(
            irr::IrrlichtDevice *dev,
            irr::scene::ISceneNode *parent,
            irr::scene::ISceneManager *smgr,
            irr::s32 id = -1,
            const irr::core::vector3df& pos = irr::core::vector3df(0, 0, 0),
            const irr::core::vector3df& rot = irr::core::vector3df(0, 0, 0))
        : AbstractControlPanelSceneNode(dev, parent, smgr, id, pos, rot)
        {
        }
        void setTarget(TT *t)
        {
            if (m_target != nullptr)
                m_target->drop();
            m_target = t;
            m_target->grab();
        }
        TT *target() { return m_target; }
        const TT *target() const { return m_target; }
        ~TargetedAbstractControlPanel()
        {
            if (m_target != nullptr)
                m_target->drop();
        }
    };

    class KeyInputAbstractControlPanel : virtual public AbstractControlPanelSceneNode
    {
    protected:
        std::shared_ptr<AbstractInputKeyTriggeredActionManager> m_trKeyActions;
        std::shared_ptr<InputKeyStateActionManager> m_stKeyActions;
    public:
        KeyInputAbstractControlPanel(
            irr::IrrlichtDevice *dev,
            irr::scene::ISceneNode *parent,
            irr::scene::ISceneManager *smgr,
            irr::s32 id,
            const irr::core::vector3df& pos,
            const irr::core::vector3df& rot)
        : AbstractControlPanelSceneNode(dev, parent, smgr, id, pos, rot)
        {
        }
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
        bool OnEvent(const irr::SEvent&) override;
    };
}
