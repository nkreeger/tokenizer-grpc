cmake_minimum_required(VERSION 3.30)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(TokenizerServer C CXX)

# Stock setup
find_program(_PROTOBUF_PROTOC protoc)
find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)

option(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")

find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

get_filename_component(tokenizer_proto "tokenizer.proto" ABSOLUTE)
get_filename_component(tokenizer_proto_path "${tokenizer_proto}" PATH)

# Generated sources
set(tokenizer_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/tokenizer.pb.cc")
set(tokenizer_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/tokenizer.pb.h")
set(tokenizer_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/tokenizer.grpc.pb.cc")
set(tokenizer_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/tokenizer.grpc.pb.h")

add_custom_command(
    OUTPUT "${tokenizer_proto_srcs}" "${tokenizer_proto_hdrs}" "${tokenizer_grpc_srcs}" "${tokenizer_grpc_hdrs}"
    COMMAND ${_PROTOBUF_PROTOC}
    ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
    --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
    -I "${tokenizer_proto_path}"
    --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
    "${tokenizer_proto}"
    DEPENDS "${tokenizer_proto}"
)

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_library(tokenizer_grpc_proto
    ${tokenizer_grpc_srcs}
    ${tokenizer_grpc_hdrs}
    ${tokenizer_proto_srcs}
    ${tokenizer_proto_hdrs}
)
target_link_libraries(tokenizer_grpc_proto
    protobuf::libprotobuf
)

add_executable(tokenizer_server tokenizer_server.cc)
target_link_libraries(tokenizer_server
    tokenizer_grpc_proto
    gRPC::grpc++
    gRPC::grpc++_reflection
    protobuf::libprotobuf
)

