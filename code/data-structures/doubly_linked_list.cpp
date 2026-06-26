// Doubly Linked List
// The student builds a doubly linked list of int with head_/tail_ pointers and
// O(1) insertion/removal at both ends, plus index insertion, value removal, and reverse.
// Compile/run: g++ -std=c++17 -Wall doubly_linked_list.cpp -o out && ./out
// Implement every method marked TODO until main() prints all checks passed.

#include <cassert>
#include <iostream>
#include <stdexcept>

class DoublyLinkedList {
public:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        explicit Node(int v) : data(v), prev(nullptr), next(nullptr) {}
    };

    // Constructs an empty list: no nodes, length 0.
    DoublyLinkedList() : head_(nullptr), tail_(nullptr), length_(0) {}

    // Releases every node so no memory leaks.
    // TODO: free memory — walk from head_ deleting each node.
    ~DoublyLinkedList() {
        // TODO: free memory
    }

    // Non-copyable to keep ownership of raw nodes unambiguous.
    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;

    // Returns the number of elements. O(1).
    int size() const { return length_; }

    // Returns true when the list has no elements. O(1).
    bool empty() const { return length_ == 0; }

    // Inserts val as the new first element.
    // Updates head_ (and tail_ when the list was empty) and length_. O(1).
    void push_front(int val) {
        throw std::logic_error("TODO: implement DoublyLinkedList::push_front");
    }

    // Inserts val as the new last element.
    // Updates tail_ (and head_ when the list was empty) and length_. O(1).
    void push_back(int val) {
        throw std::logic_error("TODO: implement DoublyLinkedList::push_back");
    }

    // Removes the first element.
    // Precondition: list is non-empty (assert). Frees the old head node, updates
    // head_ (and tail_ when the list becomes empty) and length_. O(1).
    void pop_front() {
        throw std::logic_error("TODO: implement DoublyLinkedList::pop_front");
    }

    // Removes the last element.
    // Precondition: list is non-empty (assert). Frees the old tail node, updates
    // tail_ (and head_ when the list becomes empty) and length_. O(1).
    void pop_back() {
        throw std::logic_error("TODO: implement DoublyLinkedList::pop_back");
    }

    // Returns the first element's value by copy.
    // Precondition: list is non-empty (assert). O(1).
    int front() const {
        throw std::logic_error("TODO: implement DoublyLinkedList::front");
    }

    // Returns the last element's value by copy.
    // Precondition: list is non-empty (assert). O(1).
    int back() const {
        throw std::logic_error("TODO: implement DoublyLinkedList::back");
    }

    // Inserts val so that it ends up at position idx (0-based).
    // idx in [0, size()] (assert); idx == 0 behaves like push_front,
    // idx == size() like push_back. Walks to the insertion point. O(n).
    void insert_at(int idx, int val) {
        throw std::logic_error("TODO: implement DoublyLinkedList::insert_at");
    }

    // Removes the first node whose data equals val.
    // Returns true if a node was removed, false if val is absent.
    // Correctly relinks neighbors and updates head_/tail_/length_. O(n).
    bool remove_value(int val) {
        throw std::logic_error("TODO: implement DoublyLinkedList::remove_value");
    }

    // Reverses the list in place so order is back-to-front.
    // Swaps prev/next on every node and swaps head_/tail_. O(n).
    void reverse() {
        throw std::logic_error("TODO: implement DoublyLinkedList::reverse");
    }

    // Prints elements front to back as "[a, b, c]" for visual inspection.
    // Read-only traversal; safe to use while debugging. O(n).
    void debug_print() const {
        std::cout << "[";
        for (Node* cur = head_; cur != nullptr; cur = cur->next) {
            std::cout << cur->data;
            if (cur->next != nullptr) std::cout << ", ";
        }
        std::cout << "]\n";
    }

private:
    Node* head_;
    Node* tail_;
    int length_;
};

int main() {
    try {
        DoublyLinkedList list;
        assert(list.empty());
        assert(list.size() == 0);

        // push_back builds 10, 20, 30
        list.push_back(10);
        list.push_back(20);
        list.push_back(30);
        assert(!list.empty());
        assert(list.size() == 3);
        assert(list.front() == 10);
        assert(list.back() == 30);

        // push_front prepends 5 and 1 -> 1, 5, 10, 20, 30
        list.push_front(5);
        list.push_front(1);
        assert(list.size() == 5);
        assert(list.front() == 1);
        assert(list.back() == 30);

        // pop_front removes 1 -> 5, 10, 20, 30
        list.pop_front();
        assert(list.front() == 5);
        assert(list.size() == 4);

        // pop_back removes 30 -> 5, 10, 20
        list.pop_back();
        assert(list.back() == 20);
        assert(list.size() == 3);

        // insert_at: idx 0 (head), middle, and end (== size)
        list.insert_at(0, 100);   // 100, 5, 10, 20
        assert(list.front() == 100);
        list.insert_at(2, 7);     // 100, 5, 7, 10, 20
        list.insert_at(list.size(), 99); // 100, 5, 7, 10, 20, 99
        assert(list.back() == 99);
        assert(list.size() == 6);

        // remove_value: present (middle), absent, and head
        assert(list.remove_value(7));     // 100, 5, 10, 20, 99
        assert(list.size() == 5);
        assert(!list.remove_value(12345)); // unchanged
        assert(list.size() == 5);
        assert(list.remove_value(100));   // 5, 10, 20, 99
        assert(list.front() == 5);
        assert(list.size() == 4);

        // reverse: 5, 10, 20, 99 -> 99, 20, 10, 5
        list.reverse();
        assert(list.front() == 99);
        assert(list.back() == 5);
        assert(list.size() == 4);

        // reverse again restores original order
        list.reverse();
        assert(list.front() == 5);
        assert(list.back() == 99);

        // drain from both ends
        list.pop_front(); // 10, 20, 99
        list.pop_back();  // 10, 20
        assert(list.size() == 2);
        assert(list.front() == 10);
        assert(list.back() == 20);

        // single-element edge: remove down to empty
        list.pop_front(); // 20
        assert(list.front() == list.back());
        list.pop_back();  // empty
        assert(list.empty());
        assert(list.size() == 0);

        std::cout << "All checks passed\n";
    } catch (const std::exception& e) {
        std::cerr << "FAILED (likely unimplemented): " << e.what() << "\n";
        return 1;
    }
    return 0;
}
