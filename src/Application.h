
#pragma once

#include <irrlicht.h>

#include <CGUITTFont.h>
#include <Utils/InputKeyActionManager.h>
#include <Simulation.h>
#include <Settings.h>
#include <ScreenUtils/ScreenText.h>

namespace IOSP
{
    class Application : public irr::IEventReceiver
    {
    public:
        enum Actions
        {
            TimeFaster = 1,
            TimeSlower,
            LoadTTF
        };
        enum GuiElements
        {
            OpenTTFButton = 1,
            OpenTTFFileDialog
        };
    protected:
        irr::IrrlichtDevice *m_dev{nullptr};
        irr::video::IVideoDriver *m_drv{nullptr};
        irr::scene::ISceneManager *m_smgr{nullptr};
        irr::io::IFileSystem *m_fs{nullptr};
        irr::gui::IGUIEnvironment *m_gui{nullptr};
        Simulation *m_simulation{nullptr};
        irr::gui::IGUIStaticText *m_guiRunStats{nullptr};
        irr::gui::IGUIButton *m_loadTTFButton{nullptr};
        SimpleInputKeyTriggeredActionManager m_trKeyActions;
        irr::io::path m_basePath;
        Settings m_settings;
        ScreenText m_sampleText{"Sample text"};
    public:
        Application();
        ~Application();
        irr::IrrlichtDevice *device() { return m_dev; }
        const irr::IrrlichtDevice *device() const { return m_dev; }
        Simulation *simulation() { return m_simulation; }
        const Simulation *simulation() const { return m_simulation; }
        void setSimulation(Simulation *s) { m_simulation = s; }
        bool OnEvent(const irr::SEvent&) override;
        bool OnGuiEvent(const irr::SEvent::SGUIEvent&);
//         bool OnKeyInput(const irr::SEvent::SKeyInput&);
        void run();
        bool loadTTF(const irr::io::path&, const irr::u32);
        bool openTTFLoadFileDialog()
        {
            m_gui->addFileOpenDialog(L"Load TTF file", true, nullptr, OpenTTFFileDialog);
            return true;
        }
    };
}
