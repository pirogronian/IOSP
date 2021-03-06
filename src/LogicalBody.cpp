
#include <cassert>
#include <cstdio>

#include "LogicalBody.h"

using namespace IOSP;
using namespace irr;

std::size_t LogicalBody::getBodyInternalIndex(const BulletBodySceneNode *body) const
{
    std::size_t i = 0;
    while(i < m_bodies.size())
    {
        if (m_bodies[i] == body)  break;
        i++;
    }
    return i;
}

std::vector<BulletBodySceneNode*>::iterator LogicalBody::getBodyInternalIterator(const BulletBodySceneNode *body)
{
    std::vector<BulletBodySceneNode*>::iterator it = m_bodies.begin();
    while(it != m_bodies.end())
    {
        if (*it == body)  break;
        it++;
    }
    return it;
}

bool LogicalBody::hasBody(BulletBodySceneNode *body, bool extracheck) const
{
    bool c1 = body->getLogicalBody() == this;
    if (extracheck)
    {
        bool c2 = getBodyInternalIndex(body) < m_bodies.size();
        assert(c1 == c2);
    }
    return c1;
}

bool LogicalBody::addBody(BulletBodySceneNode *body, bool extracheck)
{
    if (hasBody(body, extracheck))  return false;
    m_bodies.push_back(body);
    body->setLogicalBody(this);
    modify();
    return true;
}

bool LogicalBody::delBody(BulletBodySceneNode *body)
{
    auto it = getBodyInternalIterator(body);
    if (it == m_bodies.end())  return false;
    m_bodies.erase(it);
    body->setLogicalBody(nullptr);
    modify();
    return true;
}

void IOSP::dump(const LogicalBody& lb)
{
    auto bodies = lb.getBodies();
    std::printf("LogicalBody: {%i}\n", bodies.size());
    for (auto body : bodies)
    {
        auto n = body->getComponentIndexSize();
        std::printf(" %s [%i] %s\n", body->getName(), n, body == lb.getRoot() ? " (root)" : "");
        for (int i = 0; i < n; i++)
        {
            std::printf("  %s\n", body->getComponentName(i).c_str());
        }
    }
}
