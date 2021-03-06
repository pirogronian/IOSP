
#include <cstdio>

#include <Utils/Dump.h>
#include <Utils/Conversions.h>
#include <Thruster.h>
#include <BulletWorldSceneNode.h>
#include "MagicSimpleRocketControlPanel.h"

using namespace IOSP;

IOSP::MagicSimpleRocketControlPanel::MagicSimpleRocketControlPanel(
            irr::scene::ISceneNode *parent,
            irr::scene::ISceneManager *smgr,
            irr::s32 id,
            const irr::core::vector3df& pos,
            const irr::core::vector3df& rot)
        : ControlPanelSceneNode(parent, smgr, id, pos, rot)
{
    m_rayStart.setValue(0, 0, 0);
    m_rayStop.setValue(0, 0, 10);

    m_trDisplay.setAlignment(0.5, 0);
    m_trDisplay.getPadding().set(5);
    m_trDisplay.getMargin().set(5);
    m_trDisplay.adjustGeometry();
    m_trDisplay.getOwnBackgroundColor().set(127, 127, 0, 0);

    m_infoRoot.setAlignment(0.5, 1);

//     m_massText.setBackgroundPolicy(ScreenElement::UseParentBackground);
    m_massText.setAlignment(0.5, 0);
    m_massText.getPadding().set(10);
    m_massText.setFormat("Mass: %4f, hit: %i, hit name: %s");
    m_massText.updateContent(false, 0, 0);
//     m_massText.setShift(0, -2 * H);
    m_massText.getOwnBackgroundColor().set(127, 0, 127, 0);

//     m_velText.setBackgroundPolicy(ScreenElement::UseParentBackground);
    m_velText.setAlignment(0.5, 0);
    m_velText.getPadding().set(10);
    m_velText.setFormat(9, 4, "Linear vel");
    m_velText.updateContent(0, 0, 0);
//     m_velText.setShift(0, -H);
    m_velText.setBelow(&m_massText);
    m_velText.getOwnBackgroundColor().set(127, 0, 0, 127);

//     m_accText.setBackgroundPolicy(ScreenElement::UseParentBackground);
    m_accText.setAlignment(0.5, 0);
    m_accText.getPadding().set(10);
    m_accText.setFormat(9, 4, "Linear acc");
    m_accText.updateContent(0, 0, 0);
    m_accText.setBelow(&m_velText);
    m_accText.getOwnBackgroundColor().set(127, 127, 0, 127);

    m_forceText.setAlignment(0.5, 0);
    m_forceText.getPadding().set(10);
    m_forceText.setFormat(9, 4, "Linear force");
    m_forceText.updateContent(0, 0, 0);
    m_forceText.setBelow(&m_accText);
    m_forceText.getOwnBackgroundColor().set(127, 127, 127, 127);

    m_infoRoot.getPadding().set(5);
    m_infoRoot.setCanShrink(true);
    m_infoRoot.setCanExpand(true);
    m_infoRoot.adjustGeometry();

    m_sfDisplay.setValueScale(10);
    m_sfDisplay.setVisualScale(5);
    m_sfDisplay.setFormat(8, 2);
    m_sfDisplay.setRequestedDimension(75, 200);
    m_sfDisplay.setAlignment(0.5, 0.5);
    m_sfDisplay.getText().setBackgroundPolicy(ScreenElement::NoBackground);
    m_sfDisplay.updateRectangle();

//     m_stKeyActions->bind(ThrustAction, irr::KEY_KEY_V);
    m_stKeyActions.bind(PitchUpAction, irr::KEY_KEY_W);
    m_stKeyActions.bind(PitchDownAction, irr::KEY_KEY_S);
    m_stKeyActions.bind(RollClockwiseAction, irr::KEY_KEY_A);
    m_stKeyActions.bind(RollAnticlockwiseAction, irr::KEY_KEY_D);
    m_stKeyActions.bind(YawLeftAction, irr::KEY_KEY_Q);
    m_stKeyActions.bind(YawRightAction, irr::KEY_KEY_E);

    m_trKeyActions.bind(IncreaseMassAction, irr::KEY_KEY_8);
    m_trKeyActions.bind(DecreaseMassAction, irr::KEY_KEY_2);
    m_trKeyActions.bind(ToggleGrasp, irr::KEY_KEY_1);
    m_trKeyActions.bind(ToggleThrust, irr::KEY_KEY_V);
}

void IOSP::MagicSimpleRocketControlPanel::update()
{
    if (!m_controlTarget)  return;
    auto *body = (BulletBodySceneNode*)m_controlTarget;
    if (m_stKeyActions.isActive(ThrustAction))
    {
//          std::puts("Thrust On!");
        body->applyForceLocal(btVector3(0, 0, 3), btVector3(0, 0, 0));
    }
    if (m_stKeyActions.isActive(PitchUpAction))
    {
//         std::puts("Pitch up On!");
        body->applyTorqueLocal(btVector3(-1, 0, 0));
    }
    else if (m_stKeyActions.isActive(PitchDownAction))
    {
//         std::puts("Pitch down On!");
        body->applyTorqueLocal(btVector3(1, 0, 0));
    }
    if (m_stKeyActions.isActive(RollClockwiseAction))
    {
//         std::puts("Roll clockwise On!");
        body->applyTorqueLocal(btVector3(0, 0, 1));
    }
    else if (m_stKeyActions.isActive(RollAnticlockwiseAction))
    {
//         std::puts("Roll anticlockwise On!");
        body->applyTorqueLocal(btVector3(0, 0, -1));
    }
    if (m_stKeyActions.isActive(YawLeftAction))
    {
//          std::puts("Roll clockwise On!");
        body->applyTorqueLocal(btVector3(0, -1, 0));
    }
    else if (m_stKeyActions.isActive(YawRightAction))
    {
//         std::puts("Roll anticlockwise On!");
        body->applyTorqueLocal(btVector3(0, 1, 0));
    }
    if (m_trKeyActions.isTriggered(IncreaseMassAction))
    {
        m_controlTarget->setMass(m_controlTarget->getMass() + 1);
    }
    if (m_trKeyActions.isTriggered(DecreaseMassAction))
    {
        m_controlTarget->setMass(m_controlTarget->getMass() - 1);
    }

    auto wnode = m_controlTarget->getWorld();
    auto rayResult = m_controlTarget->rayTestClosest(m_rayStart, m_rayStop);
    m_hit = rayResult.hasHit();
    if (m_hit)
    {
        m_hitBody = (btRigidBody*)(rayResult.m_collisionObject);
        auto target = BulletBodySceneNode::getNode(m_hitBody);
        m_hitName = target->getName();
    }
    else { m_hitName = nullptr; m_hitBody = nullptr; }

    if (m_trKeyActions.isTriggered(ToggleGrasp))
    {
        if (m_hitBody && !m_joint)
        {
            m_joint = m_controlTarget->attachFixed(m_hitBody);
        }
        else if (m_joint)
        {
            wnode->deleteConstraint(m_joint);
            m_joint = nullptr;
        }
    }

    if (m_trKeyActions.isTriggered(ToggleThrust))
    {
        auto thruster = dynamic_cast<Thruster*>(m_controlTarget->getRootComponent().getChildSafe(0));
        if (!thruster)  puts("No thruster found!");
        thruster->setOn(!thruster->isOn());
    }

    m_trKeyActions.reset();

    auto r = m_controlTarget->getRotation();
    m_sfDisplay.setValue(-r.X);
    m_sfDisplay.updateRectangle();

    m_trDisplay.updateContent(m_controlTarget->getBodyTransform());
    m_trDisplay.updateRectangle();
    auto mass = m_controlTarget->getMass();
    auto delta = m_controlTarget->getLastDelta();
    m_massText.updateContent(false, mass, m_hit, m_hitName);
    auto lv = m_controlTarget->getLinearVelocity();
    m_velText.updateContent(lv);
    auto la = m_controlTarget->getLinearAcceleration();
    m_accText.updateContent(la);
    auto lf = m_controlTarget->getAppliedForce();
    m_forceText.updateContent(lf);
    m_infoRoot.updateRectangle();
}

void IOSP::MagicSimpleRocketControlPanel::render()
{
}

void IOSP::MagicSimpleRocketControlPanel::drawUI()
{
    m_trDisplay.draw();
    m_infoRoot.draw();
    m_sfDisplay.draw();
    auto node = m_controlTarget;
    if (node)
    {
        auto tr = node->getBodyTransform();
        auto start = tr * m_rayStart;
        auto stop = tr * m_rayStop;
        auto *drv = getVideoDriver();
        drv->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());
        drv->draw3DLine(fromBullet(start), fromBullet(stop));
    }
}

void IOSP::MagicSimpleRocketControlPanel::OnRegisterSceneNode()
{
    if (IsVisible)
        SceneManager->registerNodeForRendering(this);

    ISceneNode::OnRegisterSceneNode();
}
