#ifndef CUDA_TESTS_H_
#define CUDA_TESTS_H_

//------------------------------------------------------------------------------
// Stub CUDA Session class.

class CudaSession {
 public:
  CudaSession() {}
  virtual ~CudaSession() {}

  void allocateStubMemory();
};

#endif  // CUDA_TESTS_H_