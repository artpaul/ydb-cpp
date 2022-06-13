#include "session.h"

namespace ydbcpp {

Session::Session(TableClient client)
    : client_(std::move(client)) {
}

std::string Session::SessionId() const {
  return session_id_;
}

Status Session::Create() {
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
  return Status(ret.operation().status());
}

std::pair<Status, std::string> Session::BeginTransaction(
    const TxSettings& tx_settings) {
  Ydb::Table::BeginTransactionRequest req;
  // Synchronous request.
  req.mutable_operation_params()->set_operation_mode(
      Ydb::Operations::OperationParams::SYNC);
  req.set_session_id(session_id_);
  //
  switch (tx_settings.Mode()) {
    case TransactionMode::OnlineReadOnly:
      req.mutable_tx_settings()->mutable_online_read_only();
      break;
    case TransactionMode::SerializableReadWrite:
      req.mutable_tx_settings()->mutable_serializable_read_write();
      break;
    case TransactionMode::StaleReadOnly:
      req.mutable_tx_settings()->mutable_stale_read_only();
      break;
  }

  const auto ret = client_.BeginTransaction(req).get();

  if (ret.operation().status() == Ydb::StatusIds::SUCCESS) {
    Ydb::Table::BeginTransactionResult result;
    if (ret.operation().result().UnpackTo(&result)) {
      return std::make_pair(
          Status(ret.operation().status()), result.tx_meta().id());
    }
  }

  return std::make_pair(Status(ret.operation().status()), std::string());
}

Status Session::CommitTransaction(std::string tx_id) {
  Ydb::Table::CommitTransactionRequest req;
  // Synchronous request.
  req.mutable_operation_params()->set_operation_mode(
      Ydb::Operations::OperationParams::SYNC);
  req.set_session_id(session_id_);
  req.set_tx_id(std::move(tx_id));

  const auto ret = client_.CommitTransaction(req).get();

  return Status(ret.operation().status());
}

Status Session::RollbackTransaction(std::string tx_id) {
  Ydb::Table::RollbackTransactionRequest req;
  // Synchronous request.
  req.mutable_operation_params()->set_operation_mode(
      Ydb::Operations::OperationParams::SYNC);
  req.set_session_id(session_id_);
  req.set_tx_id(std::move(tx_id));

  const auto ret = client_.RollbackTransaction(req).get();

  return Status(ret.operation().status());
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

std::pair<Status, Ydb::Table::ExecuteQueryResult> Session::ExecuteDataQuery(
    std::string query, const TxControl& tx_control) {
  return ExecuteDataQuery(
      std::move(query), tx_control, std::map<std::string, Ydb::TypedValue>());
}

std::pair<Status, Ydb::Table::ExecuteQueryResult> Session::ExecuteDataQuery(
    std::string query,
    const TxControl& tx_control,
    const std::map<std::string, Ydb::TypedValue>& params) {
  Ydb::Table::ExecuteDataQueryRequest req;

  // Synchronous request.
  req.mutable_operation_params()->set_operation_mode(
      Ydb::Operations::OperationParams::SYNC);
  req.set_session_id(session_id_);
  req.mutable_query()->set_yql_text(std::move(query));
  // Params.
  for (const auto& [name, value] : params) {
    (*req.mutable_parameters())[name] = value;
  }
  // Transaction.
  tx_control.ToProto(req.mutable_tx_control());

  const auto ret = client_.ExecuteDataQuery(req).get();

  if (ret.operation().status() == Ydb::StatusIds::SUCCESS) {
    Ydb::Table::ExecuteQueryResult result;

    if (ret.operation().result().UnpackTo(&result)) {
      return std::make_pair(
          Status(ret.operation().status()), std::move(result));
    } else {
      assert(false);
    }
  }

  return std::make_pair(
      Status(ret.operation().status()), Ydb::Table::ExecuteQueryResult());
}

} // namespace ydbcpp
