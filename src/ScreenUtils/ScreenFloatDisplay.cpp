
#include <Utils/FloatFormatString.h>

#include "ScreenFloatDisplay.h"

using namespace irr;
using namespace IOSP;

void IOSP::SimpleFloatDisplay::setFormat(unsigned char total, unsigned char frac, const char *caption)
{
    if (total > 0)
    {
        char ffs[64];
        generateFloatFormatString(ffs, total, frac);
        char vfs[m_maxLen];
        if (caption)
            snprintf(vfs, m_maxLen, "%s: %s", caption, ffs);
        else
            snprintf(vfs, m_maxLen, "%s", ffs);
        m_format = vfs;
    }
    ScreenFormattedText::setFormat(m_format.c_str());
}

void IOSP::SimpleFloat3Display::setFormat(unsigned char total, unsigned char frac, const char *caption)
{
    char ffs[64];
    generateFloatFormatString(ffs, total, frac);
    char vfs[m_maxLen];
    if (caption)
        snprintf(vfs, m_maxLen, "%s: [%s, %s, %s]", caption, ffs, ffs, ffs);
    else
        snprintf(vfs, m_maxLen, "[%s, %s, %s]", ffs, ffs, ffs);
    m_format = vfs;
    ScreenFormattedText::setFormat(m_format.c_str());
}

btVector3 IOSP::SimpleTransformDisplay::getRotation(const btTransform& tr)
{
    btScalar x, y, z;
    tr.getRotation().getEulerZYX(z, y, x);
    return btVector3(x, y, z);
}

IOSP::SimpleTransformDisplay::SimpleTransformDisplay(ScreenElement *p) : ScreenElement(p)
{
    setCanShrink(true);
    setCanExpand(true);
    setFormat(9, 4);
    updateContent(btTransform::getIdentity());
    m_pos.setAlignment(0.5, 0);
    m_rot.setAlignment(0.5, 0);
    auto H = m_pos.getRequestedDimension(ScreenRectangle::Outer).Height;
    m_rot.setShift(0, H);
    adjustGeometry();
}

void IOSP::SimpleTransformDisplay::setFormat(unsigned char total, unsigned char fraction)
{
    m_pos.setFormat(total, fraction, "Position");
    m_rot.setFormat(total, fraction, "Rotation");
}

void IOSP::SimpleTransformDisplay::setValue(const btTransform &tr)
{
    auto p = tr.getOrigin();
    auto r = getRotation(tr);
    m_pos.setValue(p);
    m_rot.setValue(r);
}

void IOSP::SimpleTransformDisplay::updateContent(const btTransform &tr)
{
    auto p = tr.getOrigin();
    auto r = getRotation(tr);
    m_pos.updateContent(p);
    m_rot.updateContent(r);
}

void IOSP::ScaleFloatDisplay::draw(bool children)
{
    auto *drv = getVideoDriver();
    auto color = getColor();
    int top = getInner().UpperLeftCorner.Y;
    int bottom = getInner().LowerRightCorner.Y;
    int left = getInner().UpperLeftCorner.X;
    int right = getInner().LowerRightCorner.X;
//     int hcenter = left + (right - left) / 2
    int linei = getLineNumberFromAbsolutePosition(top);
    int linep = getAbsoluteLinePosition(linei);
    auto ts = m_sfd.getOuter().getSize();
//     std::printf(
//         "First line nr %i (val: %f) at: %i (rel: %f), betweem %i and %i\n",
//                 linei, getLineValue(linei), linep, getRelativeFromAbsolutePosition(linep), top, bottom);
    core::position2d<s32> lstart, lend;
    while (linep <= bottom)
    {
//         std::printf("Line nr %i at: %i, betweem %i and %i\n", linei, linep, top, bottom);
        double val = getLineValue(linei);
        lstart.X = left;
        lstart.Y = linep;
        lend.X = right;
        lend.Y = linep;
        drv->draw2DLine(lstart, lend, color);
        m_sfd.updateContent(val);
        m_sfd.setShift((right - left), getRelativeLinePosition(linei) + (bottom - top)/2 - ts.Height / 2);
        m_sfd.updateRectangle();
//         std::printf("Line %i, val %f, format: \"%s\", text: \"%ls\"\n", linei, val, m_sfd.getFormat(), m_sfd.getText().c_str());
        m_sfd.draw();
        linei--;
        linep = getAbsoluteLinePosition(linei);
    }
}
