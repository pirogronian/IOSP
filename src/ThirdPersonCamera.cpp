
#include <cstdio>

#include "ThirdPersonCamera.h"

using namespace irr;
using namespace IOSP;

std::vector<ThirdPersonCamera*> IOSP::ThirdPersonCamera::s_vector;
std::vector<ThirdPersonCamera*>::iterator IOSP::ThirdPersonCamera::s_current{IOSP::ThirdPersonCamera::s_vector.end()};
bool IOSP::ThirdPersonCamera::s_active{true};

ThirdPersonCamera::ThirdPersonCamera(irr::scene::ISceneNode *target)
{
    auto smgr = getSceneManager();
    m_camera = smgr->addCameraSceneNodeMaya();
    m_targetNode = target;
}

ThirdPersonCamera::ThirdPersonCamera(const ThirdPersonCamera& other)
{
    auto smgr = getSceneManager();
    auto ocam = other.m_camera;
    auto animators = ocam->getAnimators();
    for(auto animator : animators)
        if (animator->getType() == irr::scene::ESNAT_CAMERA_MAYA)
        {
            auto ma = (scene::ISceneNodeAnimatorCameraMaya*)animator;
            m_camera = smgr->addCameraSceneNodeMaya(
                ocam->getParent(),
                ma->getRotateSpeed(),
                ma->getZoomSpeed(),
                ma->getMoveSpeed(),
                -1,
                ma->getDistance()
            );
            m_camera->setPosition(ocam->getPosition()); // Ineffective )-;
        }
    m_targetNode = other.m_targetNode;
}

void ThirdPersonCamera::addCurrent(ThirdPersonCamera *cam)
{
    s_vector.push_back(cam);
    s_current = s_vector.end() - 1;
    if (s_active) setCurrentActive();
    std::printf("ThirdPersonCamera: current added. Count: %i\n", s_vector.size());
}

void ThirdPersonCamera::deleteCurrent()
{
    auto cam = getCurrent();
    if (!cam)  return;
    delete cam;
    s_current = s_vector.erase(s_current);
    std::printf("ThirdPersonCamera: current removed. Count: %i\n", s_vector.size());
}

void ThirdPersonCamera::setCurrentActive()
{
    auto cam = getCurrent();
    if (!cam)  return;
    auto smgr = cam->getSceneManager();
    smgr->setActiveCamera(cam->getCamera());
    std::printf("ThirdPersonCamera: current made active. Count: %i\n", s_vector.size());
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
    std::printf("ThirdPersonCamera: current cloned. Count: %i\n", s_vector.size());
}

void ThirdPersonCamera::switchCurrentNext()
{
    if (s_vector.size() < 2)  return;
    s_current++;
    if (s_current == s_vector.end())
        s_current = s_vector.begin();
    if (s_active)
        setCurrentActive();
    std::printf("ThirdPersonCamera: next. Current: %i\n", std::distance(s_vector.begin(), s_current));
}

void ThirdPersonCamera::switchCurrentPrevious()
{
    if (s_vector.size() < 2)  return;
    if (s_current == s_vector.begin())
        s_current = s_vector.end() - 1;
    else
        s_current--;
    if (s_active)
        setCurrentActive();
    std::printf("ThirdPersonCamera: previous. Current: %i\n", std::distance(s_vector.begin(), s_current));
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
