# Week 6 — Restricted-Access ADTs: Stacks, Queues, Deques & Monotonic Stack

This week is about structures that deliberately give you less. A stack only lets you touch the top, a queue only the two ends, and that restriction is exactly what makes them fast and what makes certain problems collapse into a single linear pass. You build each one by hand both array- and list-backed, switch to `std::stack`, `std::queue`, and `std::deque` as the professional default, implement a circular (ring-buffer) queue, and then drill the monotonic stack and monotonic deque until next-greater and sliding-window problems feel mechanical. A short sparse-matrix build closes the linear-structures unit and sets up the array view of trees you meet next.

Back to the [course README](../README.md). Pattern reference: [docs/patterns.md](../docs/patterns.md).

## By the end of this week

- Implement a LIFO stack two ways, vector-backed and singly-list-backed, with O(1) `push`, `pop`, and `top`, and explain why each is O(1).
- Implement a FIFO queue with O(1) `enqueue`, `dequeue`, and `front`, and a fixed-size circular queue that reuses its buffer with modular indexing.
- Use `std::stack`, `std::queue`, and `std::deque` correctly, including the container-adaptor design and the `void pop()` gotcha (read `top()`/`front()` first).
- Recognize when a problem wants a monotonic stack, pick the right direction (increasing vs decreasing), decide whether to store indices or values, and solve it in amortized O(n).
- Apply a monotonic deque to sliding-window maximum in O(n).
- Build a coordinate (list-of-triples) sparse matrix and state when it beats a dense 2D array.
- Choose between stack, queue, deque, and the monotonic variants under timed conditions from the signal in the problem statement.

The week's milestone: hand-built array- and list-backed stack and queue classes, a working circular queue, and a sparse-matrix representation, with fluent monotonic stack and monotonic deque under timed conditions.

---

## Lecture 21 — Stacks: Array-Backed, List-Backed, and Expression Evaluation

A stack is the smallest interesting data structure. One end, three operations, all constant time. We build it twice so you see that the abstract behavior is independent of the storage, then spend the rest of the lecture on the application that justifies the structure: parsing.

**Objectives**

- Implement a LIFO stack two ways, vector-backed and singly-list-backed, with O(1) `push`, `pop`, and `top`.
- Use `std::stack` and understand its container-adaptor design and its `void pop()`.
- Apply stacks to balanced parentheses and expression evaluation: postfix evaluation, and infix to postfix.

**Topics covered**

- LIFO semantics. `push`, `pop`, `top`, `empty`, all O(1).
- Array-backed stack: `push_back`/`pop_back` on a vector inherits the vector's amortized O(1) growth.
- List-backed stack: insert and remove at the head of a singly linked list, O(1) with no resizing.
- `std::stack` as an adaptor over `std::deque` by default. `pop()` returns `void`, so read `top()` before you `pop()`.
- Guarding `top()` and `pop()` against an empty stack. Calling either on empty is undefined behavior, so check `empty()` first.
- Applications: balanced brackets, postfix (RPN) evaluation, infix to postfix conversion, and simulating a call stack.
- Tie-back: a stack is the explicit, data-structure form of the call stack that recursion uses implicitly. Anything recursive can be rewritten with an explicit stack, which is the bridge from Week 2.

**Patterns**

- [Stack for parsing / matching](../docs/patterns.md)

**In-class problems**

- Valid Parentheses
- Min Stack
- Evaluate Reverse Polish Notation
- Simplify Path

---

## Lecture 22 — Monotonic Stack: Next Greater, Span, and Histogram

The monotonic stack is one of the most useful patterns in the whole course, and the first time most students see it they assume it is O(n²) because of the inner pop loop. It is not. Each element is pushed once and popped once, so the total work is O(n) no matter how the loop looks. Getting that argument into your bones is the point of this lecture.

**Objectives**

- Maintain a monotonically increasing or decreasing stack so that each element is pushed and popped at most once, giving O(n).
- Choose the correct monotonic direction, and decide whether to store indices or values for distance queries.
- Solve next-greater, daily-temperatures, and largest-rectangle problems, using sentinels to flush the stack at the end.

**Topics covered**

- The monotonic stack invariant: before pushing the incoming element, pop everything that violates the order, and resolve each popped element against the incoming one.
- Increasing vs decreasing direction: which one you keep determines whether you are answering next-greater or next-smaller.
- Storing indices rather than values when the answer is a distance, for example "how many days until a warmer temperature."
- Sentinel seeding and post-processing for leftover elements. In the histogram, pushing a trailing bar of height 0 flushes everything still on the stack so no rectangle is missed.
- Amortized analysis: each element is pushed at most once and popped at most once, so the loop is O(n) total even though any single step can pop many items.

**Patterns**

- [Monotonic stack](../docs/patterns.md)

**In-class problems**

- Next Greater Element I
- Daily Temperatures
- Next Greater Element II (circular)
- Largest Rectangle in Histogram

---

## Lecture 23 — Queues, Circular Queue (Ring Buffer), Deque & Monotonic Deque

Queues look like stacks turned around, but the naive implementation hides a trap. Shifting an array down on every dequeue is O(n) per operation, which is the kind of mistake that passes small tests and dies in production. The fix is the ring buffer, and once you have a double-ended queue the monotonic technique from yesterday extends straight to sliding windows.

**Objectives**

- Implement a FIFO queue (list-backed, with head and tail pointers) and a fixed-size circular queue using modular indexing.
- Use `std::queue` and `std::deque`, and know that a `deque` has a segmented, non-contiguous layout.
- Apply a monotonic deque to sliding-window maximum in O(n).

**Topics covered**

- FIFO semantics: `enqueue`, `dequeue`, `front`, all O(1) when done right. A queue that shifts the array on each dequeue is O(n) per dequeue, which is the thing to avoid.
- Circular queue: a fixed buffer with `head`, `tail`, and either an explicit `count` or modular arithmetic. The full-vs-empty ambiguity when `head == tail` is the detail everyone gets wrong once, resolved with a count or a reserved empty slot.
- `std::queue` as an adaptor, backed by `std::deque` by default. Its `pop()` also returns `void`, so read `front()` first.
- `std::deque`: O(1) at both ends and O(1) random access, but not stored contiguously, so there is no `.data()` and no pointer arithmetic across the whole structure.
- Monotonic deque: pop weaker candidates off the back, pop out-of-window indices off the front, and the front always holds the current window's answer.
- `std::priority_queue` exists and is the heap-backed cousin, but the heap itself is deferred to the trees track in Week 10.

**Patterns**

- [Deque / monotonic queue](../docs/patterns.md)
- [Monotonic stack](../docs/patterns.md)

**In-class problems**

- Design Circular Queue
- Implement Queue using Stacks
- Sliding Window Maximum (monotonic deque)
- Number of Recent Calls (sliding queue)

---

## Lecture 24 — Sparse Matrices + Stack/Queue Capstone & Mixed Drill

The last lecture does two jobs. First, sparse matrices: a quick, practical structure that makes the case for indexed storage and previews the array-as-tree idea from next week. Second, a timed mixed drill, because knowing each ADT in isolation is not the skill that matters. The skill is reading a problem and naming the right one fast.

**Objectives**

- Build a small sparse-matrix representation (coordinate, list-of-triples) and reason about when it beats a dense 2D array.
- Consolidate stack vs queue vs deque selection on a mixed problem set.
- Run a timed mixed mock-interview drill across the week's restricted-access ADTs.

**Topics covered**

- Sparse-matrix motivation: a dense 2D array spends O(rows × cols) space even when almost every cell is zero, which is wasteful for mostly-empty data.
- Coordinate representation: store only the non-zeros as `(row, col, value)` triples, then build, store, and query against that list.
- Indexed-array thinking as the bridge to the array representation of a binary tree you meet in Week 8 (parent at `i`, children at `2i+1` and `2i+2`).
- Decision drill: read the signal in a problem statement and map it to the ADT. "Most recent / undo / matching" points to a stack; "first come first served / level order" to a queue; "both ends / window extremes" to a deque or monotonic deque.
- Track capstone review plus a timed mixed mock-interview set spanning everything from Lecture 21 on.

**Patterns**

- [Monotonic stack](../docs/patterns.md)
- [Stack for parsing / matching](../docs/patterns.md)
- [Deque / monotonic queue](../docs/patterns.md)

**In-class problems**

- Build and query a sparse matrix (triple representation)
- Asteroid Collision (stack)
- Implement Stack using Queues
- Basic Calculator II (stack parsing)

---

## Homework

Do these between lectures, not in one sitting. Warmups confirm the mechanics, Core is where the week's real practice is, and the Challenge problems are the ones worth struggling with before you look anything up.

### Warmup

- Valid Parentheses
- Implement Queue using Stacks

### Core

- Min Stack
- Evaluate Reverse Polish Notation
- Daily Temperatures
- Next Greater Element II
- Design Circular Queue
- Asteroid Collision

### Challenge

- Largest Rectangle in Histogram
- Sliding Window Maximum

---

## Before next week

- Your array-backed and list-backed stack classes both compile and pass their asserts, and you can say why each operation is O(1).
- Your list-backed queue and your circular queue both work, and you can explain how you resolve the `head == tail` full-vs-empty ambiguity.
- You can write a monotonic stack from a blank file without copying, and explain the push-once/pop-once argument for O(n) out loud.
- Sliding Window Maximum runs in O(n) with a monotonic deque, not O(n·k).
- You can look at a fresh problem and name stack, queue, deque, or monotonic in under a minute. If you can't yet, redo the Lecture 24 decision drill.
- Skim the [pattern reference](../docs/patterns.md) entries for the three patterns above before Week 7 moves on to sorting and binary search.
