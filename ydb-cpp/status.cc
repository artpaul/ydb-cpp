#include "status.h"

namespace ydbcpp {

static constexpr size_t TRANSPORT_STATUSES_FIRST = 401000;
static constexpr size_t TRANSPORT_STATUSES_LAST = 401999;

Status::Status(Ydb::StatusIds::StatusCode status_code)
    : status_code_(status_code) {
}

Ydb::StatusIds::StatusCode Status::GetStatus() const {
  return status_code_;
}

bool Status::IsSuccess() const {
  return status_code_ == Ydb::StatusIds::SUCCESS;
}

bool Status::IsTransportError() const {
  return static_cast<size_t>(status_code_) >= TRANSPORT_STATUSES_FIRST &&
         static_cast<size_t>(status_code_) <= TRANSPORT_STATUSES_LAST;
}

} // namespace ydbcpp
