
#include <btBulletDynamicsCommon.h>
#include <irrlicht.h>

namespace IOSP
{
    class BulletMotionState : public btMotionState
    {
        irr::scene::ISceneNode& m_node;
    public:
        BulletMotionState(irr::scene::ISceneNode &node) : m_node(node) {}
        void getWorldTransform(btTransform &) const override;
        void setWorldTransform(const btTransform&) override;
    };
}
