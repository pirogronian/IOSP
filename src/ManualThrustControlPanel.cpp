
#include "ManualThrustControlPanel.h"

using namespace irr;
using namespace IOSP;

ManualThrustControlPanel::ManualThrustControlPanel(
            irr::scene::ISceneNode *parent,
            irr::scene::ISceneManager *smgr,
            irr::s32 id,
            const irr::core::vector3df& pos,
            const irr::core::vector3df& rot)
        : ControlPanelSceneNode(parent, smgr, id, pos, rot)
{
    auto gui = getGUIEnvironment();
    m_window = gui->addWindow(
        core::recti(5, 50, 155, 255),
        false,
        L"Linear thrusters");
    m_ltListbox = gui->addListBox(core::recti(5, 20, 145, 35), m_window, LinearThrusterListBox);
}

void ManualThrustControlPanel::scanForLinearThrusters()
{
    auto tr = m_controlTarget;
    if (!tr)  return;
    m_lths.clear();
    auto n = tr->getComponentIndexSize();
    for(std::size_t i = 0; i < n; i++)
    {
        auto c = tr->getComponent(i);
        if (!c)  continue;
        auto lth = dynamic_cast<LinearThruster*>(c);
        if (!lth)  continue;
        m_lths.push_back(i);
    }
}
