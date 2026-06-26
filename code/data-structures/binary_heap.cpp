// Binary Min-Heap / Priority Queue
//
// The student builds a min-heap on top of std::vector<T>: push (sift up),
// pop (remove the minimum, then sift down), and an O(n) build-heap constructor.
//
// Compile/run:
//   g++ -std=c++17 -Wall binary_heap.cpp -o out && ./out
//
// Implement every method marked TODO until main() prints all checks passed.

#include <cassert>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

template <class T>
class MinHeap {
public:
    // Constructs an empty heap. Leaves the object in a valid empty state.
    MinHeap() = default;

    // Build-heap constructor: copies the elements, then arranges them into a
    // valid min-heap. Target time complexity: O(n) (sift_down from the last
    // internal node down to the root, not n separate pushes).
    // Edge cases: empty input yields an empty heap.
    explicit MinHeap(const std::vector<T>& items);

    // No owned raw resources; the vector frees itself.
    ~MinHeap() = default;

    // Returns true when the heap holds no elements. O(1).
    bool empty() const { return data_.empty(); }

    // Returns the number of stored elements. O(1).
    int size() const { return static_cast<int>(data_.size()); }

    // Returns a const reference to the minimum element (the root).
    // Throws std::out_of_range when the heap is empty. O(1).
    const T& top() const;

    // Inserts value and restores the heap order by sifting the new element up
    // from the last position. Target time complexity: O(log n).
    void push(const T& value);

    // Removes the minimum element: moves the last element to the root, shrinks
    // the vector, then sifts the new root down. Target time complexity: O(log n).
    // Throws std::out_of_range when the heap is empty.
    void pop();

    // Reads the backing array left-to-right (level order). Does not reveal the
    // sift logic. For visualization only.
    std::string debug_to_string() const {
        std::string out = "[";
        for (std::size_t i = 0; i < data_.size(); ++i) {
            if (i) out += ", ";
            out += std::to_string(data_[i]);
        }
        out += "]";
        return out;
    }

private:
    std::vector<T> data_;

    // Index helpers (0-based array layout).
    static int parent(int i) { return (i - 1) / 2; }
    static int left(int i) { return 2 * i + 1; }
    static int right(int i) { return 2 * i + 2; }

    // Moves the element at index i toward the root until the parent is <= it.
    // Used by push. Target time complexity: O(log n).
    void sift_up(int i);

    // Moves the element at index i toward the leaves until both children are
    // >= it (swapping with the smaller child each step). Used by pop and by the
    // build-heap constructor. Target time complexity: O(log n).
    void sift_down(int i);
};

template <class T>
MinHeap<T>::MinHeap(const std::vector<T>& items) {
    (void)items;
    throw std::logic_error("TODO: implement MinHeap::MinHeap(const std::vector<T>&)");
}

template <class T>
const T& MinHeap<T>::top() const {
    throw std::logic_error("TODO: implement MinHeap::top");
}

template <class T>
void MinHeap<T>::push(const T& value) {
    (void)value;
    throw std::logic_error("TODO: implement MinHeap::push");
}

template <class T>
void MinHeap<T>::pop() {
    throw std::logic_error("TODO: implement MinHeap::pop");
}

template <class T>
void MinHeap<T>::sift_up(int i) {
    (void)i;
    throw std::logic_error("TODO: implement MinHeap::sift_up");
}

template <class T>
void MinHeap<T>::sift_down(int i) {
    (void)i;
    throw std::logic_error("TODO: implement MinHeap::sift_down");
}

int main() {
    try {
        // Empty heap.
        MinHeap<int> h;
        assert(h.empty());
        assert(h.size() == 0);

        // push in a deliberately unsorted order; top() must track the minimum.
        const std::vector<int> input = {5, 3, 8, 1, 9, 2, 7, 4, 6, 0};
        for (int x : input) h.push(x);
        assert(!h.empty());
        assert(h.size() == static_cast<int>(input.size()));
        assert(h.top() == 0);

        // Repeated pop yields ascending order.
        int prev = h.top();
        h.pop();
        while (!h.empty()) {
            int cur = h.top();
            assert(cur >= prev);
            prev = cur;
            h.pop();
        }
        assert(h.empty());
        assert(h.size() == 0);

        // top() on an empty heap throws.
        bool threw = false;
        try {
            h.top();
        } catch (const std::out_of_range&) {
            threw = true;
        }
        assert(threw);

        // pop() on an empty heap throws.
        threw = false;
        try {
            h.pop();
        } catch (const std::out_of_range&) {
            threw = true;
        }
        assert(threw);

        // Build-heap constructor, then repeated pop yields sorted output.
        const std::vector<int> raw = {12, 4, 7, 1, 3, 11, 9, 2, 8, 6, 5, 10};
        MinHeap<int> b(raw);
        assert(b.size() == static_cast<int>(raw.size()));

        std::vector<int> drained;
        while (!b.empty()) {
            drained.push_back(b.top());
            b.pop();
        }
        std::vector<int> expected = raw;
        std::sort(expected.begin(), expected.end());
        assert(drained == expected);

        // Build-heap on empty input.
        MinHeap<int> e(std::vector<int>{});
        assert(e.empty());
        assert(e.size() == 0);

        // Single element.
        MinHeap<int> one(std::vector<int>{42});
        assert(one.size() == 1);
        assert(one.top() == 42);
        one.pop();
        assert(one.empty());

        // Duplicates are handled.
        MinHeap<int> d;
        for (int x : {2, 2, 1, 1, 3, 3}) d.push(x);
        std::vector<int> dout;
        while (!d.empty()) {
            dout.push_back(d.top());
            d.pop();
        }
        assert((dout == std::vector<int>{1, 1, 2, 2, 3, 3}));

        std::cout << "All checks passed\n";
    } catch (const std::exception& e) {
        std::cerr << "FAILED (likely unimplemented): " << e.what() << "\n";
        return 1;
    }
    return 0;
}
