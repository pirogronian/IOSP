
#pragma once

#include <limits>

#include <Common.h>
#include <BulletWorldSceneNode.h>

namespace IOSP
{
    class BulletUpdatable
    {
    protected:
        std::size_t m_WorldIndex{std::numeric_limits<std::size_t>::max()};
        BulletWorldSceneNode *m_world{nullptr};
        void setWorldIndex(std::size_t id) { m_WorldIndex = id; }
    public:
        std::size_t worldIndex() { return m_WorldIndex; }
        const std::size_t worldIndex() const { return m_WorldIndex; }
        virtual void update(time_t) = 0;
        friend BulletWorldSceneNode;
        virtual ~BulletUpdatable()
        {
            if (m_world)
                m_world->unregisterUpdatable(this);
        }
    };
}
