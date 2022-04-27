#include <ydb-cpp/event.h>
#include <ydb-cpp/executor.h>

namespace ydbcpp {

ClientExecutor::ClientExecutor(
    std::shared_ptr<grpc::Channel> channel, size_t threads)
    : channel_(std::move(channel))
    , cq_(std::make_unique<grpc::CompletionQueue>())
    , stop_(false) {
  for (size_t i = 0, end = std::max<size_t>(threads, 1ul); i < end; ++i) {
    threads_.emplace_back([this]() { Loop(); });
  }
}

ClientExecutor::~ClientExecutor() {
  cq_->Shutdown();

  stop_ = true;

  for (auto& t : threads_) {
    if (t.joinable()) {
      t.join();
    }
  }
}

std::shared_ptr<grpc::Channel> ClientExecutor::GetChannel() const {
  return channel_;
}

grpc::CompletionQueue* ClientExecutor::GetQueue() const {
  return cq_.get();
}

void ClientExecutor::Loop() {
  while (true) {
    void* tag = nullptr;
    bool ok = false;
    // Block waiting to read the next event from the completion queue. The
    // event is uniquely identified by its tag, which in this case is the
    // memory address of a CallData instance.
    // The return value of Next should always be checked. This return value
    // tells us whether there is any kind of event or cq_ is shutting down.
    if (cq_->Next(&tag, &ok)) {
      if (tag) {
        static_cast<Event*>(tag)->Proceed(ok);
      }
    } else {
      // todo: if stop_
      break;
    }
  }
}

} // namespace ydbcpp
