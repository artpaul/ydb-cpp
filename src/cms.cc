#include <ydb-cpp/cms.h>
#include <ydb-cpp/executor.h>
#include <ydb-cpp/method.h>

namespace ydbcpp {

CmsClient::CmsClient(std::shared_ptr<ClientExecutor> executor)
    : executor_(std::move(executor))
    , stub_(Ydb::Cms::V1::CmsService::NewStub(executor_->GetChannel())) {
}

CmsClient::~CmsClient() = default;

std::future<Ydb::Cms::CreateDatabaseResponse> CmsClient::CreateDatabase(
    const Ydb::Cms::CreateDatabaseRequest& request) {
  return SimpleClientMethod<Ydb::Cms::CreateDatabaseResponse>::Call(
      &Ydb::Cms::V1::CmsService::Stub::AsyncCreateDatabase, stub_.get(),
      request, executor_->GetQueue());
}

std::future<Ydb::Cms::GetDatabaseStatusResponse> CmsClient::GetDatabaseStatus(
    const Ydb::Cms::GetDatabaseStatusRequest& request) {
  return SimpleClientMethod<Ydb::Cms::GetDatabaseStatusResponse>::Call(
      &Ydb::Cms::V1::CmsService::Stub::AsyncGetDatabaseStatus, stub_.get(),
      request, executor_->GetQueue());
}

std::future<Ydb::Cms::AlterDatabaseResponse> CmsClient::AlterDatabase(
    const Ydb::Cms::AlterDatabaseRequest& request) {
  return SimpleClientMethod<Ydb::Cms::AlterDatabaseResponse>::Call(
      &Ydb::Cms::V1::CmsService::Stub::AsyncAlterDatabase, stub_.get(), request,
      executor_->GetQueue());
}

std::future<Ydb::Cms::ListDatabasesResponse> CmsClient::ListDatabases(
    const Ydb::Cms::ListDatabasesRequest& request) {
  return SimpleClientMethod<Ydb::Cms::ListDatabasesResponse>::Call(
      &Ydb::Cms::V1::CmsService::Stub::AsyncListDatabases, stub_.get(), request,
      executor_->GetQueue());
}

std::future<Ydb::Cms::RemoveDatabaseResponse> CmsClient::RemoveDatabase(
    const Ydb::Cms::RemoveDatabaseRequest& request) {
  return SimpleClientMethod<Ydb::Cms::RemoveDatabaseResponse>::Call(
      &Ydb::Cms::V1::CmsService::Stub::AsyncRemoveDatabase, stub_.get(),
      request, executor_->GetQueue());
}

std::future<Ydb::Cms::DescribeDatabaseOptionsResponse>
CmsClient::DescribeDatabaseOptions(
    const Ydb::Cms::DescribeDatabaseOptionsRequest& request) {
  return SimpleClientMethod<Ydb::Cms::DescribeDatabaseOptionsResponse>::Call(
      &Ydb::Cms::V1::CmsService::Stub::AsyncDescribeDatabaseOptions,
      stub_.get(), request, executor_->GetQueue());
}

} // namespace ydbcpp
