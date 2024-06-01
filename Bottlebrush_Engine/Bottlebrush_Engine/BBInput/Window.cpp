#include "Window.h"

Window::Window(WindowMode window_mode, CursorMode cursor_mode,
               const std::string& window_name, int width, int height) {
  if (!glfwInit()) {
    glfwTerminate();
    throw std::runtime_error("ERROR: Failed to create GLFW window!");
  }

  cursor_mode_ = cursor_mode;
  fullscreen_ = false;
  primary_monitor_ = glfwGetPrimaryMonitor();
  window_size_ = {width, height};
  swap_interval_ = kSwapInterval;
  video_mode_ = glfwGetVideoMode(primary_monitor_);
  window_mode_ = window_mode;
  window_name_ = window_name;

  if (width == 0 || height == 0)
    window_size_ = {video_mode_->width, video_mode_->height};

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, kVersionMajor);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, kVersionMinor);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
  glfwWindowHint(GLFW_RED_BITS, video_mode_->redBits);
  glfwWindowHint(GLFW_GREEN_BITS, video_mode_->greenBits);
  glfwWindowHint(GLFW_BLUE_BITS, video_mode_->blueBits);
  glfwWindowHint(GLFW_REFRESH_RATE, video_mode_->refreshRate);
  glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
  glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
  glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
  glfwWindowHint(GLFW_SAMPLES, kMultiSamples);
}

void Window::Create() {
  SpawnWindowContext();
  GetFrameBufferSize();
  MakeContextCurrent();
  AssignSwapInterval();
  if (window_mode_ == CURSOR) SetCursorInputMode();
  if (window_mode_ == RAWMTN) SetRawMtnInputMode();
}

float Window::GetAspectRatio() const {
  return static_cast<float>(std::get<0>(window_size_)) /
         static_cast<float>(std::get<1>(window_size_));
}

Window::WindowContext Window::GetContext() const { return window_context_; }

Window::CursorMode Window::GetCursorMode() const { return cursor_mode_; }

bool Window::GetFullscreen() const { return fullscreen_; }

Window::WindowMonitor Window::GetPrimaryMonitor() const {
  return primary_monitor_;
}

bool Window::GetShouldClose() const {
  return glfwWindowShouldClose(window_context_);
}

std::tuple<int, int> Window::GetSize() const { return window_size_; }

Window::WindowVideoMode Window::GetVideoMode() const { return video_mode_; }

Window::WindowMode Window::GetWindowMode() const { return window_mode_; }

const std::string& Window::GetWindowName() const { return window_name_; }

void Window::Remove() { CeaseWindowContext(); }

void Window::Swap() { ShiftWindowBuffers(); }

void Window::SetCursorMode(CursorMode cursor_mode) {
  cursor_mode_ = cursor_mode;
}

void Window::SetFullscreen(bool fullscreen) {
  fullscreen_ = fullscreen;
  primary_monitor_ = fullscreen ? glfwGetPrimaryMonitor() : nullptr;
  AllotWindowMonitor();
  GetFrameBufferSize();
}

void Window::SetShouldClose(bool should_close) {
  if (should_close) CloseWindowContext();
}

void Window::SetSize(int width, int height) {
  window_size_ = {width, height};
  SetWindowFrameSize();
  GetFrameBufferSize();
}

void Window::SetWindowMode(WindowMode window_mode) {
  window_mode_ = window_mode;
  if (window_mode_ == CURSOR) SetCursorInputMode();
  if (window_mode_ == RAWMTN) SetRawMtnInputMode();
}

void Window::SetWindowName(const std::string& wName) { 
    window_name_ = wName; 
}

void Window::Poll() { PollEventsListener(); }

void Window::AllotWindowMonitor() {
  glfwSetWindowMonitor(window_context_, primary_monitor_, 0, 0,
                       std::get<0>(window_size_), std::get<1>(window_size_),
                       GLFW_DONT_CARE);
}

void Window::AssignSwapInterval() { glfwSwapInterval(swap_interval_); }

void Window::CeaseWindowContext() {
  glfwDestroyWindow(window_context_);
  glfwTerminate();
}

void Window::CloseWindowContext() {
  glfwSetWindowShouldClose(window_context_, GLFW_TRUE);
}

void Window::GetFrameBufferSize() {
  glfwGetFramebufferSize(window_context_, &buffer_width_, &buffer_height_);
}

void Window::MakeContextCurrent() { glfwMakeContextCurrent(window_context_); }

void Window::PollEventsListener() { glfwPollEvents(); }

void Window::SetCursorInputMode() {
  glfwSetInputMode(window_context_, window_mode_, cursor_mode_);
}

void Window::SetRawMtnInputMode() {
  if (!glfwRawMouseMotionSupported()) {
    glfwTerminate();
    throw std::runtime_error("ERROR: Raw mouse motion is not supported!");
  }

  glfwSetInputMode(window_context_, window_mode_, GLFW_TRUE);
}

void Window::SetWindowFrameSize() {
  glfwSetWindowSize(window_context_, std::get<0>(window_size_),
                    std::get<1>(window_size_));
}

void Window::ShiftWindowBuffers() { glfwSwapBuffers(window_context_); }

void Window::SpawnWindowContext() {
  window_context_ =
      glfwCreateWindow(std::get<0>(window_size_), std::get<1>(window_size_),
                       window_name_.c_str(), nullptr, nullptr);

  if (window_context_ == nullptr) {
    glfwTerminate();
    throw std::runtime_error("ERROR: Failed to create GLFW window!");
  }
}
