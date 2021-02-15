
#include <BulletWorldSceneNode.h>
#include <BulletBodySceneNode.h>
#include <BulletDebugDrawer.h>

#include <ThirdPersonCamera.h>
#include <Utils/BulletShapes.h>
#include <TestScene.h>

#include <MagicSimpleRocketControlPanel.h>

#include <cstdio>

using namespace IOSP;
using namespace irr;

BulletBodySceneNode *createTestModel()
{
    auto *smgr = IrrCommonObject::getSceneManager();
    auto *am = smgr->getMesh("testmodel.dae");
    if (!am)  return nullptr;
    auto *model = smgr->addMeshSceneNode(am->getMesh(0), 0);
    auto *convex = createConvexHullShape(model);
    auto *brigid = new btRigidBody(1, nullptr, convex);
    auto *body = new BulletBodySceneNode(smgr->getRootSceneNode(), smgr, brigid);
    model->setParent(body);
    model->setMaterialFlag(video::EMF_LIGHTING, false);
    model->setName("TestModel");
    return body;
}

BulletBodySceneNode *createTestCube()
{
    auto *smgr = IrrCommonObject::getSceneManager();
    auto *bbox = new btBoxShape(btVector3(5, 5, 5));
    auto *brigid = new btRigidBody(5, nullptr, bbox);
    auto *body = new BulletBodySceneNode(smgr->getRootSceneNode(), smgr, brigid);
    auto *cube = smgr->addCubeSceneNode(10, body);
    cube->setMaterialFlag(video::EMF_LIGHTING, false);
    body->setName("TestCube");
    return body;
}

Simulation *IOSP::TestScene()
{
    auto *smgr = IrrCommonObject::getSceneManager();
    auto *cam = smgr->addCameraSceneNodeMaya();
//     auto *light = smgr->addLightSceneNode();
    auto *bworld = new BulletWorldSceneNode(smgr->getRootSceneNode(), smgr);
    bworld->setGlobalGravity(btVector3(0, 0, 0));
    bworld->setName("BulletWorld");
    auto *bsphere = new btSphereShape(5);

    auto testCube = createTestCube();
    bworld->addBody(testCube);
    auto testModel = createTestModel();
    if (testModel)
    {
        testModel->setPosition(core::vector3df(0, 0, -20));
        testModel->syncTransform();
        bworld->addBody(testModel);
    }
    auto *bbox2 = new btBoxShape(btVector3(25, 25, 0));
    auto *bwall = new btRigidBody(0, nullptr, bbox2);
    auto *wall = new BulletBodySceneNode(smgr->getRootSceneNode(), smgr, bwall);
    wall->setPosition(core::vector3df(0, 0, 20));
    wall->setRotation(core::vector3df(0, 45, 0));
    wall->syncTransform();
    bworld->addBody(wall);
    wall->setName("BWall");
    auto *tcpanel = new MagicSimpleRocketControlPanel(smgr->getRootSceneNode(), smgr, 1234);
    tcpanel->setTarget(testModel);
    ThirdPersonCamera::create(cam, testModel);
    auto *sim = new Simulation();
    sim->addWorld(bworld);
    sim->setActivePanel(tcpanel);
    return sim;
}
