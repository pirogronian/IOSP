
#pragma once

#include <Utils/CommonObject.h>

namespace IOSP
{
    class SettingsWindow : public CommonObject
    {
        static SettingsWindow *s_window;
        static int s_titleBarH;
        static int s_padding;
        static int s_textPadding;
        irr::gui::IGUIWindow *m_window{nullptr};
    public:
        static bool isOpen() { return s_window != nullptr; }
        static int getTitleBarHeight() { return s_titleBarH; }
        static int getPadding() { return s_padding; }
        static int getTextPadding() { return s_textPadding; }
        static irr::core::recti getWindowContentRectangle(const irr::gui::IGUIWindow*);
        static irr::core::recti getElementContentRectangle(const irr::gui::IGUIElement*);
        static SettingsWindow *getInstance() { return s_window; }
        SettingsWindow();
        ~SettingsWindow();
        void createFontTabContent(irr::gui::IGUITab *);
    };
}
