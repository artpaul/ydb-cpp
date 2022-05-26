#pragma once

#include <functional>
#include <memory>

namespace ydbcpp {

class Event {
 public:
  virtual ~Event() = default;

  void Proceed(const bool ok) {
    std::unique_ptr<Event> this_{this};
    DoProcess(ok);
  }

 protected:
  virtual void DoProcess(const bool ok) = 0;
};

template <typename Derived>
class EventFactory : public std::enable_shared_from_this<Derived> {
  class FunctionEvent : public Event {
   public:
    FunctionEvent(std::function<void(bool)> cb, std::shared_ptr<Derived> m)
        : cb_(std::move(cb)), method_(std::move(m)) {
    }

    void DoProcess(const bool ok) override {
      cb_(ok);
    }

   private:
    const std::function<void(bool)> cb_;
    const std::shared_ptr<Derived> method_;
  };

 protected:
  Event* MakeEvent(std::function<void()> cb) {
    return new FunctionEvent([cb](bool) { cb(); }, this->shared_from_this());
  }

  Event* MakeEvent(std::function<void(bool ok)> cb) {
    return new FunctionEvent(std::move(cb), this->shared_from_this());
  }
};

} // namespace ydbcpp
