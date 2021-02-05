
#pragma once

#include <ControlPanelSceneNode.h>
#include <BulletBodySceneNode.h>
#include <ScreenUtils/ScreenText.h>
#include <ScreenUtils/ScreenFloatDisplay.h>

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
        ScreenElement m_infoRoot;
        ScreenFormattedText m_massText{&m_infoRoot}, m_velText{&m_infoRoot}, m_accText{&m_infoRoot};
        SimpleVector3Display m_rotText{&m_infoRoot};
    public:
        enum TriggeredActions
        {
            StartThrustAction = 1,
            StopThrustAction,
            IncreaseMassAction,
            DecreaseMassAction
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
        void updateUI() override;
        void render() override;
        void OnRegisterSceneNode() override;
        void setTarget(BulletBodySceneNode *b) { ControlPanelSceneNode::setTarget(b); }
    };
}
