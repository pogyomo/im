#ifndef IM_FORWARD_LIST_H_
#define IM_FORWARD_LIST_H_

#include <forward_list>
#include <initializer_list>
#include <limits>
#include <memory>

namespace im {

namespace impl {
namespace forward_list {

template <class T>
class node {
public:
    node() = delete;
    node(const T& value, const std::shared_ptr<node>& next)
        : value_(value), next_(next) {}
    node(T&& value, const std::shared_ptr<node>& next)
        : value_(std::forward<T>(value)), next_(next) {}
    node(const node& node) : value_(node.value_), next_(node.next_) {}
    node(node&& node)
        : value_(std::move(node.value_)), next_(std::move(node.next_)) {}
    inline const T& value() const { return value_; }
    inline const std::shared_ptr<node>& next() const { return next_; }

private:
    T value_;
    std::shared_ptr<node> next_;
};

template <class T>
class iterator {};

}  // namespace forward_list
}  // namespace impl

template <class T, class Allocator = std::allocator<T>>
class forward_list {
public:
    using size_type = std::size_t;
    using reference = const T&;
    using iterator = impl::forward_list::iterator<T>;

    explicit forward_list(const Allocator& a = Allocator())
        : node_(nullptr), a_(a) {}

    explicit forward_list(size_type n, const T& x = T(),
                          const Allocator& a = Allocator())
        : node_(nullptr), a_(a) {
        for (size_type i = 0; i < n; i++) {
            node_ = std::allocate_shared<node>(a_, x, node_);
        }
    }

    template <class InputIterator>
    forward_list(InputIterator first, InputIterator last,
                 const Allocator& a = Allocator())
        : node_(nullptr), a_(a) {
        for (InputIterator it = first; it != last; it++) {
            node_ = std::allocate_shared<node>(a_, *it, node_);
        }
    }

    forward_list(const forward_list& x) : node_(x.node_), a_(x.a_) {}

    forward_list(forward_list&& x)
        : node_(std::move(x.node_)), a_(std::move(x.a_)) {}

    forward_list(std::initializer_list<T> il, const Allocator& a = Allocator())
        : node_(nullptr), a_(a) {
        for (T& x : il) {
            node_ = std::allocate_shared<node>(a_, std::move(x), node_);
        }
    }

    forward_list& operator=(const forward_list& x) {
        node_ = x.node_;
        a_ = x.a_;
        return *this;
    }

    forward_list& operator=(forward_list&& x) {
        node_ = std::move(x.node_);
        a_ = std::move(x.a_);
        return *this;
    }

    iterator begin() const;
    iterator end() const;

    bool empty() const noexcept { return node_.get() == nullptr; }

    size_type max_size() const noexcept {
        return std::numeric_limits<size_type>::max();
    }

    reference front() const { return node_->value(); }

    template <class... Args>
    forward_list emplace_front(Args&&... args) {
        auto new_node = std::allocate_shared<node>(
            a_, T(std::forward<Args>(args)...), node_);
        return forward_list(std::move(new_node), a_);
    }

private:
    using node = impl::forward_list::node<T>;

    forward_list(std::shared_ptr<node>&& node, const Allocator& a)
        : node_(std::move(node)), a_(a) {}

    std::shared_ptr<node> node_;
    Allocator a_;
};

}  // namespace im

#endif  // IM_FORWARD_LIST_H_
