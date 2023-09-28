#ifndef CUDA_GRAPHICS_RESOURCE_H
#define CUDA_GRAPHICS_RESOURCE_H

#include "buffer.h"
#include "texture.h"

struct cudaGraphicsResource;
struct cudaArray;

struct MappedPointer {
  void *data;
  uint64_t size;
};

class CUDAGraphicsResource {

public:
  CUDAGraphicsResource();

  void Begin();
  void End();

  cudaArray *GetMappedArray();
  MappedPointer GetMappedPointer();
  void RegisterBuffer(const Buffer &buffer);
  void RegisterTexture(const Texture &texture);

private:
  cudaGraphicsResource *cuda_resource_{nullptr};
};

#endif // CUDA_GRAPHICS_RESOURCE_H