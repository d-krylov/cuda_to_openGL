#include "common.h"
#include "cuda_graphics_resource.h"
#include <iostream>

CUDAGraphicsResource::CUDAGraphicsResource() {
  uint32_t count;
  int32_t id[16];

  auto status = cudaGLGetDevices(&count, id, 1, cudaGLDeviceListAll);

  if (status != cudaSuccess) {
    std::cout << "First error" << std::endl;
  }

  status = cudaSetDevice(id[0]);

  if (status != cudaSuccess) {
  }
}

void CUDAGraphicsResource::RegisterBuffer(const Buffer &buffer) {
  CUDA_CHECK(cudaGraphicsGLRegisterBuffer(&cuda_resource_, buffer.GetID(),
                                          cudaGraphicsMapFlagsNone));
}

void CUDAGraphicsResource::RegisterTexture(const Texture &texture) {
  CUDA_CHECK(cudaGraphicsGLRegisterImage(&cuda_resource_, texture.GetID(),
                                         GL_TEXTURE_2D,
                                         cudaGraphicsMapFlagsWriteDiscard));
}

MappedPointer CUDAGraphicsResource::GetMappedPointer() {
  void *device_pointer;
  uint64_t size;
  CUDA_CHECK(cudaGraphicsResourceGetMappedPointer(&device_pointer, &size,
                                                  cuda_resource_));
  return MappedPointer{device_pointer, size};
}

cudaArray *CUDAGraphicsResource::GetMappedArray() {
  cudaArray *array;
  CUDA_CHECK(
      cudaGraphicsSubResourceGetMappedArray(&array, cuda_resource_, 0, 0));
  return array;
}

void CUDAGraphicsResource::Begin() {
  CUDA_CHECK(cudaGraphicsMapResources(1, &cuda_resource_, 0));
}

void CUDAGraphicsResource::End() {
  CUDA_CHECK(cudaGraphicsUnmapResources(1, &cuda_resource_, 0));
}
