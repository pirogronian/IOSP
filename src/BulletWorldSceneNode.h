
#pragma once

#include <irrlicht.h>
#include <btBulletDynamicsCommon.h>
#include <Common.h>
#include <Utils/AutoIndexer.h>
// #include <BulletUpdatable.h>

namespace IOSP
{
    class BulletUpdatable;
    class BulletBodySceneNode;

    class BulletWorldSceneNode : public irr::scene::ISceneNode
    {
        btDefaultCollisionConfiguration m_config;
        btCollisionDispatcher m_dispatcher{&m_config};
        btDbvtBroadphase m_broadphase;
        btSequentialImpulseConstraintSolver m_solver;
        btDiscreteDynamicsWorld m_world{&m_dispatcher, &m_broadphase, &m_solver, &m_config};
        int m_maxSubSteps{128};
        btScalar m_minStepDelta{1./60.};
        irr::core::aabbox3d<irr::f32> m_bbox;
        AutoIndexer<BulletUpdatable*> m_updatableIndex;
    public:
        static BulletWorldSceneNode* getNode(btDynamicsWorld *w) {
            return static_cast<BulletWorldSceneNode*>(w->getWorldUserInfo());
        }
        BulletWorldSceneNode(
            irr::scene::ISceneNode *,
            irr::scene::ISceneManager *,
            irr::s32 id = -1,
            const irr::core::vector3df& position = irr::core::vector3df(0, 0, 0),
            const irr::core::vector3df& rotation = irr::core::vector3df(0, 0, 0),
            const irr::core::vector3df& scale = irr::core::vector3df(1, 1, 1));
        void OnRegisterSceneNode() override;
        btDiscreteDynamicsWorld& getBulletWorld() { return m_world; }
        const btDiscreteDynamicsWorld& getBulletWorld() const { return m_world; }
        void setGlobalGravity(const btVector3& v) { m_world.setGravity(v); }
        btVector3 getGlobalGravity() const { return m_world.getGravity(); }
        void setMinStepDelta(btScalar d) { m_minStepDelta = d; }
        btScalar getMinStepDelta() const { return m_minStepDelta; }
        btScalar getMaxSubSteps() const { return m_maxSubSteps; }
        void setMaxSubSteps(btScalar m) { m_maxSubSteps = m; }
        void stepSimulation(btScalar d);
        irr::scene::ESCENE_NODE_TYPE getType() const override
        {
            return (irr::scene::ESCENE_NODE_TYPE)IOSP::ESNT_BULLET_WORLD;
        }
        void render() override {}
        const irr::core::aabbox3d<irr::f32>& getBoundingBox() const
        {
            return m_bbox;
        }
        void update(irr::u32);
        bool registerUpdatable(BulletUpdatable *);
        bool unregisterUpdatable(BulletUpdatable *);
        bool addBody(BulletBodySceneNode *);
        bool removeBody(BulletBodySceneNode *);
        btFixedConstraint *createFixedConstraint(btRigidBody *body1,
                                                btRigidBody *body2, 
                                                const btTransform& tr1,
                                                const btTransform& tr2)
        {
            auto cnt = new btFixedConstraint(*body1, *body2, tr1, tr2);
            if (cnt)
                m_world.addConstraint(cnt, true);
            return cnt;
        }
        btFixedConstraint *createFixedJoint(
            BulletBodySceneNode *,
            BulletBodySceneNode *,
            const btTransform&,
            const btTransform&);
        btFixedConstraint *createFixedConstraint(btRigidBody *, btRigidBody *);
        btFixedConstraint *createFixedJoint(
            BulletBodySceneNode *,
            BulletBodySceneNode *);
        void deleteConstraint(btTypedConstraint *j)
        {
            m_world.removeConstraint(j);
            delete j;
        }
        btCollisionWorld::ClosestRayResultCallback rayTestClosest(const btVector3& start, const btVector3& stop) const
        {
            btCollisionWorld::ClosestRayResultCallback callback(start, stop);
            m_world.rayTest(start, stop, callback);
            return callback;
        }
    };
}
