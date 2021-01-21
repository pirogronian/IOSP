
#pragma once

#include <AbstractControlPanelSceneNode.h>
#include <BulletBodySceneNode.h>

namespace IOSP
{
    class TestControlPanel : public TargetedAbstractControlPanel<BulletBodySceneNode>
    {
    protected:
        bool m_isThrust{false};
    public:
        TestControlPanel(
            irr::IrrlichtDevice *dev,
            irr::scene::ISceneNode *parent,
            irr::scene::ISceneManager *smgr,
            irr::s32 id = -1,
            const irr::core::vector3df& pos = irr::core::vector3df(0, 0, 0),
            const irr::core::vector3df& rot = irr::core::vector3df(0, 0, 0))
        : TargetedAbstractControlPanel(dev, parent, smgr, id, pos, rot) {}
        void update() override;
        void render() override;
        bool OnEvent(const irr::SEvent&) override;
        void OnRegisterSceneNode() override;
    };
}
