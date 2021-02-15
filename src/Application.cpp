
#include <cstdio>
#include <Utils/IrrCommonObject.h>
#include <ThirdPersonCamera.h>
#include "Application.h"

using namespace IOSP;

using namespace irr;

Application::Application()
{
    IrrCommonObject::setThrowOnNull(true);
    m_dev = irr::createDevice(
        irr::video::EDT_OPENGL,
        irr::core::dimension2d<irr::u32>(800, 600),
        16, false, true, true, this
    );

    if (!m_dev)  return;
    IrrCommonObject::setDevice(m_dev);
    m_smgr = m_dev->getSceneManager();
    m_drv = m_dev->getVideoDriver();
    m_gui = m_dev->getGUIEnvironment();
    m_fs = m_dev->getFileSystem();

    m_basePath = m_fs->getWorkingDirectory();

    m_settings.setFilesystem(m_fs);

    m_settings.path() = m_basePath + "/Config.xml";
    m_settings.load();
    m_settings.printFonts();
    Settings::Font dfont = m_settings.getFont();
    if (!dfont.file.empty()) loadTTF(dfont.file, dfont.size);

    m_trKeyActions.bind(TimeFaster, irr::KEY_PRIOR);
    m_trKeyActions.bind(TimeSlower, irr::KEY_NEXT);

    m_guiRunStats = m_gui->addStaticText(L"Static text", irr::core::rect<irr::s32>(0, 0, 200, 15));
    m_guiRunStats->setDrawBackground(true);
    m_loadTTFButton = m_gui->addButton(irr::core::rect<irr::s32>(0, 20, 50, 35), 0, OpenTTFButton, L"Load font");
}

bool Application::OnEvent(const SEvent& event)
{
    if (event.EventType == irr::EET_GUI_EVENT)
    {
        if (OnGuiEvent(event.GUIEvent))  return true;
    }
    if (m_trKeyActions.OnEvent(event))
    {
        if (m_trKeyActions.isTriggered(TimeFaster))  m_simulation->setTimeMultiplier(m_simulation->timeMultiplier() + 1);
        if (m_trKeyActions.isTriggered(TimeSlower))  m_simulation->setTimeMultiplier(m_simulation->timeMultiplier() - 1);
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
                    if (!loadTTF(fname, 14))
                    {
                        irr::core::stringw text("Cannot load TrueType font from file: ");
                        text += fname;
                        m_gui->addMessageBox(L"Cannot load font!", text.c_str());
                    }
                    else m_settings.setFont(L"Default", fname, 14);
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
    while(m_dev->run())
    {
        m_simulation->update();

        if (m_uiTimer.update(m_dev->getTimer()->getTime()))
            updateUI();
        m_drv->beginScene(true, true, irr::video::SColor(0,50,50,50));
        ThirdPersonCamera::updateAll();
        m_smgr->drawAll();
        m_simulation->drawDebug();
        m_gui->drawAll();
        m_drv->endScene();
        irr::core::stringw wcaption = L"IOSP [";
        wcaption += m_drv->getFPS();
        wcaption += L" fps]";
        m_dev->setWindowCaption(wcaption.c_str());
    }
}

bool IOSP::Application::loadTTF(const irr::io::path& fname, const irr::u32 size)
{
    auto *font = irr::gui::CGUITTFont::createTTFont(m_dev, fname, size);
    if (!font)
        return false;
    m_gui->getSkin()->setFont(font);
    return true;
}

IOSP::Application::~Application()
{
    m_settings.save();
    m_dev->drop();
}
