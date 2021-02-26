
#pragma once

#include <vector>
#include <optional>
#include <Utils/VectorHelper.h>
#include <btBulletDynamicsCommon.h>
#include <irrlicht.h>

namespace IOSP
{
    class BulletBodySceneNode;
    class Component
    {
        friend BulletBodySceneNode;
    protected:
        int m_localIndex{-1};
        int m_globalIndex{-1};
        btTransform m_transform{btTransform::getIdentity()};
        Component *m_parent{nullptr};
        std::vector<std::optional<Component*>> m_children{0};
    public:
        Component() = default;
        int getLocalIndex() const { return m_localIndex; }
        int getGlobalIndex() const { return m_globalIndex; }
        Component *getParent() { return m_parent; }
        const Component *getParent() const { return m_parent; }
        void updateTransform();
        void addChild(Component *, int, const btTransform& = btTransform::getIdentity());
        Component *getChild(int index)
        {
            return m_children.at(index).value_or(nullptr);
        }
        const Component *getChild(int index) const
        {
            return m_children.at(index).value_or(nullptr);
        }
        Component *getChildSafe(int index)
        {
            if (!isIndexValid(m_children, index))  return nullptr;
            return m_children[index].value_or(nullptr);
        }
        const Component *getChildSafe(int index) const
        {
            if (!isIndexValid(m_children, index))  return nullptr;
            return m_children[index].value_or(nullptr);
        }
        virtual void update(BulletBodySceneNode *, irr::u32);
        virtual ~Component();
    };
}

