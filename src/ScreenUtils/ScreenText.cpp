
#include <cstdio>
#include <cstdarg>

#include "ScreenText.h"

using namespace irr;
using namespace IOSP;

void IOSP::ScreenText::updateContent(bool children)
{
    auto f = getFont();
    if (!f)  return;
    m_reqDim = createBaseFromInner(f->getDimension(m_text.c_str()));
//     ScreenElement::updateRectangle();
    if (children)  updateChildrenContent();
}

void IOSP::ScreenText::draw(bool children)
{
    drawBackground();
    gui::IGUIFont *f = getFont();
    if (!f)  return;
    f->draw(m_text, getInner(), m_color);
//     std::printf("draw: %ls\n", m_text.c_str());
    if (children) drawChildren();
}

void IOSP::ScreenFormattedText::setValues(int n, ...)
{
    va_list args;
    va_start(args, n);
    va_end(args);
    char ft[m_maxLen];
    vsnprintf(ft, m_maxLen, m_f, args);
    m_text = ft;
}

void IOSP::ScreenFormattedText::setValues(va_list args)
{
    char ft[m_maxLen];
    vsnprintf(ft, m_maxLen, m_f, args);
    m_text = ft;
}

void IOSP::ScreenFormattedText::updateContent(bool children, ...)
{
    va_list args;
    va_start (args, children);
    va_end(args);
    setValues(args);
    ScreenText::updateContent(children);
}
