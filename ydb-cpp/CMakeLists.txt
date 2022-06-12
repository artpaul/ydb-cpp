add_library (ydb-cpp
  "grpc/cms.cc"
  "grpc/discovery.cc"
  "grpc/executor.cc"
  "grpc/operation.cc"
  "grpc/scheme.cc"
  "grpc/table.cc"
  "params.cc"
  "session.cc"
  "status.cc"
  "table_builder.cc"
)

target_link_libraries (ydb-cpp PUBLIC
  ydb-cpp-proto
)
