
#include "CopyFrom.h"

using namespace IOSP;

btCollisionObject &copyFrom(
    btCollisionObject& obj,
    btCollisionObject& other)
{
    int afm = btCollisionObject::CF_ANISOTROPIC_FRICTION_DISABLED;
    if (other.hasAnisotropicFriction(btCollisionObject::CF_ANISOTROPIC_FRICTION))
        afm = btCollisionObject::CF_ANISOTROPIC_FRICTION;
    else if (other.hasAnisotropicFriction(btCollisionObject::CF_ANISOTROPIC_ROLLING_FRICTION))
        afm = btCollisionObject::CF_ANISOTROPIC_ROLLING_FRICTION;
    obj.setAnisotropicFriction(other.getAnisotropicFriction(), afm);
    obj.setCollisionFlags(other.getCollisionFlags());
    obj.setHitFraction(other.getHitFraction());
    obj.setContactProcessingThreshold(other.getContactProcessingThreshold());
    obj.setCollisionShape(other.getCollisionShape());
    obj.setDeactivationTime(other.getDeactivationTime());
    obj.setRestitution(other.getRestitution());
    obj.setFriction(other.getFriction());
    obj.setRollingFriction(other.getRollingFriction());
    obj.setSpinningFriction(other.getSpinningFriction());
    obj.setContactStiffnessAndDamping(
        other.getContactStiffness(),
        other.getContactDamping()
    );
    obj.setBroadphaseHandle(other.getBroadphaseHandle());
    obj.setCcdSweptSphereRadius(other.getCcdSweptSphereRadius());
    obj.setCcdMotionThreshold(other.getCcdMotionThreshold());
    return obj;
}

btRigidBody& copyFrom(btRigidBody& obj, btRigidBody& other)
{
    obj.setGravity(other.getGravity());
    obj.setDamping(
        other.getLinearDamping(),
        other.getAngularDamping()
    );
    obj.setSleepingThresholds(
        other.getLinearSleepingThreshold(),
        other.getAngularSleepingThreshold()
    );
    obj.setLinearFactor(other.getLinearFactor());
    btScalar m = other.getMass();
    obj.setMassProps(m, btVector3(m, m, m));
    obj.setCenterOfMassTransform(other.getCenterOfMassTransform());
    obj.setNewBroadphaseProxy(other.getBroadphaseProxy());
    obj.setAngularFactor(other.getAngularFactor());
    obj.setFlags(other.getFlags());
    return obj;
}
