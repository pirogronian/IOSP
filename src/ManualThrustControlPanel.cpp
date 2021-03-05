
#include <cstdio>

#include <imgui.h>
#include <Gui.h>
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

void ManualThrustControlPanel::scanForThrusters()
{
    auto lbody = m_controlTarget->getLogicalBody();
    if (!lbody)
    {
        std::puts("Cannot scan: No logical body found.");
        return;
    }
    m_ths.setLogicalBody(lbody);
    m_ths.scanForType<Thruster>();
//     auto tr = m_controlTarget;
//     if (!tr)  return;
//     m_ths.clear();
//     auto n = tr->getComponentIndexSize();
//     std::printf("Target components number: %i\n", n);
//     for(std::size_t i = 0; i < n; i++)
//     {
//         auto c = tr->getComponent(i);
//         if (!c)  continue;
//         std::printf("Found component at index: %i\n", i);
//         auto lth = dynamic_cast<Thruster*>(c);
//         if (!lth)  continue;
//         std::printf("Found thruster at index: %i\n", i);
//         m_ths.push_back(i);
//     }
}

void ManualThrustControlPanel::updateImGui()
{
    ImGui::Begin("Thrusters");
    auto lbody = m_controlTarget->getLogicalBody();
    if (!lbody)
    {
        ImGui::Text("No logical body found.");
        ImGui::End();
        return;
    }
    auto bodies = lbody->getBodies();
    for(auto &entry : m_ths.getVector())
    {
        auto lt = dynamic_cast<Thruster*>(entry.node->getComponent(entry.index));
        if (!lt)  continue;
        std::string name = entry.node->getComponentName(entry.index);
        ImGui::Text(name.c_str());
        ImGui::Text("On:"); ImGui::SameLine();
        ImGui::PushID(ImGuiIDs.next());
        bool on = lt->isOn();
        ImGui::Checkbox("", &on);
        ImGui::PopID(); ImGui::SameLine();
        if (on != lt->isOn())  lt->setOn(on);
        float thrust = lt->getDemandedThrust();
        float max = lt->getMaxThrust();
        float min = lt->allowNegativeThrust() ? -max : 0;
        ImGui::Text("Thrust:");
        ImGui::SameLine();
        ImGui::PushID(ImGuiIDs.next());
        ImGui::DragFloat("", &thrust, 0.1, min, max);
        ImGui::PopID(); 
        if (thrust != lt->getDemandedThrust()) lt->setThrust(thrust);
    }
    ImGui::End();
}

void ManualThrustControlPanel::setTarget(BulletBodySceneNode *target)
{
    ControlPanelSceneNode::setTarget(target);
    scanForThrusters();
}
