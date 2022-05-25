#pragma once

#include <ydb-api-protos/ydb_discovery_v1.grpc.pb.h>

#include <future>
#include <memory>

namespace ydbcpp {

class ClientExecutor;

class DiscoveryClient {
 public:
  DiscoveryClient(std::shared_ptr<ClientExecutor> executor);
  ~DiscoveryClient();

  std::future<Ydb::Discovery::ListEndpointsResponse> ListEndpoints(
      const Ydb::Discovery::ListEndpointsRequest& request);

  std::future<Ydb::Discovery::WhoAmIResponse> WhoAmI(
      const Ydb::Discovery::WhoAmIRequest& request);

 private:
  std::shared_ptr<ClientExecutor> executor_;
  std::unique_ptr<Ydb::Discovery::V1::DiscoveryService::Stub> stub_;
};

} // namespace ydbcpp
