
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
