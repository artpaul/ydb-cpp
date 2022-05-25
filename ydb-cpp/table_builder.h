#pragma once

#include <ydb-api-protos/protos/ydb_table.pb.h>

#include <string>
#include <vector>

namespace ydbcpp {

class TableBuilder {
 public:
  TableBuilder& AddNullableColumn(std::string name,
      Ydb::Type::PrimitiveTypeId type,
      std::string family = std::string());

  TableBuilder& SetPrimaryKeyColumns(
      std::vector<std::string> primary_key_columns);

  TableBuilder& SetPrimaryKeyColumn(std::string primary_key_column);

  Ydb::Table::CreateTableRequest Build() const;

  // TTableBuilder& SetStorageSettings(const TStorageSettings& settings);
  // TTableBuilder& SetUniformPartitions(ui64 partitionsCount);
  // TTableBuilder& SetPartitioningSettings(const TPartitioningSettings&
  // settings);
 private:
  std::vector<Ydb::Table::ColumnMeta> columns_;
  std::vector<std::string> primary_key_;
};

} // namespace ydbcpp
