#pragma once

#include <ydb-api-protos/protos/ydb_value.pb.h>

#include <chrono>
#include <map>
#include <string>

namespace ydbcpp {

class ParamsBuilder;

class ParamValueBuilder {
 public:
  ParamValueBuilder(ParamsBuilder* params, Ydb::TypedValue* value);

  ParamValueBuilder& String(std::string value);

  ParamValueBuilder& Timestamp(const std::chrono::microseconds value);

  ParamsBuilder& Build();

 private:
  ParamsBuilder* params_;
  Ydb::TypedValue* value_;
};

class ParamsBuilder {
 public:
  ParamValueBuilder AddParam(const std::string& name);

  std::map<std::string, Ydb::TypedValue> Build() const;

 private:
  std::map<std::string, Ydb::TypedValue> values_;
};

Ydb::TypedValue MakeStringValue(std::string data);

Ydb::TypedValue MakeUint8Value(uint8_t data);

Ydb::TypedValue MakeUint16Value(uint16_t data);

Ydb::TypedValue MakeUint32Value(uint32_t data);

Ydb::TypedValue MakeUint64Value(uint64_t data);

} // namespace ydbcpp
