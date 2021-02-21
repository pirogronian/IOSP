
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
    auto *convex = createConvexHullShape(am->getMesh(0));
    auto *brigid = new btRigidBody(1, nullptr, convex);
    auto *body = new BulletBodySceneNode(smgr->getRootSceneNode(), smgr, brigid);
    auto *model = smgr->addMeshSceneNode(am->getMesh(0), body);
    model->setMaterialFlag(video::EMF_LIGHTING, true);
//     model->setMaterialFlag(video::EMF_ANISOTROPIC_FILTER, true);
//     model->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
//     model->setMaterialFlag(video::EMF_ANTI_ALIASING, true);
//     model->setDebugDataVisible(irr::scene::EDS_NORMALS);
    model->setName("TestModel");
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
//     cube->setMaterialFlag(video::EMF_ANISOTROPIC_FILTER, true);
    cube->setScale(core::vector3df(5, 5, 5));
    body->setName("TestCube");
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
//     bb->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
    return light;
}

Simulation *IOSP::TestScene()
{
    auto *smgr = IrrCommonObject::getSceneManager();
    auto *cam = smgr->addCameraSceneNodeMaya();
//     auto *light = smgr->addLightSceneNode();
    auto light = createTestLigth();
    light->setPosition(core::vector3df(0, 0, 25));
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
