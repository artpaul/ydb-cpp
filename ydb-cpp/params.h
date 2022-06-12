#pragma once

#include <ydb-api-protos/protos/ydb_value.pb.h>

#include <map>
#include <string>

namespace ydbcpp {

class ParamsBuilder;

class ParamValueBuilder {
 public:
  ParamValueBuilder(ParamsBuilder* params, Ydb::TypedValue* value);

  ParamValueBuilder& String(std::string value);

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

} // namespace ydbcpp
