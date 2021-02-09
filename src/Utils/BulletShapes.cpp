
#include <Utils/Conversions.h>

#include "BulletShapes.h"

using namespace irr;
using namespace IOSP;

void IOSP::ConvexHullAddVertices(
    btConvexHullShape *cshape,
    const scene::IMeshBuffer *mbuf,
    const core::vector3df& scale)
{
    u32 vNum = mbuf->getVertexCount();
    switch (mbuf->getVertexType())
    {
        case video::EVT_STANDARD:
        {
            auto vts = (video::S3DVertex*)mbuf->getVertices();
            for (u32 i = 0; i < vNum; i++)
                cshape->addPoint(toBullet(vts[i].Pos * scale));
        }
        break;
        case video::EVT_2TCOORDS:
        {
            auto vts = (video::S3DVertex2TCoords*)mbuf->getVertices();
            for (u32 i = 0; i < vNum; i++)
                cshape->addPoint(toBullet(vts[i].Pos * scale));
        }
        default:
            break;
    }
}

void IOSP::ConvexHullAddVertices(
    btConvexHullShape *cshape,
    const scene::IMesh *mesh,
    const core::vector3df& scale)
{
    int mbNum = mesh->getMeshBufferCount();
    for(int i = 0; i < mbNum; i++)
        ConvexHullAddVertices(cshape, mesh->getMeshBuffer(i));
}
