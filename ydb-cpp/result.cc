#include "result.h"

namespace ydbcpp {

DataResult::DataResult(Ydb::ResultSet data)
    : data_(std::move(data)) {
  for (size_t i = 0; i < data_.columns_size(); ++i) {
    columns_.emplace(data_.columns(i).name(), i);
  }
}

/// List of column descriptions.
std::vector<DataResult::Column> DataResult::Columns() const {
  std::vector<Column> columns;
  for (size_t i = 0; i < data_.columns_size(); ++i) {
    columns.emplace_back(data_.columns(i).name(), &data_.columns(i).type());
  }
  return columns;
}

size_t DataResult::ColumnsCount() const {
  return data_.columns_size();
}

size_t DataResult::RowsCount() const {
  return data_.rows_size();
}

bool DataResult::Truncated() const {
  return data_.truncated();
}

DataResult::Row DataResult::operator[](size_t idx) const {
  if (idx < data_.rows_size()) {
    return Row(this, idx);
  }
  throw std::out_of_range(std::to_string(idx));
}

DataResult::Iterator DataResult::begin() const {
  return Iterator(this, 0);
}

DataResult::Iterator DataResult::end() const {
  return Iterator(this, data_.rows_size());
}

} // namespace ydbcpp
