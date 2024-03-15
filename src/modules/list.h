#ifndef A2_SIMPLE_NAVIGATOR_SRC_MODULES_LIST_H_

#define A2_SIMPLE_NAVIGATOR_SRC_MODULES_LIST_H_

#include <functional>
#include <iostream>
#include <limits>

namespace s21 {

template <typename T>
class list {
 private:
  template <typename IT>
  class ListIterator;
  template <typename CIT>
  class ListConstIterator;

 public:
  //  List Member type

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using iterator = ListIterator<value_type>;
  using const_iterator = ListConstIterator<T>;

  // List Functions

  list() noexcept {
    size_ = 0;
    node_ = nullptr;
  }

  list(const list &q) {
    if (!q.empty()) {
      for (auto it = q.begin(); it != q.end(); it++) {
        push_back(*it);
      }
    }
  }

  list(list &&q) noexcept {
    size_ = q.size_;
    node_ = q.node_;
    back_ = q.back_;
    front_ = q.front_;
    q.node_ = nullptr;
    q.size_ = 0;
    q.back_ = nullptr;
    q.front_ = nullptr;
  }

  list &operator=(list &&q) noexcept {
    if (this != &q) {
      clear();
      node_ = q.node_;
      front_ = q.front_;
      back_ = q.back_;
      size_ = q.size_;
      q.node_ = nullptr;
      q.size_ = 0;
      q.back_ = nullptr;
      q.front_ = nullptr;
    }
    return *this;
  }

  list &operator=(const list &q) {
    if (this != &q) {
      clear();
      list tmp(q);
      *this = std::move(tmp);
    }
    return *this;
  }

  ~list() noexcept { clear(); }

  list(size_type n, const T &value = T()) {
    for (size_t i = 0; i < n; i++) {
      try {
        push_back(value);
      } catch (...) {
        clear();
        throw;
      }
    }
  }

  list(std::initializer_list<value_type> const &items) {
    for (auto it = items.begin(); it != items.end(); it++) {
      try {
        push_back(*it);
      } catch (...) {
        ::operator delete(node_);
        clear();
        throw;
      }
    }
  }

  // List Element access

  const_reference front() const { return *(front_->item); }

  const_reference back() const { return *(back_->item); }

  // List Iterators

  iterator begin() noexcept {
    if (!empty()) {
      iterator result(front_);
      return result;
    } else {
      return end();
    }
  }

  const_iterator begin() const noexcept {
    if (!empty()) {
      const_iterator result(front_);
      return result;
    } else {
      return end();
    }
  }

  iterator end() noexcept {
    if (!empty()) {
      iterator result(back_->prev_, back_);
      return result;
    } else {
      return nullptr;
    }
  }

  const_iterator end() const noexcept {
    if (!empty()) {
      const_iterator result(back_->prev_, back_);
      return result;
    } else {
      return nullptr;
    }
  }

  // List Capacity

  bool empty() const noexcept { return size_ == 0; }

  size_type size() const noexcept { return size_; }

  size_type max_size() const noexcept {
    return (std::numeric_limits<size_type>::max() / 2) / sizeof(Node);
  }

  // List Modifiers

  void clear() noexcept {
    while (size_ != 0) {
      pop_front();
    }
    front_ = nullptr;
    back_ = nullptr;
    node_ = nullptr;
  }

  iterator insert(iterator pos, const_reference value) {
    bool front = false;
    if (pos == begin()) {
      push_front(value);
      front = true;
    } else if (pos == end()) {
      push_back(value);
    } else {
      Node *new_node = (Node *)::operator new(sizeof(Node));
      try {
        new (new_node) Node(value);
      } catch (...) {
        ::operator delete(new_node);
        throw;
      }
      pos--;
      node_ = pos.GetPtr_();
      new_node->prev_ = node_->prev_;
      new_node->next_ = node_;
      node_->prev_ = new_node;
      node_->prev_->prev_->next_ = new_node;
      size_++;
      return new_node;
    }
    return front == true ? front_ : back_;
  }

  void erase(iterator pos) noexcept {
    if (size_ > 0) {
      if (pos == begin()) {
        pop_front();
      } else if (pos.GetPtr_() == back_) {
        pop_back();
      } else {
        node_ = pos.GetPtr_();
        node_->next_->prev_ = node_->prev_;
        node_->prev_->next_ = node_->next_;
        delete node_;
        size_--;
      }
    }
  }

  void push_back(const_reference value) {
    Node *new_node = (Node *)::operator new(sizeof(Node));
    try {
      new (new_node) Node(value);
    } catch (...) {
      ::operator delete(new_node);
      throw;
    }
    if (node_ == nullptr) {
      back_ = new_node;
      front_ = new_node;
      node_ = new_node;
    } else {
      node_ = back_;
      back_ = new_node;
      node_->prev_ = new_node;
      new_node->next_ = node_;
    }
    size_++;
  }

  void pop_back() noexcept {
    if (size_ > 1) {
      node_ = back_->next_;
      if (node_->prev_ != nullptr) {
        node_->prev_->~Node();
        ::operator delete(node_->prev_);
        node_->prev_ = nullptr;
      }
      back_ = node_;
    } else if (size_ == 1) {
      if (node_ != nullptr) {
        node_->~Node();
        ::operator delete(node_);
        node_ = nullptr;
      }
    }
    size_--;
  }

  void push_front(const_reference value) {
    Node *new_node = (Node *)::operator new(sizeof(Node));
    try {
      new (new_node) Node(value);
    } catch (...) {
      ::operator delete(new_node);
      throw;
    }
    if (node_ == nullptr) {
      back_ = new_node;
      front_ = new_node;
      node_ = new_node;
    } else {
      node_ = front_;
      front_ = new_node;
      node_->next_ = new_node;
      new_node->prev_ = node_;
    }
    size_++;
  }

  void pop_front() noexcept {
    if (size_ > 1) {
      node_ = front_->prev_;
      if (node_->next_ != nullptr) {
        node_->next_->~Node();
        ::operator delete(node_->next_);
        node_->next_ = nullptr;
      }
      front_ = node_;
    } else if (size_ == 1) {
      if (node_ != nullptr) {
        node_->~Node();
        ::operator delete(node_);
        node_ = nullptr;
      }
    }
    size_--;
  }

  void swap(list &other) {
    std::swap(size_, other.size_);
    std::swap(front_, other.front_);
    std::swap(back_, other.back_);
    std::swap(node_, other.node_);
  }

  void merge(list &other) {
    node_ = front_;
    other.node_ = other.front_;
    if (!empty()) {
      for (size_type i = 0; i < other.size_; ++i) {
        while (node_->prev_ != nullptr && *node_->item < *other.node_->item) {
          node_ = node_->prev_;
        }
        if (node_->prev_ == nullptr && *node_->item < *other.node_->item) {
          node_->prev_ = other.node_;
          if (other.node_) {
            other.node_->next_ = node_;
          }
          break;
        }
        Node *tmp = other.node_;
        if (tmp) {
          other.node_ = other.node_->prev_;
          (*tmp).InsertBetweenNodes(node_, node_->next_);
          if (other.node_) {
            other.node_->next_ = nullptr;
          }
        }
      }
      size_ += other.size_;
      FindFrontAndBack();
      other.size_ = 0;
      other.node_ = nullptr;
    } else {
      *this = std::move(other);
    }
  }

  void splice(iterator pos, list &other) noexcept {
    if (empty()) {
      *this = other;
    } else if (!other.empty()) {
      if (pos == end()) {
        back_->prev_ = other.front_;
        other.front_->next_ = back_;
        back_ = other.back_;
        node_ = front_;
      } else if (pos == begin()) {
        front_->next_ = other.back_;
        other.back_->prev_ = front_;
        front_ = other.front_;
        node_ = front_;
      } else {
        node_ = pos.GetPtr_();
        Node *tmp = node_->next_;
        node_->next_ = other.back_;
        other.back_->prev_ = node_;
        other.front_->next_ = tmp;
        tmp->prev_ = other.front_;
      }
      other.node_ = nullptr;
      size_ += other.size_;
      other.size_ = 0;
    }
  }

  void reverse() {
    if (size_ > 1) {
      node_ = front_;
      for (size_t i = 0; i < size_; i++) {
        std::swap(node_->next_, node_->prev_);
        node_ = node_->next_;
      }
      std::swap(front_, back_);
    }
  }

  void unique() {
    if (!empty()) {
      auto it2 = begin();
      it2++;
      for (auto it = begin(); it != end();) {
        if (it2 != end()) {
          if (*it != *it2) {
            it++;
            it2++;
          } else {
            erase(it2);
            it2 = it;
            it2++;
          }
        } else {
          it++;
        }
      }
    }
  }

  void sort() {
    for (auto i = begin(); i != end(); i++) {
      for (auto j = begin(); j != end(); j++) {
        auto next = j;
        next++;
        if (next != end() && *j > *next) {
          auto temp = *j;
          *j = *next;
          *next = temp;
        }
      }
    }
  }

  // List insert many

  template <typename... Args>
  iterator insert_many(iterator pos, Args &&...args) {
    list tmp;
    tmp.insert_many_back(args...);
    iterator res = tmp.begin();
    if (empty() || res == end()) {
      res = end();
    } else {
      res = pos;
    }
    splice(pos, tmp);
    return res;
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    size_t count = 0;
    for (auto item : {std::forward<Args>(args)...}) {
      try {
        push_back(item);
      } catch (...) {
        for (size_t i = 0; i < count; ++i) {
          pop_back();
        }
        throw;
      }
      ++count;
    }
  }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    size_t count = 0;
    for (auto item : {std::forward<Args>(args)...}) {
      try {
        push_front(item);
      } catch (...) {
        for (size_t i = 0; i < count; ++i) {
          pop_front();
        }
        throw;
      }
      ++count;
    }
  }

 private:
  class Node {
   public:
    Node() {
      next_ = nullptr;
      prev_ = nullptr;
      item = nullptr;
    }

    Node(const T &value) {
      next_ = nullptr;
      prev_ = nullptr;
      item = (T *)::operator new(sizeof(T));
      try {
        new (item) T(value);
      } catch (...) {
        ::operator delete(item);
        throw;
      }
    }

    void InsertBetweenNodes(Node *prev, Node *next) noexcept {
      if (prev) {
        prev->next_ = this;
      }
      prev_ = prev;
      if (next) {
        next->prev_ = this;
      }
      next_ = next;
    }

    ~Node() {
      if (item != nullptr) {
        item->~T();
        ::operator delete(item);
      }
    }

    Node *next_ = nullptr;
    Node *prev_ = nullptr;
    T *item = nullptr;
  };

  template <typename IT>
  class ListIterator {
   public:
    using pointer = Node *;
    using iterator_reference = IT &;

    ListIterator() {
      ptr_ = nullptr;
      ptr_prev_ = nullptr;
    }

    ListIterator(pointer ptr) {
      ptr_ = ptr;
      ptr_prev_ = nullptr;
    }

    ListIterator(pointer ptr, pointer prev) {
      ptr_ = ptr;
      ptr_prev_ = prev;
    }

    ListIterator &operator=(const ListIterator &other) {
      ptr_ = other.ptr_;
      ptr_prev_ = other.ptr_prev_;
      return *this;
    }
    ListIterator(const ListIterator &other) {
      ptr_ = other.ptr_;
      ptr_prev_ = other.ptr_prev_;
    }

    iterator_reference operator*() const { return *ptr_->item; }

    bool operator==(const ListIterator &other) const {
      return other.ptr_ == ptr_ ? true : false;
    }

    ListIterator &operator++(int) {
      if (ptr_ != nullptr) {
        ptr_prev_ = ptr_;
        ptr_ = ptr_->prev_;
      } else if (ptr_prev_ != nullptr) {
        while (ptr_prev_->next_ != nullptr) {
          ptr_prev_ = ptr_prev_->next_;
        }
        ptr_ = ptr_prev_;
        ptr_prev_ = nullptr;
      }
      return *this;
    }

    ListIterator &operator--(int) {
      if (ptr_ != nullptr) {
        ptr_prev_ = ptr_;
        ptr_ = ptr_->next_;
      } else if (ptr_prev_ != nullptr) {
        while (ptr_prev_->prev_ != nullptr) {
          ptr_prev_ = ptr_prev_->prev_;
        }
        ptr_ = ptr_prev_;
        ptr_prev_ = nullptr;
      }
      return *this;
    }

    ListIterator &operator++() {
      (*this)++;
      return *this;
    }

    ListIterator &operator--() {
      (*this)--;
      return *this;
    }

    ~ListIterator() = default;

    bool operator!=(const ListIterator &other) const {
      return other.ptr_ != ptr_;
    }

    pointer GetPtr_() { return ptr_; }

   private:
    pointer ptr_ = nullptr;
    pointer ptr_prev_ = nullptr;
  };

  template <typename CIT>
  class ListConstIterator {
   public:
    using pointer = Node *;
    using iterator_reference = CIT &;

    ListConstIterator() {
      ptr_ = nullptr;
      ptr_prev_ = nullptr;
    }

    ListConstIterator(pointer ptr) {
      ptr_ = ptr;
      ptr_prev_ = nullptr;
    }

    ListConstIterator(pointer ptr, pointer prev) {
      ptr_ = ptr;
      ptr_prev_ = prev;
    }

    ListConstIterator &operator=(const ListConstIterator &other) {
      ptr_ = other.ptr_;
      ptr_prev_ = other.ptr_prev_;
      return *this;
    }

    ListConstIterator(const ListConstIterator &other) {
      ptr_ = other.ptr_;
      ptr_prev_ = other.ptr_prev_;
    }

    iterator_reference operator*() const { return *ptr_->item; }

    bool operator==(const ListConstIterator &other) const {
      return other.ptr_ == ptr_ ? true : false;
    }

    ListConstIterator operator=(const ListIterator<value_type> &other) {
      return other.ptr_;
    }

    ListConstIterator &operator++(int) {
      if (ptr_ != nullptr) {
        ptr_ = ptr_->prev_;
      } else if (ptr_prev_ != nullptr) {
        while (ptr_prev_->next_ != nullptr) {
          ptr_prev_ = ptr_prev_->next_;
        }
        ptr_ = ptr_prev_;
        ptr_prev_ = nullptr;
      }
      return *this;
    }

    ListConstIterator &operator--(int) {
      if (ptr_ != nullptr) {
        ptr_prev_ = ptr_;
        ptr_ = ptr_->next_;
      } else if (ptr_prev_ != nullptr) {
        while (ptr_prev_->prev_ != nullptr) {
          ptr_prev_ = ptr_prev_->prev_;
        }
        ptr_ = ptr_prev_;
        ptr_prev_ = nullptr;
      }
      return *this;
    }

    ListConstIterator &operator++() {
      (*this)++;
      return *this;
    }

    ListConstIterator &operator--() {
      (*this)--;
      return *this;
    }

    bool operator!=(const ListConstIterator &other) const {
      return other.ptr_ != ptr_;
    }

   private:
    friend class ListIterator<value_type>;
    pointer ptr_ = nullptr;
    pointer ptr_prev_ = nullptr;
  };

  void FindFrontAndBack() {
    Node *tmp = node_;
    while (node_->next_ != nullptr) {
      node_ = node_->next_;
    }
    while (tmp->prev_ != nullptr) {
      tmp = tmp->prev_;
    }
    front_ = node_;
    back_ = tmp;
  }

  size_type size_ = 0;
  Node *front_ = nullptr;
  Node *back_ = nullptr;
  Node *node_ = nullptr;
};
}  // namespace s21

#endif
