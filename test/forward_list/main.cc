#include <cassert>
#include <initializer_list>
#include <utility>

#include "im/forward_list.h"

bool compare_using_iterator(im::forward_list<int> l1,
                            std::initializer_list<int> il) {
    auto it1 = l1.begin();
    auto it2 = il.begin();

    int count = 0;
    for (; it1 != l1.end() && it2 != il.end(); ++it1, ++it2, ++count) {
        if (*it1 != *it2) return false;
    }
    return count == il.size();
}

void push_front() {
    im::forward_list<int> l1;
    auto l2 = l1.push_front(0);
    auto l3 = l2.push_front(1);
    auto l4 = l3.push_front(2);

    assert(l1.empty());
    assert(l2.front() == 0);
    assert(l3.front() == 1);
    assert(l4.front() == 2);
}

void emplace_front() {
    im::forward_list<std::pair<int, int>> l1;
    auto l2 = l1.emplace_front(0, 1);
    auto l3 = l1.emplace_front(2, 3);
    auto l4 = l1.emplace_front(4, 5);

    auto r2 = std::make_pair<int, int>(0, 1);
    auto r3 = std::make_pair<int, int>(2, 3);
    auto r4 = std::make_pair<int, int>(4, 5);

    assert(l1.empty());
    assert(l2.front() == r2);
    assert(l3.front() == r3);
    assert(l4.front() == r4);
}

void iterator() {
    im::forward_list<int> l1;
    auto l2 = l1.push_front(0);
    auto l3 = l2.push_front(1);
    auto l4 = l3.push_front(2);

    assert(compare_using_iterator(l4, {2, 1, 0}));
}

void push_and_pop() {
    im::forward_list<int> l1;
    auto l2 = l1.push_front(0);
    auto l3 = l2.push_front(1);
    auto l4 = l3.push_front(2);
    auto l5 = l4.pop_front();
    auto l6 = l5.push_front(3);

    assert(compare_using_iterator(l2, {0}));
    assert(compare_using_iterator(l3, {1, 0}));
    assert(compare_using_iterator(l4, {2, 1, 0}));
    assert(compare_using_iterator(l5, {1, 0}));
    assert(compare_using_iterator(l6, {3, 1, 0}));
}

int main() {
    push_front();
    emplace_front();
    iterator();
    push_and_pop();
    return 0;
}
