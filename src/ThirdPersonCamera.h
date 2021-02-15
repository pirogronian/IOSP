
#pragma once

#include <irrlicht.h>

#include <Utils/AutoIndexer.h>

namespace IOSP
{
    class ThirdPersonCamera
    {
    protected:
        irr::scene::ISceneNode *m_targetNode{nullptr};
        irr::scene::ICameraSceneNode *m_camera{nullptr};
        static AutoIndexer<ThirdPersonCamera*> s_index;
    public:
        void setCamera(irr::scene::ICameraSceneNode *c)
        {
            if (m_camera)
                m_camera->drop();
            m_camera = c;
            m_camera->grab();
        }
        irr::scene::ICameraSceneNode *camera() { return m_camera; }
        const irr::scene::ICameraSceneNode *camera() const { return m_camera; }
        void setTarget(irr::scene::ISceneNode *n)
        {
            if (m_targetNode)
                m_targetNode->drop();
            m_targetNode = n;
            m_targetNode->grab();
        }
        void update()
        {
            if (!m_camera || !m_targetNode) return;
            m_camera->setTarget(m_targetNode->getPosition());
        }
        static std::size_t create(irr::scene::ICameraSceneNode *, irr::scene::ISceneNode * = nullptr);
        static ThirdPersonCamera *get(std::size_t i) { return s_index.get(i); }
        static bool remove(std::size_t i) { return s_index.remove(i); }
        static void updateAll();
    };
}
