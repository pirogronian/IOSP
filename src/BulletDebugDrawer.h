
#pragma once

#include <irrlicht.h>

#include <btBulletDynamicsCommon.h>

namespace IOSP
{
    class BulletDebugDrawer : public btIDebugDraw
    {
        int m_mode{btIDebugDraw::DBG_NoDebug};
        irr::video::IVideoDriver *m_drv{nullptr};
    public:
        BulletDebugDrawer(irr::video::IVideoDriver *drv) : m_drv(drv) {}
        void setDebugMode(int mode) override { m_mode = mode; }
        int getDebugMode() const override { return m_mode; }
        void drawLine(const btVector3&, const btVector3&, const btVector3&) override;
        void drawContactPoint(const btVector3&, const btVector3&, btScalar, int, const btVector3&) override;
        void reportErrorWarning(const char*) override;
        void draw3dText(const btVector3&, const char*) override;
    };
}
