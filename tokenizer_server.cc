#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include <iostream>

#include "tokenizer.grpc.pb.h"

#include <cuda.h>
#include <cuda_runtime.h>

//------------------------------------------------------------------------------
// Stub CUDA Session class.

//
//
// TODO(kreeger): LEFT OFF RIGHT HERE - MOVE THIS TO A SEPERATE LIBRARY AND LINK.
// GETTING THE nvcc COMPILER THROUGH absl ISN'T GOOD!
//
//

#define ENSURE_SUCCESS(result, msg) \
  if (result != CUDA_SUCCESS) { std::cerr << msg << std::endl; }

class CudaSession {
 public:
  CudaSession() {}

  void allocateStubMemory() {
    CUresult result;

    // Allocate 10MB for fun:
    size_t bytes = 1024 * 1025 * 10;

    CUdeviceptr deviceptr;
    result = cuMemAlloc(&deviceptr, bytes);
    ENSURE_SUCCESS(result, "Could not allocate device memory");

    result = cuMemFree(deviceptr);
    ENSURE_SUCCESS(result, "Could not free device memory");
  }

  virtual ~CudaSession() {}
};


//------------------------------------------------------------------------------
// TokenizerServiceImpl

class TokenizerServiceImpl final : public tokenizer::Tokenizer::Service {
  grpc::Status SendTokens(grpc::ServerContext* context,
                          const ::tokenizer::TokenRequest* request,
                          ::tokenizer::TokenRequestReply* response) {
    std::cerr << "Hi from SendTokens()" << std::endl;

    for (int i = 0; i < request->tokens_size(); i++) {
      std::cerr << request->tokens(i) << std::endl;
    }

    return grpc::Status::OK;
  }

  CudaSession* session;

 public:
  void initCuda() {
    // Stub to just make sure a CUDA device is setup.
    session = new CudaSession();
    session->allocateStubMemory();
  }

  virtual ~TokenizerServiceImpl() {
    if (session) {
      delete session;
    }
  }
};

int main(int argc, char** argv) {
  std::string server_address = "0.0.0.0:50051";

  TokenizerServiceImpl service;
  service.initCuda();

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  grpc::ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
  return 0;
}