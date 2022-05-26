#include <ydb-cpp/session.h>

namespace ydbcpp {

Session::Session(TableClient client)
    : client_(std::move(client)) {
}

std::string Session::SessionId() const {
  return session_id_;
}

Ydb::Operations::Operation Session::Create() {
  Ydb::Table::CreateSessionRequest req;
  // Synchronous request.
  req.mutable_operation_params()->set_operation_mode(
      Ydb::Operations::OperationParams::SYNC);
  auto ret = client_.CreateSession(req).get();
  if (ret.operation().status() == Ydb::StatusIds::SUCCESS) {
    Ydb::Table::CreateSessionResult result;
    if (ret.operation().result().UnpackTo(&result)) {
      session_id_ = result.session_id();
    }
  }
  return ret.operation();
}

Status Session::DropTable(const std::string path) {
  Ydb::Table::DropTableRequest req;
  // Synchronous request.
  req.mutable_operation_params()->set_operation_mode(
      Ydb::Operations::OperationParams::SYNC);
  req.set_session_id(session_id_);
  req.set_path(std::move(path));

  const auto result = client_.DropTable(req).get();

  return Status(result.operation().status());
}

Status Session::ExecuteDataQuery(
    std::string query, const TxControl& tx_control) {
  Ydb::Table::ExecuteDataQueryRequest req;

  // Synchronous request.
  req.mutable_operation_params()->set_operation_mode(
      Ydb::Operations::OperationParams::SYNC);
  req.set_session_id(session_id_);
  req.mutable_query()->set_yql_text(std::move(query));

  tx_control.ToProto(req.mutable_tx_control());

  const auto result = client_.ExecuteDataQuery(req).get();

  return Status(result.operation().status());
}

} // namespace ydbcpp
