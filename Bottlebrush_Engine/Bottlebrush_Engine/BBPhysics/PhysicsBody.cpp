#include "PhysicsBody.h"

PhysicsBody::PhysicsBody(PhysicsBodyType type, glm::vec3 position,
                         glm::vec3 rotation, glm::vec3 scale)
    : body_(nullptr),
      position_(position),
      rotation_(rotation),
      scale_(scale),
      type_(type) {}

const glm::vec3& PhysicsBody::GetPosition() const { return position_; }

PhysicsBody::RigidBody PhysicsBody::GetRigidBody() const { return body_; }

const glm::vec3& PhysicsBody::GetRotation() const { return rotation_; }

const glm::vec3& PhysicsBody::GetScale() const { return scale_; }

PhysicsBody::PhysicsBodyType PhysicsBody::GetType() const { return type_; }

void PhysicsBody::SetPosition(const glm::vec3& position) {
    position_ = position;
    SetRigidBodyTrns();
}

void PhysicsBody::SetRigidBody(RigidBody body) {
    body_ = body;
    SetRigidBodyTrns();
    SetRigidBodyType();
}

void PhysicsBody::SetRotation(const glm::vec3& rotation) {
    rotation_ = rotation;
    SetRigidBodyTrns();
}

void PhysicsBody::SetScale(const glm::vec3& scale) {
    scale_ = scale;
    SetRigidBodyTrns();
}

void PhysicsBody::SetType(PhysicsBodyType type) {
    type_ = type;
    SetRigidBodyType();
}

void PhysicsBody::SetRigidBodyTrns() {
    auto p = rp3d::Vector3(position_.x, position_.y, position_.z);
    auto o = rp3d::Quaternion(rotation_.x, rotation_.y, rotation_.z, 1.0f);
    auto t = rp3d::Transform(p, o);
    body_->setTransform(t);
}

void PhysicsBody::SetRigidBodyType() {
    switch (type_) {
        case kStatic:
            body_->setType(rp3d::BodyType::STATIC);
            break;
        case kKinematic:
            body_->setType(rp3d::BodyType::KINEMATIC);
            break;
        case kDynamic:
            body_->setType(rp3d::BodyType::DYNAMIC);
            break;
        default:
            break;
    }
}
