#include "scheme.h"

#include "executor.h"
#include "method.h"

namespace ydbcpp {

SchemeClient::SchemeClient(std::shared_ptr<ClientExecutor> executor)
    : executor_(std::move(executor))
    , stub_(Ydb::Scheme::V1::SchemeService::NewStub(executor_->GetChannel())) {
}

SchemeClient::~SchemeClient() = default;

std::future<Ydb::Scheme::DescribePathResponse> SchemeClient::DescribePath(
    const Ydb::Scheme::DescribePathRequest& request) {
  return SimpleClientMethod<Ydb::Scheme::DescribePathResponse>::Call(
      &Ydb::Scheme::V1::SchemeService::Stub::AsyncDescribePath, stub_.get(),
      request, executor_->GetQueue());
}

std::future<Ydb::Scheme::ListDirectoryResponse> SchemeClient::ListDirectory(
    const Ydb::Scheme::ListDirectoryRequest& request) {
  return SimpleClientMethod<Ydb::Scheme::ListDirectoryResponse>::Call(
      &Ydb::Scheme::V1::SchemeService::Stub::AsyncListDirectory, stub_.get(),
      request, executor_->GetQueue());
}

std::future<Ydb::Scheme::MakeDirectoryResponse> SchemeClient::MakeDirectory(
    const Ydb::Scheme::MakeDirectoryRequest& request) {
  return SimpleClientMethod<Ydb::Scheme::MakeDirectoryResponse>::Call(
      &Ydb::Scheme::V1::SchemeService::Stub::AsyncMakeDirectory, stub_.get(),
      request, executor_->GetQueue());
}

std::future<Ydb::Scheme::ModifyPermissionsResponse>
SchemeClient::ModifyPermissions(
    const Ydb::Scheme::ModifyPermissionsRequest& request) {
  return SimpleClientMethod<Ydb::Scheme::ModifyPermissionsResponse>::Call(
      &Ydb::Scheme::V1::SchemeService::Stub::AsyncModifyPermissions,
      stub_.get(), request, executor_->GetQueue());
}

std::future<Ydb::Scheme::RemoveDirectoryResponse> SchemeClient::RemoveDirectory(
    const Ydb::Scheme::RemoveDirectoryRequest& request) {
  return SimpleClientMethod<Ydb::Scheme::RemoveDirectoryResponse>::Call(
      &Ydb::Scheme::V1::SchemeService::Stub::AsyncRemoveDirectory, stub_.get(),
      request, executor_->GetQueue());
}

} // namespace ydbcpp
