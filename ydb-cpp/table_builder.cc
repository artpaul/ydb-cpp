#include "table_builder.h"

namespace ydbcpp {

TableBuilder& TableBuilder::AddNullableColumn(
    std::string name, Ydb::Type::PrimitiveTypeId type, std::string family) {
  Ydb::Table::ColumnMeta column;

  column.set_name(std::move(name));
  column.mutable_type()->mutable_optional_type()->mutable_item()->set_type_id(
      type);
  column.set_family(std::move(family));

  columns_.push_back(std::move(column));

  return *this;
}

TableBuilder& TableBuilder::SetPrimaryKeyColumns(
    std::vector<std::string> primary_key_columns) {
  primary_key_ = std::move(primary_key_columns);
  return *this;
}

TableBuilder& TableBuilder::SetPrimaryKeyColumn(
    std::string primary_key_column) {
  primary_key_.clear();
  primary_key_.push_back(std::move(primary_key_column));
  return *this;
}

Ydb::Table::CreateTableRequest TableBuilder::Build() const {
  Ydb::Table::CreateTableRequest result;

  // Columns.
  for (const auto& column : columns_) {
    result.add_columns()->CopyFrom(column);
  }
  // Primary keys.
  for (const auto& key : primary_key_) {
    result.add_primary_key(key);
  }

  return result;
}

} // namespace ydbcpp
