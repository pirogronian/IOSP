
#include <cassert>

#include <exception>

#include <Utils/Dump.h>
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
}

int IOSP::SettingsWindow::getParam(const gui::IGUIElement *ptr, int def)
{
    auto node = m_guiIntMap.find(ptr);
    if (!node)  return def;
    return node->getValue();
}

void IOSP::SettingsWindow::createContent()
{
    if (!m_settings)  throw std::logic_error("Cannot create settings window: no settings provided!");
    if (m_window)  throw std::logic_error("Cannot create settings window: Content already created!");
    auto size = getVideoDriver()->getCurrentRenderTargetSize();
    auto gui = getGUIEnvironment();
    m_window = gui->addWindow(
        core::recti(50, 50, size.Width - 50, size.Height - 50),
        true, L"Settings", 0, SettingsDialog);
    auto tab = gui->addTabControl(getWindowContentRectangle(m_window), m_window);
    tab->setAlignment(gui::EGUIA_SCALE, gui::EGUIA_SCALE, gui::EGUIA_SCALE, gui::EGUIA_SCALE);
    m_fontTab = tab->addTab(L"Fonts");
    auto variousTab = tab->addTab(L"Various");
    createFontTabContent(m_fontTab);
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
    m_maxFontButtonsWidth = maxW;
    for (int i = 0; i < TotalFontCount; i++)
    {
        auto ifont = getFont(i);
        auto fname = getFontName(i).c_str();
        const wchar_t *fpath = nullptr;
        gui::IGUIFont *font = ifont;
        if (!font) { font = defFont; fpath = L""; }
        else fpath = m_settings->getFont(getFontName(i)).file.c_str();
        auto size = font->getDimension(fname);
        size.Width = maxW + 2*getTextPadding();
        size.Height += 2*getTextPadding();
        core::recti rect(core::position2d(p, ch), size);
        auto butt = gui->addButton(rect, tab, FontButton, fname, fpath);
        setParam(butt, i);
        butt->setOverrideFont(font);
        ch += size.Height + p;
    }
}

void IOSP::SettingsWindow::createFontEdit(int i)
{
    if (m_fontEditGroup)
    {
//         std::printf("Already existing font group: used by %i\n", m_fontEditGroup->getReferenceCount());
        m_fontTab->removeChild(m_fontEditGroup);
//         m_fontEditGroup->drop();
    }
    auto gui = getGUIEnvironment();
    auto p = getPadding();
    auto tp = getTextPadding();
    int ch = p;
    int few = m_maxFontButtonsWidth + 2 * (p + tp);
    auto fname = getFontName(i);
    m_currentFont = m_settings->getFont(fname);
    const wchar_t *fpath = L"[not set]";
    if (m_currentFont.size) fpath = m_currentFont.file.c_str();
//     std::printf("Current font name: %ls\n", fname.c_str());
//     std::printf("Current font size: %i\n", m_currentFont.size);
    auto font = getFont();
    auto fnsize = font->getDimension(fname.c_str());
    fnsize.Width += 2 * tp;
    fnsize.Height += 2 * tp;
    auto fpsize = font->getDimension(fpath);
    fpsize.Width += 2 * tp;
    fpsize.Height += 2 * tp;
    auto totH = fnsize.Height + fpsize.Height + 25 + 4 * p;
    auto totW = fnsize.Width > fpsize.Width ? fnsize.Width : fpsize.Width;
    if (totW < 75) totW = 75;
    totW += 2 * p;
    m_fontEditGroup = gui->addStaticText(
        L"",
        core::recti(core::position2d(few, p), core::dimension2d(totW, totH)),
        true, true, m_fontTab);
    core::recti titleRect(core::position2d(p, ch), fnsize);
//     dump(titleRect);
    auto title = gui->addStaticText(
        fname.c_str(),
        titleRect,
        true, true, m_fontEditGroup
    );
    ch += fnsize.Height + p;
    core::recti pathRect(core::position2d(p, ch), fpsize);
//     dump(pathRect);
    auto button = gui->addButton(
        pathRect,
        m_fontEditGroup, FontPathButton, fpath
    );
    ch += fpsize.Height + p;
    core::recti sizeRect(core::position2d(p, ch), core::dimension2d(75, 25));
    auto spin = gui->addSpinBox(L"?", sizeRect, true, m_fontEditGroup, FontSizeSpinbox);
    setParam(spin, i);
    spin->setStepSize(1);
    spin->setDecimalPlaces(0);
    spin->getEditBox()->setTextAlignment(gui::EGUIA_LOWERRIGHT, gui::EGUIA_CENTER);
    if (m_currentFont.size)
    {
        spin->setRange(5, 30);
        spin->setValue(m_currentFont.size);
    } else spin->setEnabled(false);
}

IOSP::SettingsWindow::~SettingsWindow()
{
//     m_window->drop();
    s_window = nullptr;
}

bool IOSP::SettingsWindow::OnEvent(const SEvent& event)
{
    bool ret = false;
    if (event.EventType == EET_GUI_EVENT)
    {
        auto gevent = event.GUIEvent;
        auto caller = gevent.Caller;
        auto id = caller ? caller->getID() : -1;
        switch (gevent.EventType)
        {
            case gui::EGET_ELEMENT_CLOSED:
            {
                if (id == SettingsDialog)
                {
                    delete this;
//                     ret = true;
                }
            }
            break;
            case gui::EGET_BUTTON_CLICKED:
            {
                if (id == FontButton)
                {
                    int i = getParam(caller, -1);
                    if (i >= 0)  createFontEdit(i);
                }
                break;
            }
            break;
            case gui::EGET_SPINBOX_CHANGED:
            {
                if (id == FontSizeSpinbox)
                {
                    int i = getParam(caller, -1);
                    if (i >= 0)
                    {
                        std::printf("Setting font size for: %ls (%i)\n", getFontName(i).c_str(), i);
                        Settings::Font f = m_settings->getFont(getFontName(i));
                        if (!f.file.empty())
                        {
                            int size = static_cast<gui::IGUISpinBox*>(caller)->getValue();
                            if (setTTF(f.file.c_str(), size, i))
                            {
                                m_settings->setFont(getFontName(i), f.file.c_str(), size);
                            }
                        }
                    }
                    break;
                }
            }
            default:
                ;
        }
    }
    return ret;
}
