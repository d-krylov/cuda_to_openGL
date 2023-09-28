#include "common.h"
#include "renderer.h"

__global__ void Draw(uint32_t *image, uint32_t w, uint32_t h) {

  auto x = blockIdx.x * blockDim.x + threadIdx.x;
  auto y = blockIdx.y * blockDim.y + threadIdx.y;

  if (x > w || y > h)
    return;

  int vertex_index = y * w + x;

  image[vertex_index] = 0xff0000ff;
}

Renderer::Renderer(uint32_t w, uint32_t h) : width_(w), height_(h) {
  cudaMalloc(&data_, w * h * sizeof(uint32_t));
}

Renderer::~Renderer() { cudaFree(data_); }

void Renderer::RunKernel(cudaArray *texture) {
  dim3 threads(32, 32);

  int bx = width_ / threads.x;
  int by = height_ / threads.y;

  dim3 blocks(bx, by);

  Draw<<<blocks, threads>>>(data_, width_, height_);

  auto pitch = width_ * sizeof(uint32_t);

  CUDA_CHECK(cudaMemcpy2DToArray(texture, 0, 0, data_, pitch, pitch, height_,
                                 cudaMemcpyDeviceToDevice));
}
