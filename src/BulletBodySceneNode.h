
#pragma once

#include <irrlicht.h>
#include <BulletMotionState.h>
#include <btBulletDynamicsCommon.h>

namespace IOSP
{
    class BulletBodySceneNode : public irr::scene::ISceneNode
    {
        BulletMotionState m_mstate{*this};
        btRigidBody *m_bbody;
        irr::core::aabbox3d<irr::f32> m_bbox;
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
        btRigidBody* bulletRigidBody() { return m_bbody; }
        const btRigidBody* bulletRigidBody() const { return m_bbody; }
        const irr::core::aabbox3d<irr::f32>& getBoundingBox() const { return m_bbox; }
        void render() {}
        void syncTransform();
        void syncInertia();
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
