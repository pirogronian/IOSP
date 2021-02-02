
#pragma once

#include <irrlicht.h>
#include <Utils/LinkedList.h>
#include <Utils/IrrlichtObject.h>

namespace IOSP
{
    class ScreenElement : public IrrlichtObject
    {
    public:
        typedef irr::core::dimension2d<irr::u32> Dimension;
        typedef irr::core::rect<irr::s32> Rectangle;
    protected:
        Dimension m_dim;
        Rectangle m_rect;
        LinkedPtrList<ScreenElement> m_children;
        ScreenElement *m_parent{nullptr};
        float m_vAlign{0};
        float m_hAlign{0};
        bool m_dirty{false}; // Actually, I dont see any useful usage of it for now.
        static irr::video::SColor s_bg;
        irr::video::SColor m_bg{0, 0, 0, 0};
        irr::gui::IGUIFont *m_font{nullptr};
    public:
        ScreenElement(ScreenElement *p = nullptr);
        virtual ~ScreenElement() {}
        const Rectangle& rectangle() const { return m_rect; }
        void updateRectangle();
        float verticalAlignment() const { return m_vAlign; }
        float horizontalAlignment() const { return m_hAlign; }
        void setVerticalAlignment(float a) { m_vAlign = a; }
        void setHorizontalAlignment(float a) { m_hAlign = a; }
        bool isDirty() const { return m_dirty; }
        void setDirty(bool d) { m_dirty = d; }
        irr::video::SColor& getDefaultBackgroundColor() { return s_bg; }
        const irr::video::SColor& getDefaultBackgroundColor() const { return s_bg; }
        irr::video::SColor& getBackgroundColor() { return m_bg.getAlpha() ? m_bg : s_bg; }
        const irr::video::SColor& getBackgroundColor() const { return m_bg.getAlpha() ? m_bg : s_bg; }
        irr::gui::IGUIFont *getDefaultFont() { return IrrlichtObject::getFont(); }
        const irr::gui::IGUIFont *getDefaultFont() const { return IrrlichtObject::getFont(); }
        irr::gui::IGUIFont *getFont() { return m_font ? m_font : getDefaultFont(); }
        const irr::gui::IGUIFont *getFont() const { return m_font ? m_font : getDefaultFont(); }
        void setFont(irr::gui::IGUIFont *f) { m_font = f; }
        virtual bool addChild(ScreenElement *);
        virtual bool removeChild(ScreenElement *);
        virtual void updateChildren();
        virtual void drawChildren();
        virtual void update()
        {
            updateRectangle();
            updateChildren();
        }
        virtual void drawBackground()
        {
            auto drv = getDriver();
            if (!drv)  return;
            drv->draw2DRectangle(getBackgroundColor(), m_rect);
        }
        virtual void draw()
        {
            drawBackground();
            drawChildren();
        }
    };
};
