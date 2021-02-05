
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
        void setValues(double v)
        {
            ScreenFormattedText::setValues(1, v);
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
    };
}
