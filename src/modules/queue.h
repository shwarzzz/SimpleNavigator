#ifndef A2_SIMPLE_NAVIGATOR_SRC_MODULES_QUEUE_H_

#define A2_SIMPLE_NAVIGATOR_SRC_MODULES_QUEUE_H_

#include "list.h"

namespace s21 {
template <typename T>
class queue {
 public:
  //  Queue Member type

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  // Queue Member functions

  queue() { list = new s21::list<value_type>(); }

  queue(const queue &q) : queue() {
    for (auto it = q.list->begin(); it != q.list->end(); it++) {
      try {
        list->push_back(*it);
      } catch (...) {
        list->clear();
        delete list;
        throw;
      }
    }
  }

  queue(queue &&q) noexcept {
    list = q.list;
    q.list = nullptr;
  }

  queue &operator=(queue &&q) noexcept {
    if (this != &q) {
      list->clear();
      delete list;
      list = q.list;
      q.list = nullptr;
    }
    return *this;
  }

  queue &operator=(const queue &q) {
    if (this != &q) {
      queue tmp(q);
      *this = std::move(tmp);
    }
    return *this;
  }

  ~queue() noexcept {
    if (list != nullptr) {
      list->clear();
      delete list;
    }
  }

  queue(std::initializer_list<value_type> const &items) : queue() {
    for (auto it = items.begin(); it != items.end(); it++) {
      list->push_back(*it);
    }
  }

  // Queue Element access

  const_reference front() const { return list->front(); }

  const_reference back() const { return list->back(); }

  // Queue Capacity

  bool empty() const noexcept { return list->empty(); }

  size_type size() const noexcept { return list->size(); }

  // Queue Modifiers

  void push(const_reference value) { list->push_back(value); }

  void pop() { list->pop_front(); }

  void swap(queue &other) { list->swap(*other.list); }

  // Queue insert many

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    list->insert_many_back(args...);
  }

 private:
  s21::list<value_type> *list;
};
}  // namespace s21

#endif
