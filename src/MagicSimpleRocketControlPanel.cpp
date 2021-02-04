
#include <cstdio>

#include "MagicSimpleRocketControlPanel.h"

using namespace IOSP;

IOSP::MagicSimpleRocketControlPanel::MagicSimpleRocketControlPanel(
            irr::IrrlichtDevice *dev,
            irr::scene::ISceneNode *parent,
            irr::scene::ISceneManager *smgr,
            irr::s32 id,
            const irr::core::vector3df& pos,
            const irr::core::vector3df& rot)
        : ControlPanelSceneNode(dev, parent, smgr, id, pos, rot)
{
    m_rotText.setAlignment(0.5, 1);
    m_rotText.getPadding().set(10);
    m_rotText.setFormat("Rotation: [%10f, %10f, %10f]");

    m_massText.setAlignment(0.5, 1);
    m_massText.getPadding().set(10);
    m_massText.setFormat("Mass: %4f");

    m_trKeyActions = std::make_shared<SimpleInputKeyTriggeredActionManager>();
    m_stKeyActions = std::make_shared<InputKeyStateActionManager>();

    m_stKeyActions->bind(ThrustAction, irr::KEY_KEY_V);
    m_stKeyActions->bind(PitchUpAction, irr::KEY_KEY_W);
    m_stKeyActions->bind(PitchDownAction, irr::KEY_KEY_S);
    m_stKeyActions->bind(RollClockwiseAction, irr::KEY_KEY_A);
    m_stKeyActions->bind(RollAnticlockwiseAction, irr::KEY_KEY_D);
    m_stKeyActions->bind(YawLeftAction, irr::KEY_KEY_Q);
    m_stKeyActions->bind(YawRightAction, irr::KEY_KEY_E);
}

void IOSP::MagicSimpleRocketControlPanel::update()
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
            body->applyForceLocal(btVector3(0, 0, -3), btVector3(0, 0, 0));
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
        if (m_stKeyActions->isActive(YawLeftAction))
        {
//             std::puts("Roll clockwise On!");
//             body->bulletRigidBody()->applyTorque(btVector3(0, 0, 1));
            body->applyTorqueLocal(btVector3(0, 1, 0));
        }
        else if (m_stKeyActions->isActive(YawRightAction))
        {
//             std::puts("Roll anticlockwise On!");
//             body->bulletRigidBody()->applyTorque(btVector3(0, 0, -1));
            body->applyTorqueLocal(btVector3(0, -1, 0));
        }

        ControlPanelSceneNode::update();
    }
}

void IOSP::MagicSimpleRocketControlPanel::updateUI()
{
    auto r = m_controlTarget->getRotation();
    m_rotText.setValues(3, r.X, r.Y, r.Z);
    m_rotText.setShift(0, -m_rotText.getRequestedDimension(ScreenRectangle::Outer).Height);
    m_rotText.update();
    auto mass = ((BulletBodySceneNode*)m_controlTarget)->getMass();
    m_massText.update(1, mass);
}

void IOSP::MagicSimpleRocketControlPanel::render()
{
    m_rotText.draw();
    m_massText.draw();
}

void IOSP::MagicSimpleRocketControlPanel::OnRegisterSceneNode()
{
    if (IsVisible)
        SceneManager->registerNodeForRendering(this);

    ISceneNode::OnRegisterSceneNode();
}
