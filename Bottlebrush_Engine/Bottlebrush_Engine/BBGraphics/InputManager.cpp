#include <InputManager.h>

void InputManager::ProcessInput(Window window) {
  if (exitScreen) {
    if (glfwGetMouseButton(window.GetContext(),
                           GLFW_MOUSE_BUTTON_LEFT == GLFW_PRESS)) {
      window.SetShouldClose(true);
    }
    return;
  }

  if (glfwGetKey(window.GetContext(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    exitScreen = true;
  }

  if (glfwGetKey(window.GetContext(), GLFW_KEY_W) == GLFW_PRESS)
    gameScene.fetchCamera().ProcessKeyboard(FORWARD, delta);
  if (glfwGetKey(window.GetContext(), GLFW_KEY_S) == GLFW_PRESS)
    gameScene.fetchCamera().ProcessKeyboard(BACKWARD, delta);
  if (glfwGetKey(window.GetContext(), GLFW_KEY_A) == GLFW_PRESS)
    gameScene.fetchCamera().ProcessKeyboard(LEFT, delta);
  if (glfwGetKey(window.GetContext(), GLFW_KEY_D) == GLFW_PRESS)
    gameScene.fetchCamera().ProcessKeyboard(RIGHT, delta);
  if (glfwGetKey(window.GetContext(), GLFW_KEY_SPACE) == GLFW_PRESS)
    gameScene.fetchCamera().ProcessKeyboard(UP, delta);
  if (glfwGetKey(window.GetContext(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    gameScene.fetchCamera().ProcessKeyboard(DOWN, delta);
}

void InputManager::FramebufferSizeCallback(Window::WindowContext window, int width,
                             int height) {
  glViewport(0, 0, width, height);
}

void InputManager::KeyCallback(Window::WindowContext window, int key, int scancode,
                 int action, int mods) {
  if (exitScreen) return;

  if (key == GLFW_KEY_C && action == GLFW_PRESS) wireframe = !wireframe;

  if (action == GLFW_PRESS && key == GLFW_KEY_LEFT_SHIFT)
    gameScene.fetchCamera().SetSpeed(gameScene.getCamera().GetSpeed() * 2.0f);
  if (action == GLFW_RELEASE && key == GLFW_KEY_LEFT_SHIFT)
    gameScene.fetchCamera().SetSpeed(gameScene.getCamera().GetSpeed() / 2.0f);
}

void InputManager::MouseCallback(Window::WindowContext window, double pos_x, double pos_y) {
  auto x = static_cast<float>(pos_x), y = static_cast<float>(pos_y);

  if (exitScreen) return;

  if (first_mouse_click) {
    last_x = x;
    last_y = y;
    first_mouse_click = false;
  }

  float x_offset = x - last_x, y_offset = last_y - y;

  last_x = x;
  last_y = y;

  gameScene.fetchCamera().ProcessMouseMovement(x_offset, y_offset);
}

void InputManager::ScrollCallback(Window::WindowContext window, double x_offset,
                    double y_offset) {
  if (exitScreen) return;
  gameScene.fetchCamera().ProcessMouseScroll(static_cast<float>(y_offset));
}