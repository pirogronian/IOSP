
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
}

void IOSP::BulletWorldSceneNode::OnRegisterSceneNode()
{
    if (IsVisible)
        SceneManager->registerNodeForRendering(this);
    ISceneNode::OnRegisterSceneNode();
}

void IOSP::BulletWorldSceneNode::stepSimulation(btScalar d)
{
    for(std::size_t i = 0; i < m_updatableIndex.size(); i++)
    {
        if (m_updatableIndex.contains(i))
            m_updatableIndex.get(i)->update(d);
    }
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
    m_world.addRigidBody(b->bulletRigidBody());
    return registerUpdatable(b);
}

bool IOSP::BulletWorldSceneNode::removeBody(BulletBodySceneNode *b)
{
    m_world.removeRigidBody(b->bulletRigidBody());
    return unregisterUpdatable(b);
}
