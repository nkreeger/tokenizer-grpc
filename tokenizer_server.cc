#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include <iostream>

#include "tokenizer.grpc.pb.h"

// class GreeterServiceImpl final : public Greeter::Service {
//   Status SayHello(ServerContext* context, const HelloRequest* request,
//                   HelloReply* reply) override {
//     std::string prefix("Hello ");
//     reply->set_message(prefix + request->name());

//     std::cerr << "Received SayHello request: " << std::endl;
//     std::cerr << request->DebugString() << std::endl;

//     return Status::OK;
//   }

//   Status SayHelloAgain(ServerContext* context, const HelloRequest* request,
//       HelloReply* reply) override {
//     std::string prefix("Hello again: ");
//     reply->set_message(prefix + request->name());
//     return Status::OK;
//   }
// };

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

//------------------------------------------------------------------------------
// TokenizerServiceImpl

class TokenizerServiceImpl final : public tokenizer::Tokenizer::Service {
  Status SendTokens(ServerContext* context,
                    const ::tokenizer::TokenRequest* request,
                    ::tokenizer::TokenRequestReply* response) {
    std::cerr << "Hi from SendTokens()" << std::endl;
    return Status::OK;
  }
};

int main(int argc, char** argv) {
  std::string server_address = "0.0.0.0:50051";

  TokenizerServiceImpl service;
  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
  return 0;
}