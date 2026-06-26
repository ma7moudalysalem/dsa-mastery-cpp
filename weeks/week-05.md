# Week 5 — Pointer-Based Memory: Singly & Doubly Linked Lists

This is where the model of memory changes. For four weeks every structure has lived in one contiguous block; this week the data scatters across the heap and the only thing holding it together is a pointer in each node. You build singly and doubly linked lists by hand with raw `new`/`delete`, learn the dummy-head trick that kills most off-by-one bugs, and drill the two patterns that make lists an interview favorite: fast & slow pointers and in-place O(1)-space reversal. It closes with the classic that ties a hashmap to a doubly linked list, the O(1) LRU cache.

## By the end of this week

You should be able to:

- Build a singly linked list from scratch with a head pointer, an optional tail, and a correct iterative destructor that frees a million-node list without overflowing the stack.
- Use a dummy/sentinel head so insert and delete at the front need no special case, and verify the result with `debug_verify_data_integrity` (size, no cycle, tail's `next` is null).
- Detect a cycle, find where it starts, and locate the middle and the nth-from-end node, each in a single pass and O(1) extra space, using Floyd's slow/fast technique.
- Reverse a full list, a sublist `[m, n]`, and nodes in k-groups with the three-pointer technique, without losing the tail or accidentally building a cycle.
- Build a doubly linked list with dual sentinels that deletes a known node in O(1), and combine it with a hashmap to implement an LRU cache where `get` and `put` are both O(1).
- Say out loud when a `std::vector` still beats `std::list` despite the O(1) splice, and why.

The patterns introduced this week are documented in the pattern reference: [Fast & slow pointers](../docs/patterns.md) and [In-place linked-list reversal](../docs/patterns.md). [Hashing for dedup/lookup](../docs/patterns.md) returns from Week 4, now paired with a list.

---

## Lecture 17 — Singly Linked Lists: Build by Hand, Dummy Head, Insert & Delete

### Objectives

- Build a singly linked list from scratch with raw `new`/`delete`, a head pointer, and an optional tail.
- Use a dummy/sentinel head to eliminate head-special-casing on insert and delete.
- Implement an iterative destructor and `debug_verify_data_integrity` to avoid leaks and stack overflow.

### Topics covered

- The node: `struct Node { int value; Node* next; }`, the head pointer, and the pointer model of memory. A list is nodes scattered on the heap, chained by `next`. Compare that to a `vector`, where the cost story is completely different.
- The cost trade-off. Insert or delete at a position you already hold a pointer to is O(1); search and random access are O(n) because you have to walk the chain. This is the mirror image of the array's profile, and choosing between them is a recurring interview decision.
- The dummy/sentinel head. Allocate one extra node in front of the real list so the "first real node" is always `dummy->next`. Now insert-at-front, delete-at-front, delete-the-only-node, and delete-in-the-middle are all the same code with no `if (head == nullptr)` branches sprinkled around.
- Core operations: delete the nth node, insert after a given position, and traverse with correct bounds so you stop before dereferencing past the tail.
- The destructor must be iterative. Walk the list with a `curr`/`next` pair and `delete` each node in a loop. A recursive destructor looks elegant and blows the call stack on a long list, which is the whole point of the aside below.
- Debug tooling: `debug_print_list` to eyeball the contents, and `debug_verify_data_integrity` to assert the size matches, there is no cycle, and the tail's `next` is null.
- Aside: `unique_ptr<Node>` ownership models the chain honestly, but a chain of `unique_ptr` destructs recursively and can overflow the stack for the same reason. Know the trap before you reach for smart pointers here.

```cpp
struct Node {
    int value;
    Node* next;
    Node(int v) : value(v), next(nullptr) {}
};

// Iterative destructor: never recurse over a list you didn't bound.
~LinkedList() {
    Node* curr = head;        // head is the dummy in the sentinel design
    while (curr != nullptr) {
        Node* next = curr->next;
        delete curr;
        curr = next;
    }
}
```

### Patterns

None new. This lecture is the mechanics that the rest of the week builds on.

### In-class problems

- Design Linked List (singly: `get` / `addAtHead` / `addAtTail` / `addAtIndex` / `delete`)
- Remove Nth Node From End of List (dummy head)
- Merge Two Sorted Lists
- Remove Linked List Elements (dummy head)

---

## Lecture 18 — Fast & Slow Pointers: Cycle, Middle, Nth-From-End

### Objectives

- Apply Floyd's slow (`+1`) / fast (`+2`) technique to detect a cycle and find its start.
- Find the middle node and the nth-from-end node in a single O(1)-space pass.
- Order null-checks correctly (`fast && fast->next`) so you never segfault.

### Topics covered

- Floyd's cycle detection. Move `slow` one step and `fast` two steps per iteration. If there is a cycle, `fast` laps `slow` and they meet inside it. If `fast` reaches null, there is no cycle. The meeting point is somewhere in the loop, not the start.
- Finding the cycle's start. After the meeting, reset one pointer to the head and advance both one step at a time. They meet again exactly at the entry to the cycle. The proof is short and worth memorizing so you can explain why, not just recite the steps.
- Middle of the list. When `fast` runs off the end, `slow` sits at the middle. Decide and state your convention for even length: the standard one returns the second of the two middles.
- Nth-from-end in one pass. Advance `fast` by `n` first, then move both together until `fast` hits the end. `slow` lands on the nth-from-end node. This is the same idea that powers Remove Nth Node From End.
- Null-check ordering. Always test `fast && fast->next` before `fast->next->next`. Short-circuit evaluation is what keeps this from dereferencing null, and getting the order wrong is the single most common bug in this lecture.
- Why O(1) space wins. You could copy the list into a `vector` and index it, but that is O(n) extra memory for something two pointers solve in place. The interviewer is checking whether you reach for the pointer trick.

```cpp
// Cycle detection, then find the start.
Node* detectCycle(Node* head) {
    Node* slow = head;
    Node* fast = head;
    while (fast && fast->next) {        // order matters: fast first
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {             // meeting point inside the cycle
            Node* p = head;
            while (p != slow) { p = p->next; slow = slow->next; }
            return p;                   // entry to the cycle
        }
    }
    return nullptr;                     // no cycle
}
```

### Patterns

- [Fast & slow pointers](../docs/patterns.md)

### In-class problems

- Linked List Cycle
- Linked List Cycle II (find cycle start)
- Middle of the Linked List
- Happy Number (fast/slow on a functional sequence)

---

## Lecture 19 — In-Place Linked-List Reversal: Full, Sublist, K-Group

### Objectives

- Reverse a full singly linked list with the `prev` / `curr` / `next` three-pointer technique in O(1) space.
- Reverse a sublist `[m, n]` and reverse nodes in k-groups by careful rewiring.
- Cache `next` before rewiring and null the old head so you never lose the list or build a cycle.

### Topics covered

- Three-pointer reversal. Walk the list with `prev`, `curr`, and a cached `next`. On each step, save `next = curr->next`, flip `curr->next = prev`, then slide both forward. When `curr` is null, `prev` is the new head. Cache before you flip, every time, or you lose the rest of the chain.
- Reverse a sublist between positions `m` and `n`. Walk to the node before `m`, reverse exactly `n - m + 1` nodes, then reconnect the reversed segment to the part before `m` and the part after `n`. A dummy head removes the special case when `m == 1`.
- Reverse nodes in k-group. Count off `k` nodes; if a full group exists, reverse it and recurse or iterate on the rest; if fewer than `k` remain, leave them as-is. The bookkeeping is connecting each reversed group's new tail to the next group's new head.
- The four bugs that show up every time: losing the tail of the reversed part, forgetting to null-terminate the new tail (which silently keeps a stale `next` and creates a cycle), reconnecting in the wrong order, and miscounting the group boundary by one.
- Optional elegance: a pointer-to-pointer (`Node**`) walk lets you rewire without a separate dummy head. Show it once. It is clean but harder to read under interview pressure, so most students keep the explicit dummy.

```cpp
// The whole pattern in five lines. Internalize this.
Node* reverse(Node* head) {
    Node* prev = nullptr;
    while (head) {
        Node* next = head->next;   // cache before rewiring
        head->next = prev;         // flip the link
        prev = head;               // slide prev forward
        head = next;               // slide curr forward
    }
    return prev;                   // new head; old head is now null-terminated
}
```

### Patterns

- [In-place linked-list reversal](../docs/patterns.md)

### In-class problems

- Reverse Linked List
- Reverse Linked List II (sublist)
- Swap Nodes in Pairs
- Reverse Nodes in k-Group

---

## Lecture 20 — Doubly Linked Lists, std::list, and the LRU Cache

### Objectives

- Build a doubly linked list with `prev`/`next` and dual sentinels for O(1) deletion given a node.
- Contrast `std::list` (O(1) splice, no random access, cache-hostile) with `std::vector`.
- Combine a hashmap with a doubly linked list to implement an O(1) LRU cache.

### Topics covered

- The node grows a back-pointer: `struct Node { Node* prev; int value; Node* next; }`. With `prev`, deleting a node you already hold is O(1): you splice it out by touching its two neighbors, no walk required. Insert and remove at both ends are O(1) too.
- Dual sentinels. Put one dummy node at the head and one at the tail so every real node always has a non-null `prev` and `next`. Boundary logic disappears: there is no "is this the first node" or "is this the last node" branch anywhere in the code.
- Rewiring order matters. Set the new node's `prev` and `next` first, then redirect the neighbors to point at it, and always update both directions. Touch the neighbors first and you can lose the node you are trying to insert.
- `std::list` is a doubly linked list. It gives you O(1) `splice` and stable iterators that survive insertions and deletions elsewhere, which `vector` does not. It pays for that with no random access and poor cache locality, since the nodes are scattered. `std::forward_list` is the singly linked, lower-overhead cousin. Mention both, default to neither without a reason.
- The LRU cache. Keep a hashmap from key to the DLL node holding that key's value. On access, read through the map in O(1), then move that node to the front of the list to mark it most-recently-used. On insert past capacity, evict the node at the back (least-recently-used) and erase its key from the map. Map plus list, both ends O(1).
- The honest trade-off. For mid-list insertions on small or medium data, a `vector` often beats `std::list` outright because contiguous memory and cache locality dominate the asymptotic O(n) shift. Know the textbook answer and know when the textbook is wrong.

```cpp
// DLL splice-out with sentinels: O(1), no edge cases.
void remove(Node* node) {            // node is a real node, never a sentinel
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

void insertFront(Node* node) {       // just after the head sentinel
    node->next = head->next;
    node->prev = head;
    head->next->prev = node;         // set the new node's links first...
    head->next = node;               // ...then redirect the neighbor
}
```

### Patterns

- [Hashing for dedup/lookup](../docs/patterns.md) (paired with a doubly linked list in the LRU cache)

### In-class problems

- Design Linked List (doubly)
- LRU Cache (hashmap + DLL, O(1))
- Flatten a Multilevel Doubly Linked List
- Copy List with Random Pointer (hashing + list)

---

## Homework

Work these between lectures. The warmups confirm you have the mechanics; the core set is the real practice; the challenges are where this week's milestone is won. Solutions for most are worked on camera. See the full bank in [problems/README.md](../problems/README.md).

### Warmup

- Reverse Linked List
- Middle of the Linked List
- Merge Two Sorted Lists

### Core

- Remove Nth Node From End of List
- Linked List Cycle II
- Palindrome Linked List
- Odd Even Linked List
- Reverse Linked List II

### Challenge

- Reverse Nodes in k-Group
- LRU Cache

A note on Palindrome Linked List: it is the week in one problem. Find the middle with fast/slow, reverse the second half in place, compare the two halves, and (if you are being tidy) reverse the second half back. It exercises every technique from the week in a single O(1)-space pass.

---

## Before next week

- [ ] Your singly linked list class compiles, uses a dummy head, and its iterative destructor frees a long list without crashing. `debug_verify_data_integrity` passes.
- [ ] You can write the three-pointer `reverse` from memory in under two minutes, with no reference.
- [ ] You can implement cycle detection and find the cycle's start, and explain in one sentence why resetting a pointer to the head works.
- [ ] Your LRU cache has `get` and `put` both running in O(1), backed by a hashmap and a doubly linked list with sentinels.
- [ ] You can state, without hedging, one concrete case where `std::vector` beats `std::list` and why.

Next week the linked list becomes the backing store for restricted-access ADTs: stacks, queues, deques, and the monotonic stack. The list mechanics you drilled here are what make those build cleanly. See [Week 6](week-06.md), and the [course overview](../README.md) for where this fits.
