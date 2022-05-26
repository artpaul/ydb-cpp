add_library (ydb-cpp
  "cms.cc"
  "discovery.cc"
  "executor.cc"
  "operation.cc"
  "scheme.cc"
  "session.cc"
  "status.cc"
  "table.cc"
  "table_builder.cc"
)

target_link_libraries (ydb-cpp PUBLIC
  ydb-cpp-proto
)
