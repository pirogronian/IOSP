
#pragma once

#include <irrlicht.h>

#include <CGUITTFont.h>
#include <Utils/InputKeyActionManager.h>
#include <Simulation.h>
#include <Settings.h>
#include <ScreenUtils/ScreenText.h>
#include <Utils/IntervalTimer.h>
#include <Utils/IrrCommonObject.h>

namespace IOSP
{
    class Application : public irr::IEventReceiver, public IrrCommonObject
    {
    public:
        enum Actions
        {
            TimeFaster = 1,
            TimeSlower,
            LoadTTF,
            SettingsAction
        };
        enum GuiElements
        {
            OpenTTFButton = 1,
            OpenTTFFileDialog,
            SettingsDialog
        };
    protected:
        Simulation *m_simulation{nullptr};
        irr::gui::IGUIStaticText *m_guiRunStats{nullptr};
        irr::gui::IGUIButton *m_loadTTFButton{nullptr};
        SimpleInputKeyTriggeredActionManager m_trKeyActions;
        irr::io::path m_basePath;
        Settings m_settings;
        IntervalTimer m_uiTimer{100};
        static Application *s_instance;
    public:
        static Application *getInstance() { return s_instance; }
        Application();
        ~Application();
        Simulation *simulation() { return m_simulation; }
        const Simulation *simulation() const { return m_simulation; }
        void setSimulation(Simulation *s) { m_simulation = s; }
        bool OnEvent(const irr::SEvent&) override;
        bool OnGuiEvent(const irr::SEvent::SGUIEvent&);
//         bool OnKeyInput(const irr::SEvent::SKeyInput&);
        void updateUI();
        void run();
        bool loadTTF(const irr::io::path&, const irr::u32);
        bool openTTFLoadFileDialog()
        {
            getGUIEnvironment()->addFileOpenDialog(L"Load TTF file", true, nullptr, OpenTTFFileDialog);
            return true;
        }
        void openSettingsDialog();
    };
}
