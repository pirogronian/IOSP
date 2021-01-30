
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
        : ControlPanelSceneNode(dev, parent, smgr, id, pos, rot)
{
    m_trKeyActions = std::make_shared<SimpleInputKeyTriggeredActionManager>();
    m_stKeyActions = std::make_shared<InputKeyStateActionManager>();

    m_stKeyActions->bind(ThrustAction, irr::KEY_KEY_V);
    m_stKeyActions->bind(PitchUpAction, irr::KEY_KEY_W);
    m_stKeyActions->bind(PitchDownAction, irr::KEY_KEY_S);
}

void IOSP::TestControlPanel::update()
{
//     if (!m_controlTarget)  std::puts("No control target!");
    if (m_controlTarget)
    {
        auto *body = (BulletBodySceneNode*)m_controlTarget;
//         body->bulletRigidBody()->setAngularFactor(btVector3(1, 1, 1));
        if (m_stKeyActions->isActive(ThrustAction))
        {
//             std::puts("Thrust On!");
//             body->bulletRigidBody()->applyForce(btVector3(0, 0, -3), btVector3(0, 0, 0));
            body->applyForceLocal(btVector3(0, 0, -3));
        }
        if (m_stKeyActions->isActive(PitchUpAction))
        {
//             std::puts("Pitch up On!");
//             body->bulletRigidBody()->applyTorque(btVector3(1, 0, 0));
            body->applyTorqueLocal(btVector3(1, 0, 0));
//             auto av = body->bulletRigidBody()->getAngularVelocity();
//             std::printf("Ang vel: [%f, %f, %f]\n", av.getX(), av.getY(), av.getZ());
        }
        else if (m_stKeyActions->isActive(PitchDownAction))
        {
//             std::puts("Pitch down On!");
//             body->bulletRigidBody()->applyTorque(btVector3(-1, 0, 0));
            body->applyTorqueLocal(btVector3(-1, 0, 0));
        }
        if (m_stKeyActions->isActive(RollClockwiseAction))
        {
//             std::puts("Roll clockwise On!");
//             body->bulletRigidBody()->applyTorque(btVector3(0, 0, 1));
            body->applyTorqueLocal(btVector3(0, 0, 1));
        }
        else if (m_stKeyActions->isActive(RollAnticlockwiseAction))
        {
//             std::puts("Roll anticlockwise On!");
//             body->bulletRigidBody()->applyTorque(btVector3(0, 0, -1));
            body->applyTorqueLocal(btVector3(0, 0, -1));
        }
//         body->bulletRigidBody()->integrateVelocities(1);
//         auto it = body->bulletRigidBody()->getInvInertiaTensor();
        auto av = body->bulletRigidBody()->getAngularVelocity();
        auto tr = body->bulletRigidBody()->getWorldTransform();
        auto rot = tr.getBasis();
        auto v1 = rot.getRow(0);
        auto v2 = rot.getRow(1);
        auto v3 = rot.getRow(2);
//         auto lv = body->bulletRigidBody()->getLinearVelocity();
//         auto t = body->bulletRigidBody()->getTotalTorque();
//         auto af = body->bulletRigidBody()->getAngularFactor();
//         std::printf("Ang damping: %f\n", ad);
//         std::printf("Ang vel: [%f, %f, %f]\n", av.getX(), av.getY(), av.getZ());
//         std::printf("Rot transf: [%f, %f, %f]\n", v1.getX(), v1.getY(), v1.getZ());
//         std::printf("Rot transf: [%f, %f, %f]\n", v2.getX(), v2.getY(), v2.getZ());
//         std::printf("Rot transf: [%f, %f, %f]\n", v3.getX(), v3.getY(), v3.getZ());
//         std::printf("Inv tensor: [%f, %f, %f]\n", it.getX(), it.getY(), it.getZ());
//         std::printf("Total torque: [%f, %f, %f]\n", t.getX(), t.getY(), t.getZ());
//         std::printf("Linear vel: [%f, %f, %f]\n", lv.getX(), lv.getY(), lv.getZ());
    }
}

void IOSP::TestControlPanel::render() {}

void IOSP::TestControlPanel::OnRegisterSceneNode()
{
    if (IsVisible)
        SceneManager->registerNodeForRendering(this);

    ISceneNode::OnRegisterSceneNode();
}
