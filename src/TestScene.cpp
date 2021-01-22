
#include <BulletWorldSceneNode.h>
#include <BulletBodySceneNode.h>
#include <BulletDebugDrawer.h>
#include <TestScene.h>

#include <Tests/NodeSearchTest.h>
#include <TestControlPanel.h>

#include <cstdio>

using namespace IOSP;
using namespace irr;

Simulation *IOSP::TestScene(IrrlichtDevice *dvc)
{
    auto *smgr = dvc->getSceneManager();
    auto *cam = smgr->addCameraSceneNodeMaya();
//     auto *cube = smgr->addCubeSceneNode(10, 0, -1, core::vector3df(0, 0, 0));
//     node->setMaterialFlag(video::EMF_LIGHTING, false);
//     auto *light = smgr->addLightSceneNode();
    auto *bworld = new BulletWorldSceneNode(smgr->getRootSceneNode(), smgr);
    bworld->setGlobalGravity(btVector3(0, 0, 1));
    bworld->setName("BulletWorld");
//     btRigidBody::btRigidBodyConstructionInfo info;
    auto *bsphere = new btSphereShape(5);
    auto *brigid = new btRigidBody(1, nullptr, bsphere);
    auto *body = new BulletBodySceneNode(smgr->getRootSceneNode(), smgr, brigid);
    body->setName("BBody");
    body->setWorld(bworld->bulletWorld());
    auto *ball = smgr->addSphereSceneNode(5, 16, body);
    ball->setMaterialFlag(video::EMF_LIGHTING, false);
    ball->setName("BBall");
    cam->setTarget(ball->getPosition());
    auto *bbox = new btBoxShape(btVector3(25, 25, 0));
    auto *bwall = new btRigidBody(0, nullptr, bbox);
    auto *wall = new BulletBodySceneNode(smgr->getRootSceneNode(), smgr, bwall);
    wall->setPosition(core::vector3df(0, 0, 15));
    wall->setWorld(bworld->bulletWorld());
    wall->setName("BWall");
//     auto *wallbox = smgr->addCubeSceneNode(1, wall);
    auto *tcpanel = new TestControlPanel(dvc, smgr->getRootSceneNode(), smgr, 1234);
    tcpanel->setTarget(body);
    tcpanel->grabEvents();
    tcpanel->stateActionManager()->bind(TestControlPanel::ThrustAction, irr::KEY_KEY_A, false, true);
    auto *sim = new Simulation(dvc);
    sim->addWorld(bworld);
    return sim;
}
