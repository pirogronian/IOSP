
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
}
