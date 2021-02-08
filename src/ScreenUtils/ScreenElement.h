
#pragma once

#include <irrlicht.h>
#include <Utils/Conversions.h>
#include <Utils/LinkedList.h>
#include <Utils/IrrCommonObject.h>
#include <ScreenUtils/ScreenRectangle.h>

namespace IOSP
{
    class ScreenElement : public IrrCommonObject, public ScreenRectangle
    {
    public:
        enum BackgroundPolicy
        {
            NoBackground,
            UseParentBackground,
            UseOwnBackground
        };
        enum ResizePolicy
        {
            CanExpand = 1,
            CanShrink = 2
        };
    protected:
        Dimension m_reqDim;
        LinkedPtrList<ScreenElement> m_children;
        ScreenElement *m_parent{nullptr};
        float m_vAlign{0};
        float m_hAlign{0};
        int m_vShift{0};
        int m_hShift{0};
        bool m_dirty{false}; // Actually, I dont see any useful usage of it for now.
        static irr::video::SColor s_bg;
        irr::video::SColor m_bg{0, 0, 0, 0};
        BackgroundPolicy m_bgPolicy{UseOwnBackground};
        irr::video::SColor m_color{255, 255, 255, 255};
        int m_resizePolicy{3};
        irr::gui::IGUIFont *m_font{nullptr};
    public:
        ScreenElement(ScreenElement *p = nullptr);
        virtual ~ScreenElement() {}
        Dimension getRequestedDimension(Layer l = Base) const;
        void setRequestedDimension(const Dimension& d) { m_reqDim = d; }
        void setRequestedDimension(irr::u32 w, irr::u32 h) { m_reqDim.Width = w; m_reqDim.Height = h; }
        float verticalAlignment() const { return m_vAlign; }
        float horizontalAlignment() const { return m_hAlign; }
        void setVerticalAlignment(float a) { m_vAlign = a; }
        void setHorizontalAlignment(float a) { m_hAlign = a; }
        void setAlignment(float h, float v) { m_hAlign = h; m_vAlign = v; }
        int getVerticalShift() const { return m_vShift; }
        int getHorizontalShift() const { return m_hShift; }
        void setVerticalShift(int v) { m_vShift = v; }
        void setHorizontalShift(int h) { m_hShift = h; }
        void setShift(int h, int v) { m_hShift = h; m_vShift = v; }
        bool isDirty() const { return m_dirty; }
        void setDirty(bool d) { m_dirty = d; }
        irr::video::SColor& getDefaultBackgroundColor() { return s_bg; }
        const irr::video::SColor& getDefaultBackgroundColor() const { return s_bg; }
        irr::video::SColor& getOwnBackgroundColor() { return m_bg; }
        const irr::video::SColor& getBackgroundColor() const { return m_bg.getAlpha() ? m_bg : s_bg; }
        BackgroundPolicy getBackgroundPolicy() const { return m_bgPolicy; }
        void setBackgroundPolicy(BackgroundPolicy bp) { m_bgPolicy = bp; }
        irr::video::SColor& getColor() { return m_color; }
        const irr::video::SColor& getColor() const { return m_color; }
        int getResizePolicy() const { return m_resizePolicy; }
        void setResizePolicy(int f) { m_resizePolicy = f; }
        bool canExpand() const { return m_resizePolicy & CanExpand; }
        bool canShrink() const { return m_resizePolicy & CanShrink; }
        void setCanExpand(bool);
        void setCanShrink(bool);
        void fitRequestedDimension();
        void adjustGeometry();
        irr::gui::IGUIFont *getDefaultFont() { return IrrCommonObject::getFont(); }
        const irr::gui::IGUIFont *getDefaultFont() const { return IrrCommonObject::getFont(); }
        irr::gui::IGUIFont *getFont() { return m_font ? m_font : getDefaultFont(); }
        const irr::gui::IGUIFont *getFont() const { return m_font ? m_font : getDefaultFont(); }
        void setFont(irr::gui::IGUIFont *f) { m_font = f; }
        virtual bool addChild(ScreenElement *);
        virtual bool removeChild(ScreenElement *);
        Rectangle calculateTotalChildrenRectangle() const;
        Dimension calculateTotalChildrenDimension() const
        {
            return toUnsigned(calculateTotalChildrenRectangle().getSize());
        }
        virtual void updateChildrenContent(bool children = true);
        virtual void updateContent(bool children = true)
        {
            if (children)
                updateChildrenContent(children);
        }
        virtual void updateRectangle(bool children = true);
        virtual void updateChildrenRectangle(bool children = true);
        virtual void drawBackground();
        virtual void drawChildren(bool children = true);
        virtual void draw(bool children = true)
        {
            drawBackground();
            if (children)
                drawChildren(children);
        }
    };
};
