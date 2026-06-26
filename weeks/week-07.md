# Week 7 — Sorting, Divide & Conquer, and Binary Search (incl. on the Answer)

[← Back to the syllabus](../README.md) · [Pattern reference](../docs/patterns.md)

This is the first heavy algorithms week. You implement the whole sorting family by hand (selection and insertion, merge, quick, heap, counting and radix), get stability right, and learn when to stop reinventing and reach for `std::sort`. Then you formalize divide and conquer and master binary search, including the predicate framework and binary search on the answer. Loop invariants and comparator correctness run through every lecture, because most sorting and searching bugs are invariant bugs in disguise.

## By the end of this week

- Implement merge, quick, heap, counting, and radix sort from scratch, and state for each one whether it is stable, in-place, and what its time and space costs are.
- State and prove the loop invariant for selection, bubble, and insertion sort, and explain why a comparator in `std::sort` must be a strict weak ordering (and why `<=` is undefined behavior).
- Use quickselect for average `O(n)` kth-element selection, and explain the decision-tree argument for the `Ω(n log n)` comparison-sort lower bound.
- Use `std::sort`, `std::stable_sort`, and `std::nth_element` correctly, and apply "sort first, then sweep" as a deliberate preprocessing pattern.
- Write a binary search that terminates and is off-by-one-free using a fixed interval convention and the overflow-safe midpoint, and reframe it as finding the boundary in a monotonic `F...FT...T` predicate.
- Apply binary search on the answer to minimize-the-maximum problems, and analyze divide-and-conquer recurrences with the Master Theorem.

---

## Lecture 25 — Elementary Sorts, Invariants & Stability

The slow sorts are not on the menu because anyone ships them. They are here because they are the cleanest place to learn loop invariants, and because insertion sort is genuinely useful as the base case inside the fast sorts you write next lecture.

**Objectives**

- State and prove the loop invariant for selection, bubble, and insertion sort.
- Define stability precisely and explain why multi-key sorting depends on it.
- Recognize insertion sort's adaptivity, `O(n + inversions)`, and the strict-weak-ordering comparator contract.

**Topics covered**

- Selection sort: `O(n^2)` comparisons always, but only `O(n)` swaps, and unstable. Proved through the invariant "the prefix `a[0..k)` holds the `k` smallest elements in sorted order."
- Bubble sort: stable, best case `O(n)` with a `swapped` flag, justified by the adjacent-swap invariant that each pass floats the largest unsorted element to its final position.
- Insertion sort: adaptive, stable, in-place, and online. Runs in `O(n + inversions)`, which is near-linear on nearly-sorted input. This is the one you will actually reuse.
- Stability defined exactly: equal keys keep their original relative order. Then multi-key sorting by sorting on the secondary key first and the primary key second with a stable sort.
- The comparator contract: it must be a strict weak ordering. A `<=` comparator violates irreflexivity and is undefined behavior in `std::sort`, not just "a little slower."
- Two practical traps: pass containers by reference (a by-value `vector` parameter silently sorts a copy), and watch the `size_t` descending-index underflow when a loop counts down to and past zero.

**Patterns**

None new this lecture. The focus is invariants and the comparator contract, which everything downstream depends on.

**In-class problems**

- Sort Colors / Dutch National Flag — a three-way partition in one pass, the seed of the quicksort partition you write next lecture.
- Implement and trace insertion sort, stating the invariant before each pass.
- Stable multi-key sort of records — sort by the secondary key, then by the primary key, and confirm the result is what stability buys you.
- Binary insertion sort — show why binary search cuts the comparison count but the element shifts stay `O(n^2)`.

---

## Lecture 26 — Merge Sort, Quick Sort, Heap Sort & Quickselect

The three `O(n log n)` sorts, plus the selection trick that falls out of quicksort. By the end you can pick between them on purpose instead of by reflex.

**Objectives**

- Implement merge sort (stable, `O(n log n)` always) and the two-pointer merge subroutine you will reuse all term.
- Implement quick sort with Lomuto or Hoare partition, and kill the worst case with a randomized or median-of-three pivot.
- Use quickselect for average `O(n)` kth-element selection, and compare all of the big sorts on time, space, stability, and cache behavior.

**Topics covered**

- Merge sort: recurrence `T(n) = 2T(n/2) + O(n)`, so `O(n log n)` in every case. Allocate the `O(n)` scratch buffer once outside the recursion rather than per call.
- Quick sort: in-place, average `O(n log n)`, but `O(n^2)` on already-sorted input under a naive first/last pivot. Randomized or median-of-three pivot makes the bad case astronomically unlikely.
- Lomuto vs Hoare partition, and the three-way (Dutch National Flag) partition that keeps quicksort fast when the array has many duplicate keys.
- Quickselect: after partitioning, recurse into only the side that contains the kth element. Average `O(n)`, worst `O(n^2)` with the same pivot caveat.
- Heap sort: `O(n log n)` worst case, in-place, unstable, with `O(n)` build-heap. Strong guarantees, but poor cache locality is why it loses to quicksort in practice.
- `mid = lo + (hi - lo) / 2` to avoid the `(lo + hi)` integer overflow. You meet this again in binary search two lectures from now.

**Patterns**

- [Quickselect / top-K](../docs/patterns.md)
- [Divide & conquer](../docs/patterns.md)

**In-class problems**

- Sort an Array — implement merge sort and verify stability on records with equal keys.
- Sort an Array — implement quick sort with a random pivot and confirm it survives a sorted input.
- Kth Largest Element in an Array — quickselect, average `O(n)`.
- Count Inversions — count them as a side effect of the merge step, divide and conquer in `O(n log n)`.

---

## Lecture 27 — Non-Comparison Sorts, the n log n Lower Bound & `std::sort` Mastery

Why no comparison sort can beat `n log n`, how to break that barrier when keys are small integers, and how to use the standard library so you stop hand-rolling sorts you do not need.

**Objectives**

- Explain the `Ω(n log n)` comparison lower bound through the decision-tree argument.
- Implement counting sort (stable, via the prefix-sum placement method) and LSD radix sort built on a stable inner sort.
- Use `std::sort`, `std::stable_sort`, and `std::nth_element` correctly, and apply sorting as a preprocessing step.

**Topics covered**

- The decision-tree lower bound: any comparison sort is a binary tree with at least `n!` leaves, so its height is `Θ(n log n)`, and height is the worst-case comparison count.
- Counting sort: `O(n + k)` where `k` is the key range. Stable only when you build the prefix-sum table and place from the right, and you handle negative keys by offsetting the range.
- Radix sort: `O(d(n + b))` for `d` digits in base `b`, correct only because the inner per-digit pass is a stable counting sort. LSD order is what makes the digits compose.
- Bucket sort: expected `O(n)` when the input is roughly uniform, degrading toward `O(n^2)` when it clusters.
- The standard library is not a mystery box: `std::sort` is introsort (quicksort that falls back to heapsort to dodge the quadratic case, with insertion sort on small ranges), `std::stable_sort` is merge-based, and `std::nth_element` is quickselect.
- The meta-pattern: sort first, then sweep. Sorting turns interval, duplicate, kth, and closest-pair problems into a single linear pass. When you must keep the original positions, sort an index array by value instead of moving the data.

**Patterns**

- [Merge intervals](../docs/patterns.md)
- [Cyclic sort](../docs/patterns.md)

**In-class problems**

- Largest Number — sort with a custom comparator (`a + b > b + a` on the string concatenations).
- Maximum Gap — radix or bucket sort to get the linear-time bound a comparison sort cannot.
- Implement counting sort, then build LSD radix sort on top of it.
- Find All Numbers Disappeared in an Array — cyclic sort, placing each value at its index in one pass.

---

## Lecture 28 — Binary Search, Search-on-the-Answer & Divide & Conquer

Binary search is the pattern most people think they know and most people write with an off-by-one bug. We fix that with one fixed convention, then generalize it from "find a value in a sorted array" to "find the boundary of a monotonic predicate," which is where the real interview value is.

**Objectives**

- Write a correct binary search using one fixed interval convention and the overflow-safe midpoint.
- Reframe binary search as finding the boundary in a monotonic `F...FT...T` predicate, which gives you `lower_bound` and `upper_bound` for free.
- Apply binary search on the answer to minimize-the-maximum problems, and formalize divide and conquer with the Master Theorem.

**Topics covered**

- The canonical invariant: pick `[lo, hi)` and stick to it. The loop condition follows from the convention, and the shrink rule is `lo = mid + 1` on one side so the interval always strictly shrinks and the loop terminates.
- The predicate framework: define a boolean `feasible(x)` that is monotonic, then find the first `x` where it flips. First-true is `lower_bound`; `count = upper_bound - lower_bound`.
- The standard tools for sorted ranges: `std::lower_bound`, `std::upper_bound`, `std::binary_search`, and `std::equal_range`.
- Binary search on the answer: when the answer is a value and `feasible(value)` is monotonic, binary search the value range instead of an array. For real-valued answers, run a fixed number of iterations rather than comparing floats for equality.
- Divide and conquer formalized: split, solve the parts, combine. Master Theorem recap so you can read a recurrence off the structure of the algorithm.
- Divide and conquer has disjoint subproblems; dynamic programming has overlapping ones. That distinction is the bridge into the DP block in a few weeks.

**Patterns**

- [Modified binary search (+ on the answer)](../docs/patterns.md)
- [Divide & conquer](../docs/patterns.md)

**In-class problems**

- Find First and Last Position of Element in Sorted Array — one `lower_bound`, one `upper_bound`.
- Search in Rotated Sorted Array — binary search where one half is always sorted; decide which half to keep.
- Koko Eating Bananas — binary search on the answer, with `feasible(speed)` checking whether Koko finishes in time.
- Pow(x, n) — fast exponentiation by divide and conquer, `O(log n)`.

---

## Homework

Work these between lectures. The warmups lock in the mechanics; the core problems are the ones that show up in interviews; the challenge problems are where binary search on the answer and merge-based counting earn their keep.

**Warmup**

- Sort Colors / Dutch National Flag
- Merge Sorted Array
- Binary Search

**Core**

- Kth Largest Element in an Array
- Search in Rotated Sorted Array
- Find Minimum in Rotated Sorted Array
- Capacity to Ship Packages Within D Days
- Largest Number

**Challenge**

- Split Array Largest Sum
- Count Inversions / Reverse Pairs
- Median of Two Sorted Arrays

If you only have time for three this week, do Search in Rotated Sorted Array, Capacity to Ship Packages Within D Days, and Median of Two Sorted Arrays. They cover the rotated-array variant, binary search on the answer, and the hardest binary search you are likely to meet.

## Before next week

- You can write merge sort, quick sort (random pivot), heap sort, counting sort, and radix sort from a blank file, and state stability, in-place, and complexity for each.
- You can implement quickselect and explain why its average case is `O(n)` and its worst case is `O(n^2)`.
- You can write a binary search that terminates and has no off-by-one error, and explain your interval convention out loud.
- You can take a "minimize the maximum" problem, write a monotonic `feasible()`, and binary search the answer.
- You can state the Master Theorem case for `T(n) = 2T(n/2) + O(n)` and explain how disjoint subproblems differ from the overlapping ones coming up in dynamic programming.
