#include "discovery.h"

#include "executor.h"
#include "method.h"

namespace ydbcpp {

DiscoveryClient::DiscoveryClient(std::shared_ptr<ClientExecutor> executor)
    : executor_(std::move(executor))
    , stub_(Ydb::Discovery::V1::DiscoveryService::NewStub(
          executor_->GetChannel())) {
}

DiscoveryClient::~DiscoveryClient() = default;

std::future<Ydb::Discovery::ListEndpointsResponse>
DiscoveryClient::ListEndpoints(
    const Ydb::Discovery::ListEndpointsRequest& request) {
  return SimpleClientMethod<Ydb::Discovery::ListEndpointsResponse>::Call(
      &Ydb::Discovery::V1::DiscoveryService::Stub::AsyncListEndpoints,
      stub_.get(), request, executor_->GetQueue());
}

std::future<Ydb::Discovery::WhoAmIResponse> DiscoveryClient::WhoAmI(
    const Ydb::Discovery::WhoAmIRequest& request) {
  return SimpleClientMethod<Ydb::Discovery::WhoAmIResponse>::Call(
      &Ydb::Discovery::V1::DiscoveryService::Stub::AsyncWhoAmI, stub_.get(),
      request, executor_->GetQueue());
}

} // namespace ydbcpp
