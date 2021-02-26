
#include <Utils/Conversions.h>

#include "BulletBodySceneNode.h"

using namespace IOSP;

void IOSP::BulletBodySceneNode::setRigidBody(btRigidBody *body)
{
    clearRigidBody();
    m_bbody = body;
    m_bbody->setUserPointer(this);
    m_bbody->setActivationState(DISABLE_DEACTIVATION);
    m_bbody->setMotionState(&m_mstate);
    syncInertia();
    syncTransform();
    if (m_world)  m_world->addRigidBody(m_bbody);
}

void IOSP::BulletBodySceneNode::clearRigidBody()
{
    if (m_bbody)
    {
        m_bbody->setUserPointer(nullptr);
        m_bbody->setMotionState(nullptr);
        if (m_world) m_world->removeRigidBody(m_bbody);
        m_bbody = nullptr;
    }
}

void IOSP::BulletBodySceneNode::setWorld(btDynamicsWorld *w)
{
    if (m_world && m_bbody)  m_world->removeRigidBody(m_bbody);
    m_world = w;
    if (m_world && m_bbody)  m_world->addRigidBody(m_bbody);
}

IOSP::BulletBodySceneNode::BulletBodySceneNode(
    irr::scene::ISceneNode *parent,
    irr::scene::ISceneManager *smgr,
    const btRigidBody::btRigidBodyConstructionInfo& info,
    irr::s32 id)
: irr::scene::ISceneNode(parent, smgr, id)
{
//     assert(getSceneManager() == smgr);
    auto rb = new btRigidBody(info);
    setRigidBody(rb);
}

IOSP::BulletBodySceneNode::BulletBodySceneNode(
    irr::scene::ISceneNode *parent,
    irr::scene::ISceneManager *smgr,
    btRigidBody *body,
    irr::s32 id)
: irr::scene::ISceneNode(parent, smgr, id)
{
//     assert(getSceneManager() == smgr);
    setRigidBody(body);
}

IOSP::BulletBodySceneNode::~BulletBodySceneNode()
{
    delete m_bbody;
}

void IOSP::BulletBodySceneNode::syncTransform()
{
    if (!m_bbody)  return;
    auto& pos = getPosition();
    auto rot = degToRad(getRotation());
    btTransform tr(btQuaternion(rot.Y, rot.X, rot.Z), btVector3(pos.X, pos.Y, pos.Z));
    m_bbody->setWorldTransform(tr);
}

void IOSP::BulletBodySceneNode::syncInertia()
{
    if (!m_bbody)  return;
    auto m = m_bbody->getMass();
    m_bbody->setMassProps(m, btVector3(m, m, m));
}

void IOSP::BulletBodySceneNode::setMass(btScalar m)
{
    if (!m_bbody)  return;
    m_bbody->setMassProps(m, btVector3(m, m, m));
}

void IOSP::BulletBodySceneNode::update(irr::u32 dt)
{
    if (!m_bbody)  return;
    m_lastDelta = static_cast<btScalar>(dt) / 1000;
    btScalar d = m_lastDelta;
    auto lv = m_bbody->getLinearVelocity();
    auto la = (lv - m_lVel)/d;
    m_lVel = lv;
    m_lAccel = la;
    m_rootComponent.update(this, dt);
}

btFixedConstraint *IOSP::BulletBodySceneNode::attachFixed(btRigidBody *body)
{
    if (!m_world)  return nullptr;
    auto wnode = BulletWorldSceneNode::getNode(m_world);
    if (!wnode)  return nullptr;
    return wnode->createFixedConstraint(getRigidBody(), body);
}

btFixedConstraint *IOSP::BulletBodySceneNode::attachFixed(BulletBodySceneNode *node)
{
    if (!m_world)  return nullptr;
    auto wnode = BulletWorldSceneNode::getNode(m_world);
    if (!wnode)  return nullptr;
    return wnode->createFixedJoint(this, node);
}
