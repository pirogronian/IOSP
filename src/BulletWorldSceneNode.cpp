
#include <Utils/Dump.h>
#include <BulletUpdatable.h>
#include <BulletBodySceneNode.h>
#include "BulletWorldSceneNode.h"

using namespace IOSP;

IOSP::BulletWorldSceneNode::BulletWorldSceneNode(
    irr::scene::ISceneNode *parent,
    irr::scene::ISceneManager *smgr,
    irr::s32 id,
    const irr::core::vector3df& position,
    const irr::core::vector3df& rotation,
    const irr::core::vector3df& scale)
: irr::scene::ISceneNode(parent, smgr, id, position, rotation, scale)
{
    m_world.setWorldUserInfo(this);
}

void IOSP::BulletWorldSceneNode::OnRegisterSceneNode()
{
    if (IsVisible)
        SceneManager->registerNodeForRendering(this);
    ISceneNode::OnRegisterSceneNode();
}

void IOSP::BulletWorldSceneNode::update(irr::u32 d)
{
    for(std::size_t i = 0; i < m_updatableIndex.size(); i++)
    {
        if (m_updatableIndex.contains(i))
            m_updatableIndex.get(i)->update(d);
    }
    stepSimulation(((btScalar)d) / 1000);
}

void IOSP::BulletWorldSceneNode::stepSimulation(btScalar d)
{
    m_world.stepSimulation(d, m_maxSubSteps, m_minStepDelta);
}

bool IOSP::BulletWorldSceneNode::registerUpdatable(BulletUpdatable *u)
{
    if (m_updatableIndex.contains(u->worldIndex()))  return false;
    auto i = m_updatableIndex.add(u);
    u->setWorldIndex(i);
    u->m_world = this;
    return true;
}

bool IOSP::BulletWorldSceneNode::unregisterUpdatable(BulletUpdatable *u)
{
    if (!m_updatableIndex.contains(u->worldIndex()))  return false;
    m_updatableIndex.remove(u->worldIndex());
    u->setWorldIndex(std::numeric_limits<std::size_t>::max());
    u->m_world = nullptr;
    return true;
}

bool IOSP::BulletWorldSceneNode::addBody(BulletBodySceneNode *b)
{
    b->setWorld(&m_world);
    return registerUpdatable(b);
}

bool IOSP::BulletWorldSceneNode::removeBody(BulletBodySceneNode *b)
{
    b->setWorld(nullptr);
    return unregisterUpdatable(b);
}

btFixedConstraint *IOSP::BulletWorldSceneNode::createFixedJoint(BulletBodySceneNode *body1,
                                                  BulletBodySceneNode *body2,
                                                  const btTransform& tr1,
                                                  const btTransform& tr2)
{
    return createFixedConstraint(body1->getRigidBody(), body2->getRigidBody(), tr1, tr2);
}

btFixedConstraint *IOSP::BulletWorldSceneNode::createFixedConstraint(btRigidBody *body1, btRigidBody *body2)
{
    auto tr1 = btTransform::getIdentity();
//     auto tr2 = body1->getWorldTransform() * body2->getWorldTransform().inverse();
    auto tr2 = body2->getWorldTransform().inverse() * body1->getWorldTransform();
//     dump(tr1);
//     dump(tr2);
//     auto tr2 = body1->getWorldTransform() * body2->getWorldTransform();
    auto cnt = createFixedConstraint(body1, body2, tr1, tr2);
//     dump(cnt->getFrameOffsetA());
//     dump(cnt->getFrameOffsetB());
    return cnt;
}

btFixedConstraint *IOSP::BulletWorldSceneNode::createFixedJoint(
    BulletBodySceneNode *body1,
    BulletBodySceneNode *body2)
{
    return createFixedConstraint(body1->getRigidBody(), body2->getRigidBody());
}
