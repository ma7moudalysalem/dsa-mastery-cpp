// Dynamic Array (your own std::vector)
// The student builds a growable, contiguous array container backing an
// int* buffer: amortized O(1) push_back via capacity doubling, bounds-checked
// access, and insert/erase with element shifting.
// Compile/run: g++ -std=c++17 -Wall dynamic_array.cpp -o out && ./out
// Implement every method marked TODO until main() prints all checks passed.
//
// NOTE: This file is a FULLY WORKED REFERENCE. Every method is implemented.
// Use it as the quality model your own work is compared against.

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>

template <class T>
class DynamicArray {
    // Backing buffer holding size_ constructed-by-assignment elements within a
    // block of capacity_ slots. Invariant: 0 <= size_ <= capacity_, and
    // data_ != nullptr exactly when capacity_ > 0.
    T* data_;
    int size_;
    int capacity_;

    // Grow the backing buffer to new_capacity (must be >= size_), copying the
    // existing elements over. O(size_). Used by push_back/insert to expand.
    void reallocate(int new_capacity) {
        assert(new_capacity >= size_);
        T* new_data = new T[new_capacity];
        for (int i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

public:
    // Construct an empty array: no buffer, size 0, capacity 0. The first
    // push_back allocates capacity 1, then capacity doubles when full.
    DynamicArray() : data_(nullptr), size_(0), capacity_(0) {}

    // Release the backing buffer. Must not throw.
    ~DynamicArray() {
        delete[] data_;
    }

    // Number of stored elements. O(1).
    int size() const { return size_; }

    // True when no elements are stored. O(1).
    bool empty() const { return size_ == 0; }

    // Allocated slot count (>= size()). O(1).
    int capacity() const { return capacity_; }

    // Append value at the end. Amortized O(1): when the buffer is full,
    // capacity grows to 1 (from 0) or doubles otherwise before inserting.
    void push_back(const T& value) {
        if (size_ == capacity_) {
            reallocate(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data_[size_] = value;
        ++size_;
    }

    // Remove the last element. O(1). Capacity is left unchanged.
    // Precondition: the array is non-empty (asserted).
    void pop_back() {
        assert(!empty());
        --size_;
    }

    // Indexed access without bounds checking beyond a debug assert. O(1).
    // Precondition: 0 <= index < size() (asserted).
    T& operator[](int index) {
        assert(index >= 0 && index < size_);
        return data_[index];
    }

    const T& operator[](int index) const {
        assert(index >= 0 && index < size_);
        return data_[index];
    }

    // Indexed access with checking. O(1).
    // Throws std::out_of_range when index is outside [0, size()).
    T& at(int index) {
        if (index < 0 || index >= size_) {
            throw std::out_of_range("DynamicArray::at index out of range");
        }
        return data_[index];
    }

    // First element. O(1). Precondition: non-empty (asserted).
    T& front() {
        assert(!empty());
        return data_[0];
    }

    // Last element. O(1). Precondition: non-empty (asserted).
    T& back() {
        assert(!empty());
        return data_[size_ - 1];
    }

    // Insert value so it ends up at position index, shifting later elements
    // one slot to the right. O(size()) due to shifting (plus possible grow).
    // index == size() appends. Precondition: 0 <= index <= size() (asserted).
    void insert(int index, const T& value) {
        assert(index >= 0 && index <= size_);
        if (size_ == capacity_) {
            reallocate(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        for (int i = size_; i > index; --i) {
            data_[i] = data_[i - 1];
        }
        data_[index] = value;
        ++size_;
    }

    // Remove the element at index, shifting later elements one slot to the
    // left. O(size()). Capacity is unchanged.
    // Precondition: 0 <= index < size() (asserted).
    void erase(int index) {
        assert(index >= 0 && index < size_);
        for (int i = index; i < size_ - 1; ++i) {
            data_[i] = data_[i + 1];
        }
        --size_;
    }

    // Remove all elements (size becomes 0). Capacity and buffer are kept so
    // later push_back reuses the existing allocation. O(1).
    void clear() {
        size_ = 0;
    }

    // Read-only view of the current contents for visualization, e.g.
    // [10, 20, 30] (size=3, capacity=4). Does not reveal any algorithm.
    void debug_print() const {
        std::cout << "[";
        for (int i = 0; i < size_; ++i) {
            std::cout << data_[i];
            if (i + 1 < size_) std::cout << ", ";
        }
        std::cout << "] (size=" << size_ << ", capacity=" << capacity_ << ")\n";
    }
};

int main() {
    try {
        // Empty state.
        DynamicArray<int> a;
        assert(a.size() == 0);
        assert(a.empty());
        assert(a.capacity() == 0);

        // push_back drives capacity 0 -> 1 -> 2 -> 4 -> 8 (doubling).
        a.push_back(0);
        assert(a.size() == 1 && a.capacity() == 1 && !a.empty());
        a.push_back(1);
        assert(a.size() == 2 && a.capacity() == 2);
        a.push_back(2);
        assert(a.size() == 3 && a.capacity() == 4);
        a.push_back(3);
        assert(a.size() == 4 && a.capacity() == 4);
        a.push_back(4);
        assert(a.size() == 5 && a.capacity() == 8);

        // Indexing and mutation.
        for (int i = 0; i < a.size(); ++i) assert(a[i] == i);
        a[2] = 20;
        assert(a[2] == 20);

        // const operator[] through a const reference.
        const DynamicArray<int>& ca = a;
        assert(ca[0] == 0 && ca[2] == 20);

        // front / back.
        assert(a.front() == 0);
        assert(a.back() == 4);

        // at() checked access.
        assert(a.at(1) == 1);
        bool threw = false;
        try { a.at(5); } catch (const std::out_of_range&) { threw = true; }
        assert(threw);
        threw = false;
        try { a.at(-1); } catch (const std::out_of_range&) { threw = true; }
        assert(threw);

        // Contents now: [0, 1, 20, 3, 4], size 5.
        // insert at middle: index 2 -> [0, 1, 99, 20, 3, 4].
        a.insert(2, 99);
        assert(a.size() == 6);
        assert(a[0] == 0 && a[1] == 1 && a[2] == 99 && a[3] == 20 &&
               a[4] == 3 && a[5] == 4);

        // insert at front: index 0 -> [7, 0, 1, 99, 20, 3, 4].
        a.insert(0, 7);
        assert(a.size() == 7);
        assert(a.front() == 7 && a[1] == 0);

        // insert at end: index == size() appends -> back becomes 8.
        a.insert(a.size(), 8);
        assert(a.back() == 8);
        assert(a.size() == 8);

        // erase from middle: remove index 3 (value 99) -> [7, 0, 1, 20, 3, 4, 8].
        a.erase(3);
        assert(a.size() == 7);
        assert(a[2] == 1 && a[3] == 20);

        // erase from front.
        a.erase(0);
        assert(a.front() == 0);
        assert(a.size() == 6);

        // pop_back.
        int before = a.size();
        a.pop_back();
        assert(a.size() == before - 1);
        assert(a.back() == 4);

        // clear keeps capacity, resets size.
        int cap_before_clear = a.capacity();
        a.clear();
        assert(a.empty());
        assert(a.size() == 0);
        assert(a.capacity() == cap_before_clear);

        // Reuse after clear works.
        a.push_back(42);
        assert(a.size() == 1 && a.front() == 42 && a.back() == 42);

        // Works with a non-trivial element type too.
        DynamicArray<std::string> words;
        words.push_back("alpha");
        words.push_back("beta");
        assert(words.size() == 2);
        assert(words.front() == "alpha" && words.back() == "beta");
        words.insert(1, "gamma");
        assert(words[1] == "gamma" && words[2] == "beta");
        words.erase(0);
        assert(words.front() == "gamma");

        std::cout << "All checks passed\n";
    } catch (const std::exception& e) {
        std::cerr << "FAILED (likely unimplemented): " << e.what() << "\n";
        return 1;
    }
    return 0;
}
