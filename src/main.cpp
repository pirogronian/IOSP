
#include <iostream>

#include <irrlicht.h>

#include <EventReceiver.h>
#include <TestScene.h>

#include <cstdio>

int main()
{
    IOSP::EventReceiver *eventReceiver = new IOSP::EventReceiver();
    irr::IrrlichtDevice *device = irr::createDevice(
        irr::video::EDT_OPENGL,
        irr::core::dimension2d<irr::u32>(800, 600),
        16, false, true, true, eventReceiver
    );
    if (!device)
        return 1;

    irr::video::IVideoDriver *driver = device->getVideoDriver();
    irr::scene::ISceneManager* smgr = device->getSceneManager();

    irr::u32 ptime = device->getTimer()->getTime(), ctime;
    auto *sim = IOSP::TestScene(device);
    sim->debugDrawer().setDebugMode(btIDebugDraw::DBG_DrawWireframe|btIDebugDraw::DBG_DrawAabb);
    eventReceiver->setSimulation(sim);

    while(device->run())
    {
        ctime = device->getTimer()->getTime();
        btScalar dtime = (ctime - ptime) / 1000.;
        ptime = ctime;
        sim->stepSimulation(dtime);

        driver->beginScene(true, true, irr::video::SColor(0,50,50,50));
        smgr->drawAll();
        sim->drawDebug();
        driver->endScene();
        irr::core::stringw wcaption = L"IOSP [";
        wcaption += driver->getFPS();
        wcaption += L" fps]";
        device->setWindowCaption(wcaption.c_str());
    }
    device->drop();

    return 0;
}
