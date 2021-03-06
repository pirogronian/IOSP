
#include <BulletWorldSceneNode.h>
#include <BulletBodySceneNode.h>
#include <BulletDebugDrawer.h>

#include <LogicalBody.h>
#include <ThirdPersonCamera.h>
#include <Utils/BulletShapes.h>
#include <LinearThruster.h>
#include <TorqueThruster.h>
#include <TestScene.h>

#include <Utils/Dump.h>

#include <MagicSimpleRocketControlPanel.h>
#include <ManualThrustControlPanel.h>

#include <cstdio>

using namespace IOSP;
using namespace irr;

BulletBodySceneNode *createTestModel()
{
    auto *smgr = IrrCommonObject::getSceneManager();
    auto *am = smgr->getMesh("testmodel.dae");
    if (!am)  return nullptr;
    auto *convex = createConvexHullShape(am->getMesh(0));
    auto *brigid = new btRigidBody(1, nullptr, convex);
    auto *body = new BulletBodySceneNode(smgr->getRootSceneNode(), smgr, brigid);
    auto *model = smgr->addMeshSceneNode(am->getMesh(0), body);
    model->setMaterialFlag(video::EMF_LIGHTING, true);
    body->setName("TestModelBody");
    body->setID(-2);
    body->getRootComponent().addChild(new LinearThruster(btVector3(0, 0, 1), 10), 0, "MainThruster");
    body->getRootComponent().addChild(new TorqueThruster(btVector3(0, 0, 1), 10), 1, "RollThruster");
    body->rebuildComponentIndex();
    auto lbody = new LogicalBody(body);
    return body;
}

BulletBodySceneNode *createTestCube()
{
    auto *smgr = IrrCommonObject::getSceneManager();
    auto *bbox = new btBoxShape(btVector3(5, 5, 5));
    auto *brigid = new btRigidBody(5, nullptr, bbox);
    auto *body = new BulletBodySceneNode(smgr->getRootSceneNode(), smgr, brigid);
//     auto *cube = smgr->addCubeSceneNode(10, body);
    auto am = smgr->getMesh("testcube.dae");
    auto cube = smgr->addMeshSceneNode(am->getMesh(0), body);
    cube->setMaterialFlag(video::EMF_LIGHTING, true);
    cube->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
    cube->setScale(core::vector3df(5, 5, 5));
    body->setName("TestCube");
    body->setID(-3);
    return body;
}

scene::ILightSceneNode *createTestLigth()
{
    auto *smgr = IrrCommonObject::getSceneManager();
    auto *drv = IrrCommonObject::getVideoDriver();
    auto light = smgr->addLightSceneNode();
    auto img = drv->getTexture("Particle.tga");
    drv->makeColorKeyTexture(img, core::position2di(0, 0));
    auto bb = smgr->addBillboardSceneNode(light, core::dimension2df(50, 50));
    bb->setMaterialFlag(video::EMF_LIGHTING, false);
    bb->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
    bb->setMaterialTexture(0, img);
    return light;
}

BulletBodySceneNode *createTerrain()
{
    video::SMaterial mat;
    auto smgr = IrrCommonObject::getSceneManager();
    auto am = smgr->addHillPlaneMesh("HillMesh", {10, 10}, {10, 10}, &mat, 10, {4, 7}, {10, 10});
    auto mnode = smgr->addMeshSceneNode(am->getMesh(0), 0);
    auto shape = createTriangleShape(mnode);
    auto body = new btRigidBody(0, nullptr, shape);
    auto bnode = new BulletBodySceneNode(smgr->getRootSceneNode(), smgr, body);
    mnode->setParent(bnode);
    mnode->setName("TerrainMeshNode");
    bnode->setName("Terrain");
    bnode->setID(-4);
    return bnode;
}

Simulation *IOSP::TestScene()
{
    auto *smgr = IrrCommonObject::getSceneManager();
//     auto *cam = smgr->addCameraSceneNodeMaya();
//     auto *light = smgr->addLightSceneNode();
    auto light = createTestLigth();
    light->setPosition(core::vector3df(0, 0, -50));
    auto *bworld = new BulletWorldSceneNode(smgr->getRootSceneNode(), smgr);
    bworld->setGlobalGravity(btVector3(0, 0, 0));
    bworld->setName("BulletWorld");
    auto *bsphere = new btSphereShape(5);

    auto testCube = createTestCube();
    bworld->addBody(testCube);
    auto testModel = createTestModel();
    testModel->setPosition(core::vector3df(0, 0, -20));
    testModel->syncTransform();
    bworld->addChild(testModel);
    auto b2 = dynamic_cast<BulletBodySceneNode*>(testModel->clone());
//         auto b2 = testModel->createCopy();
    b2->setPosition(core::vector3df(0, 5, -20));
    b2->syncTransform();
    b2->setName("ModelCopy");
    b2->setID(-5);
    auto lb = testModel->getLogicalBody();
    lb->addBody(b2);
//     bworld->addBody(b2);
    dump(lb);

    auto terrain = createTerrain();
    terrain->setPosition(core::vector3df(0, 0, 75));
    terrain->setRotation(core::vector3df(-90, 0, 0));
    terrain->syncTransform();
//     terrain->setID(-3);
    bworld->addChild(terrain);
    dump(bworld->getBulletWorld());

    auto *tcpanel = new MagicSimpleRocketControlPanel(smgr->getRootSceneNode(), smgr, 100);
    auto *mtpanel = new ManualThrustControlPanel(tcpanel, smgr, 101);
    tcpanel->setTarget(b2);
    ThirdPersonCamera::addCurrent(new ThirdPersonCamera(b2));
    auto *sim = new Simulation();
    sim->addWorld(bworld);
    sim->setActivePanel(tcpanel);
    return sim;
}
