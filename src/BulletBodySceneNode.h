
#pragma once

#include <irrlicht.h>
#include <BulletMotionState.h>
#include <btBulletDynamicsCommon.h>
#include <BulletUpdatable.h>

namespace IOSP
{
    class BulletBodySceneNode : public irr::scene::ISceneNode, public BulletUpdatable
    {
    protected:
        BulletMotionState m_mstate{*this};
        btRigidBody *m_bbody{nullptr};
        irr::core::aabbox3d<irr::f32> m_bbox;
        btVector3 m_lVel{0, 0, 0}, m_lAccel{0, 0, 0};
        btScalar m_lastDelta{0};
        btDynamicsWorld *m_world{nullptr};
    public:
        static BulletBodySceneNode *getNode(const btRigidBody *rb) {
            return static_cast<BulletBodySceneNode*>(rb->getUserPointer());
        }
        BulletBodySceneNode(irr::scene::ISceneNode *,
                            irr::scene::ISceneManager *,
                            const btRigidBody::btRigidBodyConstructionInfo&,
                            irr::s32 id = -1);
        BulletBodySceneNode(irr::scene::ISceneNode *,
                            irr::scene::ISceneManager *,
                            btRigidBody*,
                            irr::s32 id = -1);
        ~BulletBodySceneNode();
        void setWorld(btDynamicsWorld *);
        const btDynamicsWorld *getWorld() const { return m_world; }
        btDynamicsWorld *getWorld() { return m_world; }
        btVector3 getLinearVelocity() const { return m_bbody ? m_bbody->getLinearVelocity() : btVector3(0, 0, 0); }
        btVector3 getLinearAcceleration() const { return m_lAccel; }
        btScalar getLastDelta() const { return m_lastDelta; }
        btRigidBody* getRigidBody() { return m_bbody; }
        const btRigidBody* getRigidBody() const { return m_bbody; }
        void setRigidBody(btRigidBody*);
        void clearRigidBody();
        const irr::core::aabbox3d<irr::f32>& getBoundingBox() const { return m_bbox; }
        void render() {}
        void syncTransform();
        void syncInertia();
        virtual void update(irr::u32) override;
        btScalar getMass() const { return m_bbody ? m_bbody->getMass() : 0; }
        void setMass(btScalar);
        btTransform getBodyTransform() const { return m_bbody ? m_bbody->getWorldTransform() : btTransform(); }
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
            if (!m_bbody)  return;
            m_bbody->applyTorque(m_bbody->getWorldTransform().getBasis() * rot);
        }
        void applyForceLocal(const btVector3& f, const btVector3& offset = btVector3(0, 0, 0))
        {
            if (!m_bbody)  return;
            auto &tr = m_bbody->getWorldTransform().getBasis();
            m_bbody->applyForce(tr * f, tr * offset);
        }
    };
}
