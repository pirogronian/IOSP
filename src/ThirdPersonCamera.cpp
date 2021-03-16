
#include <cstdio>

#include "ThirdPersonCamera.h"

using namespace irr;
using namespace IOSP;

std::vector<ThirdPersonCamera*> IOSP::ThirdPersonCamera::s_vector;
int IOSP::ThirdPersonCamera::s_current{-1};

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
    setCurrentActive();
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
    setCurrentActive();
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
    setCurrentActive();
    std::printf("ThirdPersonCamera: current next. Current: [%i/%i]\n", getCurrentIndex(), s_vector.size());
}

void ThirdPersonCamera::switchCurrentPrevious()
{
    if (s_vector.size() < 2)  return;
    s_current--;
    if (s_current < 0)
        s_current = s_vector.size() - 1;
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
