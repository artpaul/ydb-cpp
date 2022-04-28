#include <ydb-cpp/executor.h>
#include <ydb-cpp/method.h>
#include <ydb-cpp/table.h>

namespace ydbcpp {

TableClient::TableClient(std::shared_ptr<ClientExecutor> executor)
    : executor_(std::move(executor))
    , stub_(Ydb::Table::V1::TableService::NewStub(executor_->GetChannel())) {
}

TableClient::~TableClient() = default;

std::future<Ydb::Table::CreateSessionResponse> TableClient::CreateSession(
    const Ydb::Table::CreateSessionRequest& request) {
  return SimpleClientMethod<Ydb::Table::CreateSessionResponse>::Call(
      &Ydb::Table::V1::TableService::Stub::AsyncCreateSession, stub_.get(),
      request, executor_->GetQueue());
}

std::future<Ydb::Table::DeleteSessionResponse> TableClient::DeleteSession(
    const Ydb::Table::DeleteSessionRequest& request) {
  return SimpleClientMethod<Ydb::Table::DeleteSessionResponse>::Call(
      &Ydb::Table::V1::TableService::Stub::AsyncDeleteSession, stub_.get(),
      request, executor_->GetQueue());
}

std::future<Ydb::Table::KeepAliveResponse> TableClient::KeepAlive(
    const Ydb::Table::KeepAliveRequest& request) {
  return SimpleClientMethod<Ydb::Table::KeepAliveResponse>::Call(
      &Ydb::Table::V1::TableService::Stub::AsyncKeepAlive, stub_.get(), request,
      executor_->GetQueue());
}

std::future<Ydb::Table::CreateTableResponse> TableClient::CreateTable(
    const Ydb::Table::CreateTableRequest& request) {
  return SimpleClientMethod<Ydb::Table::CreateTableResponse>::Call(
      &Ydb::Table::V1::TableService::Stub::AsyncCreateTable, stub_.get(),
      request, executor_->GetQueue());
}

std::future<Ydb::Table::DropTableResponse> TableClient::DropTable(
    const Ydb::Table::DropTableRequest& request) {
  return SimpleClientMethod<Ydb::Table::DropTableResponse>::Call(
      &Ydb::Table::V1::TableService::Stub::AsyncDropTable, stub_.get(), request,
      executor_->GetQueue());
}

std::future<Ydb::Table::AlterTableResponse> TableClient::AlterTable(
    const Ydb::Table::AlterTableRequest& request) {
  return SimpleClientMethod<Ydb::Table::AlterTableResponse>::Call(
      &Ydb::Table::V1::TableService::Stub::AsyncAlterTable, stub_.get(),
      request, executor_->GetQueue());
}

std::future<Ydb::Table::CopyTableResponse> TableClient::CopyTable(
    const Ydb::Table::CopyTableRequest& request) {
  return SimpleClientMethod<Ydb::Table::CopyTableResponse>::Call(
      &Ydb::Table::V1::TableService::Stub::AsyncCopyTable, stub_.get(), request,
      executor_->GetQueue());
}

std::future<Ydb::Table::CopyTablesResponse> TableClient::CopyTables(
    const Ydb::Table::CopyTablesRequest& request) {
  return SimpleClientMethod<Ydb::Table::CopyTablesResponse>::Call(
      &Ydb::Table::V1::TableService::Stub::AsyncCopyTables, stub_.get(),
      request, executor_->GetQueue());
}

std::future<Ydb::Table::RenameTablesResponse> TableClient::RenameTables(
    const Ydb::Table::RenameTablesRequest& request) {
  return SimpleClientMethod<Ydb::Table::RenameTablesResponse>::Call(
      &Ydb::Table::V1::TableService::Stub::AsyncRenameTables, stub_.get(),
      request, executor_->GetQueue());
}

std::future<Ydb::Table::DescribeTableResponse> TableClient::DescribeTable(
    const Ydb::Table::DescribeTableRequest& request) {
  return SimpleClientMethod<Ydb::Table::DescribeTableResponse>::Call(
      &Ydb::Table::V1::TableService::Stub::AsyncDescribeTable, stub_.get(),
      request, executor_->GetQueue());
}

std::future<Ydb::Table::ExplainDataQueryResponse> TableClient::ExplainDataQuery(
    const Ydb::Table::ExplainDataQueryRequest& request) {
  return SimpleClientMethod<Ydb::Table::ExplainDataQueryResponse>::Call(
      &Ydb::Table::V1::TableService::Stub::AsyncExplainDataQuery, stub_.get(),
      request, executor_->GetQueue());
}

std::future<Ydb::Table::PrepareDataQueryResponse> TableClient::PrepareDataQuery(
    const Ydb::Table::PrepareDataQueryRequest& request) {
  return SimpleClientMethod<Ydb::Table::PrepareDataQueryResponse>::Call(
      &Ydb::Table::V1::TableService::Stub::AsyncPrepareDataQuery, stub_.get(),
      request, executor_->GetQueue());
}

std::future<Ydb::Table::ExecuteDataQueryResponse> TableClient::ExecuteDataQuery(
    const Ydb::Table::ExecuteDataQueryRequest& request) {
  return SimpleClientMethod<Ydb::Table::ExecuteDataQueryResponse>::Call(
      &Ydb::Table::V1::TableService::Stub::AsyncExecuteDataQuery, stub_.get(),
      request, executor_->GetQueue());
}

std::future<Ydb::Table::ExecuteSchemeQueryResponse>
TableClient::ExecuteSchemeQuery(
    const Ydb::Table::ExecuteSchemeQueryRequest& request) {
  return SimpleClientMethod<Ydb::Table::ExecuteSchemeQueryResponse>::Call(
      &Ydb::Table::V1::TableService::Stub::AsyncExecuteSchemeQuery, stub_.get(),
      request, executor_->GetQueue());
}

std::future<Ydb::Table::BeginTransactionResponse> TableClient::BeginTransaction(
    const Ydb::Table::BeginTransactionRequest& request) {
  return SimpleClientMethod<Ydb::Table::BeginTransactionResponse>::Call(
      &Ydb::Table::V1::TableService::Stub::AsyncBeginTransaction, stub_.get(),
      request, executor_->GetQueue());
}

std::future<Ydb::Table::CommitTransactionResponse>
TableClient::CommitTransaction(
    const Ydb::Table::CommitTransactionRequest& request) {
  return SimpleClientMethod<Ydb::Table::CommitTransactionResponse>::Call(
      &Ydb::Table::V1::TableService::Stub::AsyncCommitTransaction, stub_.get(),
      request, executor_->GetQueue());
}

std::future<Ydb::Table::RollbackTransactionResponse>
TableClient::RollbackTransaction(
    const Ydb::Table::RollbackTransactionRequest& request) {
  return SimpleClientMethod<Ydb::Table::RollbackTransactionResponse>::Call(
      &Ydb::Table::V1::TableService::Stub::AsyncRollbackTransaction,
      stub_.get(), request, executor_->GetQueue());
}

std::future<Ydb::Table::DescribeTableOptionsResponse>
TableClient::DescribeTableOptions(
    const Ydb::Table::DescribeTableOptionsRequest& request) {
  return SimpleClientMethod<Ydb::Table::DescribeTableOptionsResponse>::Call(
      &Ydb::Table::V1::TableService::Stub::AsyncDescribeTableOptions,
      stub_.get(), request, executor_->GetQueue());
}

std::future<Ydb::Table::BulkUpsertResponse> TableClient::BulkUpsert(
    const Ydb::Table::BulkUpsertRequest& request) {
  return SimpleClientMethod<Ydb::Table::BulkUpsertResponse>::Call(
      &Ydb::Table::V1::TableService::Stub::AsyncBulkUpsert, stub_.get(),
      request, executor_->GetQueue());
}

} // namespace ydbcpp
