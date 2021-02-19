
#include <cstdio>
#include <Utils/Ownership.h>
#include <Utils/IrrCommonObject.h>
#include <ThirdPersonCamera.h>
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
    Settings::Font dfont = m_settings.getFont();
    if (!dfont.file.empty()) setTTF(dfont.file, dfont.size);

    m_trKeyActions.bind(TimeFaster, irr::KEY_PRIOR);
    m_trKeyActions.bind(TimeSlower, irr::KEY_NEXT);
    m_trKeyActions.bind(SettingsAction, irr::KEY_ESCAPE);

    auto gui = getGUIEnvironment();
    m_guiRunStats = gui->addStaticText(L"Static text", irr::core::rect<irr::s32>(0, 0, 200, 15));
    m_guiRunStats->setDrawBackground(true);
    m_loadTTFButton = gui->addButton(irr::core::rect<irr::s32>(0, 20, 50, 35), 0, OpenTTFButton, L"Load font");
}

bool Application::OnEvent(const SEvent& event)
{
    if (SettingsWindow::isOpen())
    {
        if (SettingsWindow::getInstance()->OnEvent(event))
            return true;
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
        case OpenTTFFileDialog:
        {
            if (ge.EventType == irr::gui::EGET_FILE_SELECTED)
            {
                std::puts("File selected.");
                auto *dialog = (irr::gui::IGUIFileOpenDialog*)(caller);
                auto *fname = dialog->getFileName();
                if (fname)
                {
                    if (!setTTF(fname, 14))
                    {
                        irr::core::stringw text("Cannot load TrueType font from file: ");
                        text += fname;
                        getGUIEnvironment()->addMessageBox(L"Cannot load font!", text.c_str());
                    }
                    else m_settings.setFont(fname, 14);
                }
                return true;
            }
            return false;
        }
        case OpenTTFButton:
        {
            if (ge.EventType == irr::gui::EGET_BUTTON_CLICKED)
            {
                openTTFLoadFileDialog();
                return true;
            }
            return false;
        }
        default:
            ;
    }
    return false;
}

void IOSP::Application::updateUI()
{
    irr::core::stringw dtext = "Delta time: ";
    dtext += m_simulation->lastDelta();
    dtext += ", mult: ";
    dtext += m_simulation->timeMultiplier();
    m_guiRunStats->setText(dtext.c_str());
}

void IOSP::Application::run()
{
    auto dev = getDevice();
    auto drv = getVideoDriver();
    while(dev->run())
    {
        m_simulation->update();

        if (m_uiTimer.update(dev->getTimer()->getTime()))
            updateUI();
        drv->beginScene(true, true, irr::video::SColor(0,50,50,50));
        ThirdPersonCamera::updateAll();
        getSceneManager()->drawAll();
        m_simulation->drawDebug();
        getGUIEnvironment()->drawAll();
        drv->endScene();
        irr::core::stringw wcaption = L"IOSP [";
        wcaption += drv->getFPS();
        wcaption += L" fps]";
        dev->setWindowCaption(wcaption.c_str());
    }
}

// bool IOSP::Application::loadTTF(const irr::io::path& fname, const irr::u32 size)
// {
//     auto *font = irr::gui::CGUITTFont::createTTFont(getDevice(), fname, size);
//     if (!font)
//         return false;
//     getGUIEnvironment()->getSkin()->setFont(font);
//     return true;
// }

void IOSP::Application::openSettingsDialog()
{
    if (SettingsWindow::isOpen())
    {
        std::printf("SettingsWindow already open! (%p)\n", SettingsWindow::getInstance());
        return;
    }
    m_simulation->setTimeMultiplier(0);
    auto win = new SettingsWindow();
    win->setSettings(&m_settings);
    win->createContent();
}

IOSP::Application::~Application()
{
    m_settings.save();
    s_instance = nullptr;
}
