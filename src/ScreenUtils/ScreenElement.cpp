
#include <cassert>
#include <algorithm>
#include <Utils/RelativeValue.h>

#include "ScreenElement.h"

#include <cstdio>

using namespace IOSP;
using namespace irr;

video::SColor IOSP::ScreenElement::s_bg{128, 0, 0, 0};

IOSP::ScreenElement::ScreenElement(ScreenElement *parent)
{
    if (!parent)  return;
    parent->addChild(this);
}

ScreenRectangle::Dimension IOSP::ScreenElement::getRequestedDimension(ScreenRectangle::Layer layer) const
{
    if (layer == Base)  return m_reqDim;
    auto dim = m_reqDim;
    if (layer == Inner)
    {
        dim.Width += (getPadding(Left) + getPadding(Right));
        dim.Height += (getPadding(Top) + getPadding(Bottom));
        return dim;
    }
    if (layer == Outer)
    {
        dim.Width += (getMargin(Left) + getMargin(Right));
        dim.Height += (getMargin(Top) + getMargin(Bottom));
        return dim;
    }
    assert((true, "Invalid layer for requested dimension!"));
}

void IOSP::ScreenElement::setCanExpand(bool f)
{
    if (f)
        m_resizePolicy |= CanExpand;
    else
        m_resizePolicy &= ~CanExpand;
}

void IOSP::ScreenElement::setCanShrink(bool f)
{
    if (f)
        m_resizePolicy |= CanShrink;
    else
        m_resizePolicy &= ~CanShrink;
}

void IOSP::ScreenElement::fitRequestedDimension()
{
    auto cdim = calculateTotalChildrenDimension();
    if (m_reqDim.Width < cdim.Width && canExpand())  m_reqDim.Width = cdim.Width;
    if (m_reqDim.Width > cdim.Width && canShrink())  m_reqDim.Width = cdim.Width;
    if (m_reqDim.Height < cdim.Height && canExpand())  m_reqDim.Height = cdim.Height;
    if (m_reqDim.Height > cdim.Height && canShrink())  m_reqDim.Height = cdim.Height;
}

void IOSP::ScreenElement::adjustGeometry()
{
    updateRectangle();
    fitRequestedDimension();
    updateRectangle();
}

void IOSP::ScreenElement::updateRectangle(bool children)
{
    Rectangle rect;
    Dimension dim = createOuterFromBase(m_reqDim);
    if (m_parent) rect = m_parent->getInner();
    else
    {
        auto drv = getVideoDriver();
        if (!drv)  return;
        auto sdim = drv->getCurrentRenderTargetSize();
        rect.UpperLeftCorner.X = 0;
        rect.UpperLeftCorner.Y = 0;
        rect.LowerRightCorner.X = sdim.Width;
        rect.LowerRightCorner.Y = sdim.Height;
    }
    auto &m_rect = getBase();
    m_rect.UpperLeftCorner.X = rect.UpperLeftCorner.X + nestedRangeRelativeBegin(
        (int)rect.UpperLeftCorner.X,
        (int)rect.LowerRightCorner.X,
        (int)dim.Width,
        m_hAlign) + getMargin(Left) + m_hShift;
    m_rect.UpperLeftCorner.Y = rect.UpperLeftCorner.Y + nestedRangeRelativeBegin(
        (int)rect.UpperLeftCorner.Y,
        (int)rect.LowerRightCorner.Y,
        (int)dim.Height,
        m_vAlign) + getMargin(Top) + m_vShift;
    m_rect.LowerRightCorner.X = m_rect.UpperLeftCorner.X + m_reqDim.Width;
    m_rect.LowerRightCorner.Y = m_rect.UpperLeftCorner.Y + m_reqDim.Height;
    if (children)  updateChildrenRectangle(children);
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

ScreenRectangle::Rectangle IOSP::ScreenElement::calculateTotalChildrenRectangle() const
{
    bool empty = true;
    Rectangle ret;
    for (auto &child: m_children)
    {
        Rectangle cr = child->getOuter();
        if (empty)
        {
            ret = cr;
            empty = false;
        }
        else
        {
            ret.UpperLeftCorner.X = std::min(cr.UpperLeftCorner.X, ret.UpperLeftCorner.X);
            ret.UpperLeftCorner.Y = std::min(cr.UpperLeftCorner.Y, ret.UpperLeftCorner.Y);
            ret.LowerRightCorner.X = std::max(cr.LowerRightCorner.X, ret.LowerRightCorner.X);
            ret.LowerRightCorner.Y = std::max(cr.LowerRightCorner.Y, ret.LowerRightCorner.Y);
        }
    }
    return ret;
}

void IOSP::ScreenElement::updateChildrenContent(bool children)
{
    for(auto& child: m_children)
        child->updateContent(children);
}

void IOSP::ScreenElement::updateChildrenRectangle(bool children)
{
    for(auto& child: m_children)
        child->updateRectangle(children);
}

void IOSP::ScreenElement::drawBackground()
{
    if (m_bgPolicy == NoBackground || (m_bgPolicy == UseParentBackground && m_parent))  return;
    auto drv = getVideoDriver();
    if (!drv)  return;
//     std::printf(
//         "Draw background at: [%i, %i, %i, %i]\n",
//         m_rect.UpperLeftCorner.X,
//         m_rect.UpperLeftCorner.Y,
//         m_rect.LowerRightCorner.X,
//         m_rect.LowerRightCorner.Y);
    drv->draw2DRectangle(getBackgroundColor(), m_rect);
    if (m_frame)  drv->draw2DRectangleOutline(getBase(), getColor());
}

void IOSP::ScreenElement::drawChildren(bool children)
{
    for(auto& child: m_children)
        child->draw(children);
}
