
#include "AbstractControlPanelSceneNode.h"

using namespace IOSP;

IOSP::AbstractControlPanelSceneNode::AbstractControlPanelSceneNode(
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

IOSP::AbstractControlPanelSceneNode::~AbstractControlPanelSceneNode()
{
    m_dev->drop();
    if (m_rootGui != nullptr)
        m_rootGui->drop();
}

void IOSP::AbstractControlPanelSceneNode::setVisible(bool v)
{
    if (m_rootGui != nullptr)
        m_rootGui->setVisible(v);
    irr::scene::ISceneNode::setVisible(v);
}

bool IOSP::KeyInputAbstractControlPanel::OnEvent(const irr::SEvent& event)
{
    bool trRet{false}, stRet{false};
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    {
        if (m_trKeyActions)
            trRet = m_trKeyActions->OnKeyInput(event.KeyInput);
        if (m_stKeyActions)
            stRet = m_stKeyActions->OnKeyInput(event.KeyInput);
    }
    return trRet || stRet;
}
