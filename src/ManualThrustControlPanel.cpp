
#include <imgui.h>

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

void ManualThrustControlPanel::updateImGui()
{
    ImGui::Begin("Thrusters");
    ImGui::End();
}
