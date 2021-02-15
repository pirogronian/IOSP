
#include "ThirdPersonCamera.h"

using namespace irr;
using namespace IOSP;

AutoIndexer<ThirdPersonCamera*> IOSP::ThirdPersonCamera::s_index;

std::size_t ThirdPersonCamera::create(scene::ICameraSceneNode *cam, scene::ISceneNode *target)
{
    auto tpc = new ThirdPersonCamera;
    tpc->setCamera(cam);
    tpc->setTarget(target);
    return s_index.add(tpc);
}

void ThirdPersonCamera::updateAll()
{
    for(std::size_t i = 0; i < s_index.size(); i++)
    {
        if (s_index.contains(i))
        {
            s_index.get(i)->update();
        }
    }
}
