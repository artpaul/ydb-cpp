#pragma once

#include <ydb-api-protos/protos/ydb_operation.pb.h>

#include "table.h"

namespace ydbcpp {

enum class TransactionMode {
  OnlineReadOnly,
  SerializableReadWrite,
  StaleReadOnly,
};

class TxSettings {
  friend class TxControl;

 public:
  TxSettings()
      : mode_(TransactionMode::SerializableReadWrite) {
  }

  static TxSettings SerializableRW() {
    return TxSettings(TransactionMode::SerializableReadWrite);
  }

  static TxSettings OnlineRO() {
    return TxSettings(TransactionMode::OnlineReadOnly);
  }

  static TxSettings StaleRO() {
    return TxSettings(TransactionMode::StaleReadOnly);
  }

 private:
  TxSettings(const TransactionMode mode)
      : mode_(mode) {
  }

  TransactionMode mode_;
};

class TxControl {
 public:
  static TxControl BeginTx(const TxSettings& settings = TxSettings()) {
    return TxControl(settings);
  }

  TxControl& CommitTx(bool value = true) {
    commit_tx_ = value;
    return *this;
  }

  void ToProto(Ydb::Table::TransactionControl* proto) const {
    proto->set_commit_tx(commit_tx_);

    switch (settings_.mode_) {
      case TransactionMode::OnlineReadOnly:
        proto->mutable_begin_tx()->mutable_online_read_only();
        break;
      case TransactionMode::SerializableReadWrite:;
        proto->mutable_begin_tx()->mutable_serializable_read_write();
        break;
      case TransactionMode::StaleReadOnly:;
        proto->mutable_begin_tx()->mutable_stale_read_only();
        break;
    }
  }

 private:
  TxControl(const TxSettings& settings)
      : settings_(settings) {
  }

  TxSettings settings_;
  bool commit_tx_{false};
};

class Session {
 public:
  Session(TableClient client);

  std::string SessionId() const;

  Ydb::Operations::Operation Create();

  Ydb::Operations::Operation ExecuteDataQuery(
      std::string query, const TxControl& tx_control);

 public:
  TableClient client_;
  std::string session_id_;
};

} // namespace ydbcpp
