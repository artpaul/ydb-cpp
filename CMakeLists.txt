
cmake_minimum_required (VERSION 3.15)

project (ydb-cpp)
    list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
    include (add_subdirectories)

    # Setup C++ standard.
    set (CMAKE_CXX_STANDARD 17)
    set (CMAKE_CXX_STANDARD_REQUIRED ON)
    set (CMAKE_CXX_EXTENSIONS OFF)

    if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
        set (CMAKE_BUILD_TYPE "Debug")
    endif ()

    # Setup gRpc.
    set (RE2_BUILD_TESTING OFF CACHE BOOL "" FORCE)
    set (gRPC_BUILD_CSHARP_EXT OFF CACHE BOOL "" FORCE)
    set (gRPC_BUILD_GRPC_CSHARP_PLUGIN OFF CACHE BOOL "" FORCE)
    set (gRPC_BUILD_GRPC_NODE_PLUGIN OFF CACHE BOOL "" FORCE)
    set (gRPC_BUILD_GRPC_OBJECTIVE_C_PLUGIN OFF CACHE BOOL "" FORCE)
    set (gRPC_BUILD_GRPC_PHP_PLUGIN OFF CACHE BOOL "" FORCE)
    set (gRPC_BUILD_GRPC_PYTHON_PLUGIN OFF CACHE BOOL "" FORCE)
    set (gRPC_BUILD_GRPC_RUBY_PLUGIN OFF CACHE BOOL "" FORCE)
    set (protobuf_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set (protobuf_DEBUG_POSTFIX "")

    set (_PROTOBUF_LIBPROTOBUF libprotobuf)
    set (_REFLECTION grpc++_reflection)
    set (_PROTOBUF_PROTOC $<TARGET_FILE:protoc>)
    set (_GRPC_GRPCPP grpc++)
    set (_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:grpc_cpp_plugin>)

    # Dependencies.
    add_subdirectories (
        contrib/grpc
    )
