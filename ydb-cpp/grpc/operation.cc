#include "operation.h"

#include "executor.h"
#include "method.h"

namespace ydbcpp {

OperationClient::OperationClient(std::shared_ptr<ClientExecutor> executor)
    : executor_(std::move(executor))
    , stub_(Ydb::Operation::V1::OperationService::NewStub(
          executor_->GetChannel())) {
}

OperationClient::~OperationClient() = default;

std::future<Ydb::Operations::GetOperationResponse>
OperationClient::GetOperation(
    const Ydb::Operations::GetOperationRequest& request) {
  return SimpleClientMethod<Ydb::Operations::GetOperationResponse>::Call(
      &Ydb::Operation::V1::OperationService::Stub::AsyncGetOperation,
      stub_.get(), request, executor_->GetQueue());
}

std::future<Ydb::Operations::CancelOperationResponse>
OperationClient::CancelOperation(
    const Ydb::Operations::CancelOperationRequest& request) {
  return SimpleClientMethod<Ydb::Operations::CancelOperationResponse>::Call(
      &Ydb::Operation::V1::OperationService::Stub::AsyncCancelOperation,
      stub_.get(), request, executor_->GetQueue());
}

std::future<Ydb::Operations::ForgetOperationResponse>
OperationClient::ForgetOperation(
    const Ydb::Operations::ForgetOperationRequest& request) {
  return SimpleClientMethod<Ydb::Operations::ForgetOperationResponse>::Call(
      &Ydb::Operation::V1::OperationService::Stub::AsyncForgetOperation,
      stub_.get(), request, executor_->GetQueue());
}

std::future<Ydb::Operations::ListOperationsResponse>
OperationClient::ListOperations(
    const Ydb::Operations::ListOperationsRequest& request) {
  return SimpleClientMethod<Ydb::Operations::ListOperationsResponse>::Call(
      &Ydb::Operation::V1::OperationService::Stub::AsyncListOperations,
      stub_.get(), request, executor_->GetQueue());
}

} // namespace ydbcpp
