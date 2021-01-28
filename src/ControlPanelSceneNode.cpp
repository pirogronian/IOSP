
#include <cstdio>
#include "ControlPanelSceneNode.h"

using namespace IOSP;

IOSP::ThirdPersonCamera IOSP::ControlPanelSceneNode::thirdPersonCamera;

IOSP::ControlPanelSceneNode::ControlPanelSceneNode(
            irr::IrrlichtDevice *dev,
            irr::scene::ISceneNode *parent,
            irr::scene::ISceneManager *smgr,
            irr::s32 id,
            const irr::core::vector3df& pos,
            const irr::core::vector3df& rot)
: irr::scene::ISceneNode(parent, smgr, id, pos, rot)
{
    m_dev = dev;
    m_dev->grab();
}

IOSP::ControlPanelSceneNode::~ControlPanelSceneNode()
{
    if (m_controlTarget)
        m_controlTarget->drop();
    m_dev->drop();
    if (m_rootGui != nullptr)
        m_rootGui->drop();
}

void IOSP::ControlPanelSceneNode::setVisible(bool v)
{
    if (m_rootGui != nullptr)
        m_rootGui->setVisible(v);
    irr::scene::ISceneNode::setVisible(v);
}

bool IOSP::ControlPanelSceneNode::OnEvent(const irr::SEvent& event)
{
    if (event.EventType != irr::EET_KEY_INPUT_EVENT)  return false;
    bool trRet{false}, stRet{false};
    if (m_trKeyActions)
        trRet = m_trKeyActions->OnKeyInput(event.KeyInput);
    if (m_stKeyActions)
        stRet = m_stKeyActions->OnKeyInput(event.KeyInput);
//     std::printf("Control panel event accepted: %i, %i\n", trRet, stRet);
    return trRet || stRet;
}
