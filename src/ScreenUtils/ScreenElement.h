
#pragma once

#include <irrlicht.h>
#include <Utils/LinkedList.h>
#include <Utils/IrrlichtObject.h>
#include <ScreenUtils/ScreenRectangle.h>
#include <Utils/Accumulator.h>

namespace IOSP
{
    class ScreenElement : public IrrlichtObject, public ScreenRectangle
    {
    public:
        enum BackgroundPolicy
        {
            NoBackground,
            UseParentBackground,
            UseOwnBackground
        };
    protected:
        Dimension m_reqDim;
        LinkedPtrList<ScreenElement> m_children;
        ScreenElement *m_parent{nullptr};
        float m_vAlign{0};
        float m_hAlign{0};
        bool m_dirty{false}; // Actually, I dont see any useful usage of it for now.
        static irr::video::SColor s_bg;
        irr::video::SColor m_bg{0, 0, 0, 0};
        BackgroundPolicy m_bgPolicy{UseOwnBackground};
        irr::gui::IGUIFont *m_font{nullptr};
        static irr::u32 s_updateDelta;
        irr::u32 m_lastUpdate{0};
        Accumulator<irr::s32> m_updAcc{s_updateDelta};
        bool needsUpdate();
    public:
        ScreenElement(ScreenElement *p = nullptr);
        virtual ~ScreenElement() {}
        Dimension getRequestedDimension() const { return m_reqDim; }
        void setRequestedDimension(const Dimension& d) { m_reqDim; }
        void setRequestedDimension(irr::u32 w, irr::u32 h) { m_reqDim.Width = w; m_reqDim.Height = h; }
        void updateRectangle();
        float verticalAlignment() const { return m_vAlign; }
        float horizontalAlignment() const { return m_hAlign; }
        void setVerticalAlignment(float a) { m_vAlign = a; }
        void setHorizontalAlignment(float a) { m_hAlign = a; }
        bool isDirty() const { return m_dirty; }
        void setDirty(bool d) { m_dirty = d; }
        irr::video::SColor& getDefaultBackgroundColor() { return s_bg; }
        const irr::video::SColor& getDefaultBackgroundColor() const { return s_bg; }
        irr::video::SColor& getOwnBackgroundColor() { return m_bg; }
        const irr::video::SColor& getBackgroundColor() const { return m_bg.getAlpha() ? m_bg : s_bg; }
        BackgroundPolicy getBackgroundPolicy() const { return m_bgPolicy; }
        void setBackgroundPolicy(BackgroundPolicy bp) { m_bgPolicy = bp; }
        irr::gui::IGUIFont *getDefaultFont() { return IrrlichtObject::getFont(); }
        const irr::gui::IGUIFont *getDefaultFont() const { return IrrlichtObject::getFont(); }
        irr::gui::IGUIFont *getFont() { return m_font ? m_font : getDefaultFont(); }
        const irr::gui::IGUIFont *getFont() const { return m_font ? m_font : getDefaultFont(); }
        void setFont(irr::gui::IGUIFont *f) { m_font = f; }
        irr::s32 getUpdateDelta() const { return m_updAcc.referenceDelta(); }
        void setUpdateDelta(irr::s32 d) { m_updAcc.referenceDelta() = d; }
        virtual bool addChild(ScreenElement *);
        virtual bool removeChild(ScreenElement *);
        virtual void updateChildren();
        virtual void drawChildren();
        virtual void update()
        {
            if (!needsUpdate()) return;
            updateRectangle();
            updateChildren();
        }
        virtual void drawBackground()
        {
            if (m_bgPolicy == NoBackground || (m_bgPolicy == UseParentBackground && m_parent))  return;
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
