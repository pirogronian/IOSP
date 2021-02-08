
#pragma once

#include <cstring>
#include <irrlicht.h>
#include <ScreenUtils/ScreenElement.h>

namespace IOSP
{
    class ScreenText : public ScreenElement
    {
    protected:
        irr::core::stringw m_text;
    public:
        using ScreenElement::updateContent;
        using ScreenElement::draw;
        ScreenText(ScreenElement *parent = nullptr) : ScreenElement(parent) {}
        ScreenText(const irr::core::stringw& text, ScreenElement *parent = nullptr)
        : m_text{text}, ScreenElement(parent) {}
        ~ScreenText() {}
        const irr::core::stringw& text() const { return m_text; }
        void setText(const irr::core::stringw& t) { m_text = t; }
        void setText(const wchar_t *t) { m_text = t; }
        const irr::core::stringw& getText() const { return m_text; }
        void updateContent(bool children = true) override;
        void draw(bool children = true) override;
    };

    class ScreenFormattedText : public ScreenText
    {
    protected:
        const char *m_f{nullptr};
        std::size_t m_maxLen{1024};
    public:
        using ScreenText::updateContent;
        const char *getFormat() const { return m_f; }
        void setFormat(const char *f) { m_f = f; }
        std::size_t getMaxLen() const { return m_maxLen; }
        void setMaxLen(std::size_t n) { m_maxLen = n; }
        void setValues(int , ...);
        void setValues(va_list);
        void updateContent(bool, ...);
        ScreenFormattedText(ScreenElement *parent = nullptr) : ScreenText(parent) {}
        ScreenFormattedText(const char *f, ScreenElement *parent = nullptr)
        : ScreenText(parent)
        {
            setFormat(f);
        }
    };
}
