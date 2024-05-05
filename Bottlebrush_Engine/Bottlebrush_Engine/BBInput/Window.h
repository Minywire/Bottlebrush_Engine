#ifndef BOTTLEBRUSH_ENGINE_WINDOW_H
#define BOTTLEBRUSH_ENGINE_WINDOW_H

#include <stdexcept>
#include <string>
#include <tuple>

#include "glad/glad.h"
#include "glfw/glfw3.h"

class Window {
 public:
  typedef GLFWwindow* WindowContext;
  typedef GLFWmonitor* WindowMonitor;
  typedef const GLFWvidmode* WindowVideoMode;

  enum CursorMode {
    CURSOR_DISABLED = GLFW_CURSOR_DISABLED,
    CURSOR_HIDDEN = GLFW_CURSOR_HIDDEN,
    CURSOR_NORMAL = GLFW_CURSOR_NORMAL
  };

  enum WindowMode { CURSOR = GLFW_CURSOR, RAWMTN = GLFW_RAW_MOUSE_MOTION };

  static const int kMultiSamples = 4;
  static const int kSwapInterval = 0;
  static const int kVersionMajor = 3;
  static const int kVersionMinor = 3;

  Window(WindowMode window_mode, CursorMode cursor_mode,
         const std::string& window_name, int width, int height);

  void Create();
  [[nodiscard]] float GetAspectRatio() const;
  [[nodiscard]] WindowContext GetContext() const;
  [[nodiscard]] CursorMode GetCursorMode() const;
  [[nodiscard]] bool GetFullscreen() const;
  [[nodiscard]] WindowMonitor GetPrimaryMonitor() const;
  [[nodiscard]] bool GetShouldClose() const;
  [[nodiscard]] std::tuple<int, int> GetSize() const;
  [[nodiscard]] WindowVideoMode GetVideoMode() const;
  [[nodiscard]] WindowMode GetWindowMode() const;
  void Remove();
  void Swap();
  void SetCursorMode(CursorMode cursor_mode);
  void SetFullscreen(bool fullscreen);
  void SetShouldClose(bool should_close);
  void SetSize(int width, int height);
  void SetWindowMode(WindowMode window_mode);
  void Poll();

 private:
  void AllotWindowMonitor();
  void AssignSwapInterval();
  void CeaseWindowContext();
  void CloseWindowContext();
  void GetFrameBufferSize();
  void MakeContextCurrent();
  void PollEventsListener();
  void SetCursorInputMode();
  void SetRawMtnInputMode();
  void SetWindowFrameSize();
  void ShiftWindowBuffers();
  void SpawnWindowContext();

  int buffer_height_, buffer_width_;
  CursorMode cursor_mode_;
  bool fullscreen_;
  WindowMonitor primary_monitor_;
  std::tuple<int, int> window_size_;
  int swap_interval_;
  WindowContext window_context_;
  WindowVideoMode video_mode_;
  WindowMode window_mode_;
  std::string window_name_;
};

#endif  // BOTTLEBRUSH_ENGINE_WINDOW_H
