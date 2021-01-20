
#pragma once

#include <irrlicht.h>
#include <cstdio>

namespace IOSP
{
    void inline NodeSearchByNameTest(irr::scene::ISceneNode *node, irr::core::stringc name)
    {
        std::printf("NodeSearchByNameTest(%p, %s)\n", node, name.c_str());
        auto *smgr = node->getSceneManager();
        assert(smgr != nullptr);
        node->setName(name);
        assert(name == node->getName());
        assert(smgr->getSceneNodeFromName(name.c_str()) == node);
    }

    void inline NodeSearchByIdTest(irr::scene::ISceneNode *node, irr::s32 id)
    {
        std::printf("NodeSearchByIdTest(%p, %d)\n", node, id);
        auto *smgr = node->getSceneManager();
        assert(smgr != nullptr);
        node->setID(id);
        assert(id == node->getID());
        assert(smgr->getSceneNodeFromId(id) == node);
    }
}
