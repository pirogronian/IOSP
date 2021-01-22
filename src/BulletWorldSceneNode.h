
#pragma once

#include <irrlicht.h>
#include <btBulletDynamicsCommon.h>
#include <Common.h>

namespace IOSP
{
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
    public:
        BulletWorldSceneNode(
            irr::scene::ISceneNode *,
            irr::scene::ISceneManager *,
            irr::s32 id = -1,
            const irr::core::vector3df& position = irr::core::vector3df(0, 0, 0),
            const irr::core::vector3df& rotation = irr::core::vector3df(0, 0, 0),
            const irr::core::vector3df& scale = irr::core::vector3df(1, 1, 1));
        void OnRegisterSceneNode() override;
        btDiscreteDynamicsWorld& bulletWorld() { return m_world; }
        const btDiscreteDynamicsWorld& bulletWorld() const { return m_world; }
        void setGlobalGravity(const btVector3& v) { m_world.setGravity(v); }
        btVector3 getGlobalGravity() const { return m_world.getGravity(); }
        void setMinStepDelta(btScalar d) { m_minStepDelta = d; }
        btScalar getMinStepDelta() const { return m_minStepDelta; }
        void stepSimulation(btScalar d)
        {
            m_world.stepSimulation(d, m_maxSubSteps, m_minStepDelta);
        }
        irr::scene::ESCENE_NODE_TYPE getType() const override
        {
            return (irr::scene::ESCENE_NODE_TYPE)IOSP::ESNT_BULLET_WORLD;
        }
        void render() override {}
        const irr::core::aabbox3d<irr::f32>& getBoundingBox() const
        {
            return m_bbox;
        }
    };
}
