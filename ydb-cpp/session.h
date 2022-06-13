#pragma once

#include <ydb-api-protos/protos/ydb_operation.pb.h>

#include <map>
#include <optional>

#include "grpc/table.h"
#include "status.h"

namespace ydbcpp {

enum class TransactionMode {
  OnlineReadOnly,
  SerializableReadWrite,
  StaleReadOnly,
};

class TxSettings {
  friend class TxControl;

 public:
  TxSettings() noexcept
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

  TransactionMode Mode() const noexcept {
    return mode_;
  }

 private:
  TxSettings(const TransactionMode mode) noexcept
      : mode_(mode) {
  }

  TransactionMode mode_;
};

class TxControl {
 public:
  static TxControl BeginTx(const TxSettings& settings = TxSettings()) {
    return TxControl(settings);
  }

  static TxControl Tx(std::string tx_id) {
    return TxControl(std::move(tx_id));
  }

 public:
  TxControl& CommitTx(bool value = true) {
    commit_tx_ = value;
    return *this;
  }

  void ToProto(Ydb::Table::TransactionControl* proto) const {
    proto->set_commit_tx(commit_tx_);

    if (tx_id_) {
      proto->set_tx_id(*tx_id_);
    } else {
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
  }

 private:
  explicit TxControl(std::string tx_id)
      : tx_id_(std::move(tx_id)) {
  }

  explicit TxControl(const TxSettings& settings)
      : settings_(settings) {
  }

  TxSettings settings_;
  std::optional<std::string> tx_id_;
  bool commit_tx_{false};
};

class Session {
 public:
  Session(TableClient client);

  std::string SessionId() const;

  Status Create();

 public:
  std::pair<Status, std::string> BeginTransaction(
      const TxSettings& tx_settings);

  Status CommitTransaction(std::string tx_id);

  Status RollbackTransaction(std::string tx_id);

  /** Create new table. */
  Status CreateTable(const std::string path /*desc, settings*/);

  /** Deletes a table. */
  Status DropTable(const std::string path);

  std::pair<Status, Ydb::Table::ExecuteQueryResult> ExecuteDataQuery(
      std::string query, const TxControl& tx_control);

  std::pair<Status, Ydb::Table::ExecuteQueryResult> ExecuteDataQuery(
      std::string query,
      const TxControl& tx_control,
      const std::map<std::string, Ydb::TypedValue>& params);

  // Status
  // - AlterTable
  // - CopyTable
  // - CopyTables
  // - RenameTables
  // - ExecuteSchemeQuery
  // - Close (close session)

 public:
  TableClient client_;
  std::string session_id_;
};

} // namespace ydbcpp
