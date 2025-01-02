#include "cuda_tests.h"

#include <cuda.h>
#include <cuda_runtime.h>


#include <iostream>

#define CU_ENSURE_SUCCESS(result, msg) \
  if (result != CUDA_SUCCESS) {        \
    std::cerr << msg << std::endl;     \
  }

void CudaSession::allocateStubMemory() {
  CUresult result;

  // Allocate 10MB for fun:
  size_t bytes = 1024 * 1025 * 10;

  CUdeviceptr deviceptr;
  result = cuMemAlloc(&deviceptr, bytes);
  CU_ENSURE_SUCCESS(result, "Could not allocate device memory");

  result = cuMemFree(deviceptr);
  CU_ENSURE_SUCCESS(result, "Could not free device memory");
}
