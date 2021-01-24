
#include <cstdio>

#include <Application.h>

using namespace IOSP;

using namespace irr;

Application::Application()
{
    m_dev = irr::createDevice(
        irr::video::EDT_OPENGL,
        irr::core::dimension2d<irr::u32>(800, 600),
        16, false, true, true, this
    );
    if (!m_dev)  return;
    m_smgr = m_dev->getSceneManager();
    m_drv = m_dev->getVideoDriver();

    m_trKeyActions.bind(TimeFaster, irr::KEY_PRIOR);
    m_trKeyActions.bind(TimeSlower, irr::KEY_NEXT);

    m_guiRunStats = m_gui->addStaticText(L"Static text", irr::core::rect<irr::s32>(0, 0, 200, 15));
    m_guiRunStats->setDrawBackground(true);
}

bool Application::OnEvent(const SEvent& event)
{
    if (m_simulation)
    {
        if (m_simulation->OnEvent(event))  return true;
    }
//     if (event.EventType == irr::EET_KEY_INPUT_EVENT)
//     {
//         if (event.KeyInput.PressedDown)
//             std::printf("Pressed key: %i\n", event.KeyInput.Key);
//     }
    if (m_trKeyActions.OnEvent(event))
    {
        if (m_trKeyActions.isTriggered(TimeFaster))  m_simulation->setTimeMultiplier(m_simulation->timeMultiplier() + 1);
        if (m_trKeyActions.isTriggered(TimeSlower))  m_simulation->setTimeMultiplier(m_simulation->timeMultiplier() - 1);
            m_trKeyActions.reset();
        return true;
    }

    return false;
}

void IOSP::Application::run()
{
    while(m_dev->run())
    {
        m_simulation->update();
        irr::core::stringw dtext = "Delta time: ";
        dtext += m_simulation->lastDelta();
        dtext += ", mult: ";
        dtext += m_simulation->timeMultiplier();
        m_guiRunStats->setText(dtext.c_str());

        m_drv->beginScene(true, true, irr::video::SColor(0,50,50,50));
        m_smgr->drawAll();
        m_gui->drawAll();
        m_simulation->drawDebug();
        m_drv->endScene();
        irr::core::stringw wcaption = L"IOSP [";
        wcaption += m_drv->getFPS();
        wcaption += L" fps]";
        m_dev->setWindowCaption(wcaption.c_str());
    }
}

IOSP::Application::~Application()
{
    m_dev->drop();
}
