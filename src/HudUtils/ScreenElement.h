
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
        virtual bool addChild(ScreenElement *);
        virtual bool removeChild(ScreenElement *);
        virtual void updateChildren();
        virtual void drawChildren();
        virtual void update()
        {
            updateRectangle();
            updateChildren();
        }
        virtual void draw()
        {
            drawChildren();
        }
    };
};
