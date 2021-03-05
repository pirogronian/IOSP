
#include <cassert>
#include <Utils/VectorHelper.h>
#include "Component.h"

using namespace irr;
using namespace IOSP;

Component::Component(const Component& other)
{
    m_localIndex = other.m_localIndex;
    m_globalIndex = other.m_globalIndex;
    m_transform = other.m_transform;
    m_localName = other.m_localName;
}

void Component::cloneChildren(const Component& other, bool children)
{
    for(auto child : other.m_children)
    {
        if (!child)  continue;
        auto nc = child.value()->clone(children);
        addChild(nc, nc->getLocalIndex(), nc->getLocalName(), nc->getTransform(), false);
    }
}

// Component *Component::clone(bool children)
// {
//     auto ret = new Component(*this);
//     if (children)
//         ret->cloneChildren(*this, children);
//     return ret;
// }

void Component::updateTransform()
{
    for (auto &child : m_children)
    {
        if (!child)  continue;
        child.value()->m_transform = m_transform * child.value()->m_transform;
        child.value()->updateTransform();
    }
}

void Component::addChild(Component *child, int index, const char *name, const btTransform& tr, bool localTr)
{
    assert(index >= 0);
    ensureSize(m_children, index);
    assert(!m_children[index]);
    m_children[index] = child;
    child->m_localIndex = index;
    child->m_localName = name;
    if (localTr)
    {
        child->m_transform = m_transform * tr;
        child->updateTransform();
    }
    else
        child->m_transform = tr;
}

void Component::update(BulletBodySceneNode *node, u32 dtime)
{
    for (auto child : m_children)
        if (child) child.value()->update(node, dtime);
}

Component::~Component()
{
    for (auto &child : m_children)
    {
        if (child)  delete child.value();
    }
}
