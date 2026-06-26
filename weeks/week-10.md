# Week 10 — Binary Heaps, Priority Queues, and Heap Patterns

You build a binary heap from scratch this week: sift-up, sift-down, the O(n) build-heap, and heapsort. Then you switch to `std::priority_queue` and get its inverted comparator right the first time instead of the third. The back half is pure pattern drilling on the three things heaps actually buy you in interviews: top-K, two heaps for a streaming median, and K-way merge.

By Friday you can reach for a heap the moment a problem mentions "K largest," "median of a stream," or "merge K sorted," and you can explain why each one wants a heap and not a sort.

## By the end of this week

- State the two heap properties, shape (a complete binary tree) and partial order (parent before children), and explain why a partial order is cheaper to maintain than a fully sorted structure.
- Implement `push` (sift-up), `pop`/`extract` (sift-down), and `top` on an array-backed heap, with the index math memorized: parent `(i-1)/2`, children `2i+1` and `2i+2`.
- Derive why Floyd's build-heap is O(n) and not O(n log n), using the telescoping sum over level heights.
- Implement in-place heapsort and characterize it honestly: O(n log n), in-place, unstable.
- Name what a heap is bad at: arbitrary search is O(n), there's no sorted iteration, and there's no built-in decrease-key.
- Use `std::priority_queue` (a max-heap by default) and build a min-heap with `greater<>` or a custom comparator, knowing the comparator returns true for the element with *lower* priority.
- Solve Top-K with a size-K heap and get the counterintuitive direction right: a min-heap for the K largest, a max-heap for the K smallest.
- Maintain a running median with a max-heap over the lower half and a min-heap over the upper half, kept balanced so the two tops straddle the middle.
- Merge K sorted sequences with a min-heap of current heads in O(N log K).
- Read a problem's signal words and pick the right heap pattern without trial and error.

The week's milestone: build a from-scratch binary heap with an O(n) build-heap and a working heapsort, then solve a streaming-median problem with two heaps and a merge-k-sorted-lists problem with a K-way-merge heap, all benchmarked and assert-tested.

Patterns this week: [Top-K Elements](../docs/patterns.md), [Two Heaps](../docs/patterns.md), and [K-Way Merge](../docs/patterns.md).

---

## Lecture 37 — Binary Heaps: Structure, Sift-Up, Sift-Down

A heap keeps the minimum (or maximum) at your fingertips for O(1) read and O(log n) update, and it does it with a plain array and no pointers. Before you ever type `priority_queue`, you build the thing so you know exactly what it costs.

### Objectives

- State the two heap properties (complete-tree shape plus partial heap order) and explain why a partial order is cheaper than a full order.
- Implement `push` (sift-up) and `pop`/`extract` (sift-down) in O(log n) on an array-backed heap.
- Use the array-as-tree index math: parent `(i-1)/2`, children `2i+1` and `2i+2`.

### Topics

- Two properties, both required. The shape property says the tree is a *complete* binary tree: every level full except possibly the last, which fills left to right. That completeness is exactly what lets the heap live in a contiguous array with no gaps. The order property (for a min-heap) says every parent is `<=` its children. Note what it does *not* say: siblings are unordered, and the structure is nowhere near fully sorted. That partial order is the whole point. Maintaining "parent before children" costs O(log n) per update; maintaining a total order would cost more and you don't need it to answer "what's the minimum."
- Array representation. Store the tree level by level in an array. From index `i`: parent is `(i-1)/2`, left child is `2i+1`, right child is `2i+2`. No node pointers, no allocation per element, and the layout is cache-friendly because you walk contiguous memory.
- `push` is append-then-sift-up. Put the new value at the end (preserving completeness), then bubble it up: while it's smaller than its parent, swap. It rises at most the height of the tree, so O(log n).
- `pop` is swap-then-shrink-then-sift-down. Save the root (the answer), move the last element to the root, shrink the array by one, then push that element down: repeatedly swap it with its smaller child until both children are `>=` it. Again O(log n).
- `top` is O(1). It's just `a[0]`.
- Min-heap versus max-heap is one comparison flipped. You convert between them either by negating values on the way in and out, or by flipping the comparator. The structure and the logic are identical otherwise.

### In-class problems

- Implement a binary min-heap (`push`/`pop`/`top`) from scratch
- Last Stone Weight
- Kth Largest Element in a Stream
- Sift-down a single element into a valid heap

---

## Lecture 38 — Build-Heap, Heapsort, and Heap Limitations

Two results that surprise people: you can heapify an arbitrary array in O(n), not O(n log n), and the same machinery gives you a sort with no quadratic worst case. Then the honest part, the things a heap simply can't do, so you don't reach for one when it's the wrong tool.

### Objectives

- Derive why Floyd's build-heap is O(n), not O(n log n).
- Implement in-place heapsort and characterize it as O(n log n), in-place, and unstable.
- Recognize heap limitations: no efficient arbitrary search, no ordered iteration, no built-in decrease-key.

### Topics

- Floyd's build-heap. Start from the last internal node at index `n/2 - 1` and sift-down each node back to index 0. Going bottom-up matters: when you sift-down a node, both its subtrees are already valid heaps, so the operation is sound.
- The O(n) proof. The naive bound says n nodes times O(log n) each, giving O(n log n). That's a real upper bound, just loose. Most nodes are near the bottom and can only sift a short distance. A node at height `h` does O(h) work, and there are at most `ceil(n / 2^(h+1))` nodes at height `h`. Summing gives `n * sum over h of h / 2^(h+1)`, and that series converges to a constant (it's `sum h/2^h = 2`). So the total is O(n). The savings come from counting work by node height instead of charging every node the full tree height.
- Heapsort. Build a max-heap in O(n). Then repeatedly swap the root (the current maximum) to the end of the array, shrink the heap by one, and sift-down the new root. After n-1 rounds the array is sorted ascending, in place. Building is O(n) and the n sift-downs are O(log n) each, so O(n log n) overall.
- Heapsort versus quicksort. Heapsort has a guaranteed O(n log n) worst case where quicksort can degrade to O(n^2). In practice quicksort is usually faster anyway because of better constants and far friendlier cache behavior: heapsort's parent/child jumps scatter across memory, while quicksort scans contiguously. Heapsort is also unstable. Know the trade, and know why `std::sort` is introsort (quicksort that falls back to heapsort to dodge the worst case).
- Heap weaknesses, stated plainly. Searching for an arbitrary value is O(n), because the partial order tells you nothing about where a non-extreme element sits. There's no sorted iteration; the array order is not sorted order. And there's no built-in decrease-key.
- Working around the missing decrease-key. To support it you need a position map from element to its current index so you can find the node and sift it. A common shortcut in interview code is lazy deletion: push the updated entry as a duplicate and skip stale entries when you pop them. You'll see exactly this in Dijkstra in the graphs week.

### In-class problems

- Implement build-heap in O(n) and prove the bound
- Heapsort from scratch (ascending via max-heap)
- Convert a min-heap to a max-heap
- Show heap search is O(n) with a counterexample

---

## Lecture 39 — std::priority_queue, Top-K, and the Comparator Trap

Now switch to the STL and treat it as the default. `std::priority_queue` is the heap you'll actually ship. The catch is the comparator: it's backwards from what most people expect, and getting it wrong gives you a max-heap when you wanted a min-heap. This is also where the Top-K pattern lands, with its own counterintuitive twist.

### Objectives

- Use `std::priority_queue` (a max-heap by default) and build a min-heap with `greater<>` and custom comparators.
- Solve Top-K with a size-K heap, getting the counterintuitive direction right (a min-heap for the K largest).
- Avoid the comparator inversion bug where the comparator defines *lower* priority.

### Topics

- The API. `std::priority_queue<int>` is a max-heap: `top()` is the largest, `push`/`pop` are O(log n), `top` is O(1). For a min-heap, spell out all three template arguments: `priority_queue<int, vector<int>, greater<int>>`.
- The comparator trap. The comparator you pass answers "does a come before b in sort order," and the element that sorts *last* ends up on top. So `less<>` (the default) puts the largest on top, and `greater<>` puts the smallest on top. The mental rule: the comparator returns true for the element with *lower* priority. People write the comparison the way they'd write it for `std::sort` and get an upside-down heap. Decide the direction you want, then sanity-check `top()` on a tiny example before trusting it.
- Custom comparators. For a `struct` or a tuple, pass a comparator functor or a lambda. With a lambda you must give the type to the template and the instance to the constructor: `priority_queue<T, vector<T>, decltype(cmp)> pq(cmp);`.
- Top-K, and the direction that trips everyone. To keep the K *largest* elements, use a *min-heap* of size K. Push each element; whenever the size exceeds K, pop the smallest. What survives is the K largest, and the heap's top is the Kth largest. This runs in O(n log K) time and O(K) space, which beats sorting (O(n log n)) when K is much smaller than n. The instinct to use a max-heap for "largest" is the trap: a max-heap of size K would let you pop the largest, which is the opposite of what you want.
- Top-K frequent. Count with a hash map, then run the same size-K heap over the (value, count) pairs keyed on count. Same pattern, one preprocessing step in front.
- Related tools. `make_heap`, `push_heap`, and `pop_heap` heapify and update a range in place when you want heap behavior on an existing container without the `priority_queue` wrapper. And when you only need the K elements unordered, not maintained over a stream, `std::nth_element` partitions around the Kth element in O(n) average time, which is faster than a heap for the static, one-shot case.

### Patterns

- [Top-K Elements](../docs/patterns.md)

### In-class problems

- Kth Largest Element in an Array
- Top K Frequent Elements
- K Closest Points to Origin
- Sort Characters by Frequency

---

## Lecture 40 — Two Heaps, K-Way Merge, and Heap Synthesis

The two patterns that make heaps feel powerful. Two heaps gives you a running median over a stream in O(log n) per insert. K-way merge collapses K sorted sequences into one in O(N log K). We close by tying the week's patterns to the signal words that should trigger each one.

### Objectives

- Maintain a running median with a max-heap (lower half) and a min-heap (upper half), balanced so the tops straddle the middle.
- Merge K sorted sequences with a min-heap of current heads in O(N log K).
- Choose the right heap pattern from a problem's signal words.

### Topics

- Two heaps. Split the stream into a lower half and an upper half. The lower half lives in a max-heap, so its top is the largest of the small numbers. The upper half lives in a min-heap, so its top is the smallest of the large numbers. Keep the sizes balanced (equal, or the lower half one larger), and the median is either the max-heap's top or the average of the two tops. Each insert is O(log n): add to one heap, then rebalance by moving one element across if the sizes drift apart by more than one.
- The rebalance is where bugs live. A clean rule: push to the max-heap, move its top to the min-heap, then if the min-heap is now larger, move its top back. That keeps the order invariant (every lower-half element `<=` every upper-half element) and the size invariant in a fixed sequence of steps.
- K-way merge. Seed a min-heap with the first element of each of the K sequences, tagged with which sequence it came from. Pop the global minimum, append it to the output, then push the *next* element from that same sequence. Repeat until the heap is empty. The heap never holds more than K items, so each of the N total elements costs O(log K), giving O(N log K). This is exactly merge sort's merge step generalized from 2 lists to K.
- Connection back to merge sort. The 2-way merge you wrote for merge sort is the K=2 case. The heap is what makes "pick the smallest current head" efficient when there are more than two heads to compare.
- Pattern triggers, said once so they stick. "Median," "balance," or "two halves of a stream" points to two heaps. "K largest" or "K smallest" points to Top-K. "Merge K sorted" or "K sorted lists/arrays/matrix" points to K-way merge. Reading these signals correctly is most of the battle in the heap section of an interview.

### Patterns

- [Two Heaps](../docs/patterns.md)
- [K-Way Merge](../docs/patterns.md)
- [Top-K Elements](../docs/patterns.md)

### In-class problems

- Find Median from Data Stream
- Merge k Sorted Lists
- Kth Smallest Element in a Sorted Matrix
- Find K Pairs with Smallest Sums

---

## Homework

Work these between lectures, in roughly this order. The warmups confirm the mechanics are in your hands; the core set is the week's real practice; the challenges combine two ideas at once.

**Warmup**

- Last Stone Weight
- Kth Largest Element in a Stream
- Sort Characters by Frequency

**Core**

- Kth Largest Element in an Array
- Top K Frequent Elements
- K Closest Points to Origin
- Task Scheduler
- Reorganize String
- Implement a binary min-heap with build-heap from scratch

**Challenge**

- Find Median from Data Stream
- Merge k Sorted Lists
- Kth Smallest Element in a Sorted Matrix

---

## Before next week

- You can implement an array-backed min-heap from scratch (`push`, `pop`, `top`) with the parent/child index math correct, and you can write sift-up and sift-down without looking them up.
- You can explain why build-heap is O(n) using the height-weighted sum, and you can implement heapsort and state that it's O(n log n), in-place, and unstable.
- You can name what heaps are bad at: O(n) arbitrary search, no sorted iteration, no built-in decrease-key, and what the position-map and lazy-deletion workarounds do about the last one.
- You can use `std::priority_queue`, build a min-heap with `greater<>` or a custom comparator, and you no longer write the comparator backwards.
- You can solve Top-K with a size-K heap in the right direction, run a streaming median with two heaps, and merge K sorted sequences with a K-way-merge heap.
- The week's homework is done, and you can read a new problem and name the heap pattern (Top-K, two heaps, or K-way merge) before you start coding.

If any of those is shaky, rework that lecture's problems before Week 11. The lazy-deletion and position-map ideas come back in Dijkstra.

---

Back to the [course README](../README.md) · Pattern reference: [docs/patterns.md](../docs/patterns.md)
