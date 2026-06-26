// Singly Linked List
//
// The student builds a singly linked list of int from scratch: a head/tail
// pointer pair with an explicit length counter, plus the standard insert,
// remove, access, and reverse operations.
//
// Compile: g++ -std=c++17 -Wall singly_linked_list.cpp -o out
// Run:     ./out
//
// Implement every method marked TODO until main() prints all checks passed.

#include <cassert>
#include <iostream>
#include <stdexcept>

class SinglyLinkedList {
public:
    struct Node {
        int data;
        Node* next;
        Node(int value) : data(value), next(nullptr) {}
    };

    // Construct an empty list: no nodes, length 0.
    SinglyLinkedList() : head_(nullptr), tail_(nullptr), length_(0) {}

    // Destructor: release every node so no memory leaks.
    // TODO: free memory -- walk the list and delete each node.
    ~SinglyLinkedList() {
        // TODO: free memory
    }

    // Non-copyable for this exercise (manual ownership of raw pointers).
    SinglyLinkedList(const SinglyLinkedList&) = delete;
    SinglyLinkedList& operator=(const SinglyLinkedList&) = delete;

    // Return the number of elements currently stored. O(1).
    int size() const { return length_; }

    // Return true when the list holds no elements. O(1).
    bool empty() const { return length_ == 0; }

    // Insert value as the new first element.
    // After the call, front() == value and size() grows by one.
    // Must keep tail_ correct when inserting into an empty list.
    // Target: O(1).
    void push_front(int value) {
        throw std::logic_error("TODO: implement SinglyLinkedList::push_front");
    }

    // Append value as the new last element.
    // After the call, the value sits at index size()-1; size() grows by one.
    // Must keep head_ correct when appending to an empty list.
    // Target: O(1) using tail_.
    void push_back(int value) {
        throw std::logic_error("TODO: implement SinglyLinkedList::push_back");
    }

    // Remove the first element.
    // Precondition: the list is non-empty (assert / throw on empty).
    // Must update tail_ to nullptr when the last element is removed, and
    // free the removed node. size() shrinks by one. Target: O(1).
    void pop_front() {
        throw std::logic_error("TODO: implement SinglyLinkedList::pop_front");
    }

    // Return the value of the first element without removing it.
    // Throws std::out_of_range when the list is empty. Target: O(1).
    int front() const {
        throw std::logic_error("TODO: implement SinglyLinkedList::front");
    }

    // Return the value stored at position index (0-based).
    // Valid range is [0, size()-1]; throws std::out_of_range otherwise.
    // Target: O(index) -- walk from head_.
    int get(int index) const {
        throw std::logic_error("TODO: implement SinglyLinkedList::get");
    }

    // Insert value so that it ends up at position index, shifting the
    // existing element at index (and all after it) one place toward the tail.
    // Valid range is [0, size()]: index == 0 behaves like push_front,
    // index == size() behaves like push_back. Throws std::out_of_range when
    // index is outside [0, size()]. Keep head_/tail_/length_ consistent.
    // Target: O(index).
    void insert_at(int index, int value) {
        throw std::logic_error("TODO: implement SinglyLinkedList::insert_at");
    }

    // Remove the first node whose data equals value.
    // Return true if a matching node was found and removed, false otherwise.
    // Must handle removing the head and removing the tail (update head_/tail_)
    // and free the removed node. Target: O(n).
    bool remove_value(int value) {
        throw std::logic_error("TODO: implement SinglyLinkedList::remove_value");
    }

    // Reverse the list in place so the order of elements is flipped.
    // After the call head_ points at the old tail and tail_ at the old head;
    // size() is unchanged. No new nodes are allocated. Target: O(n).
    void reverse() {
        throw std::logic_error("TODO: implement SinglyLinkedList::reverse");
    }

    // Print the list as "a -> b -> c" followed by a newline.
    // An empty list prints "(empty)". Read-only view for debugging.
    void debug_print() const {
        if (head_ == nullptr) {
            std::cout << "(empty)\n";
            return;
        }
        for (Node* cur = head_; cur != nullptr; cur = cur->next) {
            std::cout << cur->data;
            if (cur->next != nullptr) {
                std::cout << " -> ";
            }
        }
        std::cout << "\n";
    }

private:
    Node* head_;
    Node* tail_;
    int length_;
};

int main() {
    try {
        SinglyLinkedList list;

        // Empty state.
        assert(list.empty());
        assert(list.size() == 0);

        // push_front builds reverse insertion order: 3, 2, 1.
        list.push_front(1);
        list.push_front(2);
        list.push_front(3);
        assert(!list.empty());
        assert(list.size() == 3);
        assert(list.front() == 3);
        assert(list.get(0) == 3);
        assert(list.get(1) == 2);
        assert(list.get(2) == 1);

        // push_back appends at the tail: 3, 2, 1, 4, 5.
        list.push_back(4);
        list.push_back(5);
        assert(list.size() == 5);
        assert(list.get(3) == 4);
        assert(list.get(4) == 5);
        assert(list.front() == 3);

        // insert_at the middle: place 99 at index 2 -> 3, 2, 99, 1, 4, 5.
        list.insert_at(2, 99);
        assert(list.size() == 6);
        assert(list.get(0) == 3);
        assert(list.get(1) == 2);
        assert(list.get(2) == 99);
        assert(list.get(3) == 1);
        assert(list.get(5) == 5);

        // insert_at the front (index 0) acts like push_front.
        list.insert_at(0, 7);
        assert(list.front() == 7);
        assert(list.get(0) == 7);
        assert(list.size() == 7);

        // insert_at the end (index == size) acts like push_back.
        int n = list.size();
        list.insert_at(n, 42);
        assert(list.size() == n + 1);
        assert(list.get(list.size() - 1) == 42);

        // List is now: 7, 3, 2, 99, 1, 4, 5, 42.
        // remove_value present: drop 99 -> 7, 3, 2, 1, 4, 5, 42.
        assert(list.remove_value(99) == true);
        assert(list.size() == 7);
        assert(list.get(0) == 7);
        assert(list.get(1) == 3);
        assert(list.get(2) == 2);
        assert(list.get(3) == 1);

        // remove_value at the head: drop 7 -> 3, 2, 1, 4, 5, 42.
        assert(list.remove_value(7) == true);
        assert(list.front() == 3);
        assert(list.size() == 6);

        // remove_value at the tail: drop 42 -> 3, 2, 1, 4, 5.
        assert(list.remove_value(42) == true);
        assert(list.size() == 5);
        assert(list.get(list.size() - 1) == 5);

        // remove_value absent: list unchanged.
        assert(list.remove_value(1000) == false);
        assert(list.size() == 5);

        // reverse: 3, 2, 1, 4, 5 -> 5, 4, 1, 2, 3.
        list.reverse();
        assert(list.size() == 5);
        assert(list.get(0) == 5);
        assert(list.get(1) == 4);
        assert(list.get(2) == 1);
        assert(list.get(3) == 2);
        assert(list.get(4) == 3);
        assert(list.front() == 5);

        // pop_front walks the reversed list from the new head.
        list.pop_front();
        assert(list.front() == 4);
        assert(list.size() == 4);

        list.pop_front();
        assert(list.front() == 1);
        assert(list.size() == 3);

        // Drain the rest; the list ends empty with a consistent tail.
        list.pop_front();
        list.pop_front();
        list.pop_front();
        assert(list.empty());
        assert(list.size() == 0);

        // After draining, push_back must still work (tail_ reset correctly).
        list.push_back(10);
        assert(list.front() == 10);
        assert(list.size() == 1);

        std::cout << "All checks passed\n";
    } catch (const std::exception& e) {
        std::cerr << "FAILED (likely unimplemented): " << e.what() << "\n";
        return 1;
    }
    return 0;
}
