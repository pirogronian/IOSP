
#include "ScreenText.h"

using namespace irr;
using namespace IOSP;

const gui::IGUIFont * IOSP::ScreenText::font() const
{
    auto *g = gui();
    if (!g)  return nullptr;
    return g->getSkin()->getFont();
}

gui::IGUIFont * IOSP::ScreenText::font()
{
    auto *g = gui();
    if (!g)  return nullptr;
    return g->getSkin()->getFont();
}

void IOSP::ScreenText::update()
{
    auto f = font();
    if (!f)  return;
    m_dim = f->getDimension(m_text.c_str());
    ScreenElement::update();
}

void IOSP::ScreenText::draw()
{
    auto *drv = driver();
    if (!drv)  return;
    drv->draw2DRectangle(video::SColor(128, 128, 64, 32), m_rect);
    gui::IGUIFont *f = font();
    if (!f)  return;
    f->draw(m_text, m_rect, m_color);
    drawChildren();
}
