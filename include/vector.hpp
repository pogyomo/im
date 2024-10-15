#ifndef IM_VECTOR_H_
#define IM_VECTOR_H_

#include <iterator>
#include <memory>
namespace im {

namespace impl {
namespace vector {

template <class T>
class iterator {};

}  // namespace vector
}  // namespace impl

template <class T, class Allocator = std::allocator<T>>
class vector {
private:
    typedef std::allocator_traits<Allocator> alloc_traits;

public:
    typedef const T& reference;
    typedef impl::vector::iterator<T> iterator;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef Allocator allocator_type;
    typedef typename alloc_traits::const_pointer pointer;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef T value_type;

    explicit vector(const Allocator& a = Allocator());
    explicit vector(size_type n);
    vector(size_type n, const T& value, const Allocator& a = Allocator());
    template <class InputIterator>
    vector(InputIterator first, InputIterator last,
           const Allocator& = Allocator());
    vector(const vector& x);
    vector(vector&& x);
    vector(const vector& x, const Allocator& a);
    vector(vector&& x, const Allocator& a);
    vector(std::initializer_list<T> il, const Allocator& a = Allocator());

    ~vector();

    iterator begin() const;
    iterator end() const;
    reverse_iterator rbegin() const;
    reverse_iterator rend() const;

    size_type size() const noexcept;
    size_type max_size() const noexcept;
    bool empty() const noexcept;

    reference operator[](size_type n) const;
    reference at(size_type n) const;
    reference front() const;
    reference back() const;

    vector push_back(const T& x);
    vector push_back(T&& x);
    vector pop_back();

    allocator_type get_allocator() const noexcept;
};

}  // namespace im

#endif  // IM_VECTOR_H_
