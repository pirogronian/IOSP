
#pragma once

#include <vector>
#include <Utils/Ownership.h>
#include <Utils/IrrCommonObject.h>

namespace IOSP
{
    class ThirdPersonCamera : public IrrCommonObject
    {
    protected:
        irr::scene::ISceneNode *m_targetNode{nullptr};
        irr::scene::ICameraSceneNode *m_camera{nullptr};
        static std::vector<ThirdPersonCamera*> s_vector;
        static std::vector<ThirdPersonCamera*>::iterator s_current;
        static bool s_active;
    public:
        ThirdPersonCamera(irr::scene::ISceneNode *target = nullptr);
        ThirdPersonCamera(const ThirdPersonCamera&);
        ~ThirdPersonCamera()
        {
            m_camera->drop();
            clearOwnership(m_targetNode);
        }
        irr::scene::ICameraSceneNode *getCamera() { return m_camera; }
        const irr::scene::ICameraSceneNode *getCamera() const { return m_camera; }
        void setTarget(irr::scene::ISceneNode *n)
        {
            switchOwnership(m_targetNode, n);
        }
        irr::scene::ISceneNode *getTarget() { return m_targetNode; }
        const irr::scene::ISceneNode *getTarget() const { return m_targetNode; }
        void update()
        {
            if (!m_targetNode) return;
            m_camera->setTarget(m_targetNode->getPosition());
        }
        static void addCurrent(ThirdPersonCamera *);
        static ThirdPersonCamera *getCurrent() {
            if (s_current == s_vector.end())  return nullptr;
            return *s_current;
        }
        static void deleteCurrent();
        static void setCurrentActive();
        static void cloneCurrent();
        static void switchCurrentNext();
        static void switchCurrentPrevious();
        static void updateCurrent();
        static void updateAll();
    };
}
