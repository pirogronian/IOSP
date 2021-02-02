
#pragma once

#include <irrlicht.h>
#include <ScreenUtils/ScreenElement.h>

namespace IOSP
{
    class ScreenText : public ScreenElement
    {
    protected:
        irr::core::stringw m_text;
        irr::video::SColor m_color{255, 255, 255, 255};
    public:
        ScreenText(ScreenElement *parent = nullptr) : ScreenElement(parent) {}
        ScreenText(const irr::core::stringw& text, ScreenElement *parent = nullptr)
        : m_text{text}, ScreenElement(parent) {}
        ~ScreenText() {}
        irr::video::SColor& color() { return m_color; }
        const irr::video::SColor& color() const { return m_color; }
        irr::core::stringw& text() { return m_text; }
        const irr::core::stringw& text() const { return m_text; }
        void setText(const irr::core::stringw& t) { m_text = t; }
        void setText(const wchar_t *t) { m_text = t; }
        void update();
        void draw();
    };
}
