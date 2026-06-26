# Week 3 — Arrays, Strings & the Linear-Scan Patterns

This is your first contact with a concrete data structure. You build a `vector<T>` by hand so you understand size versus capacity, amortized `push_back`, and exactly when a pointer or iterator goes stale. Then you drill the three patterns that turn a brute-force nested loop into a single O(n) pass over contiguous memory: two pointers, prefix sums, and sliding window.

Everything this week lives in a flat array or a string. That is the point. Before you touch a pointer-based structure in Week 5 or a tree in Week 8, you should be able to scan a line of memory and answer a range, pair, or subarray question without a second loop.

## By the end of this week

You should be able to:

- Implement a `Vector<T>` from scratch with `new[]`/`delete[]`, a doubling `grow()`, and an amortized O(1) `push_back`, and explain the amortized argument out loud.
- State the cost of every vector operation cold: O(1) random access, O(1) amortized append, O(n) insert/erase at an arbitrary position, O(n) worst-case single append on a reallocation.
- Predict when an iterator, pointer, or reference is invalidated by reallocation, insert, or erase, and spot the bug in a loop that mutates while it iterates.
- Recognize and write the two-pointer pattern in both forms: opposite-ends on a sorted array, and same-direction slow/fast read-write for in-place compaction.
- Precompute 1D and 2D prefix sums to answer any range or submatrix sum in O(1), with correct `n+1` sizing and `long long` to avoid overflow.
- Combine a prefix sum with a hashmap to count subarrays with a target sum in O(n).
- Apply both window styles: a fixed-size window with an incrementally updated aggregate, and a variable window that expands right and shrinks left until valid.
- Reduce an "exactly K" window question to `atMost(K) - atMost(K-1)`.

The milestone for the week: dynamic-array internals and invalidation are second nature, and you can recognize and implement two pointers, prefix sums, and sliding window on arrays and strings in O(n).

The patterns introduced this week are documented in the [pattern reference](../docs/patterns.md): [Two pointers](../docs/patterns.md), [Prefix sums](../docs/patterns.md), and [Sliding window](../docs/patterns.md). Keep it open while you solve.

---

## Lecture 9 — Dynamic Arrays: `vector<T>` Internals & Iterator Invalidation

You cannot reason about the cost of anything built on top of an array until you know what a dynamic array actually does when it runs out of room. So we build one.

### Objectives

- Build a `Vector<T>` by hand with `new[]`/`delete[]` and a doubling `grow()`, and explain why `push_back` is amortized O(1).
- Distinguish size from capacity, and separate the cost of insert/erase (O(n) shifting) from random access (O(1)).
- Predict iterator, pointer, and reference invalidation on reallocation, insert, and erase.

### Topics covered

- Size versus capacity. Geometric growth (doubling, or ×1.5) and why a constant multiplier is what makes the amortized argument work. The aggregate argument for amortized O(1) `push_back`, and the O(n) worst-case single append that triggers a reallocation.
- O(n) insert and erase at an arbitrary position because elements have to shift. O(1) random access as a `base + offset` computation.
- The hand-built `Vector<T>`: `grow()` allocates a bigger block, copies the old elements, then frees the old block. `debug_verify_data_integrity()` and `debug_to_string()` to check your work as you go.
- Iterator invalidation rules. `reserve()` to pay the copy cost up front and amortize it away. `v[i]` is undefined behavior out of bounds; `v.at(i)` throws.
- The professional details: `vector<bool>` is a bit-packed specialization (and why that surprises people), `emplace_back` versus `push_back`, move-on-grow and why a `noexcept` move constructor matters here, and `'\n'` over `std::endl` in hot loops.

### Patterns

None introduced. This lecture is the substrate the rest of the week stands on.

### In-class problems

- Implement `Vector<T>` with a doubling `push_back` and the debug methods.
- Remove Element (in place).
- Move Zeroes.
- Spot the iterator-invalidation bug in a `push_back`-while-iterating loop.

---

## Lecture 10 — Two Pointers: Opposite-Ends & Read/Write

One nested loop becomes one linear pass. The two-pointer pattern shows up in two distinct shapes, and you need to recognize both on sight.

### Objectives

- Apply the opposite-ends technique on a sorted array to replace an O(n²) nested loop with an O(n) pass.
- Apply the same-direction slow/fast read-write technique for in-place compaction and deduplication.
- Recognize the sorted or monotonic precondition the sum variant needs, and avoid signed/unsigned underflow.

### Topics covered

- Opposite-ends: pair-sum on a sorted array, reversing in place, palindrome checks, and container-with-most-water. Two pointers start at the two ends and move toward each other based on a comparison.
- Same-direction read/write: a `read` pointer scans every element while a `write` pointer marks where the next kept element goes. This is how you do in-place removal and dedup without a second array.
- The sum variant requires a sorted or otherwise monotonic property. Without it, moving a pointer tells you nothing, and you are back to brute force or a hash table.
- Prefer index-based pointers over iterators here so the bounds logic stays obvious. Watch for `size_t` underflow when a pointer would go below zero.

### Patterns

- [Two pointers](../docs/patterns.md)

### In-class problems

- Two Sum II — Input Array Is Sorted.
- Valid Palindrome.
- Container With Most Water.
- Remove Duplicates from Sorted Array.

---

## Lecture 11 — Prefix Sums: 1D, 2D & Prefix-Sum + Hashmap

If you are answering many range-sum queries on a fixed array, recomputing each one is wasteful. Precompute once, answer each query in O(1).

### Objectives

- Precompute prefix sums so any range sum answers in O(1), with correct `n+1` sizing and `long long` to avoid overflow.
- Extend the idea to 2D prefix sums for submatrix queries.
- Combine prefix sums with a hashmap, seeded with `{0: 1}`, to count subarrays whose sum equals K.

### Topics covered

- The recurrence `pre[i] = pre[i-1] + a[i]`, and the range sum over `[i, j]` as `pre[j+1] - pre[i]`.
- The off-by-one that trips everyone: use `n+1` entries with `pre[0] = 0` so the empty prefix has a slot. Use `long long` on large arrays because the running total overflows `int` fast.
- 2D prefix sums for submatrix totals, using inclusion-exclusion to combine four corners.
- Prefix sum plus `unordered_map` for subarray-sum-equals-K. Why the `{0: 1}` seed is required (it accounts for subarrays that start at index 0). Product-of-array-except-self as a prefix/suffix pass with no division.

### Patterns

- [Prefix sums](../docs/patterns.md)

### In-class problems

- Range Sum Query — Immutable.
- Subarray Sum Equals K (prefix sum + hashmap).
- Product of Array Except Self.
- Range Sum Query 2D — Immutable.

---

## Lecture 12 — Sliding Window: Fixed & Variable

A window is a contiguous range you slide across the array, updating a running aggregate instead of recomputing it from scratch. Get the template right once and a large class of substring and subarray problems collapses to O(n).

### Objectives

- Apply a fixed-size window with an incrementally updated aggregate, so you never recompute the whole window.
- Apply a variable-size window: expand right, then shrink left with a `while` (not an `if`) until the window is valid again, recording the answer as you go.
- Track window state with a frequency array or map, and reduce an "exactly K" question to `atMost(K) - atMost(K-1)`.

### Topics covered

- Fixed window: a running sum or running max over a window of size k, updated by adding the entering element and removing the leaving one.
- Variable window: grow the right edge, and while the window is invalid, shrink the left edge. The expand / shrink / record template that every variable-window problem follows.
- Window state as either a single running aggregate or a frequency map/array. The reason shrinking uses `while` and not `if`: one new element can force several removals before the window is valid again.
- Never recompute the aggregate from scratch inside the loop; that quietly turns O(n) back into O(n²). For character windows, an `int freq[128]` or `freq[26]` beats a hashmap. Prune zero entries when you need `map.size()` to reflect the count of distinct characters.

### Patterns

- [Sliding window](../docs/patterns.md)

### In-class problems

- Maximum Average Subarray I (fixed window).
- Longest Substring Without Repeating Characters.
- Minimum Size Subarray Sum.
- Permutation in String.

---

## Homework

Solve these between lectures. They are grouped by difficulty, not by lecture, so part of the work is deciding which pattern each one wants. Most map directly to a pattern from this week; a couple combine two.

### Warmup

- **Squares of a Sorted Array** — two pointers from the ends, merging inward.
- **Sort Colors / Dutch National Flag** — three-way partition with a same-direction pointer trio.

### Core

- **3Sum** — sort, then fix one element and run opposite-ends two pointers on the rest.
- **Find Pivot Index** — a prefix-sum identity, no extra array needed.
- **Longest Repeating Character Replacement** — variable window keyed on the most frequent character in the window.

### Challenge

- **Subarray Sums Divisible by K** — prefix sums plus a hashmap, counting by remainder (mind negative mods in C++).
- **Minimum Window Substring** — variable window with a need/have count over a frequency map.
- **Trapping Rain Water (two-pointer version)** — opposite-ends pointers tracking left-max and right-max.

The full set, with links and the running pattern tally, is in the [problem bank](../problems/README.md).

---

## Before next week

- [ ] Your `Vector<T>` compiles, runs, and passes `debug_verify_data_integrity()` after a sequence of `push_back`, `insert`, and `erase` calls.
- [ ] You can explain the amortized O(1) `push_back` argument without notes, and say what `reserve()` changes.
- [ ] You can state from memory which operations invalidate iterators, pointers, and references, and why.
- [ ] You can write both two-pointer shapes (opposite-ends and read/write) and the variable-window template from a blank file, without looking them up.
- [ ] You finished every Warmup and Core problem, and attempted at least two Challenge problems.

If any box is unchecked, rework that piece before Week 4. Hashing in Week 4 leans on the same scanning instincts, and cyclic sort reuses the in-place read/write idea you drilled here.

Back to the [course README](../README.md).
