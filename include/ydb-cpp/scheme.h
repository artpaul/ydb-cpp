#pragma once

#include <ydb-api-protos/ydb_scheme_v1.grpc.pb.h>

#include <future>
#include <memory>

namespace ydbcpp {

class ClientExecutor;

class SchemeClient {
 public:
  SchemeClient(std::shared_ptr<ClientExecutor> executor);
  ~SchemeClient();

  /** Returns information about object with given path. */
  std::future<Ydb::Scheme::DescribePathResponse> DescribePath(
      const Ydb::Scheme::DescribePathRequest& request);

  /** Returns information about given directory and objects inside it. */
  std::future<Ydb::Scheme::ListDirectoryResponse> ListDirectory(
      const Ydb::Scheme::ListDirectoryRequest& request);

  /** Make Directory. */
  std::future<Ydb::Scheme::MakeDirectoryResponse> MakeDirectory(
      const Ydb::Scheme::MakeDirectoryRequest& request);

  /** Modify permissions. */
  std::future<Ydb::Scheme::ModifyPermissionsResponse> ModifyPermissions(
      const Ydb::Scheme::ModifyPermissionsRequest& request);

  /** Remove Directory. */
  std::future<Ydb::Scheme::RemoveDirectoryResponse> RemoveDirectory(
      const Ydb::Scheme::RemoveDirectoryRequest& request);

 private:
  std::shared_ptr<ClientExecutor> executor_;
  std::unique_ptr<Ydb::Scheme::V1::SchemeService::Stub> stub_;
};

} // namespace ydbcpp
