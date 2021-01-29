
#pragma once

#include <ControlPanelSceneNode.h>
#include <BulletBodySceneNode.h>

namespace IOSP
{
    class TestControlPanel : public ControlPanelSceneNode
    {
    protected:
        bool m_isThrust{false};
        void setTarget(irr::scene::ISceneNode*);
    public:
        enum TriggeredActions
        {
            StartThrustAction = 1,
            StopThrustAction
        };
        enum StateActions
        {
            ThrustAction = 1,
            PitchUpAction,
            PitchDownAction,
            RollClockwiseAction,
            RollAnticlockwiseAction
        };
        TestControlPanel(
            irr::IrrlichtDevice *dev,
            irr::scene::ISceneNode *parent,
            irr::scene::ISceneManager *smgr,
            irr::s32 id = -1,
            const irr::core::vector3df& pos = irr::core::vector3df(0, 0, 0),
            const irr::core::vector3df& rot = irr::core::vector3df(0, 0, 0));
        void update() override;
        void render() override;
        void OnRegisterSceneNode() override;
        void setTarget(BulletBodySceneNode *b) { ControlPanelSceneNode::setTarget(b); }
    };
}
