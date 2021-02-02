
#pragma once

#include <ControlPanelSceneNode.h>
#include <BulletBodySceneNode.h>
#include <ScreenUtils/ScreenText.h>

namespace IOSP
{
    /*
     * It's called "magic", because it magically make a simple rocket
     * from any BulletBodySceneNode which is set as a target.
     */
    class MagicSimpleRocketControlPanel : public ControlPanelSceneNode
    {
    protected:
        bool m_isThrust{false};
        void setTarget(irr::scene::ISceneNode*);
        ScreenText m_rotText;
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
            RollAnticlockwiseAction,
            YawLeftAction,
            YawRightAction
        };
        MagicSimpleRocketControlPanel(
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
