
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
    m_ths.scan();
}

void ManualThrustControlPanel::update()
{
    auto lbody = m_controlTarget->getLogicalBody();
    if (!lbody)  return;
    if (trySync(*lbody))
    {
        m_ths.clear();
        scanForThrusters();
    }
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
        auto lt = entry.component;
//         if (!lt)  continue;
        std::string name = lt->getBodyNode()->getComponentName(lt->getGlobalIndex());
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
