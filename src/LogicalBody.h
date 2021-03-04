
#pragma once

#include <vector>
#include <BulletBodySceneNode.h>

namespace IOSP
{
    class LogicalBody
    {
    protected:
        BulletBodySceneNode *m_root;
        std::vector<BulletBodySceneNode*> m_bodies;
    public:
        LogicalBody(BulletBodySceneNode *root) : m_root(root)
        {
            addBody(root, false);
        }
        BulletBodySceneNode *getRoot() { return m_root; }
        const BulletBodySceneNode* getRoot() const { return m_root; }
        std::size_t getBodiesNumber() const { return m_bodies.size(); }
        std::size_t getBodyInternalIndex(const BulletBodySceneNode *) const;
        std::vector<BulletBodySceneNode*>::iterator getBodyInternalIterator(const BulletBodySceneNode *);
        bool hasBody(BulletBodySceneNode *, bool = false) const;
        bool addBody(BulletBodySceneNode *, bool = false);
        bool delBody(BulletBodySceneNode *);
    };
}
