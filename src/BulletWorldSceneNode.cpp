
#include <Utils/Dump.h>
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
    for(std::size_t i = 0; i < m_bodiesIndex.size(); i++)
    {
        if (m_bodiesIndex.contains(i))
            m_bodiesIndex.get(i)->update(d);
    }
    stepSimulation(((btScalar)d) / 1000);
}

void IOSP::BulletWorldSceneNode::stepSimulation(btScalar d)
{
    m_world.stepSimulation(d, m_maxSubSteps, m_minStepDelta);
}

bool IOSP::BulletWorldSceneNode::addBody(BulletBodySceneNode *b)
{
    if (m_bodiesIndex.contains(b->getWorldIndex()))  return false;
    b->setWorld(this);
    if (b->getRigidBody())  m_world.addRigidBody(b->getRigidBody());
    auto i = m_bodiesIndex.add(b);
    b->setWorldIndex(i);
    b->m_world = this;
    return true;
}

bool IOSP::BulletWorldSceneNode::removeBody(BulletBodySceneNode *b)
{
    if (!m_bodiesIndex.contains(b->getWorldIndex()))  return false;
    b->setWorld(nullptr);
    if (b->getRigidBody())  m_world.removeRigidBody(b->getRigidBody());
    m_bodiesIndex.remove(b->getWorldIndex());
    b->setWorldIndex(std::numeric_limits<std::size_t>::max());
    b->m_world = nullptr;
    return true;
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
