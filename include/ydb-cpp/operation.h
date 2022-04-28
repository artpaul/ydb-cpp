#pragma once

#include <ydb-api-protos/ydb_operation_v1.grpc.pb.h>

#include <future>
#include <memory>

namespace ydbcpp {

class ClientExecutor;

class OperationClient {
 public:
  OperationClient(std::shared_ptr<ClientExecutor> executor);
  ~OperationClient();

  /**
   * Check status for a given operation.
   */
  std::future<Ydb::Operations::GetOperationResponse> GetOperation(
      const Ydb::Operations::GetOperationRequest& request);

  /**
   * Starts cancellation of a long-running operation,
   * Clients can use GetOperation to check whether the cancellation succeeded
   * or whether the operation completed despite cancellation.
   */
  std::future<Ydb::Operations::CancelOperationResponse> CancelOperation(
      const Ydb::Operations::CancelOperationRequest& request);

  /**
   * Forgets long-running operation. It does not cancel the operation and
   * returns an error if operation was not completed.
   */
  std::future<Ydb::Operations::ForgetOperationResponse> ForgetOperation(
      const Ydb::Operations::ForgetOperationRequest& request);

  /**
   * Lists operations that match the specified filter in the request.
   */
  std::future<Ydb::Operations::ListOperationsResponse> ListOperations(
      const Ydb::Operations::ListOperationsRequest& request);

 private:
  std::shared_ptr<ClientExecutor> executor_;
  std::unique_ptr<Ydb::Operation::V1::OperationService::Stub> stub_;
};

} // namespace ydbcpp
