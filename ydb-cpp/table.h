#pragma once

#include <ydb-api-protos/ydb_table_v1.grpc.pb.h>

#include <future>
#include <memory>

namespace ydbcpp {

class ClientExecutor;

class TableClient {
 public:
  TableClient(std::shared_ptr<ClientExecutor> executor);
  ~TableClient();

  /**
   *  Create new session. Implicit session creation is forbidden,
   * so user must create new session before execute any query,
   * otherwise BAD_SESSION status will be returned.
   * Simultaneous execution of requests are forbiden.
   * Sessions are volatile, can be invalidated by server, for example in case
   * of fatal errors. All requests with this session will fail with BAD_SESSION
   * status. So, client must be able to handle BAD_SESSION status.
   * */
  std::future<Ydb::Table::CreateSessionResponse> CreateSession(
      const Ydb::Table::CreateSessionRequest& request);

  /**
   * Ends a session, releasing server resources associated with it.
   */
  std::future<Ydb::Table::DeleteSessionResponse> DeleteSession(
      const Ydb::Table::DeleteSessionRequest& request);

  /**
   * Idle sessions can be kept alive by calling KeepAlive periodically.
   */
  std::future<Ydb::Table::KeepAliveResponse> KeepAlive(
      const Ydb::Table::KeepAliveRequest& request);

  /**
   * Creates new table.
   */
  std::future<Ydb::Table::CreateTableResponse> CreateTable(
      const Ydb::Table::CreateTableRequest& request);

  /**
   * Drop table.
   */
  std::future<Ydb::Table::DropTableResponse> DropTable(
      const Ydb::Table::DropTableRequest& request);

  /**
   * Modifies schema of given table.
   */
  std::future<Ydb::Table::AlterTableResponse> AlterTable(
      const Ydb::Table::AlterTableRequest& request);

  /**
   * Creates copy of given table.
   */
  std::future<Ydb::Table::CopyTableResponse> CopyTable(
      const Ydb::Table::CopyTableRequest& request);

  /**
   * Creates consistent copy of given tables.
   */
  std::future<Ydb::Table::CopyTablesResponse> CopyTables(
      const Ydb::Table::CopyTablesRequest& request);

  /**
   * Creates consistent move of given tables.
   */
  std::future<Ydb::Table::RenameTablesResponse> RenameTables(
      const Ydb::Table::RenameTablesRequest& request);

  /**
   * Returns information about given table (metadata).
   */
  std::future<Ydb::Table::DescribeTableResponse> DescribeTable(
      const Ydb::Table::DescribeTableRequest& request);

  /**
   * Explains data query.
   * SessionId of previously created session must be provided.
   */
  std::future<Ydb::Table::ExplainDataQueryResponse> ExplainDataQuery(
      const Ydb::Table::ExplainDataQueryRequest& request);

  /**
   * Prepares data query, returns query id.
   * SessionId of previously created session must be provided.
   */
  std::future<Ydb::Table::PrepareDataQueryResponse> PrepareDataQuery(
      const Ydb::Table::PrepareDataQueryRequest& request);

  /**
   * Executes data query.
   * SessionId of previously created session must be provided.
   */
  std::future<Ydb::Table::ExecuteDataQueryResponse> ExecuteDataQuery(
      const Ydb::Table::ExecuteDataQueryRequest& request);

  /**
   * Executes scheme query.
   * SessionId of previously created session must be provided.
   */
  std::future<Ydb::Table::ExecuteSchemeQueryResponse> ExecuteSchemeQuery(
      const Ydb::Table::ExecuteSchemeQueryRequest& request);

  /**
   * Begins new transaction.
   */
  std::future<Ydb::Table::BeginTransactionResponse> BeginTransaction(
      const Ydb::Table::BeginTransactionRequest& request);

  /**
   * Commits specified active transaction.
   */
  std::future<Ydb::Table::CommitTransactionResponse> CommitTransaction(
      const Ydb::Table::CommitTransactionRequest& request);

  /**
   * Performs a rollback of the specified active transaction.
   */
  std::future<Ydb::Table::RollbackTransactionResponse> RollbackTransaction(
      const Ydb::Table::RollbackTransactionRequest& request);

  /**
   * Describe supported table options.
   */
  std::future<Ydb::Table::DescribeTableOptionsResponse> DescribeTableOptions(
      const Ydb::Table::DescribeTableOptionsRequest& request);

  /**
   * Upserts a batch of rows non-transactionally.
   * Returns success only when all rows were successfully upserted. In case of
   * an error some rows might be upserted and some might not.
   */
  std::future<Ydb::Table::BulkUpsertResponse> BulkUpsert(
      const Ydb::Table::BulkUpsertRequest& request);

 private:
  struct State {
    std::shared_ptr<ClientExecutor> executor;
    std::unique_ptr<Ydb::Table::V1::TableService::Stub> stub;

    State(std::shared_ptr<ClientExecutor> e,
        std::unique_ptr<Ydb::Table::V1::TableService::Stub> s)
        : executor(std::move(e))
        , stub(std::move(s)) {
    }
  };

  std::shared_ptr<State> state_;
};

} // namespace ydbcpp
