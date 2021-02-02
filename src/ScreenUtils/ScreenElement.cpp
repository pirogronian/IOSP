
#include <Utils/RelativeValue.h>

#include "ScreenElement.h"

using namespace IOSP;
using namespace irr;

video::SColor IOSP::ScreenElement::s_bg{128, 0, 0, 0};

IOSP::ScreenElement::ScreenElement(ScreenElement *parent)
{
    if (!parent)  return;
    parent->addChild(this);
}

void IOSP::ScreenElement::updateRectangle()
{
    Rectangle rect;
    Dimension dim = fromInner(m_reqDim);
    if (m_parent) rect = m_parent->getInner();
    else
    {
        auto drv = getDriver();
        if (!drv)  return;
        auto sdim = drv->getCurrentRenderTargetSize();
        rect.UpperLeftCorner.X = getMargin(Top);
        rect.UpperLeftCorner.Y = getMargin(Left);
        rect.LowerRightCorner.X = sdim.Width - getMargin(Right);
        rect.LowerRightCorner.Y = sdim.Height - getMargin(Bottom);
    }
    auto &m_rect = getBase();
    m_rect.UpperLeftCorner.X = nestedRangeRelativeBegin(
        (int)rect.UpperLeftCorner.X,
        (int)rect.LowerRightCorner.X,
        (int)dim.Width,
        m_hAlign);
    m_rect.UpperLeftCorner.Y = nestedRangeRelativeBegin(
        (int)rect.UpperLeftCorner.Y,
        (int)rect.LowerRightCorner.Y,
        (int)dim.Height,
        m_vAlign);
    m_rect.LowerRightCorner.X = m_rect.UpperLeftCorner.X + dim.Width;
    m_rect.LowerRightCorner.Y = m_rect.UpperLeftCorner.Y + dim.Height;
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
