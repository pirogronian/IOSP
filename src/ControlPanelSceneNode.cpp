
#include <cstdio>
#include "ControlPanelSceneNode.h"

using namespace IOSP;

IOSP::ControlPanelSceneNode::ControlPanelSceneNode(
            irr::scene::ISceneNode *parent,
            irr::scene::ISceneManager *smgr,
            irr::s32 id,
            const irr::core::vector3df& pos,
            const irr::core::vector3df& rot)
: irr::scene::ISceneNode(parent, smgr, id, pos, rot)
{
}

IOSP::ControlPanelSceneNode::~ControlPanelSceneNode()
{
    if (m_controlTarget)
        m_controlTarget->drop();
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
    bool ret = false;
    if (event.EventType != irr::EET_KEY_INPUT_EVENT)  return false;
    bool trRet{false}, stRet{false};
    trRet = m_trKeyActions.OnKeyInput(event.KeyInput);
    stRet = m_stKeyActions.OnKeyInput(event.KeyInput);
    ret = trRet || stRet;
    if (ret) return true;
    for(auto child : getChildren())
    {
        auto panel = dynamic_cast<ControlPanelSceneNode*>(child);
        if (!panel)  continue;
        ret = panel->OnEvent(event);
        if (ret)  return true;
    }
    return false;
}
