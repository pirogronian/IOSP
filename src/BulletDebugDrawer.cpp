
#include <cstdio>
#include <Utils/Conversions.h>
#include "BulletDebugDrawer.h"

using namespace IOSP;

void IOSP::BulletDebugDrawer::drawLine(const btVector3& start, const btVector3& end, const btVector3& color)
{
//     std::printf("drawLine()\n");
    m_drv->draw3DLine(fromBullet(start), fromBullet(end), toIrrlichtColor(color));
}

void IOSP::BulletDebugDrawer::drawContactPoint(
    const btVector3& PointOnB,
    const btVector3& normalOnB,
    btScalar distance,
    int lifeTime,
    const btVector3& color)
{
    
}

void IOSP::BulletDebugDrawer::reportErrorWarning(const char* warningString)
{
    std::puts(warningString);
}

void IOSP::BulletDebugDrawer::draw3dText(const btVector3& location, const char* textString)
{
    
}
