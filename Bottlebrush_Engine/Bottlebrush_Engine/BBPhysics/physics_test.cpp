#include <cstdio>

#include "PhysicsMgr.h"
#include "reactphysics3d/reactphysics3d.h"
using namespace reactphysics3d;

int main() {
    std::vector<uint32_t> indices;
    PhysicsMgr& physics_mgr = PhysicsMgr::GetInstance();
    physics_mgr.CreateWorld();

    for (int i = 0; i < 3; i++) {
        auto index = physics_mgr.CreateBody();
        indices.push_back(index);
    }

    for (auto& i : indices) {
        physics_mgr.CreateBoxCollider(i, {0.5f, 0.5f, 0.5f});

        auto pbody = physics_mgr.ObtainBody(i);

        auto position = pbody.GetPosition();
        auto rotation = pbody.GetRotation();
        auto scale = pbody.GetScale();
        auto type = pbody.GetType();
        auto collider = pbody.GetCollider();

        printf("Index:\n\tMgr: %d\n\tInt: %d\n", i,
               pbody.GetRigidBody()->getEntity().getIndex());
        printf("Type:\n\tMgr: %u\n\tInt: %u\n", type,
               static_cast<int>(pbody.GetRigidBody()->getType()));
        printf("Position:\n\tMgr: %f, %f, %f\n\tInt: %f, %f, %f\n", position.x,
               position.y, position.z,
               pbody.GetRigidBody()->getTransform().getPosition().x,
               pbody.GetRigidBody()->getTransform().getPosition().y,
               pbody.GetRigidBody()->getTransform().getPosition().z);
        printf("Rotation:\n\tMgr: %f, %f, %f\n\tInt: %f, %f, %f\n", rotation.x,
               rotation.y, rotation.z,
               pbody.GetRigidBody()->getTransform().getOrientation().x,
               pbody.GetRigidBody()->getTransform().getOrientation().y,
               pbody.GetRigidBody()->getTransform().getOrientation().z);
        printf("Scale: %f, %f, %f\n", scale.x, scale.y, scale.z);
        printf("Collider:\n\tMgr: %s\n\tInt: %s\n",
               collider->getCollisionShape()->to_string().c_str(),
               physics_mgr.GetWorld()
                   ->getRigidBody(i)
                   ->getCollider(0)
                   ->getCollisionShape()
                   ->to_string()
                   .c_str());
        printf("Address:\n\tMgr: %p\n\tInt: %p\n\n", pbody.GetRigidBody(),
               physics_mgr.GetWorld()->getRigidBody(i));
    }

    for (auto& i : indices) {
        physics_mgr.RemoveBody(i);
    }

    physics_mgr.DeleteWorld();

    return EXIT_SUCCESS;
}