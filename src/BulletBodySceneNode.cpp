
#include <Conversions.h>

#include "BulletBodySceneNode.h"

using namespace IOSP;

IOSP::BulletBodySceneNode::BulletBodySceneNode(
    irr::scene::ISceneNode *parent,
    irr::scene::ISceneManager *smgr,
    const btRigidBody::btRigidBodyConstructionInfo& info,
    irr::s32 id)
: irr::scene::ISceneNode(parent, smgr, id)
{
//     assert(getSceneManager() == smgr);
    m_bbody = new btRigidBody(info);
    m_bbody->setMotionState(&m_mstate);
}

IOSP::BulletBodySceneNode::BulletBodySceneNode(
    irr::scene::ISceneNode *parent,
    irr::scene::ISceneManager *smgr,
    btRigidBody *body,
    irr::s32 id)
: irr::scene::ISceneNode(parent, smgr, id)
{
//     assert(getSceneManager() == smgr);
    m_bbody = body;
    m_bbody->setMotionState(&m_mstate);
}

IOSP::BulletBodySceneNode::~BulletBodySceneNode()
{
    delete m_bbody;
}

void IOSP::BulletBodySceneNode::syncTransform()
{
    auto& pos = getPosition();
    auto rot = degToRad(getRotation());
    btTransform tr(btQuaternion(rot.X, rot.Y, rot.Z), btVector3(pos.X, pos.Y, pos.Z));
    m_bbody->setWorldTransform(tr);
}
