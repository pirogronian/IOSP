
#include <cstdio>

#include <irrlicht.h>
#include <Application.h>
#include <TestScene.h>

int main()
{
    IOSP::Application app;
    if (!app.device())
        return 1;

    irr::video::IVideoDriver *driver = app.device()->getVideoDriver();
    irr::scene::ISceneManager* smgr = app.device()->getSceneManager();
    irr::gui::IGUIEnvironment *gui = app.device()->getGUIEnvironment();
    app.loadTTF("/usr/share/fonts/gnu-free/FreeMono.otf", 14);

    auto *sim = IOSP::TestScene(app.device());
    sim->debugDrawer().setDebugMode(btIDebugDraw::DBG_DrawWireframe|btIDebugDraw::DBG_DrawAabb);
    app.setSimulation(sim);

    sim->init();
    app.run();

    return 0;
}
