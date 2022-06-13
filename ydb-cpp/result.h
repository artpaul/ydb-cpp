#pragma once

#include <ydb-api-protos/protos/ydb_value.pb.h>

#include <unordered_map>
#include <vector>

namespace ydbcpp {

class DataValue {
 public:
  DataValue(const Ydb::Value* value, const Ydb::Type* type)
      : value_(value)
      , type_(type) {
  }

  const Ydb::Value& Value() const {
    return *value_;
  }

  const Ydb::Type& Type() const {
    return *type_;
  }

 private:
  const Ydb::Value* value_;
  const Ydb::Type* type_;
};

class DataResult {
 public:
  class Column {
   public:
    Column(const std::string& name, const Ydb::Type* type)
        : name_(name)
        , type_(type) {
    }

    const std::string& Name() const {
      return name_;
    }

    const Ydb::Type& Type() const {
      return *type_;
    }

   private:
    std::string name_;
    const Ydb::Type* type_;
  };

  ///
  class Row {
   public:
    Row(const DataResult* data, size_t idx)
        : data_(data)
        , idx_(idx) {
    }

    DataValue operator[](const std::string& name) const {
      if (auto ci = data_->columns_.find(name); ci != data_->columns_.end()) {
        return DataValue(&data_->data_.rows(idx_).items(ci->second),
            &data_->data_.columns(ci->second).type());
      }
      throw std::out_of_range(name);
    }

   private:
    const DataResult* data_;
    size_t idx_;
  };

  class Iterator {
   public:
    Iterator(const DataResult* data, size_t idx)
        : data_(data)
        , idx_(idx) {
    }

    bool operator==(const Iterator& other) const {
      return data_ == other.data_ && idx_ == other.idx_;
    }

    bool operator!=(const Iterator& other) const {
      return !this->operator==(other);
    }

    Iterator& operator++() {
      ++idx_;
      return *this;
    }

    Row operator*() const {
      return Row(data_, idx_);
    }

   private:
    const DataResult* data_;
    size_t idx_;
  };

 public:
  explicit DataResult(Ydb::ResultSet data);

  /// List of column descriptions.
  std::vector<Column> Columns() const;

  size_t ColumnsCount() const;

  size_t RowsCount() const;

  bool Truncated() const;

  Row operator[](size_t idx) const;

  Iterator begin() const;

  Iterator end() const;

 private:
  Ydb::ResultSet data_;
  std::unordered_map<std::string, size_t> columns_;
};

} // namespace ydbcpp
