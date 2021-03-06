
#pragma once

#include <Utils/SimpleState.h>
#include <ComponentSet.h>
#include <Thruster.h>
#include <ControlPanelSceneNode.h>
// #include <Gui.h>

namespace IOSP
{
    class ManualThrustControlPanel : public ControlPanelSceneNode, public SimpleState
    {
    protected:
        struct ThrusterState
        {
            bool on{false};
            float thrust{0};
        };
        ComponentSet<Thruster, ThrusterState> m_ths;
    public:
        ManualThrustControlPanel(
            irr::scene::ISceneNode *parent,
            irr::scene::ISceneManager *smgr,
            irr::s32 id = -1,
            const irr::core::vector3df& pos = irr::core::vector3df(0, 0, 0),
            const irr::core::vector3df& rot = irr::core::vector3df(0, 0, 0));
        void render() override {}
        void update() override;
        void drawUI() override {}
        void updateImGui() override;
        void scanForThrusters();
        void setTarget(BulletBodySceneNode*) override;
    };
}
