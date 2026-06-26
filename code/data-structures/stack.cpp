// Stack (array-backed)
//
// You build a generic LIFO stack on top of a growable array. The backing
// buffer doubles its capacity when full. You implement push, pop, and top;
// the constructor and the read-only debug helpers are provided.
//
// Compile & run:
//   g++ -std=c++17 -Wall stack.cpp -o out && ./out
//
// Implement every method marked TODO until main() prints all checks passed.

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>

template <class T>
class Stack {
public:
    // Construct an empty stack with no allocated buffer.
    Stack() : data_(nullptr), size_(0), capacity_(0) {}

    // Release the backing buffer.
    // Target: O(1) (plus element destruction handled by delete[]).
    // Must not throw.
    ~Stack() {
        // TODO: free the backing buffer with delete[] data_.
        // Left empty for now (a leak, not a crash) so the test harness can run before
        // you implement it. A destructor must never throw, so do not put a throw here.
    }

    // True when the stack holds no elements.
    // Target: O(1).
    bool empty() const { return size_ == 0; }

    // Number of elements currently on the stack.
    // Target: O(1).
    int size() const { return size_; }

    // Push value onto the top of the stack.
    // If size_ == capacity_, grow the buffer first: new capacity is
    // capacity_ * 2 when capacity_ > 0, otherwise 1 (the first push).
    // Growing copies existing elements into the new buffer and frees the old.
    // Target: O(1) amortized.
    // Edge cases: first push from empty/zero-capacity state must allocate.
    void push(const T& value) {
        (void)value;
        throw std::logic_error("TODO: implement Stack::push");
    }

    // Remove the top element.
    // Target: O(1).
    // Edge cases: calling pop() on an empty stack is a precondition violation;
    // guard it with assert(!empty()). Capacity is not required to shrink.
    void pop() {
        throw std::logic_error("TODO: implement Stack::pop");
    }

    // Return a reference to the top element.
    // Target: O(1).
    // Edge cases: throws std::out_of_range when the stack is empty.
    T& top() {
        throw std::logic_error("TODO: implement Stack::top");
    }

    // Read-only view of the buffer from bottom to top, e.g. "[1, 2, 3]"
    // with the top element last. Does not reveal push/pop logic.
    std::string debug_to_string() const {
        std::string out = "[";
        for (int i = 0; i < size_; ++i) {
            if (i > 0) out += ", ";
            out += std::to_string(data_[i]);
        }
        out += "]";
        return out;
    }

private:
    T* data_;
    int size_;
    int capacity_;
};

int main() {
    try {
        Stack<int> s;

        // Empty-state invariants.
        assert(s.empty());
        assert(s.size() == 0);

        // top() on an empty stack must throw; count that it did.
        int threw = 0;
        try {
            s.top();
        } catch (const std::out_of_range&) {
            ++threw;
        }
        assert(threw == 1);

        // push / size / empty.
        s.push(10);
        assert(!s.empty());
        assert(s.size() == 1);
        assert(s.top() == 10);

        s.push(20);
        s.push(30);
        assert(s.size() == 3);
        assert(s.top() == 30);

        // top() returns a mutable reference.
        s.top() = 99;
        assert(s.top() == 99);
        s.top() = 30;

        // LIFO order on pop.
        s.pop();
        assert(s.top() == 20);
        assert(s.size() == 2);

        s.pop();
        assert(s.top() == 10);
        assert(s.size() == 1);

        s.pop();
        assert(s.empty());
        assert(s.size() == 0);

        // Growth across the doubling boundary stays correct.
        for (int i = 0; i < 100; ++i) {
            s.push(i);
            assert(s.top() == i);
            assert(s.size() == i + 1);
        }
        for (int i = 99; i >= 0; --i) {
            assert(s.top() == i);
            s.pop();
        }
        assert(s.empty());

        std::cout << "All checks passed\n";
    } catch (const std::exception& e) {
        std::cerr << "FAILED (likely unimplemented): " << e.what() << "\n";
        return 1;
    }
    return 0;
}
