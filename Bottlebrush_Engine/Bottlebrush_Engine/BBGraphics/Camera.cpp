#include "Camera.h"

Camera::Camera(glm::vec3 position) {
  front_ = {0.0f, 0.0f, -1.0f};
  world_up_ = {0.0f, 1.0f, 0.0f};
  sensitivity_ = kSensitivity;
  speed_ = kSpeed;
  pitch_ = kPitch;
  position_ = position;
  yaw_ = kYaw;
  zoom_ = kMaxZoom;

  Update();
}

Camera::Camera(float x, float y, float z) {
  front_ = {0.0f, 0.0f, -1.0f};
  world_up_ = {0.0f, 1.0f, 0.0f};
  sensitivity_ = kSensitivity;
  speed_ = kSpeed;
  pitch_ = kPitch;
  position_ = {x, y, z};
  yaw_ = kYaw;

  Update();
}

glm::vec3 Camera::GetFront() const { return front_; }

float Camera::GetSensitivity() const { return sensitivity_; }

float Camera::GetSpeed() const { return speed_; }

float Camera::GetPitch() const { return pitch_; }

glm::vec3 Camera::GetPosition() const { return position_; }

float Camera::GetPositionX() const { return position_.x; }

float Camera::GetPositionY() const { return position_.y; }

float Camera::GetPositionZ() const { return position_.z; }

glm::vec3 Camera::GetRight() const { return right_; }

glm::vec3 Camera::GetUp() const { return up_; }

glm::mat4 Camera::GetViewMatrix() const { return look_at_; }

glm::vec3 Camera::GetWorldUp() const { return world_up_; }

float Camera::GetZoom() const { return zoom_; }

float Camera::GetYaw() const { return yaw_; }

void Camera::SetFront(float x, float y, float z) { front_ = {x, y, z}; }

void Camera::SetSensitivity(float sensitivity) { sensitivity_ = sensitivity; }

void Camera::SetSpeed(float speed) { speed_ = speed; }

void Camera::SetPitch(float pitch) { pitch_ = pitch; }

void Camera::SetPosition(glm::vec3 position) { position_ = position; }

void Camera::SetPosition(float x, float y, float z) { position_ = {x, y, z}; }

void Camera::SetPositionX(float x) { position_.x = x; }

void Camera::SetPositionY(float y) { position_.y = y; }

void Camera::SetPositionZ(float z) { position_.z = z; }

void Camera::SetViewMatrix(glm::vec3 position, glm::vec3 front, glm::vec3 up) {
  look_at_ = glm::lookAt(position, position + front, up);
}

void Camera::SetZoom(float zoom) { zoom_ = zoom; }

void Camera::SetYaw(float yaw) { yaw_ = yaw; }

void Camera::ProcessKeyboard(CameraMovement direction, float delta) {
  float velocity = speed_ * delta;

  if (direction == FORWARD) position_ += front_ * velocity;
  if (direction == BACKWARD) position_ -= front_ * velocity;
  if (direction == LEFT) position_ -= right_ * velocity;
  if (direction == RIGHT) position_ += right_ * velocity;
  if (direction == UP) position_ += up_ * velocity;
  if (direction == DOWN) position_ -= up_ * velocity;

  Update();
}

void Camera::ProcessMouseMovement(float x_offset, float y_offset,
                                  bool constrain_pitch) {
  x_offset *= sensitivity_;
  y_offset *= sensitivity_;

  yaw_ += x_offset;
  pitch_ += y_offset;

  if (constrain_pitch) {
    if (pitch_ > kMaxPitch) pitch_ = kMaxPitch;
    if (pitch_ < kMinPitch) pitch_ = kMinPitch;
  }

  Update();
}

void Camera::ProcessMouseScroll(float y_offset) {
  zoom_ -= y_offset;

  if (zoom_ < kMinZoom) zoom_ = kMinZoom;
  if (zoom_ > kMaxZoom) zoom_ = kMaxZoom;

  Update();
}

void Camera::Update() {
  front_.x = std::cos(glm::radians(yaw_)) * std::cos(glm::radians(pitch_));
  front_.y = std::sin(glm::radians(pitch_));
  front_.z = std::sin(glm::radians(yaw_)) * std::cos(glm::radians(pitch_));
  front_ = glm::normalize(front_);
  right_ = glm::normalize(glm::cross(front_, world_up_));
  up_ = glm::normalize(glm::cross(right_, front_));
  look_at_ = glm::lookAt(position_, position_ + front_, up_);
}
