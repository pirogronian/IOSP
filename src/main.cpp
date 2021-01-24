
#include <cstdio>

#include <irrlicht.h>
#include <CGUITTFont.h>
#include <EventReceiver.h>
#include <TestScene.h>

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
    irr::gui::IGUIEnvironment *gui = device->getGUIEnvironment();
    auto *font = irr::gui::CGUITTFont::createTTFont(device->getGUIEnvironment(), "/usr/share/fonts/gnu-free/FreeMono.otf", 14);
    if (!font)  std::puts("Font not loaded!");
    gui->getSkin()->setFont(font);
    auto *dtimeText = gui->addStaticText(L"Static text", irr::core::rect<irr::s32>(0, 0, 150, 15));
    dtimeText->setDrawBackground(true);
    dtimeText->setAlignment(irr::gui::EGUIA_SCALE, irr::gui::EGUIA_SCALE, irr::gui::EGUIA_SCALE, irr::gui::EGUIA_SCALE);

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
        irr::core::stringw dtext = "Delta time: ";
        dtext += dtime;
        dtimeText->setText(dtext.c_str());

        driver->beginScene(true, true, irr::video::SColor(0,50,50,50));
        smgr->drawAll();
        gui->drawAll();
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
