#include "renderer.h"

__global__ void Draw(float *image, uint32_t w, uint32_t h) {

  auto x = blockIdx.x * blockDim.x + threadIdx.x;
  auto y = blockIdx.y * blockDim.y + threadIdx.y;

  if (x > w || y > h)
    return;

  int vertex_index = y * w + x;

  float u = float(x) / float(w);
  float v = float(y) / float(h);

  u = u * 2.0f - 1.0f;
  v = v * 2.0f - 1.0f;

  image[5 * vertex_index + 0] = u;
  image[5 * vertex_index + 1] = v;
  image[5 * vertex_index + 2] = std::sqrt(u * u + v * v);
  image[5 * vertex_index + 3] = 0.0f;
  image[5 * vertex_index + 4] = 0.0f;
}

void RunKernel(float *data, uint32_t w, uint32_t h) {
  dim3 threads(32, 32);

  int bx = w / threads.x;
  int by = h / threads.y;

  dim3 blocks(bx, by);

  Draw<<<blocks, threads>>>(data, w, h);
}
