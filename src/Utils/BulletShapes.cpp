
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

void IOSP::addTriangles(
    btTriangleMesh *mesh,
    const scene::IMeshBuffer *mbuf,
    const core::vector3df& scale)
{
    const u32 vn = mbuf->getVertexCount();
    const u16 *inds = mbuf->getIndices();
    const u32 in = mbuf->getIndexCount();
    btVector3 triangle[3];
//     std::printf("Vcount: %i\n", vn);

    switch(mbuf->getVertexType())
    {
        case video::EVT_STANDARD:
        {
//             std::puts("Vtype: S3DVertex");
            auto vs = (video::S3DVertex*)mbuf->getVertices();
            for (int i = 0; i < in; i+=3)
            {
                for (int j = 0; j < 3; j++)
                {
                    auto index = inds[i + j];
                    if (index > vn) continue;
                    triangle[j] = toBullet(vs[index].Pos * scale);
                }
                mesh->addTriangle(triangle[0], triangle [1], triangle[2]);
            }
        }
        break;
        case video::EVT_2TCOORDS:
        {
//             std::puts("Vtype: S3DVertex2TCoords");
            auto vs = (video::S3DVertex2TCoords*)mbuf->getVertices();
            for (int i = 0; i < in; i+=3)
            {
                for (int j = 0; j < 3; j++)
                {
                    auto index = inds[i + j];
                    if (index > vn) continue;
                    triangle[j] = toBullet(vs[index].Pos * scale);
                }
                mesh->addTriangle(triangle[0], triangle [1], triangle[2]);
            }
        }
    }
}

void IOSP::addTriangles(
    btTriangleMesh *bmesh,
    const irr::scene::IMesh *imesh,
    const core::vector3df& scale)
{
    int mbNum = imesh->getMeshBufferCount();
        for(int i = 0; i < mbNum; i++)
            addTriangles(bmesh, imesh->getMeshBuffer(i), scale);
}
