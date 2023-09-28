#ifndef RENDERER_H
#define RENDERER_H

#include <cstdint>

struct cudaArray;

class Renderer {
public:
  Renderer(uint32_t w, uint32_t h);
  ~Renderer();

  void RunKernel(cudaArray *texture);

private:
  uint32_t *data_{nullptr};
  uint32_t width_;
  uint32_t height_;
};

#endif // RENDERER_H