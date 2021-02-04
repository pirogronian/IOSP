
#pragma once

#include <irrlicht.h>
#include <BulletMotionState.h>
#include <btBulletDynamicsCommon.h>
#include <BulletUpdatable.h>

namespace IOSP
{
    class BulletBodySceneNode : public irr::scene::ISceneNode, public BulletUpdatable
    {
        BulletMotionState m_mstate{*this};
        btRigidBody *m_bbody;
        irr::core::aabbox3d<irr::f32> m_bbox;
        btVector3 m_lVel, m_lAccel;
        btScalar m_lastDelta;
    public:
        BulletBodySceneNode(irr::scene::ISceneNode *,
                            irr::scene::ISceneManager *,
                            const btRigidBody::btRigidBodyConstructionInfo&,
                            irr::s32 id = -1);
        BulletBodySceneNode(irr::scene::ISceneNode *,
                            irr::scene::ISceneManager *,
                            btRigidBody*,
                            irr::s32 id = -1);
        ~BulletBodySceneNode();
        void setWorld(btDynamicsWorld& w)
        {
            w.addRigidBody(m_bbody);
        }
        btVector3 getLinearVelocity() const { return m_bbody->getLinearVelocity(); }
        btVector3 getLinearAcceleration() const { return m_lAccel; }
        btScalar getLastDelta() const { return m_lastDelta; }
        btRigidBody* bulletRigidBody() { return m_bbody; }
        const btRigidBody* bulletRigidBody() const { return m_bbody; }
        const irr::core::aabbox3d<irr::f32>& getBoundingBox() const { return m_bbox; }
        void render() {}
        void syncTransform();
        void syncInertia();
        virtual void update(irr::u32) override;
        btScalar getMass() const { return m_bbody ? m_bbody->getMass() : 0; }
        void setMass(btScalar);
//         void setPosition(const irr::core::vector3df& pos) override
//         {
//             ISceneNode::setPosition(pos);
//             syncTransform();
//         }
//         void setRotation(const irr::core::vector3df& pos) override
//         {
//             ISceneNode::setRotation(pos);
//             syncTransform();
//         }
        void applyTorqueLocal(const btVector3& rot)
        {
            m_bbody->applyTorque(m_bbody->getWorldTransform().getBasis() * rot);
        }
        void applyForceLocal(const btVector3& f, const btVector3& offset = btVector3(0, 0, 0))
        {
            auto &tr = m_bbody->getWorldTransform().getBasis();
            m_bbody->applyForce(tr * f, tr * offset);
        }
    };
}
