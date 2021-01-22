
#pragma once

#include <AbstractControlPanelSceneNode.h>
#include <BulletBodySceneNode.h>

namespace IOSP
{
    class TestControlPanel : 
    virtual public TargetedAbstractControlPanel<BulletBodySceneNode>,
    virtual public KeyInputAbstractControlPanel
    {
    protected:
        bool m_isThrust{false};
    public:
        enum Actions
        {
            ThrustAction = 1
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
    };
}
