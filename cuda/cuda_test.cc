#include "cuda.h"

#include <cuda_runtime.h>

#include <iostream>

int main() {
  std::cerr << "Hello Cuda" << std::endl;

  CUdevice device;
  CUcontext context;
  CUmodule module;
  CUfunction kernel;
  CUresult result;

  unsigned int flags = 0;

  int numDevices = 0;
  cudaGetDeviceCount(&numDevices);
  if (numDevices == 0) {
    std::cerr << "This host has no devices!" << std::endl;
    return 0;
  }

  // Loop through and print out device metadata.
  std::cerr << "Number of devices: " << numDevices << std::endl;
  for (int i = 0; i < numDevices; ++i) {
    cudaDeviceProp prop;
    cudaGetDeviceProperties(&prop, i);

    std::cerr << "  name: " << prop.name << std::endl;
    std::cerr << "  version: " << prop.major << "." << prop.minor << std::endl;
    std::cerr << "  SMs: " << prop.multiProcessorCount << std::endl;
    std::cerr << "  MHz: " << prop.clockRate / 1000 << std::endl;
    std::cerr << "  totalGlobalMem: " << (prop.totalGlobalMem / 1024 / 1024)
              << "MB" << std::endl;
  }

  return 0;
}