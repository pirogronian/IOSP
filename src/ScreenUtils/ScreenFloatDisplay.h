
#pragma once

#include <ScreenUtils/ScreenText.h>

namespace IOSP
{
    class AbstractScreenFloatDisplay : public ScreenFormattedText
    {
    protected:
        void setValues(int, ...);
        void setValues(va_list);
        void updateContent(bool, ...);
        irr::core::stringc m_format;
    public:
        AbstractScreenFloatDisplay(ScreenElement *p = nullptr) : ScreenFormattedText(p) {}
        virtual void setFormat(unsigned char, unsigned char, const char *caption = nullptr) = 0;
    };

    class SimpleFloatDisplay : public AbstractScreenFloatDisplay
    {
    public:
        SimpleFloatDisplay(ScreenElement *p = nullptr) : AbstractScreenFloatDisplay(p) {}
        void setFormat(unsigned char, unsigned char, const char * = nullptr) override;
        void setValue(double v)
        {
            ScreenFormattedText::setValues(1, v);
        }
        void updateContent(bool c = true) override {
            ScreenFormattedText::updateContent(c);
        }
        void updateContent(double v, bool children = true)
        {
            ScreenFormattedText::updateContent(children, v);
        }
    };

    class SimpleFloat3Display : public AbstractScreenFloatDisplay
    {
    public:
        SimpleFloat3Display(ScreenElement *p = nullptr) : AbstractScreenFloatDisplay(p) {}
        void setFormat(unsigned char, unsigned char, const char * = nullptr) override;
        void setValues(double x, double y, double z)
        {
            ScreenFormattedText::setValues(3, x, y, z);
        }
        void updateContent(double x, double y, double z, bool c = true)
        {
            ScreenFormattedText::updateContent(c, x, y, z);
        }
        void updateContent(const btVector3& v, bool c = true)
        {
            updateContent(v.getX(), v.getY(), v.getZ(), c);
        }
        void updateContent(const irr::core::vector3df& v, bool c = true)
        {
            updateContent(v.X, v.Y, v.Z, c);
        }
    };

    class ScaleFloatDisplay : public ScreenElement
    {
    protected:
        float m_valScale{1};
        float m_valShift{0};
        float m_visScale{1};
        double m_value{0};
        SimpleFloatDisplay m_sfd{this};
    public:
        ScaleFloatDisplay(ScreenElement *p = nullptr) : ScreenElement(p) {}
        float getValueScale() const { return m_valScale; }
        void setValueScale(float s) { m_valScale = s; }
        float getValueShift() const { return m_valShift; }
        void setValueShift(float v) { m_valShift = v; }
        double getValue() const { return m_valScale; }
        void setValue(double v) { m_value = v; }
        float getVisualScale() const { return m_visScale; }
        void setVisualScale(float s) { m_visScale = s; }
        SimpleFloatDisplay& getText() { return m_sfd; }
        const SimpleFloatDisplay& getText() const { return m_sfd; }
        double getLineValue(double i) const { return i * m_valScale + m_valShift; }
        double getRelativeLinePosition(double i) const { return -(getLineValue(i) - m_value) * m_visScale; }
        double getAbsoluteLinePosition(double i) const {
            return getInner().getCenter().Y + getRelativeLinePosition(i);
        }
        double getLineNumberFromValue(double v) const { return (v - m_valShift)/m_valScale; }
        double getRelativeFromAbsolutePosition(double abs) const { return abs - getBase().getCenter().Y; }
        double getLineNumberFromRelativePosition(double pos) const {
            return -getLineNumberFromValue((pos) / m_visScale - m_value);
        }
        double getLineNumberFromAbsolutePosition(double pos) const {
            return getLineNumberFromRelativePosition(getRelativeFromAbsolutePosition(pos));
        }
        void setFormat(unsigned char total, unsigned char frac) { m_sfd.setFormat(total, frac); }
        void draw(bool children = true) override;
    };
}
