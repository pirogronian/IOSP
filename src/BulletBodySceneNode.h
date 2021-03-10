
#pragma once

#include <string>
#include <irrlicht.h>
#include <Utils/AutoIndexer.h>
#include <BulletWorldSceneNode.h>
#include <BulletMotionState.h>
#include <btBulletDynamicsCommon.h>
#include <Component.h>

namespace IOSP
{
    class LogicalBody;

    class BulletBodySceneNode : public irr::scene::ISceneNode
    {
        friend BulletWorldSceneNode;
    protected:
        BulletMotionState m_mstate{*this};
        btRigidBody *m_bbody{nullptr};
        std::size_t m_worldIndex{std::numeric_limits<std::size_t>::max()};
        irr::core::aabbox3d<irr::f32> m_bbox;
        btVector3 m_lVel{0, 0, 0}, m_lAccel{0, 0, 0};
        btScalar m_lastDelta{0};
        BulletWorldSceneNode *m_world{nullptr};
        Component m_rootComponent{this};
        LogicalBody *m_logicalBody{nullptr};
        AutoIndexer<Component*> m_components;
        AutoIndexer<std::string> m_compNames;
        void autoIndexComponent(Component*, std::string prefix = "");
        void setWorld(BulletWorldSceneNode *w) { m_world = w; }
        void setWorldIndex(std::size_t i) { m_worldIndex - i; }
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
        const BulletWorldSceneNode *getWorld() const { return m_world; }
        BulletWorldSceneNode *getWorld() { return m_world; }
        std::size_t getWorldIndex() const { return m_worldIndex; }
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
        virtual void update(irr::u32);
        btScalar getMass() const { return m_bbody ? m_bbody->getMass() : 0; }
        void setMass(btScalar);
        btTransform getBodyTransform() const { return m_bbody ? m_bbody->getWorldTransform() : btTransform(); }
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
        btVector3 getAppliedForce() const { return m_bbody ? m_bbody->getTotalForce() : btVector3(0, 0, 0); }
        btCollisionWorld::ClosestRayResultCallback rayTestClosest(const btVector3& start,
                            const btVector3& stop) const
        {
            auto tr = getBodyTransform();
            if (!m_world)  return btCollisionWorld::ClosestRayResultCallback(start, stop);
            return m_world->rayTestClosest(tr * start, tr * stop);
        }
        btCollisionWorld::ClosestRayResultCallback rayTestClosest(const btVector3& stop) const
        {
            return rayTestClosest(btVector3(0, 0, 0), stop);
        }
        btFixedConstraint *attachFixed(btRigidBody *);
        btFixedConstraint *attachFixed(BulletBodySceneNode *);
        Component &getRootComponent() { return m_rootComponent; }
        const Component &getRootComponent() const { return m_rootComponent; }
        void rebuildComponentIndex() {
            clearComponentIndex();
            autoIndexComponent(&m_rootComponent);
        }
        void clearComponentIndex()
        {
            m_components.clear();
            m_compNames.clear();
        }
        Component *getComponent(std::size_t i) { return m_components.get(i, nullptr); }
        const Component *getComponent(std::size_t i) const { return m_components.get(i, nullptr); }
        std::size_t getComponentIndexSize() const { return m_components.size(); }
        LogicalBody *getLogicalBody() { return m_logicalBody; }
        const LogicalBody *getLogicalBody() const { return m_logicalBody; }
        void setLogicalBody(LogicalBody *lg) { m_logicalBody = lg; }
        std::string getComponentName(std::size_t i) { return m_compNames.get(i, std::string()); }
        void setName(const irr::c8 *name) override
        {
            ISceneNode::setName(name);
            m_rootComponent.setLocalName(name);
            rebuildComponentIndex();
        }
        void setName(const irr::core::stringc &name) override
        {
            ISceneNode::setName(name);
            m_rootComponent.setLocalName(name.c_str());
            rebuildComponentIndex();
        }
        void setID(irr::s32 i) override
        {
            ISceneNode::setID(i);
            if (m_bbody)  m_bbody->setUserIndex(i);
        }
        BulletBodySceneNode *createCopy();
        ISceneNode *clone(irr::scene::ISceneNode * = nullptr,
                          irr::scene::ISceneManager * = nullptr) override;
    };
}
