#ifndef BOTTLEBRUSH_ENGINE_INPUTMGR_H
#define BOTTLEBRUSH_ENGINE_INPUTMGR_H

#include "KeyInput.h"
#include "Window.h"

class InputMgr {
 public:
  static InputMgr& GetInstance();

  KeyInput::KeyState GetKeybdState(KeyInput::KeyType key);
  void GetMouseState();
  [[nodiscard]] const Window& GetWindow() const;
  void ReadKeybdInput(const Window& window);
  void ReadMouseInput(Window window);
  void SetWindow(Window::InputMode mode, Window::InputModeType cursor,
                 const std::string& name, int width, int height);

 private:
  InputMgr();

  void SetKeybdState(KeyInput::KeyType key, KeyInput::KeyState state);
  void SetMouseState();

  KeyInput keybd_;
  Window window_;
};

#endif  // BOTTLEBRUSH_ENGINE_INPUTMGR_H
