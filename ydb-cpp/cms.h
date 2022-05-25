#pragma once

#include <ydb-api-protos/ydb_cms_v1.grpc.pb.h>

#include <future>
#include <memory>

namespace ydbcpp {

class ClientExecutor;

class CmsClient {
 public:
  CmsClient(std::shared_ptr<ClientExecutor> executor);
  ~CmsClient();

  /**
   * Create a new database.
   */
  std::future<Ydb::Cms::CreateDatabaseResponse> CreateDatabase(
      const Ydb::Cms::CreateDatabaseRequest& request);

  /**
   * Get current database's status.
   */
  std::future<Ydb::Cms::GetDatabaseStatusResponse> GetDatabaseStatus(
      const Ydb::Cms::GetDatabaseStatusRequest& request);

  /**
   * Alter database resources.
   */
  std::future<Ydb::Cms::AlterDatabaseResponse> AlterDatabase(
      const Ydb::Cms::AlterDatabaseRequest& request);

  /**
   * List all databases.
   */
  std::future<Ydb::Cms::ListDatabasesResponse> ListDatabases(
      const Ydb::Cms::ListDatabasesRequest& request);

  /**
   * Remove database.
   */
  std::future<Ydb::Cms::RemoveDatabaseResponse> RemoveDatabase(
      const Ydb::Cms::RemoveDatabaseRequest& request);

  /**
   * Describe supported database options.
   */
  std::future<Ydb::Cms::DescribeDatabaseOptionsResponse>
  DescribeDatabaseOptions(
      const Ydb::Cms::DescribeDatabaseOptionsRequest& request);

 private:
  std::shared_ptr<ClientExecutor> executor_;
  std::unique_ptr<Ydb::Cms::V1::CmsService::Stub> stub_;
};

} // namespace ydbcpp
