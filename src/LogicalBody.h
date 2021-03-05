
#pragma once

#include <vector>
#include <Utils/SimpleState.h>
#include <BulletBodySceneNode.h>

namespace IOSP
{
    class LogicalBody : public SimpleState
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
        const std::vector<BulletBodySceneNode*>& getBodies() const { return m_bodies; }
        bool hasBody(BulletBodySceneNode *, bool = false) const;
        bool addBody(BulletBodySceneNode *, bool = false);
        bool delBody(BulletBodySceneNode *);
    };
}
