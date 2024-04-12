#ifndef BOTTLEBRUSH_ENGINE_CAMERA_H
#define BOTTLEBRUSH_ENGINE_CAMERA_H

#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

enum CameraMovement { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

const float kYaw = -90.0f;
const float kPitch = 0.0f;
const float kSpeed = 2.5f;
const float kSensitivity = 0.1f;
const float kZoom = 45.0f;

class Camera {
 public:
  glm::vec3 position_;
  glm::vec3 front_;
  glm::vec3 up_;
  glm::vec3 right_;
  glm::vec3 world_up_;
  float yaw_;
  float pitch_;
  float movement_speed_;
  float mouse_sensitivity_;
  float zoom_;

  explicit Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = kYaw,
                  float pitch = kPitch);

  Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y,
         float up_z, float yaw = kYaw, float pitch = kPitch);

  [[nodiscard]] glm::mat4 GetViewMatrix() const;
  void ProcessKeyboard(CameraMovement direction, float delta);
  void ProcessMouseMovement(float x_offset, float y_offset,
                            bool constrain_pitch = true);
  void ProcessMouseScroll(float y_offset);

 protected:
  void Update();
};

#endif  // BOTTLEBRUSH_ENGINE_CAMERA_H
