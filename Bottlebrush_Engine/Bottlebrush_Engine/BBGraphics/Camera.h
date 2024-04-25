#ifndef BOTTLEBRUSH_ENGINE_CAMERA_H
#define BOTTLEBRUSH_ENGINE_CAMERA_H

#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

enum CameraMovement { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

const float kMaxZoom = 80.0f;
const float kMinZoom = 1.0f;
const float kMaxPitch = 89.0f;
const float kMinPitch = -kMaxPitch;
const float kPitch = 0.0f;
const float kSensitivity = 0.1f;
const float kSpeed = 2.5f;
const float kYaw = -90.0f;

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
  explicit Camera(glm::vec3 position = {0.0f, 0.0f, 0.0f});
  Camera(float x, float y, float z);

  [[nodiscard]] glm::vec3 GetFront() const;
  [[nodiscard]] float GetSensitivity() const;
  [[nodiscard]] float GetSpeed() const;
  [[nodiscard]] float GetPitch() const;
  [[nodiscard]] glm::vec3 GetPosition() const;
  [[nodiscard]] float GetPositionX() const;
  [[nodiscard]] float GetPositionY() const;
  [[nodiscard]] float GetPositionZ() const;
  [[nodiscard]] glm::vec3 GetRight() const;
  [[nodiscard]] glm::vec3 GetUp() const;

  /// @brief Gets the camera view matrix.
  /// <p>
  /// The \c GetViewMatrix function evaluates the camera view matrix based on
  /// the current positional, front, and up vectors. <p> The return value is a
  /// 4x4 matrix object.
  /// @returns A 4x4 matrix object that describes the conceptual look-at matrix.
  [[nodiscard]] glm::mat4 GetViewMatrix() const;

  [[nodiscard]] glm::vec3 GetWorldUp() const;
  [[nodiscard]] float GetZoom() const;
  [[nodiscard]] float GetYaw() const;

  void SetFront(float x, float y, float z);
  void SetSensitivity(float sensitivity);
  void SetSpeed(float speed);
  void SetPitch(float pitch);
  void SetPosition(glm::vec3 position);
  void SetPosition(float x, float y, float z);
  void SetPositionX(float x);
  void SetPositionY(float y);
  void SetPositionZ(float z);
  void SetViewMatrix(glm::vec3 position, glm::vec3 front, glm::vec3 up);
  void SetZoom(float zoom);
  void SetYaw(float yaw);

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

 private:
  void Update();

  glm::vec3 front_;
  glm::mat4 look_at_;
  float pitch_;
  glm::vec3 position_;
  glm::vec3 right_;
  float sensitivity_;
  float speed_;
  glm::vec3 up_;
  glm::vec3 world_up_;
  float yaw_;
  float zoom_;
};

#endif  // BOTTLEBRUSH_ENGINE_CAMERA_H
