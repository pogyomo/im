#ifndef IM_VECTOR_H_
#define IM_VECTOR_H_

#include <iterator>
#include <memory>
namespace im {

namespace impl {
namespace vector {

template <class T>
class iterator {};

template <class T>
class const_iterator {};

}  // namespace vector
}  // namespace impl

template <class T, class Allocator = std::allocator<T>>
class vector {
private:
    typedef std::allocator_traits<Allocator> alloc_traits;

public:
    typedef T& reference;
    typedef const T& const_reference;
    typedef impl::vector::iterator<T> iterator;
    typedef impl::vector::const_iterator<T> const_iterator;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef Allocator allocator_type;
    typedef typename alloc_traits::pointer pointer;
    typedef typename alloc_traits::const_pointer const_pointer;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    explicit vector(const Allocator& = Allocator());
    explicit vector(size_type n);
    vector(size_type n, const T& value, const Allocator& = Allocator());
    template <class InputIterator>
    vector(InputIterator first, InputIterator last,
           const Allocator& = Allocator());
    vector(const vector& x);
    vector(vector&& x);
    vector(const vector& x, const Allocator& a);
    vector(vector&& x, const Allocator& a);
    vector(std::initializer_list<T> il, const Allocator& a = Allocator());

    ~vector();

    vector& operator=(const vector& x);
    vector& operator=(vector&& x);
    vector& operator=(std::initializer_list<T> il);

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;
    const_reverse_iterator rcbegin() const;
    const_reverse_iterator rcend() const;

    size_type size() const noexcept;
    bool empty() const noexcept;

    reference operator[](size_type n);
    const_reference operator[](size_type n) const;
    reference at(size_type n);
    const_reference at(size_type n) const;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;

    vector push_back(const T& x);
    vector push_back(T&& x);
    vector pop_back();

    allocator_type get_allocator() const noexcept;
};

}  // namespace im

#endif  // IM_VECTOR_H_
