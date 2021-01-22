
#include <cstdio>

#include "TestControlPanel.h"

using namespace IOSP;

IOSP::TestControlPanel::TestControlPanel(
            irr::IrrlichtDevice *dev,
            irr::scene::ISceneNode *parent,
            irr::scene::ISceneManager *smgr,
            irr::s32 id,
            const irr::core::vector3df& pos,
            const irr::core::vector3df& rot)
        : TargetedAbstractControlPanel(dev, parent, smgr, id, pos, rot),
        KeyInputAbstractControlPanel(dev, parent, smgr, id, pos, rot),
        AbstractControlPanelSceneNode(dev, parent, smgr, id, pos, rot)
{
    m_stKeyActions = std::make_shared<InputKeyStateActionManager>();
}

void IOSP::TestControlPanel::update()
{
    if (m_target != nullptr && m_stKeyActions->isActive(ThrustAction))
    {
//         std::puts("Thrust On!");
        m_target->bulletRigidBody()->applyForce(btVector3(0, 0, -3), btVector3(0, 0, 0));
        auto f = m_target->bulletRigidBody()->getTotalForce();
//         std::printf("Total force: [%f, %f, %f]\n", f.getX(), f.getY(), f.getZ());
    } //else std::puts("Thrust Off!");
}

void IOSP::TestControlPanel::render() {}

void IOSP::TestControlPanel::OnRegisterSceneNode()
{
    if (IsVisible)
        SceneManager->registerNodeForRendering(this);

    ISceneNode::OnRegisterSceneNode();
}
