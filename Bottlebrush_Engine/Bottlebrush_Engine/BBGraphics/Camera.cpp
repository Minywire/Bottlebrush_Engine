#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : front_(glm::vec3(0.0f, 0.0f, -1.0f)),
      movement_speed_(kSpeed),
      mouse_sensitivity_(kSensitivity),
      zoom_(kZoom) {
  position_ = position;
  world_up_ = up;
  yaw_ = yaw;
  pitch_ = pitch;

  Update();
}

Camera::Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y,
               float up_z, float yaw, float pitch)
    : front_(glm::vec3(0.0f, 0.0f, -1.0f)),
      movement_speed_(kSpeed),
      mouse_sensitivity_(kSensitivity),
      zoom_(kZoom) {
  position_ = glm::vec3(pos_x, pos_y, pos_z);
  world_up_ = glm::vec3(up_x, up_y, up_z);
  yaw_ = yaw;
  pitch_ = pitch;

  Update();
}

glm::mat4 Camera::GetViewMatrix() const {
  return glm::lookAt(position_, position_ + front_, up_);
}

void Camera::ProcessKeyboard(CameraMovement direction, float delta) {
  float velocity = movement_speed_ * delta;

  if (direction == FORWARD) position_ += front_ * velocity;
  if (direction == BACKWARD) position_ -= front_ * velocity;
  if (direction == LEFT) position_ -= right_ * velocity;
  if (direction == RIGHT) position_ += right_ * velocity;
  if (direction == UP) position_ += up_ * velocity;
  if (direction == DOWN) position_ -= up_ * velocity;
  //  position_.y = 0.0f;
}

void Camera::ProcessMouseMovement(float x_offset, float y_offset,
                                  bool constrain_pitch) {
  x_offset *= mouse_sensitivity_;
  y_offset *= mouse_sensitivity_;

  yaw_ += x_offset;
  pitch_ += y_offset;

  if (constrain_pitch) {
    if (pitch_ > 89.0f) pitch_ = 89.0f;
    if (pitch_ < -89.0f) pitch_ = -89.0f;
  }

  Update();
}

void Camera::ProcessMouseScroll(float y_offset) {
  zoom_ -= y_offset;

  if (zoom_ < 1.0f) zoom_ = 1.0f;
  if (zoom_ > 45.0f) zoom_ = 45.0f;
}

void Camera::Update() {
  glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);

  front.x = std::cos(glm::radians(yaw_)) * std::cos(glm::radians(pitch_));
  front.y = std::sin(glm::radians(pitch_));
  front.z = std::sin(glm::radians(yaw_)) * std::cos(glm::radians(pitch_));
  front_ = glm::normalize(front);
  right_ = glm::normalize(glm::cross(front_, world_up_));
  up_ = glm::normalize(glm::cross(right_, front_));
}
