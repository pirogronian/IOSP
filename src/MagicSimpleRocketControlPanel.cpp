
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
    m_rotText.updateContent(false, 0, 0, 0);
    auto H = m_rotText.getRequestedDimension(ScreenRectangle::Outer).Height;
    m_rotText.setShift(0, -3 * H);
    m_rotText.updateRectangle();

    m_massText.setAlignment(0.5, 1);
    m_massText.getPadding().set(10);
    m_massText.setFormat("Mass: %4f, delta: %10f");
    m_massText.updateContent(false, 0, 0);
    m_massText.setShift(0, -2 * H);
    m_massText.updateRectangle();

    m_velText.setAlignment(0.5, 1);
    m_velText.getPadding().set(10);
    m_velText.setFormat("Linear vel: [%10f, %10f, %10f]");
    m_velText.updateContent(false, 0, 0, 0);
    m_velText.setShift(0, -H);
    m_velText.updateRectangle();

    m_accText.setAlignment(0.5, 1);
    m_accText.getPadding().set(10);
    m_accText.setFormat("Linear acc: [%10f, %10f, %10f]");
    m_accText.updateContent(false, 0, 0, 0);
    m_accText.updateRectangle();

    m_trKeyActions = std::make_shared<SimpleInputKeyTriggeredActionManager>();
    m_stKeyActions = std::make_shared<InputKeyStateActionManager>();

    m_stKeyActions->bind(ThrustAction, irr::KEY_KEY_V);
    m_stKeyActions->bind(PitchUpAction, irr::KEY_KEY_W);
    m_stKeyActions->bind(PitchDownAction, irr::KEY_KEY_S);
    m_stKeyActions->bind(RollClockwiseAction, irr::KEY_KEY_A);
    m_stKeyActions->bind(RollAnticlockwiseAction, irr::KEY_KEY_D);
    m_stKeyActions->bind(YawLeftAction, irr::KEY_KEY_Q);
    m_stKeyActions->bind(YawRightAction, irr::KEY_KEY_E);

    m_trKeyActions->bind(IncreaseMassAction, irr::KEY_KEY_8);
    m_trKeyActions->bind(DecreaseMassAction, irr::KEY_KEY_2);
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
        auto *tr = dynamic_cast<SimpleInputKeyTriggeredActionManager*>(m_trKeyActions.get());
        auto *node = dynamic_cast<BulletBodySceneNode*>(m_controlTarget);
        if (tr->isTriggered(IncreaseMassAction))
        {
//             std::puts("Increase mass!");
            node->setMass(node->getMass() + 1);
        }
        if (tr->isTriggered(DecreaseMassAction))
        {
//             std::puts("Decrease mass!");
            node->setMass(node->getMass() - 1);
        }
        tr->reset();

        ControlPanelSceneNode::update();
    }
}

void IOSP::MagicSimpleRocketControlPanel::updateUI()
{
    auto *node = dynamic_cast<BulletBodySceneNode*>(m_controlTarget);
    auto r = m_controlTarget->getRotation();
    m_rotText.updateContent(false, r.X, r.Y, r.Z);
    auto mass = node->getMass();
    auto delta = node->getLastDelta();
    m_massText.updateContent(false, mass, delta);
    auto lv = node->getLinearVelocity();
    m_velText.updateContent(false, lv.getX(), lv.getY(), lv.getZ());
    auto la = node->getLinearAcceleration();
    m_accText.updateContent(false, la.getX(), la.getY(), la.getZ());
}

void IOSP::MagicSimpleRocketControlPanel::render()
{
    m_rotText.draw();
    m_massText.draw();
    m_velText.draw();
    m_accText.draw();
}

void IOSP::MagicSimpleRocketControlPanel::OnRegisterSceneNode()
{
    if (IsVisible)
        SceneManager->registerNodeForRendering(this);

    ISceneNode::OnRegisterSceneNode();
}
