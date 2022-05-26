#pragma once

#include <ydb-api-protos/protos/ydb_status_codes.pb.h>

namespace ydbcpp {

class Status {
 public:
  Status(Ydb::StatusIds::StatusCode status_code);

  Ydb::StatusIds::StatusCode GetStatus() const;

  bool IsSuccess() const;

  bool IsTransportError() const;

 private:
  Ydb::StatusIds::StatusCode status_code_;
};

} // namespace ydbcpp
