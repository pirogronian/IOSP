
#include <cstdio>

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
//     std::printf("Target components number: %i\n", n);
    for(std::size_t i = 0; i < n; i++)
    {
        auto c = tr->getComponent(i);
        if (!c)  continue;
//         std::printf("Found component at index: %i\n", i);
        auto lth = dynamic_cast<LinearThruster*>(c);
        if (!lth)  continue;
//         std::printf("Found linear thruster at index: %i\n", i);
        m_lths.push_back(i);
    }
}

void ManualThrustControlPanel::updateImGui()
{
    ImGui::Begin("Thrusters");
    for(int index : m_lths)
    {
        auto c = m_controlTarget->getComponent(index);
        if (!c)  continue;
        auto lt = dynamic_cast<LinearThruster*>(c);
        if (!lt)  continue;
        bool on = lt->isOn();
        ImGui::Checkbox("Thruster", &on);
        if (on != lt->isOn())  lt->setOn(on);
    }
    ImGui::End();
}

void ManualThrustControlPanel::setTarget(BulletBodySceneNode *target)
{
    ControlPanelSceneNode::setTarget(target);
    scanForLinearThrusters();
}
