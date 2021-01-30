
#include <irrlicht.h>
#include <btBulletDynamicsCommon.h>
#include <BulletDebugDrawer.h>

using namespace irr;

int main()
{
    auto *dev = irr::createDevice(
        irr::video::EDT_OPENGL,
        irr::core::dimension2d<irr::u32>(800, 600),
        16, false, true, true, 0);

    auto *smgr = dev->getSceneManager();
    auto *drv = dev->getVideoDriver();
    
    IOSP::BulletDebugDrawer drawer(drv);
    drawer.setDebugMode(btIDebugDraw::DBG_DrawWireframe|btIDebugDraw::DBG_DrawAabb);
    btDefaultCollisionConfiguration m_config;
    btCollisionDispatcher m_dispatcher{&m_config};
    btDbvtBroadphase m_broadphase;
    btSequentialImpulseConstraintSolver m_solver;
    btDiscreteDynamicsWorld m_world{&m_dispatcher, &m_broadphase, &m_solver, &m_config};
    
    m_world.setDebugDrawer(&drawer);
    m_world.setGravity(btVector3(0, 0, 0));
    auto *cam = smgr->addCameraSceneNodeMaya();
    cam->setPosition(core::vector3df(0, 0, 20));
    cam->setTarget(core::vector3df(0, 0, 0));
    
    btDefaultMotionState state;
    btBoxShape box(btVector3(5, 5, 5));
    btRigidBody rigid(1, 0, &box);
    rigid.setMassProps(1, btVector3(1, 1, 1));
    rigid.setActivationState(DISABLE_DEACTIVATION);
    m_world.addRigidBody(&rigid);
//     rigid.setAngularVelocity(btVector3(0, 0, 0.1));
    
//     auto *cube = smgr->addCubeSceneNode(10, smgr->getRootSceneNode());
//     cube->setMaterialFlag(video::EMF_LIGHTING, false);
    
    while(dev->run())
    {
        drv->beginScene(true, true, irr::video::SColor(0,50,50,50));
        smgr->drawAll();
        rigid.applyTorqueImpulse(btVector3(0, 0, 0.001));
        m_world.stepSimulation(0.017, 0, 1./60);
        drv->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());
        m_world.debugDrawWorld();
        drv->endScene();
    }
}
