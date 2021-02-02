
#pragma once

#include <array>
#include <irrlicht.h>

namespace IOSP
{
    class ScreenRectangle
    {
    public:
        enum Side
        {
            Left = 0,
            Top = 1,
            Right = 2,
            Bottom = 3
        };
        class Spacers : public std::array<int, 4>
        {
        public:
            Spacers(int v) : std::array<int, 4>{v, v, v, v} {}
            Spacers(int v1, int v2, int v3, int v4) : std::array<int, 4>{v1, v2, v3, v4} {}
            void set(int v) { fill(v); }
            void set(Side s, int v) { (*this)[s] = v; }
            void set(int v1, int v2, int v3, int v4)
            {
                set(Left, v1);
                set(Top, v2);
                set(Right, v3);
                set(Bottom, v4);
            }
        };
        typedef irr::core::rect<irr::s32> Rectangle;
        typedef irr::core::dimension2d<irr::u32> Dimension;
    protected:
        static Spacers s_padding;
        static Spacers s_margin;
        Spacers m_padding{0, 0, 0, 0};
        Spacers m_margin{0, 0, 0, 0};
        Rectangle m_rect;
    public:
        ScreenRectangle() : m_padding{s_padding}, m_margin{s_margin} {}
        Spacers& getPadding() { return m_padding; }
        const Spacers getPadding() const { return m_padding; }
        int getPadding(Side s) const { return m_padding[s]; }
        Spacers& getMargin() { return m_margin; }
        const Spacers& getMargin() const { return m_margin; }
        int getMargin(Side s) const { return m_margin[s]; }
        Rectangle& getBase() { return m_rect; }
        const Rectangle& getBase() const { return m_rect; }
        void setBase(const Rectangle& other) { m_rect = other; }
        Rectangle getInner() const
        {
            return Rectangle(
                m_rect.UpperLeftCorner.X + m_padding[Left],
                m_rect.UpperLeftCorner.Y + m_padding[Top],
                m_rect.LowerRightCorner.X - m_padding[Right],
                m_rect.LowerRightCorner.Y - m_padding[Bottom]);
        }
        Rectangle getOuter() const
        {
            return Rectangle(
                m_rect.UpperLeftCorner.X + m_margin[Left],
                m_rect.UpperLeftCorner.Y + m_margin[Top],
                m_rect.LowerRightCorner.X - m_margin[Right],
                m_rect.LowerRightCorner.Y - m_margin[Bottom]);
        }
        Dimension fromInner(const Dimension& inner) const
        {
            return Dimension(
                inner.Width + getPadding(Left) + getPadding(Right),
                inner.Height + getPadding(Top) + getPadding(Bottom));
        }
        Dimension fromOuter(const Dimension& inner) const
        {
            return Dimension(
                inner.Width - getMargin(Left) - getMargin(Right),
                inner.Height - getMargin(Top) - getMargin(Bottom));
        }
    };
}
