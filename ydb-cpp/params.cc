#include "params.h"

namespace ydbcpp {

ParamValueBuilder::ParamValueBuilder(
    ParamsBuilder* params, Ydb::TypedValue* value)
    : params_(params)
    , value_(value) {
}

ParamValueBuilder& ParamValueBuilder::String(std::string value) {
  value_->mutable_type()->set_type_id(Ydb::Type::STRING);
  value_->mutable_value()->set_bytes_value(std::move(value));
  return *this;
}

ParamValueBuilder& ParamValueBuilder::Timestamp(
    const std::chrono::microseconds value) {
  value_->mutable_type()->set_type_id(Ydb::Type::TIMESTAMP);
  value_->mutable_value()->set_uint64_value(value.count());
  return *this;
}

ParamsBuilder& ParamValueBuilder::Build() {
  return *params_;
}

ParamValueBuilder ParamsBuilder::AddParam(const std::string& name) {
  return ParamValueBuilder(this, &values_[name]);
}

std::map<std::string, Ydb::TypedValue> ParamsBuilder::Build() const {
  return values_;
}

Ydb::TypedValue MakeStringValue(std::string data) {
  Ydb::TypedValue value;
  value.mutable_type()->set_type_id(Ydb::Type::STRING);
  value.mutable_value()->set_bytes_value(std::move(data));
  return value;
}

Ydb::TypedValue MakeUint8Value(uint8_t data) {
  Ydb::TypedValue value;
  value.mutable_type()->set_type_id(Ydb::Type::UINT8);
  value.mutable_value()->set_uint32_value(data);
  return value;
};

Ydb::TypedValue MakeUint16Value(uint16_t data) {
  Ydb::TypedValue value;
  value.mutable_type()->set_type_id(Ydb::Type::UINT16);
  value.mutable_value()->set_uint32_value(data);
  return value;
};

Ydb::TypedValue MakeUint32Value(uint32_t data) {
  Ydb::TypedValue value;
  value.mutable_type()->set_type_id(Ydb::Type::UINT32);
  value.mutable_value()->set_uint32_value(data);
  return value;
};

Ydb::TypedValue MakeUint64Value(uint64_t data) {
  Ydb::TypedValue value;
  value.mutable_type()->set_type_id(Ydb::Type::UINT64);
  value.mutable_value()->set_uint64_value(data);
  return value;
};

} // namespace ydbcpp
