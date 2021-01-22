
#include <cstdio>

#include "TestControlPanel.h"

using namespace IOSP;

void IOSP::TestControlPanel::update()
{
    if (m_isThrust && m_target != nullptr)
    {
        m_target->bulletRigidBody()->applyForce(btVector3(0, 0, -3), btVector3(0, 0, 0));
        auto f = m_target->bulletRigidBody()->getTotalForce();
//         std::printf("Total force: [%f, %f, %f]\n", f.getX(), f.getY(), f.getZ());
    }
}

void IOSP::TestControlPanel::render() { update(); }

bool IOSP::TestControlPanel::OnEvent(const irr::SEvent& event)
{
//     std::puts("TestControlPanel::OnEvent");
    if (event.EventType != irr::EET_KEY_INPUT_EVENT)  return false;
//     std::printf("TestControlPanel::OnEvent(Key %i)\n", event.KeyInput.Key);
    if (event.KeyInput.Key == irr::KEY_UP)
    {
        if (event.KeyInput.PressedDown)  m_isThrust = true;
        else m_isThrust = false;
        return true;
    }
    return false;
}

void IOSP::TestControlPanel::OnRegisterSceneNode()
{
    if (IsVisible)
        SceneManager->registerNodeForRendering(this);

    ISceneNode::OnRegisterSceneNode();
}
