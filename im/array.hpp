#ifndef IM_ARRAY_H_
#define IM_ARRAY_H_

#include <initializer_list>
#include <iterator>

namespace im {

namespace impl {
namespace array {

template <class T>
class iterator {};

}  // namespace array
}  // namespace impl

template <class T, std::size_t N>
class array {
public:
    typedef const T& reference;
    typedef impl::array::iterator<T> iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef const T* pointer;
    typedef T value_type;

    array();
    array(size_type n, const T& value = T());
    template <class InputIterator>
    array(InputIterator first, InputIterator last);
    array(std::initializer_list<T> il);
    array(const array& x);
    array(array&& x);

    ~array();

    iterator begin() const;
    iterator end() const;
    reverse_iterator rbegin();
    reverse_iterator rend();

    size_type size() const noexcept;
    constexpr size_type max_size() const noexcept { return N; }
    bool empty() const noexcept;

    reference operator[](size_type n) const;
    reference at(size_type n) const;
    reference front() const;
    reference back() const;
};

}  // namespace im

#endif  // IM_ARRAY_H_
