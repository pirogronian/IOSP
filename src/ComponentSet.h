
#pragma once

#include <vector>
#include <LogicalBody.h>
#include <Component.h>

namespace IOSP
{
    template<typename DataType>
    class ComponentSet
    {
    public:
        struct Entry
        {
            BulletBodySceneNode *node{nullptr};
            int index{-1};
            DataType data;
            Entry(BulletBodySceneNode *n, int i) : node(n), index(i) {}
        };
    protected:
        std::vector<Entry> m_vector;
        LogicalBody* m_lbody{nullptr};
    public:
        ComponentSet() = default;
        ComponentSet(LogicalBody *lbody) : m_lbody(lbody) {}
        LogicalBody *getLogicalBody() { return m_lbody; }
        const LogicalBody *getLogicalBody() const { return m_lbody; }
        void setLogicalBody(LogicalBody *lb) { m_lbody = lb; }
        void clear() { m_vector.clear(); }
        const std::vector<Entry>& getVector() const { return m_vector; }
        std::vector<Entry>& getVector() { return m_vector; }
        template<typename T>
        void scanForType()
        {
            if (!m_lbody)  return;
            auto bodies = m_lbody->getBodies();
            for (auto body : bodies)
            {
                for (int i = 0; i < body->getComponentIndexSize(); i++)
                {
                    auto cp = dynamic_cast<T*>(body->getComponent(i));
                    if (!cp)  continue;
                    m_vector.push_back(Entry(body, i));
                }
            }
        }
        void scanForAll()
        {
            scanForType<Component>();
        }
    };
}
