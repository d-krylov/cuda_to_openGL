#ifndef COMMON_H
#define COMMON_H

#include <cuda.h>
#include <cudaGL.h>
#include <cuda_gl_interop.h>
#include <cuda_runtime.h>
#include <iostream>

#define CUDA_CHECK(error) CUDACheck(error, __FILE__, __LINE__)

inline void CUDACheck(cudaError_t error, const char *file, const int line) {
  if (error != cudaSuccess) {
    std::cout << error << " in " << file << std::endl;
  }
}

#endif // COMMON_H