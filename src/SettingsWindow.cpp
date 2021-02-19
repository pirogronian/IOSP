
#include <exception>

#include "SettingsWindow.h"
#include <Application.h>

using namespace IOSP;
using namespace irr;

IOSP::SettingsWindow *IOSP::SettingsWindow::s_window{nullptr};

int IOSP::SettingsWindow::s_titleBarH{20};
int IOSP::SettingsWindow::s_padding{2};
int IOSP::SettingsWindow::s_textPadding{5};

core::recti IOSP::SettingsWindow::getElementContentRectangle(const gui::IGUIElement *parent)
{
    auto size = parent->getAbsolutePosition().getSize();
    auto p = getPadding();
    return core::recti(p, p, size.Width - 2 * p, size.Height - 2 * p);
}

core::recti IOSP::SettingsWindow::getWindowContentRectangle(const gui::IGUIWindow *parent)
{
    auto ret = getElementContentRectangle(parent);
    ret.UpperLeftCorner.Y += getTitleBarHeight();
    return ret;
}

IOSP::SettingsWindow::SettingsWindow()
{
    if (s_window)  throw std::logic_error("Another instance of SettingsWindow already in use!");
    s_window = this;
    auto size = getVideoDriver()->getCurrentRenderTargetSize();
    auto gui = getGUIEnvironment();
    m_window = gui->addWindow(
        core::recti(50, 50, size.Width - 50, size.Height - 50),
        true, L"Settings", 0, Application::SettingsDialog);
    auto tab = gui->addTabControl(getWindowContentRectangle(m_window), m_window);
    tab->setAlignment(gui::EGUIA_SCALE, gui::EGUIA_SCALE, gui::EGUIA_SCALE, gui::EGUIA_SCALE);
    auto fontTab = tab->addTab(L"Fonts");
    auto variousTab = tab->addTab(L"Various");
    createFontTabContent(fontTab);
}

void IOSP::SettingsWindow::createFontTabContent(irr::gui::IGUITab *tab)
{
    int p = getPadding();
    int ch = p;
    int maxW = 0;
    auto gui = getGUIEnvironment();
    auto defFont = getFont();
    for (int i = 0; i < TotalFontCount; i++)
    {
        auto ifont = getFont(i);
        auto fname = getFontName(i).c_str();
        gui::IGUIFont *font = ifont;
        if (!font)  font = defFont;
        auto size = font->getDimension(fname);
        if (size.Width > maxW) maxW = size.Width;
    }
    for (int i = 0; i < TotalFontCount; i++)
    {
        auto ifont = getFont(i);
        auto fname = getFontName(i).c_str();
        gui::IGUIFont *font = ifont;
        if (!font)  font = defFont;
        auto size = font->getDimension(fname);
        size.Width = maxW + 2*getTextPadding();
        size.Height += 2*getTextPadding();
        core::recti rect(core::position2d(p, ch), size);
        auto butt = gui->addButton(rect, tab, -1, fname);
        butt->setOverrideFont(font);
        ch += size.Height + p;
    }
}

IOSP::SettingsWindow::~SettingsWindow()
{
    m_window->drop();
    s_window = nullptr;
}
