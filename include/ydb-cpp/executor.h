#pragma once

#include <grpcpp/grpcpp.h>

#include <thread>
#include <vector>

namespace ydbcpp {

class ClientExecutor {
 public:
  explicit ClientExecutor(
      std::shared_ptr<grpc::Channel> channel, size_t threads);
  ~ClientExecutor();

  std::shared_ptr<grpc::Channel> GetChannel() const;

  grpc::CompletionQueue* GetQueue() const;

 private:
  void Loop();

 private:
  std::shared_ptr<grpc::Channel> channel_;
  /// The producer-consumer queue we use to communicate asynchronously with the
  /// gRPC runtime.
  std::unique_ptr<grpc::CompletionQueue> cq_;

  std::atomic<bool> stop_;
  std::vector<std::thread> threads_;
};

} // namespace ydbcpp
