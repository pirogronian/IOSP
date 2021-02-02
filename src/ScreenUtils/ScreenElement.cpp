
#include <Utils/RelativeValue.h>

#include "ScreenElement.h"

using namespace IOSP;
using namespace irr;

IOSP::ScreenElement::ScreenElement(ScreenElement *parent)
{
    if (!parent)  return;
    parent->addChild(this);
}

void IOSP::ScreenElement::updateRectangle()
{
    Rectangle rect;
    if (m_parent) rect = m_parent->rectangle();
    else
    {
        auto drv = getDriver();
        if (!drv)  return;
        auto sdim = drv->getCurrentRenderTargetSize();
        rect.UpperLeftCorner.X = 0;
        rect.UpperLeftCorner.Y = 0;
        rect.LowerRightCorner.X = sdim.Width;
        rect.LowerRightCorner.Y = sdim.Height;
    }
    m_rect.UpperLeftCorner.X = nestedRangeRelativeBegin(
        (int)rect.UpperLeftCorner.X, (int)rect.LowerRightCorner.X, (int)m_dim.Width, m_hAlign);
    m_rect.UpperLeftCorner.Y = nestedRangeRelativeBegin(
        (int)rect.UpperLeftCorner.Y, (int)rect.LowerRightCorner.Y, (int)m_dim.Height, m_vAlign);
    m_rect.LowerRightCorner.X = m_rect.UpperLeftCorner.X + m_dim.Width;
    m_rect.LowerRightCorner.Y = m_rect.UpperLeftCorner.Y + m_dim.Height;
}

bool IOSP::ScreenElement::addChild(ScreenElement *c)
{
    if (!c || c == this || m_children.hasItem(c))  return false;
    m_children.addItem(c);
    c->m_parent = this;
    return true;
}

bool IOSP::ScreenElement::removeChild(ScreenElement *c)
{
    if (m_children.removeItem(c))
    {
        c->m_parent = nullptr;
        return true;
    }
    return false;
}

void IOSP::ScreenElement::updateChildren()
{
    for(auto& child: m_children)
        child->update();
}

void IOSP::ScreenElement::drawChildren()
{
    for(auto& child: m_children)
        child->draw();
}
