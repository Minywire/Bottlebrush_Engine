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
const float kMaxZoom = 45.0f;
const float kMinZoom = 1.0f;
const float kMaxPitch = 89.0f;
const float kMinPitch = -kMaxPitch;

/// @class Camera
/// @brief The \c Camera class encapsulates a 3D camera.
///
/// The \c Camera class is used to represent a three-dimensional orthographic
/// projection camera instance for use in a three-dimensional rendered scene.
/// <p>
/// The constructor optionally sets the positional and up vectors that represent
/// where the camera is located in three-dimensional space, as well as the yaw
/// and pitch, where required. The values of the positional and up vectors may
/// also be passed in separately.
/// @author Jaiden di Lanzo
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

  /// @brief Gets the camera view matrix.
  /// <p>
  /// The \c GetViewMatrix function evaluates the camera view matrix based on
  /// the current positional, front, and up vectors. <p> The return value is a
  /// 4x4 matrix object.
  /// @returns A 4x4 matrix object that describes the conceptual look-at matrix.
  [[nodiscard]] glm::mat4 GetViewMatrix() const;

  /// @brief Processes keyboard input movement applied to the camera.
  /// <p>
  /// The \c ProcessKeyboard function evaluates camera movements resultant of
  /// specific keyboard inputs. The camera movement will be based on the camera
  /// movement speed in the specified direction for an evaluated movement
  /// velocity.
  /// @param direction The movement direction.
  /// @param delta The time delta.
  void ProcessKeyboard(CameraMovement direction, float delta);

  /// @brief Processes mouse movement input applied to the camera.
  /// <p>
  /// The \c ProcessMouseMovement function evaluates camera movements resultant
  /// of specific mouse movements. The camera movement will be based on the
  /// camera mouse sensitivity by a specified offset in the \a x and \a y
  /// directions. <p> By default, pitch constraints are enabled to avoid camera
  /// flips and gimbal lock at certain Euler angles.
  /// @param x_offset The movement offset in the \a x direction.
  /// @param y_offset The movement offset in the \a y direction.
  /// @param constrain_pitch A flag to enable or disable pitch constraints.
  void ProcessMouseMovement(float x_offset, float y_offset,
                            bool constrain_pitch = true);

  /// @brief Processes mouse scroll input movement applied to the camera.
  /// <p>
  /// The \c ProcessMouseScroll function evaluates camera movements resultant
  /// of specific mouse scroll wheel movements. The camera movement will be
  /// based on the minimum and maximum camera zoom values by a specified offset
  /// in the \a y direction.
  /// @param y_offset The scroll movement offset in the \a y direction.
  void ProcessMouseScroll(float y_offset);

 protected:
  void Update();
};

#endif  // BOTTLEBRUSH_ENGINE_CAMERA_H
