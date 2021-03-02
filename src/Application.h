
#pragma once

#include <irrlicht.h>

#include <IrrIMGUI/IrrIMGUI.h>

#include <CGUITTFont.h>
#include <Utils/InputKeyActionManager.h>
#include <Simulation.h>
#include <Settings.h>
#include <ScreenUtils/ScreenText.h>
#include <Utils/IntervalTimer.h>
#include <Utils/CommonObject.h>
#include <Gui.h>

namespace IOSP
{
    class Application : public irr::IEventReceiver, public CommonObject
    {
    public:
        enum Actions
        {
            TimeFaster = 1,
            TimeSlower,
            CameraNext,
            CameraPrev,
            CameraClone,
            CameraDelete,
            LoadTTF,
            SettingsAction
        };
    protected:
        Simulation *m_simulation{nullptr};
        irr::gui::IGUIStaticText *m_guiRunStats{nullptr};
//         irr::gui::IGUIButton *m_loadTTFButton{nullptr};
        SimpleInputKeyTriggeredActionManager m_trKeyActions;
        irr::io::path m_basePath;
        Settings m_settings;
        IntervalTimer m_uiTimer{100};
        static Application *s_instance;
        IrrIMGUI::CIMGUIEventReceiver m_irrImGuiER;
        IrrIMGUI::IIMGUIHandle *m_irrImGui{nullptr};
    public:
        static Application *getInstance() { return s_instance; }
        Application();
        ~Application();
        Settings &getSettings() { return m_settings; }
        const Settings &getSettings() const { return m_settings; }
        Simulation *simulation() { return m_simulation; }
        const Simulation *simulation() const { return m_simulation; }
        void setSimulation(Simulation *s) { m_simulation = s; }
        bool OnEvent(const irr::SEvent&) override;
        bool OnGuiEvent(const irr::SEvent::SGUIEvent&);
//         bool OnKeyInput(const irr::SEvent::SKeyInput&);
        void updateUI();
        void updateImGui();
        void run();
        void loadFonts();
        bool loadTTF(const irr::io::path&, const irr::u32, irr::u8 = 0);
        TTF getTTF(irr::u8 type) { return m_settings.getTTF(type); }
        bool openTTFLoadFileDialog()
        {
            getGUIEnvironment()->addFileOpenDialog(L"Load TTF file", true, nullptr, OpenTTFFileDialog);
            return true;
        }
        void openSettingsDialog();
    };
}
