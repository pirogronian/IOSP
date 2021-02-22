
#pragma once

#include <irrlicht.h>
#include <btBulletDynamicsCommon.h>

namespace IOSP
{
    void ConvexHullAddVertices(
        btConvexHullShape *,
        const irr::scene::IMeshBuffer*,
        const irr::core::vector3df& scale = irr::core::vector3df(1, 1, 1));

    void ConvexHullAddVertices(
        btConvexHullShape *,
        const irr::scene::IMesh*,
        const irr::core::vector3df& scale = irr::core::vector3df(1, 1, 1));

    inline void ConvexHullAddVertices(
        btConvexHullShape *cshape,
        irr::scene::IMeshSceneNode* mnode)
    {
        ConvexHullAddVertices(cshape, mnode->getMesh(), mnode->getScale());
    }

    inline btConvexHullShape *createConvexHullShape(
        const irr::scene::IMeshBuffer *mbuf,
        const irr::core::vector3df& scale = irr::core::vector3df(1, 1, 1))
    {
        auto *ret = new btConvexHullShape();
        ConvexHullAddVertices(ret, mbuf, scale);
        return ret;
    }

    inline btConvexHullShape *createConvexHullShape(
        const irr::scene::IMesh *mesh,
        const irr::core::vector3df& scale = irr::core::vector3df(1, 1, 1))
    {
        auto *ret = new btConvexHullShape();
        ConvexHullAddVertices(ret, mesh, scale);
        return ret;
    }

    inline btConvexHullShape *createConvexHullShape(
        irr::scene::IMeshSceneNode *mnode)
    {
        auto *ret = new btConvexHullShape();
        ConvexHullAddVertices(ret, mnode);
        return ret;
    }

    void addTriangles(
        btTriangleMesh*,
        const irr::scene::IMeshBuffer *,
        const irr::core::vector3df& = irr::core::vector3df(1, 1, 1));

    void addTriangles(
        btTriangleMesh*,
        const irr::scene::IMesh *,
        const irr::core::vector3df& = irr::core::vector3df(1, 1, 1));

    inline btBvhTriangleMeshShape *createTriangleShape(btTriangleMesh *tm)
    {
        return new btBvhTriangleMeshShape(tm, false, true);
    }

    inline btBvhTriangleMeshShape *createTriangleShape(
        const irr::scene::IMeshBuffer *mb,
        const irr::core::vector3df& scale = irr::core::vector3df(1, 1, 1))
    {
        auto tm = new btTriangleMesh();
        addTriangles(tm, mb, scale);
        return createTriangleShape(tm);
    }

    inline btBvhTriangleMeshShape *createTriangleShape(
        const irr::scene::IMesh *m,
        const irr::core::vector3df& scale = irr::core::vector3df(1, 1, 1))
    {
        auto tm = new btTriangleMesh();
        addTriangles(tm, m, scale);
        return createTriangleShape(tm);
    }

    inline btBvhTriangleMeshShape *createTriangleShape(const irr::scene::IMeshSceneNode *node)
    {
        return createTriangleShape(
            (const irr::scene::IMesh*)((irr::scene::IMeshSceneNode *)node)->getMesh(), node->getScale());
    }
}
