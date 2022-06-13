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

} // namespace ydbcpp
