
#include "ScreenText.h"

using namespace irr;
using namespace IOSP;

void IOSP::ScreenText::update()
{
    auto f = getFont();
    if (!f)  return;
    m_dim = f->getDimension(m_text.c_str());
    ScreenElement::update();
}

void IOSP::ScreenText::draw()
{
    drawBackground();
    gui::IGUIFont *f = getFont();
    if (!f)  return;
    f->draw(m_text, m_rect, m_color);
    drawChildren();
}
