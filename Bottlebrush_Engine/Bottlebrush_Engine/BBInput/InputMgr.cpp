#include "InputMgr.h"

InputMgr& InputMgr::GetInstance() {
  static InputMgr instance_;
  return instance_;
}

KeyInput::KeyState InputMgr::GetKeybdState(KeyInput::KeyType key) {
  return keybd_.GetKeyState(key);
}

const Window& InputMgr::GetWindow() const { return window_; }

void InputMgr::ReadKeybdInput(const Window& window) {
  auto keys = keybd_.GetKeyTypes();

  for (const auto key : keys) {
    const int state = glfwGetKey(window.GetContext(), key);
    keybd_.SetKeyState(key, static_cast<KeyInput::KeyState>(state));
  }
}

void InputMgr::SetWindow(Window::InputMode mode, Window::InputModeType cursor,
                         const std::string& name, int width, int height) {
  window_ = Window(mode, cursor, name, width, height);
  window_.Create();
}

InputMgr::InputMgr()
    : keybd_({KeyInput::KeyType::kKeyW, KeyInput::KeyType::kKeyA,
              KeyInput::KeyType::kKeyS, KeyInput::KeyType::kKeyD,
              KeyInput::KeyType::kKeyC}),
      window_(Window::InputMode::kNone, Window::InputModeType::kCursorNone,
              std::string(), 0, 0) {}
