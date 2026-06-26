# Curriculum — DSA in C++

*Data Structures & Algorithms in C++ — From Fundamentals to Interview-Ready*

Sixteen weeks, sixty-four lectures, and a few hundred problems: build every structure by hand in C++, then learn to spot the pattern behind the interview question.

This is the full syllabus, lecture by lecture. Each week runs four lectures (75–90 minutes each), so 64 lectures total. Read it as a map of what you'll learn and in what order, not as the lecture recordings themselves.

A word on the ordering. Complexity analysis and recursion come first, before any data structure. That's deliberate. You cannot reason about a vector, a tree, or a graph algorithm without a way to measure cost and a comfort with recursion, so we install both lenses in weeks 1 and 2 and then use them on everything that follows. After that the structures track runs from arrays through graphs, and the algorithms track from sorting through dynamic programming. Every topic is taught, then drilled. The interview patterns (two pointers, sliding window, fast & slow pointers, monotonic stack, tree BFS/DFS, top-K, K-way merge, backtracking, DP families, and the rest) are woven in where they naturally belong, not bolted on at the end.

Each week below lists its theme, a summary, the four lectures (objectives, topics, patterns, in-class problems), then the week's homework and the milestone you should hit before moving on.

## Contents

| Week | Theme |
|------|-------|
| [Week 1](#week-1--complexity-analysis--the-problem-solving-framework) | Complexity Analysis & The Problem-Solving Framework |
| [Week 2](#week-2--recursion-the-universal-control-structure) | Recursion: the Universal Control Structure |
| [Week 3](#week-3--arrays-strings--the-linear-scan-patterns) | Arrays, Strings & the Linear-Scan Patterns |
| [Week 4](#week-4--hashing-cyclic-sort--merge-intervals) | Hashing, Cyclic Sort & Merge Intervals |
| [Week 5](#week-5--pointer-based-memory-singly--doubly-linked-lists) | Pointer-Based Memory: Singly & Doubly Linked Lists |
| [Week 6](#week-6--restricted-access-adts-stacks-queues-deques--monotonic-stack) | Restricted-Access ADTs: Stacks, Queues, Deques & Monotonic Stack |
| [Week 7](#week-7--sorting-divide--conquer-and-binary-search) | Sorting, Divide & Conquer, and Binary Search |
| [Week 8](#week-8--binary-trees-representation-dfs--bfs-traversals) | Binary Trees: Representation, DFS & BFS Traversals |
| [Week 9](#week-9--ordered-trees-bst-and-self-balancing-avl) | Ordered Trees: BST and Self-Balancing (AVL) |
| [Week 10](#week-10--binary-heaps-priority-queues-and-heap-patterns) | Binary Heaps, Priority Queues, and Heap Patterns |
| [Week 11](#week-11--tries-and-union-find-prefix-and-partition-structures) | Tries and Union-Find: Prefix and Partition Structures |
| [Week 12](#week-12--graphs-part-1-representation-traversal-and-ordering) | Graphs Part 1: Representation, Traversal, and Ordering |
| [Week 13](#week-13--graphs-part-2-weighted-shortest-paths--minimum-spanning-trees) | Graphs Part 2: Weighted Shortest Paths & Minimum Spanning Trees |
| [Week 14](#week-14--backtracking-exhaustive-search-with-pruning) | Backtracking: Exhaustive Search with Pruning |
| [Week 15](#week-15--dynamic-programming-i-recurrence-recognition-knapsack-and-sequence-dp) | Dynamic Programming I: Recurrence, Knapsack, and Sequence DP |
| [Week 16](#week-16--dp-finale-greedy-bitmath--interview-ready-capstone) | DP Finale, Greedy, Bit/Math & Interview-Ready Capstone |

---

## Week 1 — Complexity Analysis & The Problem-Solving Framework

**Theme:** Complexity Analysis & The Problem-Solving Framework

Install the first lens of the course: how to measure and compare algorithms. You'll learn operation counting, asymptotic notation, space and amortized analysis, and the repeatable UPSCR problem-solving framework, plus the daily C++/STL toolset and testing discipline you'll lean on for the rest of the 16 weeks.

### Lecture 1 — Course Kickoff, the Problem-Solving Framework & Measuring Work

**Objectives**
- Internalize the five-step UPSCR framework (Understand, Pattern, Strategy, Code, Review) and reuse it on every later problem.
- Count operations under the RAM model and read input constraints to guess the target complexity.
- Recognize int overflow (~2.1x10^9) and reach for `long long` early.

**Topics**
- Course mechanics, philosophy (problem-heavy, pattern-based), and why complexity and recursion are taught first.
- The five-step UPSCR framework taught explicitly.
- RAM model and operation counting as a function of n.
- Reading constraints: n<=20 suggests exponential; n<=5000 suggests O(n^2); n<=1e6 suggests O(n) or O(n log n); n<=1e9 suggests O(log n) or O(sqrt n).
- int vs long long overflow; the `g++ -std=c++17 -O2 -Wall` compile/run loop.
- First touch of `<chrono>` `steady_clock` for empirical timing.

**Patterns:** Complexity estimation from constraints.

**In-class problems**
- Solve one warmup end-to-end through all 8 framework steps.
- Given constraints (n<=20 / 5000 / 1e6 / 1e9), name the target complexity.
- Demonstrate int overflow in factorial and fix it with `long long`.

### Lecture 2 — Big-O, Big-Omega, Big-Theta & Loop Analysis

**Objectives**
- State the formal definitions of O, Omega, and Theta and de-formalize them as upper, lower, and tight bounds.
- Analyze single, nested, triangular, and halving loops and place them on the growth-class ladder.
- Separate the case axis (best/worst/average) from the notation axis (O/Omega/Theta).

**Topics**
- Formal O/Omega/Theta definitions plus intuition; dropping constants and lower-order terms.
- Loop recipes: single O(n), nested O(n*m), triangular O(n^2), halving O(log n), halving-outer times linear-inner O(n log n).
- Growth ladder: O(1) < log n < sqrt n < n < n log n < n^2 < n^3 < 2^n < n!.
- Best/worst/average case vs notation; why we usually quote worst case.
- Sequential blocks take the max, not the sum; log base is irrelevant asymptotically.
- Empirical validation with `<chrono>`; `-O2` can optimize away dead loops.

**In-class problems**
- Time complexity of a triangular loop (j = i..n).
- Time complexity of a halving loop (i *= 2).
- Best/worst/average case of linear search.
- Classify each snippet into the growth ladder (mixed set of 10).

### Lecture 3 — Space Complexity, Amortized Analysis & the Memory Model

**Objectives**
- Distinguish total vs auxiliary space and account for the recursion call stack as O(depth) space.
- Derive why geometric (doubling) growth gives amortized O(1) `push_back` while constant (+k) growth gives amortized O(n).
- Explain the stack vs heap memory model and vector size vs capacity.

**Topics**
- Auxiliary vs total space; call-stack space of recursion.
- Amortized analysis as average cost over a worst-case sequence, not a probabilistic average.
- Dynamic-array doubling: aggregate argument that n pushes cost at most 2n copies.
- Doubling vs +1 growth; `reserve()` changes constants, not Big-O.
- Stack vs heap, automatic vs dynamic lifetime.
- `std::vector` `size()` vs `capacity()`, `reserve()`, `shrink_to_fit()`; `push_back` invalidates iterators/pointers/references; the `vector<bool>` caveat.

**In-class problems**
- Amortized cost of n `push_back`s with doubling vs +1 growth.
- Space complexity of recursive vs iterative array reversal.
- Empirically validate O(n^2) by doubling input with `<chrono>`.
- Vector capacity/growth demo: observe size vs capacity as elements are added.

### Lecture 4 — C++ Essentials, STL Survey & Testing Discipline

**Objectives**
- Use references vs pointers vs `const&` correctly and pair every `new` with exactly one `delete` (and `new[]` with `delete[]`).
- Wield the DSA-relevant STL subset: vector, array, string, pair, iterators, ranged-for, and `<algorithm>` basics.
- Write assert-based tests against a disciplined edge-case checklist.

**Topics**
- References (alias, never null, no rebind) vs pointers (nullable, arithmetic) vs `const&` for big objects.
- `new`/`delete`, `new[]`/`delete[]`, templates (`template<typename T>`).
- STL: vector, array, string, pair/tuple, structured bindings, half-open `[begin, end)` ranges, `sort`/`reverse`/`min`/`max`/`accumulate`/`lower_bound`; lambda comparators.
- `assert()` for invariants; edge-case checklist (empty, size 1, all-equal, duplicates, sorted/reverse, negatives/zero, max size, overflow).
- Gotchas: dangling references, double free, off-by-one with `end()`, silent O(n) by-value copies, signed/unsigned `size()` pitfalls.

**In-class problems**
- Build a tiny `MyVector` with doubling `push_back`.
- Write a `template<typename T> myMax(...)`.
- Write an assert-based test harness plus a full edge-case checklist for a reverse function.
- Sort a `vector<pair<int,int>>` by second element with a lambda.

### Homework

| Problem | Tier |
|---------|------|
| Time complexity of a single for loop | Warmup |
| Time complexity of two nested loops | Warmup |
| Sequential blocks: O(n) then O(n^2), what is the total? | Warmup |
| Why is `string::substr` in a loop O(n^2)? Identify and fix | Challenge |
| Pass a vector by value vs `const&` and measure the copy cost | Warmup |
| Find the memory bug: dangling reference / `delete` vs `delete[]` | Core |
| Iterator invalidation: spot the bug in a push_back-while-iterating loop | Challenge |
| Classify each snippet into the growth ladder (mixed set of 10) | Core |

**Milestone:** You can state and justify the Big-O/Theta of any loop-based snippet (time, space, and amortized), apply the five-step UPSCR framework end-to-end, and are fluent in the daily STL subset and assert-based testing with an edge-case checklist.

---

## Week 2 — Recursion: the Universal Control Structure

**Theme:** Recursion: the Universal Control Structure

Install the second lens: confident recursion. You'll master the call stack, base and recursive cases, recursion on numbers/arrays/strings, recurrence-tree analysis, recursion shapes, recursion-to-iteration conversion, and finish with the memoization (DP) and backtracking seeds that later tracks build on.

### Lecture 5 — Recursion Fundamentals & Recursion on Numbers

**Objectives**
- Trace the call stack frame by frame and identify base case, recursive case, and the strictly-smaller subproblem.
- Apply the recursive leap of faith: verify only the base case and the single combination step.
- Write number recursions including fast power in O(log b), and avoid the missing-base-case stack overflow.

**Topics**
- Anatomy of recursion: base case(s), recursive case, moving toward the base.
- Call stack and stack frames; drawing `factorial(4)` frame by frame.
- The recursive leap of faith; stack overflow when the base case is unreachable.
- `factorial`, `power(a,b)`, fast power via a^b = (a^(b/2))^2, `sum_of_digits`, `gcd` (Euclid), print 1..n / n..1.
- Each frame costs O(depth) stack space; pass large objects by reference to avoid an O(n) copy per frame; `long long` for overflow.

**Patterns:** Recursive decomposition (shrink-the-input); fast exponentiation (halving).

**In-class problems**
- Factorial (recursive).
- Fast power a^b in O(log b).
- GCD (Euclidean, recursive).
- Print 1..n and n..1 (order from recursion placement).

### Lecture 6 — Recursion on Arrays/Strings & Recurrence Relations

**Objectives**
- Apply the shrink-the-input pattern over arrays and strings using indices, not substrings.
- Build and solve recurrence relations and the recursion tree for recursive cost.
- Recognize the common recurrence shapes and their solutions (linear, halving, two-halves).

**Topics**
- Shrink-the-input: process index i, recurse on i+1 or `[lo, hi]`; build on the way down vs combine on the way up.
- Array sum/max, reverse-in-place (two indices), linear search, string reverse, palindrome (i, n-1-i), count occurrences.
- Recurrences: T(n)=T(n-1)+O(1) -> O(n); T(n)=T(n-1)+O(n) -> O(n^2); T(n)=T(n/2)+O(1) -> O(log n); T(n)=2T(n/2)+O(n) -> O(n log n); T(n)=2T(n/2)+O(1) -> O(n).
- Recursion-tree method; Master theorem stated as a preview.
- Recurse with `(s, i)` not `s.substr(i)` to avoid an O(n) copy per call and an O(n^2) blowup.

**Patterns:** Recurrence + recursion-tree analysis; two-index recursion (i, n-1-i).

**In-class problems**
- Reverse an array in place recursively (two indices).
- Valid Palindrome (recursive i, n-1-i).
- Recursive binary search (sets up the Binary Search track).
- Derive and solve T(n)=2T(n/2)+O(n).

### Lecture 7 — Recursion Shapes & Recursion-to-Iteration Conversion

**Objectives**
- Distinguish head vs tail recursion and linear vs tree vs mutual recursion.
- Convert tail recursion to a loop and general recursion to an explicit `std::stack` simulation.
- Explain why tree recursion (naive Fibonacci) explodes and why explicit-stack conversion avoids call-stack overflow without changing the space class.

**Topics**
- Head recursion (work on the way up) vs tail recursion (work on the way down, loop-convertible).
- Linear vs tree (multiple) recursion (Fib = O(phi^n)); mutual recursion with forward declarations.
- Tail recursion -> while loop; general recursion -> explicit stack pushing the state you would pass.
- `std::stack`: push/top/pop (pop returns void; read top first); the explicit stack uses the same O(depth) space.
- Forward-declaration syntax for mutual recursion (`isEven`/`isOdd`).

**Patterns:** Recursion -> iteration via explicit stack.

**In-class problems**
- Convert tail-recursive factorial to an iterative loop.
- Convert recursive array sum to iterative with an explicit stack.
- Mutual recursion: `isEven` / `isOdd`.
- Manual stack simulation of a recursive traversal, live.

### Lecture 8 — Memoization Preview, Backtracking Shape & Capstone Clinic

**Objectives**
- Identify overlapping subproblems and apply top-down memoization with a cache plus sentinel to turn exponential into linear.
- Recognize the choose / explore / un-choose backtracking template on subsets and permutations skeletons.
- Synthesize the complexity and recursion lenses on fresh capstone problems.

**Topics**
- Overlapping subproblems: naive `fib(n)` recomputes exponentially (draw the tree).
- Top-down memoization: cache keyed by arguments, sentinel -1 means not computed, O(n) time and space; the DP bridge (optimal substructure + overlapping subproblems).
- Backtracking shape preview: choose -> explore -> un-choose on subsets and permutations skeletons; recursion tree equals decision tree.
- Capstone clinic re-deriving complexity for each problem; emphasizing pattern recognition.
- Cache as `vector<int> memo(n+1, -1)` passed by reference (never by value); `unordered_map` for sparse keys; `long long` for Fibonacci beyond n~46.

**Patterns:** Fibonacci / 1-D memoization (DP seed); subsets / permutations skeleton (backtracking seed).

**In-class problems**
- Naive Fibonacci -> count repeated calls (draw the tree).
- Memoized Fibonacci (vector cache, sentinel -1).
- Climbing Stairs (recursive -> memoized).
- All subsets / power set (print all, backtracking skeleton).

### Homework

| Problem | Tier |
|---------|------|
| Sum of digits | Warmup |
| Decimal to binary via recursion | Core |
| Tower of Hanoi: move count and sequence | Challenge |
| Recursive array maximum | Warmup |
| Check if an array is sorted recursively | Core |
| String permutations: print all | Challenge |
| Iterative traversal of a recursive process using `std::stack` | Challenge |
| Coin Change: recursive formulation + memo, preview only | Challenge |

**Milestone:** You can write, trace, and analyze recursion confidently (including recurrences and space), convert recursion to iteration with an explicit stack, and have seen the memoization and backtracking templates so DP and backtracking later build on recognition, not first contact.

---

## Week 3 — Arrays, Strings & the Linear-Scan Patterns

**Theme:** Arrays, Strings & the Linear-Scan Patterns

First contact with concrete data structures. You'll master dynamic-array internals (size vs capacity, amortized `push_back`, iterator invalidation), then drill the three foundational contiguous-memory patterns: two pointers, prefix sums, and sliding window.

### Lecture 9 — Dynamic Arrays: Vector\<T\> Internals & Iterator Invalidation

**Objectives**
- Build a `Vector<T>` by hand with `new[]`/`delete[]` and a doubling `grow()`, and explain amortized O(1) `push_back`.
- Distinguish size vs capacity and the cost of insert/erase (O(n) shifting) vs random access (O(1)).
- Predict iterator/pointer/reference invalidation on reallocation, insert, and erase.

**Topics**
- size vs capacity; geometric growth (x2 / x1.5); amortized O(1) `push_back` via the aggregate argument; O(n) worst-case single push.
- O(n) insert/erase at arbitrary position; O(1) random access via base+offset.
- Hand-built `Vector<T>`: `grow()` allocates, copies, frees; `debug_verify_data_integrity()` / `debug_to_string()`.
- Iterator invalidation rules; `reserve()` to amortize away copies; `v[i]` (UB) vs `v.at(i)` (throws).
- `vector<bool>` bit-packed specialization; `emplace_back` vs `push_back`; move-on-grow and the noexcept move ctor; `endl` vs `'\n'`.

**In-class problems**
- Implement `Vector<T>` with doubling `push_back` and debug methods.
- Remove Element (in-place).
- Move Zeroes.
- Spot the iterator-invalidation bug in a push_back-while-iterating loop.

### Lecture 10 — Two Pointers: Opposite-Ends & Read/Write

**Objectives**
- Apply the opposite-ends two-pointer technique on sorted arrays to replace nested loops with an O(n) pass.
- Apply the same-direction slow/fast read-write technique for in-place compaction and dedup.
- Recognize the sorted/monotonic precondition and avoid signed/unsigned underflow.

**Topics**
- Opposite-ends: pair-sum on sorted arrays, reverse, palindrome, container-with-most-water.
- Same-direction read/write: in-place removal and dedup.
- Two pointers requires a sorted or monotonic property for the sum variant.
- Index-based pointers over iterators; `size_t` underflow when a pointer goes below 0.

**Patterns:** Two pointers.

**In-class problems**
- Two Sum II - Input Array Is Sorted.
- Valid Palindrome.
- Container With Most Water.
- Remove Duplicates from Sorted Array.

### Lecture 11 — Prefix Sums: 1D, 2D & Prefix-Sum + Hashmap

**Objectives**
- Precompute prefix sums so any range sum answers in O(1), with correct n+1 sizing and `long long` to avoid overflow.
- Extend to 2D prefix sums for submatrix queries.
- Combine prefix sums with a hashmap (seeded `{0:1}`) to count subarrays with sum K.

**Topics**
- `pre[i] = pre[i-1] + a[i]`; range `[i, j]` = `pre[j+1] - pre[i]`.
- Off-by-one: n+1 entries, `pre[0]=0`; `long long` for large arrays.
- 2D prefix sums for submatrix sums.
- Prefix sum + `unordered_map` for subarray-sum-equals-K; the `{0:1}` seed; product-of-array-except-self via prefix/suffix.

**Patterns:** Prefix sums.

**In-class problems**
- Range Sum Query - Immutable.
- Subarray Sum Equals K (prefix sum + hashmap).
- Product of Array Except Self.
- Range Sum Query 2D - Immutable.

### Lecture 12 — Sliding Window: Fixed & Variable

**Objectives**
- Apply a fixed-size window with an incrementally-updated aggregate to avoid recomputation.
- Apply a variable-size window: expand right, shrink left with `while` (not `if`) until valid, and record the answer.
- Track window state with a frequency array/map and reduce "exactly K" to atMost(K) - atMost(K-1).

**Topics**
- Fixed window (running sum/max over k) and variable window (grow right, shrink left while invalid).
- Window state as a running aggregate or frequency map/array; the expand/shrink/record template.
- Shrink with `while` not `if`; never recompute the aggregate from scratch.
- `int freq[128]`/`[26]` over a hashmap for character windows; prune zero entries so `map.size()` reflects distinct count.

**Patterns:** Sliding window.

**In-class problems**
- Maximum Average Subarray I (fixed window).
- Longest Substring Without Repeating Characters.
- Minimum Size Subarray Sum.
- Permutation in String.

### Homework

| Problem | Tier |
|---------|------|
| Squares of a Sorted Array | Warmup |
| Sort Colors / Dutch National Flag | Warmup |
| 3Sum | Core |
| Find Pivot Index | Core |
| Subarray Sums Divisible by K | Challenge |
| Longest Repeating Character Replacement | Core |
| Minimum Window Substring | Challenge |
| Trapping Rain Water (two-pointer version) | Challenge |

**Milestone:** You understand dynamic-array internals and invalidation cold, and can recognize and implement the two-pointers, prefix-sum, and sliding-window patterns on arrays and strings in O(n).

---

## Week 4 — Hashing, Cyclic Sort & Merge Intervals

**Theme:** Hashing, Cyclic Sort & Merge Intervals

The payoff week: hashing turns O(n^2) array/string scans into O(n) for membership, counting, and grouping. You'll build a hash table by hand, master `unordered_map`/`set` and their pitfalls, then drill two more owned array patterns: cyclic sort and merge intervals.

### Lecture 13 — Hashing I: Hash Functions, Collisions & Build a Hash Table

**Objectives**
- Explain hash functions, why collisions are inevitable, and resolve them with separate chaining (vs open addressing conceptually).
- Implement a chaining hash table by hand and reason about load factor and rehashing.
- State that hash operations are expected/amortized O(1) but O(n) worst case under adversarial collisions.

**Topics**
- Hash function key -> bucket; collisions via pigeonhole / birthday paradox.
- Separate chaining (bucket = list/vector) vs open addressing (linear/quadratic probing, double hashing) taught conceptually.
- Load factor alpha = n/buckets drives rehashing; expected O(1), worst O(n).
- When hashing wins (membership/dedup/counting/grouping in O(n)) vs loses (needs ordering/range/sorted iteration -> balanced tree).
- Hand-rolled chaining table (`vector<list<pair<K,V>>>`) with a debug print of bucket distribution.

**Patterns:** Hashing for dedup/count/group.

**In-class problems**
- Two Sum.
- Contains Duplicate.
- Design HashMap (build a hash table by hand).
- First Unique Character in a String.

### Lecture 14 — Hashing II: unordered_map/set, Custom Keys & Pitfalls

**Objectives**
- Choose deliberately between `unordered_map`/`set` (hash, avg O(1), unordered) and `map`/`set` (tree, O(log n), sorted).
- Avoid the `operator[]` default-insert bug and use `find`/`count`/`contains` for pure lookups.
- Supply a custom hash for pair/tuple/struct keys and tune with `reserve`/`max_load_factor`.

**Topics**
- `unordered_map`/`set` vs `map`/`set` trade-offs; no iteration order from `unordered_map` (changes on rehash).
- `operator[]` default-inserts absent keys (accidental-insertion bug); `.find()`/`.count()`/`.contains()`.
- Custom keys need a `std::hash` specialization or functor; pair/tuple have no standard hash.
- `reserve(n)`/`max_load_factor` to cut rehashing; `unordered_map` references stay valid across rehash (only iterators invalidate) vs vector.
- Prefer `int[]` indexed by a small bounded key (26 letters, ASCII) when applicable.

**Patterns:** Hashing for dedup/count/group.

**In-class problems**
- Group Anagrams.
- Top K Frequent Elements.
- Longest Consecutive Sequence.
- Isomorphic Strings.

### Lecture 15 — Cyclic Sort & Index-as-Hash on Values in [1..n]

**Objectives**
- Apply cyclic sort to place each value at its index in O(n)/O(1) when values are a known permutation of 1..n.
- Use the placed array to find missing, duplicate, or first-missing-positive in a linear scan.
- Write the swap condition correctly to avoid infinite loops.

**Topics**
- Cyclic sort: while `a[i]` is not at index `a[i]-1`, swap it home; then scan for the first wrong index.
- Applies only when values are in `[1..n]` or `[0..n-1]`.
- Swap condition must check the target slot does not already hold the correct value: `while (a[i] != i+1 && a[i] != a[a[i]-1])`.
- In-place swaps with `std::swap`; relation to XOR-based missing-number tricks.

**Patterns:** Cyclic sort.

**In-class problems**
- Missing Number.
- Find All Numbers Disappeared in an Array.
- Find the Duplicate Number.
- First Missing Positive.

### Lecture 16 — Merge Intervals & Arrays/Strings/Hashing Workshop

**Objectives**
- Sort intervals by start and sweep once to merge overlapping ranges, choosing `<` vs `<=` consistently.
- Solve insert-interval and min-meeting-rooms variants.
- Consolidate the week's patterns in a mixed problem-drill before pivoting to pointer-based structures.

**Topics**
- Merge intervals: sort by start, extend current end while `next.start <= cur.end`.
- Variants: insert interval, interval intersection, meeting-rooms (min rooms via sweep / heap preview).
- Sort with a lambda comparator; intervals as `vector<vector<int>>` or `pair<int,int>`.
- Workshop: mixed arrays + strings + hashing drills consolidating the contiguous-memory + hashing half of the structures track.

**Patterns:** Merge intervals; hashing for dedup/count/group.

**In-class problems**
- Merge Intervals.
- Insert Interval.
- Interval List Intersections.
- Mixed mock-set: arrays + strings + hashing rapid drill.

### Homework

| Problem | Tier |
|---------|------|
| Valid Anagram | Warmup |
| Longest Common Prefix | Core |
| Set Mismatch | Core |
| Find All Duplicates in an Array | Core |
| Non-overlapping Intervals | Core |
| Minimum Number of Arrows to Burst Balloons | Core |
| Meeting Rooms II | Challenge |
| Subarrays with K Different Integers | Challenge |

**Milestone:** You can reach for hashing to make membership/counting/grouping O(n), implement a hash table by hand, work around `unordered_map`/`set` pitfalls, and apply cyclic sort and merge-intervals fluently, completing the array/string/hashing foundation before pointer-based structures.

---

## Week 5 — Pointer-Based Memory: Singly & Doubly Linked Lists

**Theme:** Pointer-Based Memory: Singly & Doubly Linked Lists

You pivot from contiguous memory to pointer-linked structures, building singly and doubly linked lists by hand with the dummy-head technique and mastering the fast & slow pointer and in-place reversal patterns. This is the first deep node-based unit, drilling memory discipline (`new`/`delete`, destructors) and O(1)-space list manipulation.

### Lecture 17 — Singly Linked Lists: Build by Hand, Dummy Head, Insert & Delete

**Objectives**
- Build a singly linked list from scratch with raw `new`/`delete`, a head pointer, and an optional tail.
- Use a dummy/sentinel head to eliminate head-special-casing on insert and delete.
- Implement an iterative destructor and `debug_verify_data_integrity` to avoid leaks and stack overflow.

**Topics**
- `Node { value, next }` and head pointer; pointer vs contiguous memory model.
- O(1) insert/delete at a known position vs O(n) search/random access.
- Dummy/sentinel head technique for front/middle/tail operations.
- Delete nth node, insert after position, traversal bounds.
- Iterative destructor (not recursive) to free long lists safely.
- `debug_print_list` and `debug_verify_data_integrity` (size, no cycle, `tail->next == null`).
- Aside: `unique_ptr<Node>` ownership and recursive-destructor stack overflow.

**In-class problems**
- Design Linked List (singly: get/addAtHead/addAtTail/addAtIndex/delete).
- Remove Nth Node From End of List (dummy head).
- Merge Two Sorted Lists.
- Remove Linked List Elements (dummy head).

### Lecture 18 — Fast & Slow Pointers: Cycle, Middle, Nth-From-End

**Objectives**
- Apply Floyd's slow(+1)/fast(+2) technique to detect a cycle and find its start.
- Find the middle node and the nth-from-end node in a single O(1)-space pass.
- Order null-checks correctly (`fast && fast->next`) to avoid segfaults.

**Topics**
- Floyd's cycle detection: meeting point inside a cycle.
- Finding cycle start by resetting one pointer to head.
- Middle of the list (even vs odd length convention).
- Nth-from-end via a gap of n then advance together.
- Null-check ordering and even/odd edge cases.
- Why O(1) extra space beats copy-to-vector approaches.

**Patterns:** Fast & slow pointers.

**In-class problems**
- Linked List Cycle.
- Linked List Cycle II (find cycle start).
- Middle of the Linked List.
- Happy Number (fast/slow on a functional sequence).

### Lecture 19 — In-Place Linked-List Reversal: Full, Sublist, K-Group

**Objectives**
- Reverse a full singly linked list with the prev/curr/next three-pointer technique in O(1) space.
- Reverse a sublist `[m, n]` and reverse nodes in k-groups by careful rewiring.
- Cache `next` before rewiring and null the old head to avoid losing the list or creating a cycle.

**Topics**
- Three-pointer iterative reversal (prev, curr, next).
- Reverse a sublist between positions m and n.
- Reverse nodes in k-group (count, reverse, reconnect).
- Common bugs: losing the tail, forgetting to null-terminate, creating a cycle.
- Pointer-to-pointer (`Node**`) rewiring as an optional elegant alternative.

**Patterns:** In-place linked-list reversal.

**In-class problems**
- Reverse Linked List.
- Reverse Linked List II (sublist).
- Swap Nodes in Pairs.
- Reverse Nodes in k-Group.

### Lecture 20 — Doubly Linked Lists, std::list, and the LRU Cache

**Objectives**
- Build a doubly linked list with prev/next and dual sentinels for O(1) deletion given a node.
- Contrast `std::list` (O(1) splice, no random access, cache-hostile) with `std::vector`.
- Combine a hashmap with a DLL to implement an O(1) LRU cache.

**Topics**
- `Node { prev, value, next }`; O(1) delete given a node, O(1) insert/remove at both ends.
- Sentinels at both ends to simplify boundary logic.
- Correct rewiring order: set new node's links before redirecting neighbors, update both directions.
- `std::list` iterator stability vs vector; `std::forward_list` mention.
- LRU cache: hashmap key -> DLL node, move-to-front on access.
- Cache-locality trade-off: vector often wins for mid-insertions.

**Patterns:** Hashing for dedup/lookup.

**In-class problems**
- Design Linked List (doubly).
- LRU Cache (hashmap + DLL, O(1)).
- Flatten a Multilevel Doubly Linked List.
- Copy List with Random Pointer (hashing + list).

### Homework

| Problem | Tier |
|---------|------|
| Reverse Linked List | Warmup |
| Middle of the Linked List | Warmup |
| Merge Two Sorted Lists | Warmup |
| Remove Nth Node From End of List | Core |
| Linked List Cycle II | Core |
| Palindrome Linked List | Core |
| Odd Even Linked List | Core |
| Reverse Linked List II | Core |
| Reverse Nodes in k-Group | Challenge |
| LRU Cache | Challenge |

**Milestone:** Hand-built singly and doubly linked list classes (with dummy heads, iterative destructors, and debug verification) plus a working O(1) LRU cache; fluent in fast & slow pointers and in-place O(1)-space reversal.

---

## Week 6 — Restricted-Access ADTs: Stacks, Queues, Deques & Monotonic Stack

**Theme:** Restricted-Access ADTs: Stacks, Queues, Deques & Monotonic Stack

You build stacks and queues both array- and list-backed, master `std::stack`/`queue`/`deque`, implement a circular (ring-buffer) queue, and drill the monotonic stack pattern for next-greater and histogram problems. A small sparse-matrix build consolidates indexed array thinking before the trees unit.

### Lecture 21 — Stacks: Array-Backed, List-Backed, and Expression Evaluation

**Objectives**
- Implement a LIFO stack two ways (vector-backed and singly-list-backed) with O(1) push/pop/top.
- Use `std::stack` and understand its container-adaptor design and `void pop()`.
- Apply stacks to balanced parentheses and expression evaluation (postfix eval, infix to postfix).

**Topics**
- LIFO semantics; push/pop/top/empty all O(1).
- Array-backed (`push_back`/`pop_back`) inherits vector amortized O(1); list-backed at head.
- `std::stack` as an adaptor over `std::deque`; `pop()` returns void (read `top()` first).
- Guarding `top()`/`pop()` on an empty stack.
- Applications: balanced brackets, postfix evaluation, infix -> postfix, call-stack simulation.
- Tie-back: stack as the explicit form of recursion's call stack.

**Patterns:** Stack for parsing / matching.

**In-class problems**
- Valid Parentheses.
- Min Stack.
- Evaluate Reverse Polish Notation.
- Simplify Path.

### Lecture 22 — Monotonic Stack: Next Greater, Span, and Histogram

**Objectives**
- Maintain a monotonically increasing/decreasing stack so each element is pushed and popped once for O(n).
- Choose the correct monotonic direction and store indices vs values for distance queries.
- Solve next-greater, daily-temperatures, and largest-rectangle problems with sentinels to flush the stack.

**Topics**
- Monotonic stack invariant; pop-and-resolve on an incoming element.
- Increasing vs decreasing direction for next-greater vs next-smaller.
- Storing indices for distance-to-next-greater problems.
- Sentinel seeding/post-processing for leftover elements (histogram flush with a 0).
- Amortized O(n): each element pushed and popped at most once.

**Patterns:** Monotonic stack.

**In-class problems**
- Next Greater Element I.
- Daily Temperatures.
- Next Greater Element II (circular).
- Largest Rectangle in Histogram.

### Lecture 23 — Queues, Circular Queue (Ring Buffer), Deque & Monotonic Deque

**Objectives**
- Implement a FIFO queue (list-backed head/tail) and a fixed-size circular queue with modular indexing.
- Use `std::queue` and `std::deque` and know deque's segmented (non-contiguous) layout.
- Apply a monotonic deque to sliding-window maximum in O(n).

**Topics**
- FIFO; enqueue/dequeue/front O(1); naive shifting queue is O(n) per dequeue.
- Circular queue: head/tail/count or modular arithmetic; full-vs-empty ambiguity at `head == tail`.
- `std::queue` adaptor (default deque backing); `std::queue::pop()` returns void.
- `std::deque`: O(1) both ends, O(1) random access, but not contiguous (no `.data()`).
- Monotonic deque: pop-back worse candidates, pop-front out-of-window indices.
- `std::priority_queue` exists but the heap is deferred to the trees track.

**Patterns:** Deque / monotonic queue.

**In-class problems**
- Design Circular Queue.
- Implement Queue using Stacks.
- Sliding Window Maximum (monotonic deque).
- Number of Recent Calls (sliding queue).

### Lecture 24 — Sparse Matrices + Stack/Queue Capstone & Mixed Drill

**Objectives**
- Build a small sparse-matrix representation (coordinate / list-of-triples) and reason about when it beats a dense 2D array.
- Consolidate stack vs queue vs deque selection on a mixed problem set.
- Run a mixed mock-interview drill across the week's restricted-access ADTs.

**Topics**
- Sparse matrix motivation: wasted O(rows*cols) space for mostly-zero data.
- Coordinate (row, col, value) triple representation; build, store, and query.
- Indexed-array thinking as a bridge to the trees array representation.
- Decision drill: which ADT (stack/queue/deque/monotonic) fits which signal.
- Track capstone review plus a timed mixed mock-interview set.

**Patterns:** Monotonic stack; stack for parsing / matching; deque / monotonic queue.

**In-class problems**
- Build and query a sparse matrix (triple representation).
- Asteroid Collision (stack).
- Implement Stack using Queues.
- Basic Calculator II (stack parsing).

### Homework

| Problem | Tier |
|---------|------|
| Valid Parentheses | Warmup |
| Implement Queue using Stacks | Warmup |
| Min Stack | Core |
| Evaluate Reverse Polish Notation | Core |
| Daily Temperatures | Core |
| Next Greater Element II | Core |
| Design Circular Queue | Core |
| Asteroid Collision | Core |
| Largest Rectangle in Histogram | Challenge |
| Sliding Window Maximum | Challenge |

**Milestone:** Hand-built array- and list-backed stack and queue classes plus a working circular queue and a sparse-matrix representation; fluent in the monotonic stack and monotonic deque patterns under timed conditions.

---

## Week 7 — Sorting, Divide & Conquer, and Binary Search

**Theme:** Sorting, Divide & Conquer, and Binary Search (incl. on the Answer)

The first heavy algorithms week: you implement the full sorting family (selection/insertion, merge, quick, heap, counting/radix), nail stability and `std::sort`, formalize divide & conquer, and master binary search including the predicate framework and binary-search-on-the-answer. Loop invariants and comparator correctness are emphasized throughout.

### Lecture 25 — Elementary Sorts, Invariants & Stability

**Objectives**
- State and prove the loop invariant for selection, bubble, and insertion sort.
- Define stability precisely and explain why multi-key sorting depends on it.
- Recognize insertion sort's adaptivity (O(n+inversions)) and the strict-weak-ordering comparator contract.

**Topics**
- Selection sort (O(n^2) always, O(n) swaps, unstable) via the "prefix is k smallest" invariant.
- Bubble sort (stable, best-case O(n) with a swapped flag) and the adjacent-swap invariant.
- Insertion sort (adaptive, stable, in-place, online), the practically useful one.
- Stability defined; secondary-then-stable-primary multi-key sorting.
- Comparator must be a strict weak ordering; a `<=` comparator is UB in `std::sort`.
- Pass containers by reference; the `size_t` descending-index underflow trap.

**In-class problems**
- Sort Colors / Dutch National Flag.
- Implement and trace insertion sort with an invariant.
- Stable multi-key sort of records (sort by secondary then primary).
- Binary insertion sort: why comparisons drop but shifts stay O(n^2).

### Lecture 26 — Merge Sort, Quick Sort, Heap Sort & Quickselect

**Objectives**
- Implement merge sort (stable, O(n log n) always) and the reusable two-pointer merge subroutine.
- Implement quick sort with Lomuto/Hoare partition and fix the worst-case O(n^2) via a randomized/median pivot.
- Use quickselect for O(n)-average kth-element selection and compare all the big sorts.

**Topics**
- Merge sort recurrence T(n)=2T(n/2)+O(n); O(n) buffer allocated once outside recursion.
- Quick sort: in-place, average O(n log n), worst O(n^2) on sorted input under a naive pivot.
- Lomuto vs Hoare partition; 3-way (Dutch National Flag) for many duplicates.
- Quickselect: recurse into one side, average O(n).
- Heap sort: O(n log n) worst, in-place, unstable, O(n) build-heap, poor cache behavior.
- `mid = lo + (hi-lo)/2` overflow lesson (reused in binary search).

**Patterns:** Quickselect / top-K; divide & conquer.

**In-class problems**
- Sort an Array (implement merge sort).
- Sort an Array (implement quick sort with random pivot).
- Kth Largest Element in an Array (quickselect).
- Count Inversions (merge-based divide & conquer).

### Lecture 27 — Non-Comparison Sorts, the n log n Lower Bound & std::sort Mastery

**Objectives**
- Explain the Omega(n log n) comparison lower bound via the decision-tree argument.
- Implement counting sort (stable, placement method) and LSD radix sort over a stable inner sort.
- Use `std::sort`/`stable_sort`/`nth_element` correctly and apply sorting as a preprocessing pattern.

**Topics**
- Decision-tree lower bound: n! leaves, height Theta(n log n).
- Counting sort O(n+k), stable only with the prefix-sum placement method; handling negatives.
- Radix sort O(d(n+b)) relying on a stable inner counting sort.
- Bucket sort (expected O(n) on uniform data).
- `std::sort` is introsort; `std::stable_sort` is merge-based; `std::nth_element` is quickselect.
- Meta-pattern: "sort first, then sweep" for intervals/duplicates/kth/pairs; sort indices by value.

**Patterns:** Merge intervals; cyclic sort.

**In-class problems**
- Largest Number (custom comparator).
- Maximum Gap (radix/bucket sort).
- Implement counting sort, then LSD radix sort.
- Find All Numbers Disappeared in an Array (cyclic sort).

### Lecture 28 — Binary Search, Search-on-the-Answer & Divide & Conquer

**Objectives**
- Write correct binary search using a fixed interval convention and the overflow-safe midpoint.
- Reframe binary search as finding the boundary in a monotonic F...FT...T predicate (lower/upper bound).
- Apply binary-search-on-the-answer to minimize-the-max problems and formalize D&C with the Master Theorem.

**Topics**
- Canonical invariant; loop-condition vs shrink rule; `lo = mid+1` to avoid infinite loops.
- Predicate framework: first-true (`lower_bound`) vs first->true; count = upper - lower.
- `std::lower_bound`/`upper_bound`/`binary_search`/`equal_range` on sorted ranges.
- Binary search on the answer: monotonic `feasible()` over a value range; float BS via fixed iterations.
- Divide & conquer: split, solve, combine; Master Theorem recap.
- D&C subproblems are disjoint vs DP's overlapping (foreshadows the DP block).

**Patterns:** Modified binary search (+ on the answer); divide & conquer.

**In-class problems**
- Find First and Last Position of Element in Sorted Array.
- Search in Rotated Sorted Array.
- Koko Eating Bananas (binary search on the answer).
- Pow(x, n) (fast exponentiation, divide & conquer).

### Homework

| Problem | Tier |
|---------|------|
| Sort Colors / Dutch National Flag | Warmup |
| Merge Sorted Array | Warmup |
| Binary Search | Warmup |
| Kth Largest Element in an Array | Core |
| Search in Rotated Sorted Array | Core |
| Find Minimum in Rotated Sorted Array | Core |
| Capacity to Ship Packages Within D Days | Core |
| Largest Number | Core |
| Split Array Largest Sum | Challenge |
| Count Inversions / Reverse Pairs | Challenge |
| Median of Two Sorted Arrays | Challenge |

**Milestone:** From-scratch implementations of merge, quick, heap, counting, and radix sort with correct stability; fluent in `std::sort` with custom comparators, the binary-search predicate framework, binary-search-on-the-answer, and divide & conquer analysis.

---

## Week 8 — Binary Trees: Representation, DFS & BFS Traversals

**Theme:** Binary Trees: Representation, DFS & BFS Traversals

You pivot from linear to nonlinear thinking, nailing tree mechanics, height/depth, and the array representation, then master DFS (preorder/inorder/postorder, recursive and iterative) and BFS level-order with the level-size snapshot idiom. This installs the tree DFS and tree BFS patterns that power BST, heaps, and graphs.

### Lecture 29 — Binary Trees: Representation, Terminology & Memory

**Objectives**
- Define tree terminology precisely (height vs depth, full/complete/perfect/balanced/degenerate).
- Use the array representation of a complete tree (children 2i+1/2i+2, parent (i-1)/2) as the bridge to heaps.
- Free a tree safely with a post-order recursive destructor and build test trees from level-order input.

**Topics**
- `TreeNode { val, left, right }`; tree = pointer to root or `nullptr`.
- Root, leaf, internal, ancestor/descendant; height (-1 for empty) vs depth conventions.
- Tree types: full, complete, perfect, balanced, degenerate/pathological.
- Counting facts: height h has at most 2^(h+1)-1 nodes; min/max height for n nodes.
- Array representation of a complete tree; bridge to heaps.
- Post-order `deleteTree` destructor; `buildTree` from `[1,2,3,null,null,4,5]`; `nullptr` not `NULL`.

**In-class problems**
- Maximum Depth of Binary Tree.
- Same Tree.
- Invert / Mirror Binary Tree.
- Build a tree from a level-order array and free it with a post-order destructor.

### Lecture 30 — DFS Traversals: Preorder, Inorder, Postorder (Recursive & Iterative)

**Objectives**
- Implement all three DFS orders as one template with the visit-line moved, and explain each order's use.
- Convert recursive traversals to iterative ones with an explicit `std::stack` (including the hard postorder).
- Analyze traversal cost as O(n) time and O(h) call-stack space, noting skewed-tree overflow risk.

**Topics**
- Preorder (serialize/copy), inorder (sorted on a BST), postorder (delete/subtree aggregates).
- One recursive template; only the visit-position line changes.
- Iterative preorder (push right then left), iterative inorder (walk-left/pop/go-right).
- Iterative postorder: two-stack and single-stack-with-lastVisited methods.
- Morris traversal (O(1) space) as a challenge aside.
- Pass an accumulator by reference; never return-and-concatenate vectors (O(n^2)).

**Patterns:** Tree DFS.

**In-class problems**
- Binary Tree Inorder Traversal (iterative).
- Binary Tree Postorder Traversal (iterative).
- Path Sum (root-to-leaf target).
- Diameter of Binary Tree.

### Lecture 31 — BFS Level-Order Traversal & the Tree-BFS Pattern

**Objectives**
- Implement BFS with a queue using the level-size snapshot idiom to process one level per iteration.
- Solve level-order variants: zigzag, right-side view, level averages, connect-next-pointers.
- Articulate the DFS O(h) vs BFS O(w) space trade-off and when to choose each.

**Topics**
- BFS with `std::queue`; `int sz = q.size()` snapshot at the top of each level loop.
- Level order as `vector<vector<int>>`; zigzag/spiral via alternating reversal or deque.
- Right-side view, level averages, bottom-up level order, connect siblings.
- Complexity: O(n) time, O(w) space (up to n/2 at the last level).
- `queue::pop()` returns void (read `front()` first); avoid reading `q.size()` mid-level.

**Patterns:** Tree BFS.

**In-class problems**
- Binary Tree Level Order Traversal.
- Binary Tree Zigzag (Spiral) Level Order Traversal.
- Binary Tree Right Side View.
- Minimum Depth of Binary Tree.

### Lecture 32 — Tree DFS & BFS Patterns: Path, Subtree & Structure Problems

**Objectives**
- Recognize when info bubbles up from children (DFS) vs is organized by level (BFS) and pick the traversal.
- Use a recursive helper that returns a subtree summary while updating a global answer.
- Serialize/deserialize a tree and solve LCA, balance, and symmetry with the traversal patterns.

**Topics**
- DFS helper returning height/sum/found-flag while updating a global best.
- Path-sum-all-paths, diameter, balanced-height-check, lowest common ancestor.
- Symmetric tree and same-tree via paired recursion.
- Serialize/deserialize using DFS and BFS encodings.
- Pattern decision drill: "levels/depth/nearest" -> BFS; "paths/subtree aggregate" -> DFS.
- Timed mixed mock set spanning the tree DFS and tree BFS patterns.

**Patterns:** Tree DFS; tree BFS.

**In-class problems**
- Lowest Common Ancestor of a Binary Tree.
- Balanced Binary Tree.
- Symmetric Tree.
- Serialize and Deserialize Binary Tree.

### Homework

| Problem | Tier |
|---------|------|
| Maximum Depth of Binary Tree | Warmup |
| Invert Binary Tree | Warmup |
| Average of Levels in Binary Tree | Warmup |
| Binary Tree Level Order Traversal | Core |
| Binary Tree Zigzag Level Order Traversal | Core |
| Path Sum II (all root-to-leaf paths = target) | Core |
| Diameter of Binary Tree | Core |
| Lowest Common Ancestor of a Binary Tree | Core |
| Binary Tree Maximum Path Sum | Challenge |
| Serialize and Deserialize Binary Tree | Challenge |
| Construct Binary Tree from Preorder and Inorder Traversal | Challenge |

**Milestone:** Fluent tree mechanics (terminology, height/depth, array representation, safe destructor) and complete command of all three DFS orders (recursive and iterative) plus BFS level-order with the snapshot idiom, applied to path, subtree, and structure problems under timed conditions.

---

## Week 9 — Ordered Trees: BST and Self-Balancing (AVL)

**Theme:** Ordered Trees: BST and Self-Balancing (AVL)

You move from generic binary trees into ordered search trees, mastering BST insert/search/delete and validation, then learn why unbalanced BSTs degenerate and how AVL rotations guarantee O(log n) height. Red-black trees and `std::map` are framed as the professional default.

### Lecture 33 — Binary Search Trees: Invariant, Search, Insert, Successor

**Objectives**
- Internalize the recursive BST invariant (all-left < node < all-right) and use inorder = sorted as the keystone fact.
- Implement O(h) search and insert (insert always adds a leaf) using the return-the-new-subtree-root idiom.
- Compute predecessor/successor, floor, and ceiling on a BST.

**Topics**
- BST invariant stated recursively, not just parent-child.
- Search and insert in O(h); insert as leaf attachment.
- Inorder traversal of a BST yields sorted order.
- Inorder successor (leftmost of right subtree, else lowest ancestor) and predecessor.
- Floor, ceiling, and range queries.
- `std::set` / `std::map` as balanced BSTs; `lower_bound` / `upper_bound`; contrast with `unordered_set`.

**Patterns:** BST-ordered traversal; tree DFS.

**In-class problems**
- Search in a Binary Search Tree.
- Insert into a Binary Search Tree.
- Kth Smallest Element in a BST.
- Range Sum of BST.

### Lecture 34 — BST Deletion, Validation, and Balanced Construction

**Objectives**
- Handle all three BST deletion cases, replacing two-child nodes with the inorder successor.
- Validate a BST correctly by passing (min, max) bounds down the recursion, avoiding the immediate-parent-only bug.
- Build a height-balanced BST from a sorted array in O(n).

**Topics**
- Deletion case 1 (leaf), case 2 (one child splice), case 3 (two children -> inorder successor).
- Validation via bounds propagation; `long long` bounds to dodge `INT_MIN`/`INT_MAX` overflow.
- Alternative validation: inorder must be strictly increasing.
- Build balanced BST from a sorted array (pick the middle recursively).
- Average O(log n) vs degenerate O(n) height; sorted-insert degeneration motivates balancing.
- Duplicate-key policy decisions.

**Patterns:** BST-ordered traversal; tree DFS.

**In-class problems**
- Delete Node in a BST.
- Validate Binary Search Tree.
- Convert Sorted Array to Balanced BST.
- Lowest Common Ancestor of a BST.

### Lecture 35 — Why Balance Matters: AVL Trees and Rotations

**Objectives**
- Explain why an unbalanced BST degrades to O(n) and how the AVL balance-factor invariant guarantees Theta(log n) height.
- Perform left, right, left-right, and right-left rotations as O(1) pointer surgery that preserves the BST order.
- Implement AVL insert by walking back up and rotating the first unbalanced ancestor.

**Topics**
- AVL invariant: balance factor in {-1, 0, +1} for every node.
- Left and right rotations; before/after pointer diagrams.
- Four imbalance cases: LL, RR, LR, RL and how to detect each.
- AVL insert: BST insert then rebalance the first unbalanced ancestor.
- Storing and maintaining height in the node (null height = -1 convention).
- Recomputing heights after rotation, child first.

**Patterns:** BST-ordered traversal.

**In-class problems**
- Implement AVL insert with LL/RR/LR/RL rotations.
- Balance a Binary Search Tree.
- Compute height and balance factor of every node.
- Detect which rotation a given insertion triggers.

### Lecture 36 — AVL Delete, Red-Black Overview, and std::map

**Objectives**
- Implement AVL delete and recognize that rebalancing can cascade up multiple levels to the root.
- Compare AVL and red-black trees as a read-heavy vs write-heavy trade-off.
- Know when to hand-roll a balanced tree versus reach for `std::map` / `std::set`.

**Topics**
- AVL delete: BST delete then rotate up, possibly at multiple levels.
- Red-black big picture: the 5 properties, no two consecutive reds, equal black-height.
- AVL (tighter, read-favoring) vs red-black (fewer write rotations); `std::map` / `std::set` are red-black.
- B-tree / B+-tree one-line mention (disk and DB indexes).
- Interview framing: explain AVL, but reach for `std::map` in practice.

**In-class problems**
- Implement AVL delete with cascading rebalance.
- Count of Smaller Numbers After Self (BST / order-statistics).
- Use `std::map` `lower_bound`/`upper_bound` for floor and ceiling.
- Recover Binary Search Tree (two swapped nodes).

### Homework

| Problem | Tier |
|---------|------|
| Search in a Binary Search Tree | Warmup |
| Insert into a Binary Search Tree | Warmup |
| Two Sum IV - Input is a BST | Warmup |
| Lowest Common Ancestor of a BST | Warmup |
| Kth Smallest Element in a BST | Core |
| Validate Binary Search Tree | Core |
| Delete Node in a BST | Core |
| Convert Sorted Array to Balanced BST | Core |
| Inorder Successor in BST | Core |
| Implement AVL insert with all four rotations | Challenge |
| Implement AVL delete | Challenge |
| Binary Search Tree Iterator with O(h) space | Challenge |

**Milestone:** Implement a fully working BST (search/insert/delete/validate/successor) and an AVL tree with rotations and self-balancing insert, all using the return-the-new-subtree-root idiom and verified with assert-based tests.

---

## Week 10 — Binary Heaps, Priority Queues, and Heap Patterns

**Theme:** Binary Heaps, Priority Queues, and Heap Patterns

You build a binary heap from scratch (sift-up/down, O(n) build-heap, heapsort), master `std::priority_queue` and its inverted comparator, then drill the three heap-powered interview patterns: top-K, two heaps for streaming median, and K-way merge.

### Lecture 37 — Binary Heaps: Structure, Sift-Up, Sift-Down

**Objectives**
- State the two heap properties (complete-tree shape + partial heap order) and explain why a partial order is cheaper than a full order.
- Implement push (sift-up) and pop/extract (sift-down) in O(log n) on an array-backed heap.
- Use the array-as-tree index math: parent (i-1)/2, children 2i+1 and 2i+2.

**Topics**
- Shape property (complete binary tree) + order property (parent <= children for a min-heap).
- Array representation; parent/child index arithmetic; no pointers, cache-friendly.
- push: append then sift-up; pop: swap root with last, shrink, sift-down.
- `top()` in O(1).
- Min-heap vs max-heap; converting by negation or comparator flip.

**In-class problems**
- Implement a binary min-heap (push/pop/top) from scratch.
- Last Stone Weight.
- Kth Largest Element in a Stream.
- Sift-down a single element into a valid heap.

### Lecture 38 — Build-Heap, Heapsort, and Heap Limitations

**Objectives**
- Derive why Floyd's build-heap is O(n), not O(n log n).
- Implement in-place heapsort and characterize it as O(n log n), in-place, and unstable.
- Recognize heap limitations: no efficient arbitrary search, no ordered iteration, no built-in decrease-key.

**Topics**
- Floyd's build-heap: sift-down from n/2-1 to 0; the telescoping-sum O(n) proof.
- Heapsort: build a max-heap, repeatedly swap root to end and sift-down.
- Heapsort vs quicksort (no O(n^2) worst case, worse constants/cache).
- Heap weaknesses: O(n) arbitrary search, no sorted iteration.
- decrease-key needs a position map; lazy-deletion / push-duplicates-and-skip pattern (Dijkstra preview).

**In-class problems**
- Implement build-heap in O(n) and prove the bound.
- Heapsort from scratch (ascending via max-heap).
- Convert a min-heap to a max-heap.
- Show heap search is O(n) with a counterexample.

### Lecture 39 — std::priority_queue, Top-K, and the Comparator Trap

**Objectives**
- Use `std::priority_queue` (max-heap default) and build a min-heap with `greater<>` and custom comparators.
- Solve Top-K with a size-K heap, getting the counterintuitive direction right (min-heap for K-largest).
- Avoid the comparator inversion bug where the comparator defines lower priority.

**Topics**
- `std::priority_queue` API; min-heap via `priority_queue<int, vector<int>, greater<int>>`.
- Custom struct and lambda comparators; the comparator returns true for LOWER priority.
- Top-K largest: min-heap of size K, pop the smallest when size > K, O(n log K).
- Top-K frequent via hashing + heap.
- `make_heap`/`push_heap`/`pop_heap` and `std::nth_element` as related tools.

**Patterns:** Top-K Elements.

**In-class problems**
- Kth Largest Element in an Array.
- Top K Frequent Elements.
- K Closest Points to Origin.
- Sort Characters by Frequency.

### Lecture 40 — Two Heaps, K-Way Merge, and Heap Synthesis

**Objectives**
- Maintain a running median with a max-heap (lower half) and min-heap (upper half), balanced so the tops straddle the middle.
- Merge K sorted sequences with a min-heap of current heads in O(N log K).
- Choose the right heap pattern from a problem's signal words.

**Topics**
- Two heaps: max-heap of the lower half + min-heap of the upper half; rebalancing.
- K-way merge: heap of (value, source index); pull min, push successor.
- Connection back to merge sort's merge step.
- Pattern triggers: median/balance -> two heaps; K largest/smallest -> top-K; merge K sorted -> K-way merge.

**Patterns:** Two Heaps; K-Way Merge; Top-K Elements.

**In-class problems**
- Find Median from Data Stream.
- Merge k Sorted Lists.
- Kth Smallest Element in a Sorted Matrix.
- Find K Pairs with Smallest Sums.

### Homework

| Problem | Tier |
|---------|------|
| Last Stone Weight | Warmup |
| Kth Largest Element in a Stream | Warmup |
| Sort Characters by Frequency | Warmup |
| Kth Largest Element in an Array | Core |
| Top K Frequent Elements | Core |
| K Closest Points to Origin | Core |
| Task Scheduler | Core |
| Reorganize String | Core |
| Implement a binary min-heap with build-heap from scratch | Core |
| Find Median from Data Stream | Challenge |
| Merge k Sorted Lists | Challenge |
| Kth Smallest Element in a Sorted Matrix | Challenge |

**Milestone:** Build a from-scratch binary heap with O(n) build-heap and a working heapsort, then solve a streaming-median problem with two heaps and a merge-k-sorted-lists problem with a K-way-merge heap, all benchmarked and assert-tested.

---

## Week 11 — Tries and Union-Find: Prefix and Partition Structures

**Theme:** Tries and Union-Find: Prefix and Partition Structures

You implement a trie for O(L) prefix queries and apply it to autocomplete and the trie-plus-backtracking Word Search II, then build a union-find (disjoint set) with union-by-rank and path compression, using it for connectivity, cycle detection, and as the engine that bridges into the graph track.

### Lecture 41 — Tries: Prefix Trees, Insert, Search, startsWith

**Objectives**
- Explain how shared prefixes share nodes, making insert/search/startsWith O(L) independent of the dictionary size.
- Implement a trie node with children plus an `isEndOfWord` flag, distinguishing exact search from prefix search.
- Choose between an `array[26]` and a hash-map children representation by alphabet size and density.

**Topics**
- Trie structure: a path spells a string; shared prefixes share nodes.
- insert, search (must check `isEndOfWord`), startsWith (prefix exists) all O(L).
- `children[26]` (fast, memory-heavy) vs `unordered_map<char, Node*>` (compact).
- Value-initializing child pointers to `nullptr`; recursive destructor.
- Delete as a Challenge: unmark and prune leaf nodes back up.

**Patterns:** Trie (prefix tree) traversal.

**In-class problems**
- Implement Trie (insert/search/startsWith).
- Longest Word in Dictionary (built one char at a time).
- Replace Words (dictionary roots).
- Count words with a given prefix.

### Lecture 42 — Trie Applications: Wildcards, Word Search II, Max-XOR

**Objectives**
- Support wildcard matching by branching DFS over trie children at a `.`.
- Synthesize trie + backtracking to solve Word Search II efficiently on a grid.
- Use a bitwise trie to find the maximum XOR of two numbers.

**Topics**
- Wildcard / `.` matching via DFS over branches.
- Word Search II: build a trie of words, DFS the grid pruning by trie edges.
- Why the trie turns O(W*cells*4^L) brute force into one shared prefix walk.
- Bitwise trie of bits for maximum-XOR queries.
- Memory note: compressed/radix (Patricia) tries.

**Patterns:** Trie (prefix tree) traversal; subsets / backtracking.

**In-class problems**
- Add and Search Words Data Structure (wildcard `.`).
- Word Search II.
- Maximum XOR of Two Numbers in an Array (bitwise trie).
- Design a prefix-based autocomplete.

### Lecture 43 — Union-Find: Union by Rank and Path Compression

**Objectives**
- Implement disjoint-set find and union over a forest, always operating on roots.
- Apply union-by-rank/size and path compression to achieve O(alpha(n)) amortized per operation.
- Maintain a running component count, decrementing on each successful union.

**Topics**
- DSU as a forest; `find(x)` returns the representative root.
- Union by rank/size: attach the smaller tree under the larger.
- Path compression: recursive full vs iterative path-halving.
- Inverse Ackermann alpha(n) bound (<= 4 in practice).
- `parent[]` / `rank[]` init with `iota`; mapping labels and 2D grids to indices (`r*cols+c`).
- Component count maintenance.

**Patterns:** Union-Find (disjoint set).

**In-class problems**
- Implement Union-Find with union-by-rank and path compression.
- Number of Connected Components in an Undirected Graph.
- Number of Provinces (Friend Circles).
- Find if Path Exists in Graph.

### Lecture 44 — Union-Find Applications and the Bridge to Graphs

**Objectives**
- Use DSU for cycle detection in undirected graphs and for incremental/dynamic connectivity.
- Recognize when DSU beats BFS/DFS (edges arriving over time, online connectivity queries).
- Connect DSU to Kruskal's MST and grid-component problems as a preview of the graph track.

**Topics**
- Cycle detection: union endpoints, same root before union means a cycle.
- Redundant connection, accounts merge, equation satisfiability, islands via DSU.
- DSU is merge-only (no split/deletion); rollback as an advanced aside.
- When DSU beats DFS: dynamic connectivity and offline merging.
- Kruskal's MST preview: DSU is the engine.

**Patterns:** Union-Find (disjoint set); graph BFS/DFS & components.

**In-class problems**
- Redundant Connection.
- Accounts Merge.
- Satisfiability of Equality Equations.
- Number of Islands via union-find.

### Homework

| Problem | Tier |
|---------|------|
| Implement Union-Find from scratch with both optimizations | Warmup |
| Number of Provinces | Warmup |
| Find if Path Exists in Graph | Warmup |
| Implement Trie (insert/search/startsWith) | Core |
| Add and Search Words Data Structure | Core |
| Replace Words | Core |
| Redundant Connection | Core |
| Number of Connected Components in an Undirected Graph | Core |
| Satisfiability of Equality Equations | Core |
| Word Search II | Challenge |
| Maximum XOR of Two Numbers in an Array | Challenge |
| Accounts Merge | Challenge |

**Milestone:** Ship a from-scratch trie (insert/search/startsWith plus wildcard) used to solve Word Search II, and a union-find with union-by-rank and path compression used for connected components and undirected cycle detection, both assert-tested and ready to feed the graph track.

---

## Week 12 — Graphs Part 1: Representation, Traversal, and Ordering

**Theme:** Graphs Part 1: Representation, Traversal, and Ordering

You represent graphs as adjacency lists/matrices, traverse them with DFS and BFS (recursive and iterative), and apply traversal to connected components, undirected and directed cycle detection, and topological sort of a DAG via both Kahn's and DFS methods.

### Lecture 45 — Graph Representation and Depth-First Search

**Objectives**
- Choose between adjacency list, adjacency matrix, and edge list by graph density and query needs.
- Implement DFS both recursively and iteratively with an explicit stack and disciplined visited marking.
- Treat grids as implicit graphs (cells as nodes, 4/8 neighbors as edges).

**Topics**
- Directed/undirected, weighted, DAG, dense vs sparse definitions.
- Adjacency list O(V+E) vs adjacency matrix O(V^2) vs edge list.
- Recursive DFS and iterative DFS with `std::stack` (avoids deep-recursion overflow).
- Marking visited on entry/push, not on pop.
- Grids as implicit graphs: flood fill, number of islands.
- `vector<bool>` visited proxy-element warning.

**Patterns:** Graph BFS/DFS & components; tree DFS.

**In-class problems**
- Number of Islands.
- Flood Fill.
- Clone Graph.
- Iterative DFS of an adjacency list.

### Lecture 46 — Connected Components and Cycle Detection

**Objectives**
- Count connected components in an undirected graph via repeated DFS launches (or union-find).
- Detect cycles correctly: parent-exclusion in undirected graphs, gray-node/back-edge (3-color) in directed graphs.
- Use DFS discovery/finish timestamps and recognize the false-positive undirected cycle bug.

**Topics**
- Connected components = number of DFS launches from unvisited nodes.
- Edge classification on the DFS tree; a back edge means a directed cycle.
- 3-color (white/gray/black) directed cycle detection.
- Undirected cycle detection via parent check or union-find.
- Discovery/finish times; bridges and articulation points (conceptual).

**Patterns:** Graph BFS/DFS & components.

**In-class problems**
- Number of Provinces (DFS version).
- Detect Cycle in a Directed Graph (3-color).
- Detect Cycle in an Undirected Graph.
- Pacific Atlantic Water Flow.

### Lecture 47 — Breadth-First Search and Shortest Paths on Unweighted Graphs

**Objectives**
- Use BFS with a queue to find shortest paths (fewest edges) on unweighted graphs, marking visited on enqueue.
- Apply multi-source BFS by seeding the queue with all sources at distance 0.
- Use 0-1 BFS with a deque for graphs with 0/1 edge weights.

**Topics**
- BFS distance layers; mark visited on enqueue to avoid re-enqueueing.
- Shortest path by edge count; why BFS is not a substitute for Dijkstra on weighted graphs.
- Multi-source BFS (rotting oranges, nearest exit).
- 0-1 BFS with a deque (push-front for a 0-weight edge).
- Encoding grid cells as `r*cols+c`.

**Patterns:** Graph BFS/DFS & components; tree BFS; multi-source BFS.

**In-class problems**
- Rotting Oranges (multi-source BFS).
- Word Ladder.
- Shortest Path in Binary Matrix.
- Walls and Gates.

### Lecture 48 — Topological Sort of a DAG

**Objectives**
- Produce a topological ordering with Kahn's indegree-based BFS, detecting cycles when fewer than V nodes emit.
- Produce a topological ordering via DFS reverse-finish order.
- Apply topo sort to dependency/prerequisite problems and recognize it enables DAG-DP.

**Topics**
- DAG and topological order; exists iff acyclic.
- Kahn's algorithm: indegree array + queue; cycle detection as a side effect.
- DFS-based topo sort: reverse of finish order.
- Lexicographically smallest order via a priority_queue/set in Kahn's.
- Applications: course schedule, build order; forward link to DAG longest-path DP.

**Patterns:** Topological sort; graph BFS/DFS & components.

**In-class problems**
- Course Schedule (cycle detection).
- Course Schedule II (topological order).
- Alien Dictionary.
- Minimum Height Trees.

### Homework

| Problem | Tier |
|---------|------|
| Number of Islands | Warmup |
| Flood Fill | Warmup |
| Find if Path Exists in Graph | Warmup |
| Clone Graph | Core |
| Number of Provinces | Core |
| Course Schedule | Core |
| Course Schedule II | Core |
| Rotting Oranges | Core |
| Word Ladder | Core |
| Pacific Atlantic Water Flow | Core |
| Alien Dictionary | Challenge |
| Detect Cycle in a Directed Graph with 3-color DFS | Challenge |

**Milestone:** Build a reusable graph module (adjacency-list with recursive and iterative DFS, BFS, multi-source BFS) and use it to solve connected components, directed and undirected cycle detection, and topological sort via both Kahn's and DFS, leaving you ready for weighted-graph algorithms in the next track.

---

## Week 13 — Graphs Part 2: Weighted Shortest Paths & Minimum Spanning Trees

**Theme:** Graphs Part 2 — Weighted Shortest Paths & Minimum Spanning Trees

Build on the unweighted graph traversals from Week 12 to handle weighted graphs: single-source, all-pairs, and minimum-cost-connection algorithms. Bellman-Ford and Floyd-Warshall are taught explicitly as dynamic programming on graphs, planting the DP seed that Weeks 14-15 harvest.

### Lecture 49 — Dijkstra's Algorithm: Single-Source Shortest Path with a Min-Heap

**Objectives**
- Implement Dijkstra with a priority queue and explain why it requires non-negative edge weights.
- Use the lazy-deletion idiom (push duplicates, skip stale pops) since `std::priority_queue` lacks decrease-key.
- Reconstruct the actual shortest path and apply Dijkstra to grid/cost variants.

**Topics**
- Weighted graph representation (adjacency list of (neighbor, weight) pairs).
- Greedy finalize-the-closest invariant and why a negative edge breaks it.
- Min-heap via `priority_queue<pair, vector, greater<>>`.
- O((V+E) log V) complexity.
- Path reconstruction with a parent array.
- Dijkstra on implicit grids.

**Patterns:** Weighted shortest path & MST.

**In-class problems**
- Network Delay Time.
- Path with Minimum Effort.
- Cheapest Flights Within K Stops (Dijkstra-with-stops framing).
- Swim in Rising Water.

### Lecture 50 — Bellman-Ford: Negative Edges, Negative-Cycle Detection, and DP-on-Edges

**Objectives**
- Relax all edges V-1 times and explain Bellman-Ford as DP over "shortest path using at most k edges".
- Detect a reachable negative cycle with a V-th relaxation pass.
- Choose Bellman-Ford over Dijkstra when negative weights are present.

**Topics**
- Edge-list representation and the relaxation operation.
- dist-after-k-rounds = shortest path using <= k edges (the DP framing).
- Negative-cycle detection.
- O(V*E) complexity.
- SPFA as a queue-based optimization (with a caveat).
- Overflow guard: skip relaxation through INF, use `long long`.

**Patterns:** Weighted shortest path & MST.

**In-class problems**
- Cheapest Flights Within K Stops (bounded Bellman-Ford).
- Negative Weight Cycle detection.
- Network Delay Time (Bellman-Ford version).

### Lecture 51 — Floyd-Warshall: All-Pairs Shortest Paths as 3-Loop DP

**Objectives**
- Derive the k-as-intermediate recurrence and implement Floyd-Warshall with k as the outermost loop.
- Compute transitive closure and detect negative cycles via the diagonal.
- Decide when all-pairs O(V^3) beats running single-source V times.

**Topics**
- `dp[i][j]` using intermediates from {0..k}.
- Critical loop order (k outermost) and the classic bug of getting it wrong.
- Diagonal init `dp[i][i]=0`; INF+INF overflow guard.
- Transitive closure via boolean OR.
- When V is small (<= 400).

**Patterns:** Weighted shortest path & MST.

**In-class problems**
- Find the City With the Smallest Number of Neighbors at a Threshold Distance.
- Course Schedule IV (reachability via transitive closure).
- All-Pairs Shortest Path on a small weighted graph.

### Lecture 52 — Minimum Spanning Trees: Prim & Kruskal

**Objectives**
- State the cut property and use it to justify both Prim's and Kruskal's greedy choices.
- Implement Prim's with a min-heap and Kruskal's with union-find, choosing by graph density.
- Distinguish an MST (minimize total weight) from a shortest-path tree (Dijkstra).

**Topics**
- MST definition and the cut property.
- Prim's: grow from a seed with a min-heap and an `inMST` array, O((V+E) log V).
- Kruskal's: sort edges + union-find with path compression, O(E log E).
- Dense vs sparse trade-off.
- MST vs shortest-path-tree contrast.

**Patterns:** Weighted shortest path & MST; Union-Find.

**In-class problems**
- Min Cost to Connect All Points.
- Connecting Cities With Minimum Cost.
- Kruskal's MST end-to-end with union-find.
- Optimize Water Distribution in a Village.

### Homework

| Problem | Tier |
|---------|------|
| Network Delay Time | Warmup |
| Find if Path Exists in Graph | Warmup |
| Path with Minimum Effort | Core |
| Cheapest Flights Within K Stops | Core |
| Min Cost to Connect All Points | Core |
| Find the City With the Smallest Number of Neighbors | Core |
| Swim in Rising Water | Challenge |
| Bellman-Ford negative-cycle detection from scratch | Core |
| Connecting Cities With Minimum Cost | Core |
| Reconstruct Itinerary | Challenge |

**Milestone:** You can pick and implement the correct weighted-graph algorithm (Dijkstra / Bellman-Ford / Floyd-Warshall / Prim / Kruskal) from a problem's edge-weight and density signals, and can articulate Bellman-Ford and Floyd-Warshall as dynamic programming, priming the DP block.

---

## Week 14 — Backtracking: Exhaustive Search with Pruning

**Theme:** Backtracking — Exhaustive Search with Pruning

Master the choose / explore / un-choose template across enumeration (subsets, permutations, combinations) and constraint-satisfaction (N-Queens, Sudoku, word search). This is taught immediately before DP because dynamic programming is literally backtracking plus memoization.

### Lecture 53 — Backtracking Fundamentals: Subsets, Combinations, Permutations

**Objectives**
- Apply the choose/explore/un-choose template and draw the state-space (decision) tree.
- Generate subsets, combinations, and permutations, including correct duplicate handling.
- Recognize why "undo the choice" is the defining mechanic of backtracking.

**Topics**
- The backtracking template and decision-tree model.
- Subsets via include/exclude vs the start-index loop.
- Combinations and combination sum.
- Permutations via a `used[]` array vs swap-in-place.
- Duplicate dedup: sort then skip `i>start && a[i]==a[i-1]`.

**Patterns:** Subsets/permutations (backtracking).

**In-class problems**
- Subsets / Subsets II.
- Permutations / Permutations II.
- Combination Sum / Combination Sum II.
- Letter Combinations of a Phone Number.

### Lecture 54 — Backtracking on Strings & Partitions

**Objectives**
- Backtrack over string-splitting and validity-checking problems.
- Record solutions at leaves by copying the path (not storing a reference).
- Add early validity checks to prune dead branches.

**Topics**
- Path passed by reference with `push_back`/`pop_back` around the recursive call.
- `result.push_back(path)` copies intentionally.
- Palindrome partitioning (split + is-palindrome check).
- Generate Parentheses (open/close count constraints).
- Restore IP Addresses (segment validity pruning).

**Patterns:** Subsets/permutations (backtracking).

**In-class problems**
- Generate Parentheses.
- Palindrome Partitioning.
- Restore IP Addresses.
- Word Break II.

### Lecture 55 — Constraint Backtracking: N-Queens & Sudoku

**Objectives**
- Encode constraints (columns, both diagonals) for O(1) feasibility checks.
- Solve Sudoku via constraint propagation and an MRV-style cell choice.
- Show how strong, early pruning is the difference between timing out and passing.

**Topics**
- N-Queens: occupied columns and diagonals via `r+c` and `r-c+n` indices.
- `bitset`/`vector<bool>` occupancy; a bitmask teaser for Week 16.
- Sudoku solver: row/col/box constraint sets.
- Feasibility checks and bounding as pruning.
- Counting vs listing all solutions.

**Patterns:** Subsets/permutations (backtracking).

**In-class problems**
- N-Queens.
- N-Queens II (count solutions).
- Sudoku Solver.
- Valid Sudoku (constraint-set warmup).

### Lecture 56 — Grid Backtracking & Pruning Mastery (Word Search) + Trie Synthesis

**Objectives**
- DFS a grid with in-place visited-marking and restore-on-backtrack.
- Combine a trie with grid backtracking to share prefixes across many words.
- State a general pruning checklist: feasibility, ordering, and bounding.

**Topics**
- Word Search: mutate the grid with a sentinel, restore on return.
- Why a separate visited array is avoidable.
- Word Search II: build a trie of words, prune grid DFS by trie edges.
- Turning O(W*cells*4^L) brute force into one shared prefix walk.
- General pruning heuristics.

**Patterns:** Subsets/permutations (backtracking); trie traversal.

**In-class problems**
- Word Search.
- Word Search II (trie + backtracking).
- Number of Islands (DFS framing).
- Combinations review under a time limit.

### Homework

| Problem | Tier |
|---------|------|
| Subsets | Warmup |
| Combinations | Warmup |
| Letter Combinations of a Phone Number | Warmup |
| Permutations II | Core |
| Combination Sum II | Core |
| Generate Parentheses | Core |
| Palindrome Partitioning | Core |
| Word Search | Core |
| N-Queens | Challenge |
| Sudoku Solver | Challenge |
| Word Search II | Challenge |
| Restore IP Addresses | Core |

**Milestone:** You can write the choose/explore/un-choose template from scratch for any enumeration or constraint problem, handle duplicates correctly, and add pruning that keeps exponential searches tractable, ready to convert exhaustive recursion into memoized DP next week.

---

## Week 15 — Dynamic Programming I: Recurrence Recognition, Knapsack, and Sequence DP

**Theme:** Dynamic Programming I — Recurrence Recognition, Knapsack, and Sequence DP

The hardest topic, opened deliberately right after backtracking: DP = backtracking + memoization. Move from recognizing the recurrence and memoization-vs-tabulation through 1D DP, the 0/1 and unbounded knapsack families, and the classic sequence DPs (LIS, LCS, edit distance).

### Lecture 57 — DP Intro: Recognizing the Recurrence, Memoization vs Tabulation

**Objectives**
- Identify the two DP pillars: overlapping subproblems and optimal substructure.
- Convert a brute-force recursion into a top-down memoized solution, then a bottom-up table.
- Design a complete, correct state and contrast DP with divide & conquer.

**Topics**
- The 5-step workflow: brute recursion -> identify state -> memoize -> tabulate -> optimize space.
- Overlapping subproblems (DP) vs disjoint subproblems (D&C).
- Memo as a vector initialized to sentinel -1; `unordered_map` for sparse keys.
- 1D DP on-ramp: Fibonacci, climbing stairs, house robber.
- Rolling-variable O(1) space.

**Patterns:** 1D DP (Fibonacci-style).

**In-class problems**
- Climbing Stairs (recursive -> memo -> tab).
- House Robber / House Robber II.
- Decode Ways.
- Maximum Subarray (Kadane).

### Lecture 58 — 0/1 Knapsack Family: Pick or Leave

**Objectives**
- Model the take-or-skip decision with state (index, remaining capacity).
- Space-optimize to one row and iterate capacity backwards to avoid reusing an item.
- Map subset-sum and partition problems onto the knapsack skeleton.

**Topics**
- 0/1 knapsack 2D then 1D DP.
- The signature bug: a forward capacity loop reuses items.
- Subset sum / partition equal subset sum.
- Target Sum as a +/- partition.
- Overflow on large value sums.

**Patterns:** Knapsack (0/1 + unbounded).

**In-class problems**
- 0/1 Knapsack from scratch.
- Partition Equal Subset Sum.
- Target Sum.
- Last Stone Weight II.

### Lecture 59 — Unbounded Knapsack & Counting: Coin Change

**Objectives**
- Allow item reuse by iterating capacity forwards (the mirror of the 0/1 bug).
- Distinguish counting combinations vs permutations by loop-nesting order.
- Handle min vs count aggregation and safe "infinity" sentinels.

**Topics**
- Unbounded knapsack.
- Coin Change (min coins) vs Coin Change II (count ways).
- Coins-outer/amount-inner = combinations; amount-outer/coins-inner = permutations.
- `amount+1` as a safe infinity to avoid `INT_MAX` overflow.
- Perfect squares / integer break.

**Patterns:** Knapsack (0/1 + unbounded).

**In-class problems**
- Coin Change (min).
- Coin Change II (count combinations).
- Combination Sum IV (permutation count).
- Perfect Squares.

### Lecture 60 — Sequence DP: LIS, LCS, and Edit Distance

**Objectives**
- Solve LIS in O(n^2) then O(n log n) using the tails array with binary search.
- Build the 2D prefix-comparison table for LCS and edit distance.
- Reconstruct the actual subsequence or operation list by walking the table.

**Topics**
- LIS: `dp[i]=1+max(dp[j])`; patience/tails + `lower_bound` for O(n log n).
- Subsequence vs substring; strict vs non-strict (`<` vs `<=`, `lower` vs `upper_bound`).
- LCS 2D recurrence on string prefixes.
- Edit distance (insert/delete/replace).
- Reconstruction by backtracking through the DP table.

**Patterns:** String DP (LCS / edit / palindrome); modified binary search (+ on the answer).

**In-class problems**
- Longest Increasing Subsequence (O(n^2) and O(n log n)).
- Longest Common Subsequence.
- Edit Distance.
- Delete Operation for Two Strings.

### Homework

| Problem | Tier |
|---------|------|
| Climbing Stairs | Warmup |
| House Robber | Warmup |
| Coin Change | Core |
| Coin Change II | Core |
| Partition Equal Subset Sum | Core |
| Target Sum | Core |
| Longest Increasing Subsequence | Core |
| Longest Common Subsequence | Core |
| Edit Distance | Core |
| Word Break | Core |
| Combination Sum IV | Challenge |
| Decode Ways | Core |

**Milestone:** You can recognize a DP problem from its overlapping-subproblem structure, design a correct state, write both top-down and bottom-up solutions, fix the forward/backward knapsack loop direction from memory, and reconstruct optimal solutions from sequence-DP tables.

---

## Week 16 — DP Finale, Greedy, Bit/Math & Interview-Ready Capstone

**Theme:** DP Finale, Greedy, Bit/Math & Interview-Ready Capstone

Close the course: finish DP with grid/range/tree/bitmask variants, then add greedy (and when it provably fails vs DP), bit manipulation, and math/number theory. Two timed mock interviews, a capstone, and a curated top-150 review (reinforcing DP throughout) make you interview-ready.

### Lecture 61 — DP II: Grid, Range, Tree & Bitmask DP

**Objectives**
- Solve grid DP (paths, min path, maximal square, backward "dungeon" DP).
- Apply interval/range DP by looping on increasing length with a split point.
- Extend DP onto trees (post-order subtree DP) and subsets (bitmask DP), tying back to topological-order DAG-DP.

**Topics**
- Grid DP and rolling-row space optimization.
- Range DP: `dp[i][j]` by length, split at k, O(n^3) (burst balloons, MCM, palindrome partition).
- Tree DP via post-order DFS and rerooting.
- Bitmask DP (subset-as-state, TSP-style), `1LL<<n` overflow caution.
- Counting DP with `% MOD`; DAG longest path over a topo order.

**Patterns:** 2D / grid DP; string DP (LCS / edit / palindrome); tree DFS; bitwise XOR & bit manipulation.

**In-class problems**
- Unique Paths II / Minimum Path Sum.
- Maximal Square.
- Burst Balloons (range DP).
- House Robber III (tree DP).

### Lecture 62 — Greedy: Exchange Arguments and When NOT to Be Greedy

**Objectives**
- Apply the greedy template to interval scheduling and prove it with an exchange argument.
- Contrast fractional knapsack (greedy works) with 0/1 knapsack (needs DP).
- Recognize problems where a local choice silently fails and DP is required.

**Topics**
- Greedy-choice property + optimal substructure.
- Interval scheduling: sort by finish time.
- Merge intervals / non-overlapping intervals / minimum arrows.
- Fractional vs 0/1 knapsack counterexample.
- Huffman coding via a min-heap; "greedy stays ahead" vs the exchange argument.

**Patterns:** Merge intervals; weighted shortest path & MST.

**In-class problems**
- Non-overlapping Intervals.
- Merge Intervals.
- Jump Game II.
- Task Scheduler.

### Lecture 63 — Bit Manipulation & Math / Number Theory

**Objectives**
- Use XOR identities and bit tricks for O(1)-space solutions and subset enumeration.
- Apply GCD/LCM, modular arithmetic, fast modular exponentiation, and the sieve.
- Avoid the common overflow, precedence, and negative-modulo pitfalls.

**Topics**
- AND/OR/XOR/shifts; `x&-x` lowest set bit, `x&(x-1)` clear lowest bit, power-of-two test.
- XOR pattern: single/missing number; subset masks; bridge to bitmask DP.
- Euclid GCD/LCM; modular add/mul keeping `% MOD`.
- Fast modular exponentiation O(log n); Sieve of Eratosthenes.
- Pitfalls: `1<<31` UB, `&`/`|` precedence, `((x%m)+m)%m`.

**Patterns:** Bitwise XOR & bit manipulation.

**In-class problems**
- Single Number / Single Number II.
- Missing Number (XOR).
- Count Primes (Sieve).
- Pow(x, n) / fast modular exponentiation.

### Lecture 64 — Capstone: Two Timed Mock Interviews + Top-150 Pattern Review

**Objectives**
- Run the full interview loop (clarify -> brute force -> optimize -> code -> test -> complexity) under time pressure.
- Map input constraints to the right technique via a decision-tree cheat sheet.
- Reinforce DP and the course's 28 patterns through a curated top-150 mixed set.

**Topics**
- Two timed mock interviews under realistic conditions.
- Constraint-to-technique mapping (n<=20 bitmask/backtracking; n<=500 O(n^3)/Floyd; n<=1e5 O(n log n); "minimize the max" -> BS on the answer).
- Reach-for-it pattern table across all 28 patterns.
- Curated top-150 review with extra DP reinforcement.
- Capstone synthesis problem.

**Patterns:** 1D DP (Fibonacci-style); knapsack (0/1 + unbounded); string DP (LCS / edit / palindrome); modified binary search (+ on the answer); subsets/permutations (backtracking).

**In-class problems**
- Timed Mock Interview A (graph + DP mixed).
- Timed Mock Interview B (backtracking + greedy mixed).
- Capstone: Best Time to Buy and Sell Stock with Cooldown.
- Top-150 lightning round (mixed patterns).

### Homework

| Problem | Tier |
|---------|------|
| Unique Paths II | Core |
| Maximal Square | Core |
| Burst Balloons | Challenge |
| House Robber III | Challenge |
| Non-overlapping Intervals | Core |
| Jump Game II | Core |
| Single Number III | Core |
| Counting Bits | Warmup |
| Count Primes | Core |
| Best Time to Buy and Sell Stock with Cooldown | Challenge |
| Regular Expression Matching | Challenge |
| Curated top-150 self-assessment set (mixed difficulty) | Mixed |

**Milestone:** You complete the course interview-ready: you can recognize the right pattern from problem signals across all 28 patterns, solve graph/backtracking/DP/greedy/bit/math problems fluently, and perform under timed mock-interview conditions, having reinforced DP one final time through a curated top-150 review.
