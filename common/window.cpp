#include "window.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

Window::Window() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window_ = glfwCreateWindow(512, 512, "Renderer", nullptr, nullptr);

  glfwMakeContextCurrent(window_);
  auto status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

Window::~Window() { glfwDestroyWindow(window_); }

void Window::Update() {
  glfwPollEvents();
  glfwSwapBuffers(window_);
}

bool Window::ShouldClose() { return glfwWindowShouldClose(window_); }