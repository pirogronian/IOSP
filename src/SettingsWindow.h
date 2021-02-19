
#pragma once

#include <Utils/CommonObject.h>
#include <Settings.h>
#include <Gui.h>

namespace IOSP
{
    class SettingsWindow : public CommonObject, irr::IEventReceiver
    {
        static SettingsWindow *s_window;
        static int s_titleBarH;
        static int s_padding;
        static int s_textPadding;
        irr::gui::IGUIWindow *m_window{nullptr};
        Settings *m_settings{nullptr};
        irr::core::map<void*, int> m_ptrIntMap;
        irr::gui::IGUIStaticText *m_fontEditGroup{nullptr};
        Settings::Font m_currentFont;
        irr::gui::IGUITab *m_fontTab{nullptr};
        int m_maxFontButtonsWidth{0};
    public:
        enum GuiIds {
            FontButton = GlobalGuiMaxId,
            FontPathButton,
            FontSizeSpinbox
        };
        static bool isOpen() { return s_window != nullptr; }
        static int getTitleBarHeight() { return s_titleBarH; }
        static int getPadding() { return s_padding; }
        static int getTextPadding() { return s_textPadding; }
        static irr::core::recti getWindowContentRectangle(const irr::gui::IGUIWindow*);
        static irr::core::recti getElementContentRectangle(const irr::gui::IGUIElement*);
        static SettingsWindow *getInstance() { return s_window; }
        SettingsWindow();
        ~SettingsWindow();
        bool OnEvent(const irr::SEvent&);
        void setSettings(Settings *s) { m_settings = s; }
        void createContent();
        void createFontTabContent(irr::gui::IGUITab *);
        void createFontEdit(int);
    };
}
