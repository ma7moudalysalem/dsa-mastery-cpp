// Circular Queue (ring buffer)
//
// The student builds a fixed-capacity FIFO queue backed by a single array,
// where indices wrap around modulo capacity so dequeued slots are reused.
//
// Compile: g++ -std=c++17 -Wall queue_deque.cpp -o out
// Run:     ./out
//
// Implement every method marked TODO until main() prints all checks passed.

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>

template <class T>
class CircularQueue {
public:
    // Construct an empty queue with room for `capacity` elements.
    // Throws std::invalid_argument if capacity <= 0.
    explicit CircularQueue(int capacity)
        : data_(nullptr), head_(0), count_(0), capacity_(capacity) {
        if (capacity_ <= 0) {
            throw std::invalid_argument("capacity must be positive");
        }
        data_ = new T[capacity_];
    }

    // Non-copyable: the array is owned and copy semantics are out of scope here.
    CircularQueue(const CircularQueue&) = delete;
    CircularQueue& operator=(const CircularQueue&) = delete;

    // Release the backing array.
    // Note: do not throw from a destructor.
    ~CircularQueue() {
        delete[] data_;
    }

    // Return true if the queue holds no elements. O(1).
    bool empty() const {
        throw std::logic_error("TODO: implement CircularQueue::empty");
    }

    // Return true if the queue holds capacity() elements. O(1).
    bool full() const {
        throw std::logic_error("TODO: implement CircularQueue::full");
    }

    // Return the number of elements currently stored. O(1).
    int size() const {
        throw std::logic_error("TODO: implement CircularQueue::size");
    }

    // Maximum number of elements the queue can hold. O(1). (given)
    int capacity() const { return capacity_; }

    // Insert `value` at the back of the queue. O(1).
    // Throws std::overflow_error if the queue is full.
    // The new element occupies index (head_ + count_) % capacity_.
    void enqueue(const T& value) {
        throw std::logic_error("TODO: implement CircularQueue::enqueue");
    }

    // Remove the front element. O(1).
    // Throws std::underflow_error if the queue is empty.
    // Advances head_ modulo capacity_ and decrements count_.
    void dequeue() {
        throw std::logic_error("TODO: implement CircularQueue::dequeue");
    }

    // Return a reference to the front element (oldest enqueued). O(1).
    // Throws std::underflow_error if the queue is empty.
    T& front() {
        throw std::logic_error("TODO: implement CircularQueue::front");
    }

    // Render contents front-to-back as "[a, b, c]" by walking the ring from
    // head_ for count_ steps. Reads the backing array only; reveals no
    // enqueue/dequeue logic. (given, for visualization)
    std::string debug_to_string() const {
        std::string out = "[";
        for (int i = 0; i < count_; ++i) {
            if (i > 0) out += ", ";
            int idx = (head_ + i) % capacity_;
            out += std::to_string(data_[idx]);
        }
        out += "]";
        return out;
    }

private:
    T* data_;       // backing array of length capacity_
    int head_;      // index of the front element
    int count_;     // number of elements currently stored
    int capacity_;  // length of data_
};

int main() {
    try {
        CircularQueue<int> q(3);

        // Empty state.
        assert(q.empty());
        assert(!q.full());
        assert(q.size() == 0);
        assert(q.capacity() == 3);

        // front()/dequeue() on empty throw.
        bool threw = false;
        try { q.front(); } catch (const std::underflow_error&) { threw = true; }
        assert(threw);
        threw = false;
        try { q.dequeue(); } catch (const std::underflow_error&) { threw = true; }
        assert(threw);

        // Fill to capacity.
        q.enqueue(10);
        q.enqueue(20);
        q.enqueue(30);
        assert(q.size() == 3);
        assert(q.full());
        assert(!q.empty());
        assert(q.front() == 10);
        assert(q.debug_to_string() == "[10, 20, 30]");

        // enqueue() on full throws and does not change the queue.
        threw = false;
        try { q.enqueue(40); } catch (const std::overflow_error&) { threw = true; }
        assert(threw);
        assert(q.size() == 3);
        assert(q.front() == 10);

        // FIFO order: remove two, oldest first.
        q.dequeue();
        assert(q.front() == 20);
        q.dequeue();
        assert(q.front() == 30);
        assert(q.size() == 1);
        assert(!q.full());

        // Wrap-around: with head_ advanced, new inserts reuse freed slots.
        q.enqueue(40);
        q.enqueue(50);
        assert(q.size() == 3);
        assert(q.full());
        assert(q.debug_to_string() == "[30, 40, 50]");
        assert(q.front() == 30);

        // Drain in order across the wrap boundary.
        q.dequeue();
        assert(q.front() == 40);
        q.dequeue();
        assert(q.front() == 50);
        q.dequeue();
        assert(q.empty());
        assert(q.size() == 0);

        // Reuse after draining: enqueue/dequeue still consistent.
        q.enqueue(60);
        q.enqueue(70);
        assert(q.front() == 60);
        assert(q.size() == 2);
        q.dequeue();
        assert(q.front() == 70);
        assert(q.size() == 1);

        // Capacity guard at construction.
        threw = false;
        try { CircularQueue<int> bad(0); }
        catch (const std::invalid_argument&) { threw = true; }
        assert(threw);

        std::cout << "All checks passed\n";
    } catch (const std::exception& e) {
        std::cerr << "FAILED (likely unimplemented): " << e.what() << "\n";
        return 1;
    }
    return 0;
}
