
#include <cstdio>

#include "ThirdPersonCamera.h"

using namespace irr;
using namespace IOSP;

std::vector<ThirdPersonCamera*> IOSP::ThirdPersonCamera::s_vector;
int IOSP::ThirdPersonCamera::s_current{-1};
bool IOSP::ThirdPersonCamera::s_active{true};

ThirdPersonCamera::ThirdPersonCamera(irr::scene::ISceneNode *target)
{
    auto smgr = getSceneManager();
    m_camera = smgr->addCameraSceneNodeMaya();
    m_camera->grab();
    m_targetNode = target;
}

ThirdPersonCamera::ThirdPersonCamera(const ThirdPersonCamera& other)
{
    auto smgr = getSceneManager();
    auto ocam = other.m_camera;
    m_camera = (scene::ICameraSceneNode*)ocam->clone();
    m_camera->grab();
//     auto animators = ocam->getAnimators();
//     for(auto animator : animators)
//         if (animator->getType() == irr::scene::ESNAT_CAMERA_MAYA)
//         {
//             auto ma = (scene::ISceneNodeAnimatorCameraMaya*)animator;
//             m_camera = smgr->addCameraSceneNodeMaya(
//                 ocam->getParent(),
//                 ma->getRotateSpeed(),
//                 ma->getZoomSpeed(),
//                 ma->getMoveSpeed(),
//                 -1,
//                 ma->getDistance()
//             );
//             m_camera->setPosition(ocam->getPosition()); // Ineffective )-;
//         }
    m_targetNode = other.m_targetNode;
}

ThirdPersonCamera *ThirdPersonCamera::getCurrent() {
    if (s_vector.size())  return s_vector[s_current];
    return nullptr;
}

void ThirdPersonCamera::addCurrent(ThirdPersonCamera *cam)
{
    if (!s_vector.size())  s_current = 0;
    s_vector.insert(s_vector.begin() + s_current, cam);
//     s_current = s_vector.size() - 1;
    if (s_active) setCurrentActive();
    std::printf("ThirdPersonCamera: current added. Current: [%i/%i]\n", getCurrentIndex(), s_vector.size());
}

void ThirdPersonCamera::deleteCurrent()
{
    if (s_vector.size() < 2)  return; // Leave at last one camera
    auto cam = getCurrent();
    if (!cam)  return;
    delete cam;
    s_vector.erase(s_vector.begin() + s_current);
    s_current--;
    if (s_vector.size() && s_current < 0) s_current = 0;
    if (s_active)  setCurrentActive();
    std::printf("ThirdPersonCamera: current deleted. Current: [%i/%i]\n", getCurrentIndex(), s_vector.size());
}

void ThirdPersonCamera::setCurrentActive()
{
    auto cam = getCurrent();
    if (!cam)  return;
    auto smgr = cam->getSceneManager();
    smgr->setActiveCamera(cam->getCamera());
    std::printf("ThirdPersonCamera: current made active. Current: [%i/%i]\n", getCurrentIndex(), s_vector.size());
}

void ThirdPersonCamera::cloneCurrent()
{
    ThirdPersonCamera *tpc;
    auto cur = getCurrent();
    if (cur)
        tpc = new ThirdPersonCamera(*cur);
    else
        tpc = new ThirdPersonCamera();
    addCurrent(tpc);
    setCurrentActive();
    std::printf("ThirdPersonCamera: %s. Current: [%i/%i]\n", cur ? "current cloned" : "new created", getCurrentIndex(), s_vector.size());
}

void ThirdPersonCamera::switchCurrentNext()
{
    if (s_vector.size() < 2)  return;
    s_current++;
    if (s_current >= s_vector.size())
        s_current = 0;
    if (s_active)
        setCurrentActive();
    std::printf("ThirdPersonCamera: current next. Current: [%i/%i]\n", getCurrentIndex(), s_vector.size());
}

void ThirdPersonCamera::switchCurrentPrevious()
{
    if (s_vector.size() < 2)  return;
    s_current--;
    if (s_current < 0)
        s_current = s_vector.size() - 1;
    if (s_active)
        setCurrentActive();
    std::printf("ThirdPersonCamera: current prev. Current: [%i/%i]\n", getCurrentIndex(), s_vector.size());
}

void ThirdPersonCamera::updateCurrent()
{
    auto curr = getCurrent();
    if (curr) curr->update();
}

void ThirdPersonCamera::updateAll()
{
    for(auto cam : s_vector)
    {
        cam->update();
    }
}
