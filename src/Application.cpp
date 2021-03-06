
#include <cstdio>
#include <Utils/Ownership.h>
#include <Utils/IrrCommonObject.h>
#include <ThirdPersonCamera.h>
#include <Gui.h>
#include <SettingsWindow.h>
#include "Application.h"

using namespace IOSP;

using namespace irr;

Application *Application::s_instance{nullptr};

Application::Application()
{
    if (s_instance)  std::puts("Another Application object already exists!");
    s_instance = this;
    IrrCommonObject::setThrowOnNull(true);
    ImGui::CreateContext();
    auto dev = irr::createDevice(
        irr::video::EDT_OPENGL,
        irr::core::dimension2d<irr::u32>(800, 600),
        16, false, true, true, this
    );

    if (!dev)  return;
    IrrCommonObject::setDevice(dev);

    m_basePath = getFileSystem()->getWorkingDirectory();

    m_settings.path() = m_basePath + "/Config.xml";
    m_settings.load();
    m_settings.printFonts();
    loadFonts();

    m_trKeyActions.bind(TimeFaster, irr::KEY_PRIOR);
    m_trKeyActions.bind(TimeSlower, irr::KEY_NEXT);
    m_trKeyActions.bind(SettingsAction, irr::KEY_ESCAPE);
    m_trKeyActions.bind(CameraNext, irr::KEY_F1);
    m_trKeyActions.bind(CameraPrev, irr::KEY_F1, true);
    m_trKeyActions.bind(CameraClone, irr::KEY_INSERT);
    m_trKeyActions.bind(CameraDelete, irr::KEY_DELETE);
    m_trKeyActions.bind(CameraMode, irr::KEY_TAB, false, true);
    int a = m_trKeyActions.boundAction(irr::KEY_TAB, false, true);

    m_irrImGui = IrrIMGUI::createIMGUI(dev, &m_irrImGuiER);
}

bool Application::OnEvent(const SEvent& event)
{
    if (m_irrImGuiER.OnEvent(event))  return true;
    if (SettingsWindow::isOpen())
    {
        if (SettingsWindow::getInstance()->OnEvent(event))
            return true;
        return false;
    }
    if (event.EventType == irr::EET_GUI_EVENT)
    {
        if (OnGuiEvent(event.GUIEvent))  return true;
    }
    if (m_trKeyActions.OnEvent(event))
    {
        if (m_trKeyActions.isTriggered(TimeFaster))
            m_simulation->setTimeMultiplier(m_simulation->timeMultiplier() + 1);
        if (m_trKeyActions.isTriggered(TimeSlower))
            m_simulation->setTimeMultiplier(m_simulation->timeMultiplier() - 1);
        if (m_useTPC)
        {
            if (m_trKeyActions.isTriggered(CameraNext))
                ThirdPersonCamera::switchCurrentNext();
            if (m_trKeyActions.isTriggered(CameraPrev))
                ThirdPersonCamera::switchCurrentPrevious();
            if (m_trKeyActions.isTriggered(CameraClone))
                ThirdPersonCamera::cloneCurrent();
            if (m_trKeyActions.isTriggered(CameraDelete))
                ThirdPersonCamera::deleteCurrent();
        }
        if (m_trKeyActions.isTriggered(CameraMode))
            m_useTPC = !m_useTPC;
        if (m_trKeyActions.isTriggered(SettingsAction))
            openSettingsDialog();
        m_trKeyActions.reset();
        return true;
    }
    if (m_simulation)
    {
        if (m_simulation->OnEvent(event))  return true;
    }

    return false;
}

bool IOSP::Application::OnGuiEvent(const irr::SEvent::SGUIEvent& ge)
{
    auto *caller = ge.Caller;
    assert(caller);
    auto id = caller->getID();
    switch(id)
    {
        default:
            ;
    }
    return false;
}

void IOSP::Application::updateUI()
{
}

void IOSP::Application::updateImGui()
{
    irr::core::stringc dtext = "Delta time: ";
    dtext += m_simulation->lastDelta();
    dtext += ", mult: ";
    dtext += m_simulation->timeMultiplier();
    ImGui::Begin("Statistics");
    ImGui::Text(dtext.c_str());
    ImGui::End();
}

void resetDrv(video::IVideoDriver *drv)
{
    video::SMaterial mat;
    drv->setMaterial(mat);
}

void IOSP::Application::run()
{
    auto dev = getDevice();
    auto drv = getVideoDriver();
    while(dev->run())
    {
        m_simulation->update();

        drv->beginScene(true, true, irr::video::SColor(0,50,50,50));
        ThirdPersonCamera::updateCurrent();
        getSceneManager()->drawAll();
        resetDrv(drv);
        m_simulation->drawDebug();
        ImGuiIDs.reset();
        if (m_uiTimer.update(dev->getTimer()->getTime()))
            updateUI();
        m_simulation->drawUI();
        getGUIEnvironment()->drawAll();
        m_irrImGui->startGUI();
        m_simulation->updateImGui();
        updateImGui();
        m_irrImGui->drawAll();
        drv->endScene();
        irr::core::stringw wcaption = L"IOSP [";
        wcaption += drv->getFPS();
        wcaption += L" fps]";
        dev->setWindowCaption(wcaption.c_str());
    }
}

bool IOSP::Application::loadTTF(const irr::io::path& fname, const irr::u32 size, u8 type)
{
    if (setTTF(fname, size, type))
    {
        m_settings.setTTF(fname, size, type);
        return true;
    }
    return false;
}

void IOSP::Application::loadFonts()
{
    for (int i = 0; i < InvalidFont; i++)
    {
        auto ttf = m_settings.getTTF(i);
        if (ttf.size && !ttf.file.empty())
        {
            std::printf("Load TTF: [%ls (%i)]: { %ls, %i }\n", getFontName(i).c_str(), i, ttf.file.c_str(), ttf.size);
            setTTF(ttf.file.c_str(), ttf.size, i);
        }
    }
}

void IOSP::Application::openSettingsDialog()
{
    if (SettingsWindow::isOpen())
    {
        std::printf("SettingsWindow already open! (%p)\n", SettingsWindow::getInstance());
        return;
    }
    m_simulation->setTimeMultiplier(0);
    auto win = new SettingsWindow();
    win->createContent();
}

IOSP::Application::~Application()
{
    m_settings.printFonts();
    m_settings.save();
    s_instance = nullptr;
}
