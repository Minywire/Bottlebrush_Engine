#include "Window.h"
#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class InputManager {
 public:
  void ProcessInput(Window window);

  void FramebufferSizeCallback(Window::WindowContext window, int width, int height);

  void KeyCallback(Window::WindowContext window, int key, int scancode, int action, int mods);

  void MouseCallback(Window::WindowContext window, double pos_x, double pos_y);

  void ScrollCallback(Window::WindowContext window, double x_offset, double y_offset);
 private:

};
