#ifndef A2_SIMPLE_NAVIGATOR_SRC_MODULES_STACK_H_

#define A2_SIMPLE_NAVIGATOR_SRC_MODULES_STACK_H_

#include "list.h"

namespace s21 {
template <typename T>
class stack {
 public:
  //  Stack Member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  // Stack Member functions

  stack() { list = new s21::list<value_type>(); }

  stack(const stack &s) : stack() {
    if (!s.list->empty()) {
      for (auto it = s.list->begin(); it != s.list->end(); it++) {
        try {
          list->push_back(*it);
        } catch (...) {
          list->clear();
          delete list;
          throw;
        }
      }
    }
  }

  stack(stack &&s) noexcept {
    list = s.list;
    s.list = nullptr;
  }

  stack &operator=(stack &&s) noexcept {
    if (this != &s) {
      list->clear();
      delete list;
      list = s.list;
      s.list = nullptr;
    }
    return *this;
  }

  stack &operator=(const stack &s) {
    if (this != &s) {
      stack tmp(s);
      *this = std::move(tmp);
    }
    return *this;
  }

  ~stack() noexcept {
    if (list != nullptr) {
      list->clear();
      delete list;
    }
  }

  stack(std::initializer_list<value_type> const &items) : stack() {
    for (auto it = items.begin(); it != items.end(); it++) {
      try {
        list->push_front(*it);
      } catch (...) {
        list->clear();
        delete list;
        throw;
      }
    }
  }

  // Stack Element access

  const_reference top() const { return list->front(); }

  //   Stack Capacity

  bool empty() const noexcept { return list->empty(); }

  size_type size() const noexcept { return list->size(); }

  //   Stack Modifiers

  void push(const_reference value) { list->push_front(value); }

  void pop() { list->pop_front(); }

  void swap(stack &other) { list->swap(*other.list); }

  // Stack insert many
  template <typename... Args>
  void insert_many_front(Args &&...args) {
    list->insert_many_front(args...);
  }

 private:
  s21::list<value_type> *list;
};
}  // namespace s21

#endif
