#ifndef WINDOW_H
#define WINDOW_H

struct GLFWwindow;

class Window {
public:
  Window();
  ~Window();

  bool ShouldClose();
  void Update();

private:
  GLFWwindow *window_;
};

#endif // WINDOW_H