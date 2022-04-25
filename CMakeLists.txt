cmake_minimum_required (VERSION 3.15)

project (ydb-cpp LANGUAGES C CXX)
  list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
  include (add_subdirectories)

  # Setup C++ standard.
  set (CMAKE_CXX_STANDARD 17)
  set (CMAKE_CXX_STANDARD_REQUIRED ON)
  set (CMAKE_CXX_EXTENSIONS OFF)

  if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set (CMAKE_BUILD_TYPE "Debug")
  endif ()

  # Export compile commands.
  set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

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

  # Setup include directories.
  include_directories (
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos"
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/protos"
  )

  function (generate_proto name)
    file (MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/protos")

    add_custom_command (
        OUTPUT
            "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/protos/${name}.pb.cc"
            "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/protos/${name}.pb.h"
        COMMAND
            "${_PROTOBUF_PROTOC}"
        ARGS
            --cpp_out "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/protos"
            -I "${CMAKE_CURRENT_SOURCE_DIR}/contrib/grpc/third_party/protobuf/src"
            -I "${CMAKE_CURRENT_SOURCE_DIR}/contrib/ydb-api-protos/protos"
            --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
            "${CMAKE_CURRENT_SOURCE_DIR}/contrib/ydb-api-protos/protos/${name}.proto"
        DEPENDS
            "${CMAKE_CURRENT_SOURCE_DIR}/contrib/ydb-api-protos/protos/${name}.proto"
    )
  endfunction (generate_proto name)

  function (generate_grpc name)
    file (MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos")

    add_custom_command (
      OUTPUT
        "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/${name}.grpc.pb.cc"
        "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/${name}.grpc.pb.h"
      COMMAND
            "${_PROTOBUF_PROTOC}"
      ARGS
        --grpc_out "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos"
        -I "${CMAKE_CURRENT_SOURCE_DIR}/contrib/grpc/third_party/protobuf/src"
        -I "${CMAKE_CURRENT_SOURCE_DIR}/contrib/ydb-api-protos"
        -I "${CMAKE_CURRENT_SOURCE_DIR}/contrib/ydb-api-protos/protos"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${CMAKE_CURRENT_SOURCE_DIR}/contrib/ydb-api-protos/${name}.proto"
      DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/contrib/ydb-api-protos/${name}.proto"
    )
  endfunction (generate_grpc name)

  # Generate protobufs.
  generate_proto(annotations/validation)
  generate_proto(ydb_cms)
  generate_proto(ydb_common)
  generate_proto(ydb_coordination)
  generate_proto(ydb_discovery)
  generate_proto(ydb_export)
  generate_proto(ydb_formats)
  generate_proto(ydb_import)
  generate_proto(ydb_issue_message)
  generate_proto(ydb_monitoring)
  generate_proto(ydb_operation)
  generate_proto(ydb_query_stats)
  generate_proto(ydb_rate_limiter)
  generate_proto(ydb_scheme)
  generate_proto(ydb_scripting)
  generate_proto(ydb_status_codes)
  generate_proto(ydb_table)
  generate_proto(ydb_value)

  generate_grpc(ydb_cms_v1)
  generate_grpc(ydb_coordination_v1)
  generate_grpc(ydb_discovery_v1)
  generate_grpc(ydb_export_v1)
  generate_grpc(ydb_import_v1)
  generate_grpc(ydb_monitoring_v1)
  generate_grpc(ydb_operation_v1)
  generate_grpc(ydb_rate_limiter_v1)
  generate_grpc(ydb_scheme_v1)
  generate_grpc(ydb_scripting_v1)
  generate_grpc(ydb_table_v1)

  add_library (ydb-cpp-proto
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/protos/annotations/validation.pb.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/protos/ydb_cms.pb.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/protos/ydb_common.pb.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/protos/ydb_coordination.pb.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/protos/ydb_discovery.pb.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/protos/ydb_export.pb.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/protos/ydb_formats.pb.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/protos/ydb_import.pb.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/protos/ydb_issue_message.pb.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/protos/ydb_monitoring.pb.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/protos/ydb_operation.pb.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/protos/ydb_persqueue_cluster_discovery.pb.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/protos/ydb_persqueue_v1.pb.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/protos/ydb_query_stats.pb.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/protos/ydb_rate_limiter.pb.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/protos/ydb_scheme.pb.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/protos/ydb_scripting.pb.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/protos/ydb_status_codes.pb.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/protos/ydb_table.pb.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/protos/ydb_value.pb.cc"

    "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/ydb_cms_v1.grpc.pb.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/ydb_coordination_v1.grpc.pb.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/ydb_discovery_v1.grpc.pb.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/ydb_export_v1.grpc.pb.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/ydb_import_v1.grpc.pb.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/ydb_monitoring_v1.grpc.pb.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/ydb_operation_v1.grpc.pb.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/ydb_rate_limiter_v1.grpc.pb.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/ydb_scheme_v1.grpc.pb.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/ydb_scripting_v1.grpc.pb.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/contrib/ydb-api-protos/ydb_table_v1.grpc.pb.cc"
  )

  target_link_libraries (ydb-cpp-proto PUBLIC
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
  )
