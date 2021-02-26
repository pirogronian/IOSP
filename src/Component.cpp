
#include <cassert>
#include <Utils/VectorHelper.h>
#include "Component.h"

using namespace irr;
using namespace IOSP;

void Component::updateTransform()
{
    for (auto &child : m_children)
    {
        if (!child)  continue;
        child.value()->m_transform = m_transform * child.value()->m_transform;
        child.value()->updateTransform();
    }
}

void Component::addChild(Component *child, int index, const btTransform& localTr)
{
    assert(index >= 0);
    ensureSize(m_children, index);
    assert(!m_children[index]);
    m_children[index] = child;
    child->m_localIndex = index;
    child->m_transform = m_transform * localTr;
    child->updateTransform();
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
