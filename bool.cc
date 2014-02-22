#include <iostream>
#include <vector>
#include <memory>

class invoker {
 public:
  virtual void invoke() = 0;
};

template<typename F> class invoker_impl : public invoker {
 public:
  explicit invoker_impl(F f) : f_(f) {
  }
  virtual void invoke() override {
    f_();
  }

 private:
  F f_;
};

template<typename F1, typename F2> class true_or_false_invoker_impl {
 public:
  true_or_false_invoker_impl(F1 f1, F2 f2) {
    invokers_.push_back(std::unique_ptr<invoker>(new invoker_impl<F1>(f1)));
    invokers_.push_back(std::unique_ptr<invoker>(new invoker_impl<F2>(f2)));
  }
  void invoke(bool a) {
    invokers_[static_cast<size_t>(a)]->invoke();
  }

 private:
  std::vector<std::unique_ptr<invoker>> invokers_;
};

template<typename F1, typename F2> void conditional_on_true_or_false(bool a, F1 f1, F2 f2) {
  true_or_false_invoker_impl<F1, F2> impl(f1, f2);
  impl.invoke(a);
}

int main() {
  const bool boolean_variable = (2*2 == 4);
  conditional_on_true_or_false(
    boolean_variable,
    [](){ std::cout << "False" << std::endl; },
    [](){ std::cout << "True" << std::endl; });
}
