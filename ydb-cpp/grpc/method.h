#pragma once

#include <grpcpp/grpcpp.h>

#include <future>
#include <memory>

#include "event.h"

namespace ydbcpp {

template <typename Response>
class SimpleClientMethod : public EventFactory<SimpleClientMethod<Response>> {
 public:
  SimpleClientMethod(grpc::CompletionQueue* const cq) : cq_(cq) {
  }

  template <typename F, typename Stub, typename Request>
  static std::future<Response> Call(F&& f,
      Stub* stub,
      const Request& request,
      grpc::CompletionQueue* const cq) {
    return std::make_shared<SimpleClientMethod>(cq)->Run(
        std::forward<F>(f), stub, request);
  }

  template <typename F, typename Stub, typename Request>
  std::future<Response> Run(F&& f, Stub* stub, const Request& request) {
    rpc_ = std::invoke(std::forward<F>(f), stub, &context_, request, cq_);
    // Request that, upon completion of the RPC, "reply" be updated with the
    // server's response; "status" with the indication of whether the operation
    // was successful.
    rpc_->Finish(
        &response_, &status_, this->MakeEvent([this] { OnResponse(); }));
    return promise_.get_future();
  }

 private:
  void OnResponse() {
    if (!status_.ok()) {
      // TODO
    }
    promise_.set_value(std::move(response_));
  }

 private:
  /// The producer-consumer queue we use to communicate asynchronously with the
  /// gRPC runtime.
  grpc::CompletionQueue* const cq_;
  /// Context for the client. It could be used to convey extra information to
  /// the server and/or tweak certain RPC behaviors.
  grpc::ClientContext context_;

  ///
  std::promise<Response> promise_;
  /// Container for the data we expect from the server.
  Response response_;
  /// Storage for the status of the RPC upon completion.
  grpc::Status status_;

  std::unique_ptr<grpc::ClientAsyncResponseReader<Response>> rpc_;
};

} // namespace ydbcpp
