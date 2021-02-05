
#pragma once

#include <ScreenUtils/ScreenText.h>

namespace IOSP
{
    class AbstractScreenFloatDisplay : public ScreenFormattedText
    {
    protected:
        irr::core::stringc m_format;
    public:
        AbstractScreenFloatDisplay(ScreenElement *p = nullptr) : ScreenFormattedText(p) {}
        virtual void setFormat(unsigned char, unsigned char, const char *caption = nullptr) = 0;
    };

    class SimpleVector3Display : public AbstractScreenFloatDisplay
    {
    protected:
        void setValues(int, ...);
        void setValues(va_list);
    public:
        SimpleVector3Display(ScreenElement *p = nullptr) : AbstractScreenFloatDisplay(p) {}
        void setFormat(unsigned char, unsigned char, const char * = nullptr) override;
        void setValues(double, double, double);
        void updateContent(bool, double, double, double);
    };
}
