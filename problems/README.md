# Master Problem Bank

This is the spine of the course. The lectures teach a pattern; this file is where you drill it until the pattern is automatic. There are more than 400 problems here (412 total), grouped by topic and by difficulty tier, each mapped to the week it belongs to.

Every problem uses its real, well-known name (LeetCode number, CLRS, or classic-interview canon) so you can find it on any judge. Nothing here is a made-up exercise you can only solve inside this course.

---

## How to use this bank

Three difficulty tiers, and they mean specific things:

- **Warmup** — mechanics. You should finish one in 10 to 15 minutes. If a Warmup is hard, you are missing a prerequisite, not a clever trick. Go back.
- **Core** — the must-know rep for the pattern. These are what interviews actually ask. Treat every Core problem as required.
- **Challenge** — stretch. Harder cases, nastier constraints, or two patterns stacked. Optional but encouraged. The students who clear most of these are the ones who pass the hard onsites.

### How many per week

Aim for roughly 15 to 20 problems a week: all the Warmups, every Core, and as many Challenges as you have time for. That is the volume the course is built around. Fewer than that and the patterns will not stick; the point of a problem-heavy course is that you actually solve the problems.

The graded homework set each week is 10 problems (3 Warmup, 5 Core, 2 Challenge). The rest of the list is your practice surface.

### When to look at the solution

The honest rule: struggle first, then look, then re-solve from scratch.

1. Spend a real, uninterrupted attempt. For Warmup, about 15 minutes. For Core, 30 to 40. For Challenge, up to an hour. Being stuck is where the learning happens, so do not bail early.
2. When you hit the wall, look at a hint or the pattern name only, not the full solution. Often that is enough.
3. If you read the full solution, close it and re-implement from an empty file the same day. Reading a solution and understanding it is not the same as being able to produce it. You only own a problem once you can write it cold.
4. Mark anything you needed the solution for, and re-solve it 3 days later, then a week later. That spacing is what moves a pattern into long-term memory.

### Spaced repetition

Keep a short list of problems you got wrong or needed help on. Re-solve each one on a 3-day, 1-week, 1-month schedule. A problem you can write from scratch a month later is a problem you know. A problem you solved once and never revisited is a problem you will fumble in the interview. The list does not need to be fancy; a text file with dates is enough.

### Tracking

Tick problems as you go. A simple convention that works:

- `[ ]` not attempted
- `[~]` attempted, needed a hint or the solution
- `[x]` solved cold, no help

The `[~]` items are your repetition queue.

---

## Contents

| Week | Theme | Jump |
|------|-------|------|
| 1 | Complexity analysis + UPSCR + C++/STL tooling | [Week 1](#week-1--complexity-analysis) |
| 2 | Recursion and recurrences | [Week 2](#week-2--recursion-and-recurrences) |
| 3 | Dynamic arrays & strings; two pointers; prefix sums; sliding window | [Week 3](#week-3--dynamic-arrays-strings-two-pointers-prefix-sums-sliding-window) |
| 4 | Hashing; cyclic sort; merge intervals | [Week 4](#week-4--hashing-cyclic-sort-merge-intervals) |
| 5 | Linked lists; fast & slow pointers; in-place reversal; LRU cache | [Week 5](#week-5--linked-lists-fast--slow-pointers-in-place-reversal) |
| 6 | Stacks; queues/deque; circular queue; monotonic stack & deque | [Week 6](#week-6--stacks-queues-monotonic-stack--deque) |
| 7 | Sorting; quickselect; divide & conquer; binary search + binary search on the answer | [Week 7](#week-7--sorting-divide--conquer-binary-search) |
| 8 | Binary trees; DFS preorder/inorder/postorder; BFS level-order | [Week 8](#week-8--binary-trees-dfs--bfs) |
| 9 | Binary search trees; AVL & rotations; std::map | [Week 9](#week-9--binary-search-trees-avl--rotations) |
| 10 | Binary heaps & priority queues; heapsort; top-K; two heaps; K-way merge | [Week 10](#week-10--heaps-top-k-two-heaps-k-way-merge) |
| 11 | Tries; union-find | [Week 11](#week-11--tries-and-union-find) |
| 12 | Graphs I — representation, DFS, BFS, components, cycle detection, topological sort | [Week 12](#week-12--graphs-i) |
| 13 | Graphs II — Dijkstra, Bellman-Ford, Floyd-Warshall, MST | [Week 13](#week-13--graphs-ii) |
| 14 | Backtracking — subsets, combinations, permutations, N-Queens, Sudoku, word search | [Week 14](#week-14--backtracking) |
| 15 | Dynamic programming I — memoization vs tabulation, 0/1 & unbounded knapsack, LIS, LCS, edit distance | [Week 15](#week-15--dynamic-programming-i) |
| 16 | Dynamic programming II (grid/range/tree/bitmask) + greedy + bit manipulation | [Week 16](#week-16--dynamic-programming-ii--greedy--bit-manipulation) |

Also see: [Pattern index](#pattern-index) at the bottom, which lists every interview pattern and points to its home problems.

---

## Week 1 — Complexity analysis

Big-O / Ω / Θ, amortized cost, space complexity. The UPSCR problem-solving framework. C++ and STL tooling.

Goal: read a piece of code and state a tight bound. Reason about amortized cost. Account for space, not just time. Half of these are pencil-and-paper, which is deliberate. You will analyze every algorithm for the rest of the course, so the analysis muscle gets built first.

### Warmup
| # | Problem | Source | Notes |
|---|---------|--------|-------|
| 1 | Single loop / nested loop / halving loop | analysis drill | State Θ for each by hand |
| 2 | Sum of an array | analysis drill | Prove O(n) time, O(1) space |
| 3 | Count digits of n | analysis drill | Show Θ(log n) |
| 4 | Two-loop bound: O(n+m) or O(n·m)? | analysis drill | Distinguish sequential vs nested |
| 5 | Power-of-two check | analysis drill | O(1) bit trick vs naive O(log n) |

### Core
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 6 | Running Sum of 1d Array | LC 1480 | Confirm O(n) / O(1) |
| 7 | Richest Customer Wealth | LC 1672 | Nested-loop bound |
| 8 | Build Array from Permutation | LC 1920 | In-place O(1)-space trick |
| 9 | Plus One | LC 66 | Amortized carry analysis |
| 10 | Find the Highest Altitude | LC 1732 | Prefix accumulation cost |
| 11 | Number of Good Pairs | LC 1512 | O(n²) reduced to O(n) by counting |
| 12 | Kth Missing Positive Number | LC 1539 | Linear vs logarithmic reasoning |
| 13 | Maximum Subarray | LC 53 | Establish Kadane is O(n) (revisited in DP) |
| 14 | Squares of a Sorted Array | LC 977 | O(n) two-pointer vs O(n log n) sort |
| 15 | Amortized cost of `push_back` | write-up | Explain in prose, no code |

### Challenge
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 16 | `std::vector` growth: 1.5× vs 2× | write-up | Amortized doubling proof |
| 17 | Master-theorem warmups | analysis drill | Classify 2T(n/2)+n, T(n/2)+1, 2T(n/2)+n² |
| 18 | When does O(n²) beat O(n log n)? | write-up | Constants and input size, empirical |

---

## Week 2 — Recursion and recurrences

Call stack, recurrence relations, recursion-to-iteration, a first look at memoization and backtracking.

Goal: design base and recursive cases without flailing, trace what the call stack is actually doing, and convert a recursive routine to an iterative one when you need to. Memoization shows up at the end as a bridge to DP in weeks 15 and 16.

### Warmup
| # | Problem | Source | Note |
|---|---------|--------|------|
| 19 | Factorial | classic | Recursive and iterative |
| 20 | Sum of digits | classic | Recursive |
| 21 | Reverse a string | classic | Recursive |
| 22 | Power `pow(x, n)` | classic | Naive O(n) first |
| 23 | GCD via Euclid | classic | Recursive |
| 24 | Print 1..n and n..1 | classic | Head vs tail recursion |

### Core
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 25 | Fibonacci Number | LC 509 | Naive vs memoized vs iterative; compare stack growth |
| 26 | Climbing Stairs | LC 70 | Recursion to memo to O(1) space |
| 27 | Pow(x, n) | LC 50 | Fast exponentiation, O(log n) |
| 28 | Reverse Linked List | LC 206 | Recursive version |
| 29 | Merge Two Sorted Lists | LC 21 | Recursive |
| 30 | Tower of Hanoi | classic | Count moves, prove 2ⁿ−1 |
| 31 | Generate all binary strings of length n | classic | Recursion tree |
| 32 | Recursive binary search | classic | Base case discipline |
| 33 | Sum of a nested integer list | classic | Flatten by recursion |
| 34 | Pascal's Triangle | LC 118 | Recurrence relation |

### Challenge
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 35 | Permutations | LC 46 | Recursion tree (full backtracking in week 14) |
| 36 | N-th Catalan number | classic | Recurrence |
| 37 | Hanoi to an explicit stack | classic | Recursion-to-iteration |
| 38 | Ackermann function (small inputs) | classic | Non-primitive recursion |
| 39 | Grid paths by recursion, then add memo | classic | Bridge to DP |

---

## Week 3 — Dynamic arrays & strings; two pointers; prefix sums; sliding window

`std::vector`, in-place manipulation, and the three highest-yield array/string patterns.

Goal: be fluent with `std::vector` and in-place array surgery, reach for two pointers or a sliding window the moment a problem mentions "subarray", "substring", "pair", or "window", and recognize prefix sums on sight. These patterns together account for a large slice of phone screens.

### Warmup — arrays and strings
| # | Problem | Source | Note |
|---|---------|--------|------|
| 40 | Implement a resizable array by hand | build | `push_back`/`pop_back`/`at` |
| 41 | Remove Duplicates from Sorted Array | LC 26 | Two pointers, in-place |
| 42 | Remove Element | LC 27 | In-place |
| 43 | Move Zeroes | LC 283 | In-place stable partition |
| 44 | Rotate Array | LC 189 | Reverse trick |
| 45 | Valid Palindrome | LC 125 | Two pointers, skip non-alnum |
| 46 | Reverse String | LC 344 | In-place |
| 47 | Reverse Words in a String | LC 151 | Trim, split, reverse |
| 48 | Valid Anagram | LC 242 | Count vector |
| 49 | Longest Common Prefix | LC 14 | Vertical scan |

### Core — prefix sums
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 50 | Range Sum Query – Immutable | LC 303 | Build a prefix array |
| 51 | Subarray Sum Equals K | LC 560 | Prefix sum + hashmap |
| 52 | Contiguous Array | LC 525 | Prefix with +1/−1 encoding |
| 53 | Find Pivot Index | LC 724 | Left vs right prefix |
| 54 | Product of Array Except Self | LC 238 | Prefix/suffix products, no division |
| 55 | Minimum Size Subarray Sum | LC 209 | Bridges to sliding window |
| 56 | Maximum Subarray | LC 53 | Kadane, clean |
| 57 | Continuous Subarray Sum | LC 523 | Prefix mod k |
| 58 | Range Sum Query 2D – Immutable | LC 304 | 2D prefix sums |
| 59 | Corporate Flight Bookings | LC 1109 | Difference array |

### Core — two pointers
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 60 | Two Sum II – Input Array Is Sorted | LC 167 | Converging pointers |
| 61 | 3Sum | LC 15 | Sort + two pointers |
| 62 | 3Sum Closest | LC 16 | Track best distance |
| 63 | Container With Most Water | LC 11 | Greedy two pointers |
| 64 | Trapping Rain Water | LC 42 | Two pointers (stack version in week 6) |
| 65 | Sort Colors | LC 75 | Dutch national flag |
| 66 | Remove Nth Node From End of List | LC 19 | Two-pointer gap (also week 5) |

### Core — sliding window
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 67 | Longest Substring Without Repeating Characters | LC 3 | Variable window + last-seen map |
| 68 | Longest Repeating Character Replacement | LC 424 | Window + max-freq tracking |
| 69 | Permutation in String | LC 567 | Fixed window + count match |
| 70 | Minimum Window Substring | LC 76 | Shrinking window with need-counts |
| 71 | Find All Anagrams in a String | LC 438 | Fixed window |
| 72 | Max Consecutive Ones III | LC 1004 | Window with at-most-k zeros |
| 73 | Fruit Into Baskets | LC 904 | At-most-2-distinct window |

### Challenge
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 74 | Subarrays with K Different Integers | LC 992 | Prefix + sliding window |
| 75 | Maximum Sum of 3 Non-Overlapping Subarrays | LC 689 | Prefix + DP bookkeeping |
| 76 | Number of Submatrices That Sum to Target | LC 1074 | 2D prefix + hashmap |
| 77 | Random Pick with Weight | LC 528 | Prefix sums + binary search |
| 78 | Sliding Window Maximum | LC 239 | Monotonic deque (revisited week 6) |
| 79 | Substring with Concatenation of All Words | LC 30 | Fixed multi-window |
| 80 | Longest Substring with At Most K Distinct Characters | LC 340 | Generalized window |
| 81 | Minimum Number of K Consecutive Bit Flips | LC 995 | Window + difference array |

---

## Week 4 — Hashing; cyclic sort; merge intervals

Hash tables, sets, maps. Collisions, load factor, custom hashing. Cyclic sort for index-range problems. Interval sweep.

Goal: turn "I need to look this up fast" into a hashmap solution reflexively, and understand what is happening under the hood. Hashing is the workhorse that makes dozens of later problems O(n) instead of O(n²). Cyclic sort handles the canonical "missing number" family in O(n) time and O(1) space. Merge intervals are nearly ubiquitous in scheduling and calendar problems.

### Warmup
| # | Problem | Source | Note |
|---|---------|--------|------|
| 82 | Two Sum | LC 1 | The canonical hashmap problem |
| 83 | Contains Duplicate | LC 217 | Set |
| 84 | Contains Duplicate II | LC 219 | Map of last index |
| 85 | Intersection of Two Arrays | LC 349 | Set intersection |
| 86 | Jewels and Stones | LC 771 | Set membership |

### Core — hashing
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 87 | Group Anagrams | LC 49 | Sorted-key or count-key hashing |
| 88 | Top K Frequent Elements | LC 347 | Count map + bucket/heap (also week 10) |
| 89 | Valid Sudoku | LC 36 | Sets per row/col/box |
| 90 | Longest Consecutive Sequence | LC 128 | Set + O(n) sequence walk |
| 91 | First Unique Character in a String | LC 387 | Count map |
| 92 | Subarray Sum Equals K | LC 560 | Prefix-sum hashmap |
| 93 | Isomorphic Strings | LC 205 | Two-way mapping |
| 94 | Ransom Note | LC 383 | Count map |
| 95 | 4Sum II | LC 454 | Pair-sum hashmap, O(n²) |
| 96 | LRU Cache | LC 146 | Hashmap + doubly linked list (Project 1 preview) |

### Core — cyclic sort
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 97 | Missing Number | LC 268 | Cyclic sort in place |
| 98 | Find All Numbers Disappeared in an Array | LC 448 | Cyclic sort |
| 99 | Find the Duplicate Number | LC 287 | Cyclic sort / Floyd cycle |
| 100 | First Missing Positive | LC 41 | Cyclic sort in place |

### Core — merge intervals
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 101 | Merge Intervals | LC 56 | Sort by start, sweep |
| 102 | Insert Interval | LC 57 | Merge into sorted set |
| 103 | Non-overlapping Intervals | LC 435 | Greedy by end |
| 104 | Meeting Rooms II | LC 253 | Sort events / heap |

### Challenge
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 105 | Design HashMap | LC 706 | Build it: separate chaining |
| 106 | Design HashSet | LC 705 | Open-addressing variant |
| 107 | Insert Delete GetRandom O(1) | LC 380 | Hashmap + dynamic array |
| 108 | Minimum Window Substring | LC 76 | Re-solve, hashmap-heavy framing |
| 109 | Custom hasher for `pair<int,int>` | build | Write a usable `unordered_map` hash |

---

## Week 5 — Linked lists; fast & slow pointers; in-place reversal

Singly and doubly linked lists. Pointer surgery, in-place reversal, cycle detection, LRU cache.

Goal: manipulate pointers without leaking or losing nodes, reverse a list in place, and detect cycles with two pointers. The fast/slow pointer trick generalizes well beyond lists, so it gets its own block.

### Warmup
| # | Problem | Source | Note |
|---|---------|--------|------|
| 110 | Implement a singly linked list | build | insert / delete / search |
| 111 | Implement a doubly linked list | build | With sentinel nodes |
| 112 | Delete Node in a Linked List | LC 237 | Copy-next trick |
| 113 | Middle of the Linked List | LC 876 | Fast/slow |

### Core — reversal and merge
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 114 | Reverse Linked List | LC 206 | Iterative and recursive |
| 115 | Reverse Linked List II | LC 92 | Reverse a sublist in place |
| 116 | Reverse Nodes in k-Group | LC 25 | In-place reversal, hard pointer work |
| 117 | Merge Two Sorted Lists | LC 21 | Dummy head |
| 118 | Add Two Numbers | LC 2 | Carry handling |
| 119 | Remove Nth Node From End of List | LC 19 | Two-pointer gap |
| 120 | Swap Nodes in Pairs | LC 24 | Local rewiring |
| 121 | Rotate List | LC 61 | Find length, reconnect |
| 122 | Partition List | LC 86 | Two builder lists |
| 123 | Odd Even Linked List | LC 328 | Weave two chains |

### Core — fast and slow pointers
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 124 | Linked List Cycle | LC 141 | Floyd detection |
| 125 | Linked List Cycle II | LC 142 | Find cycle entry |
| 126 | Happy Number | LC 202 | Cycle detection on a sequence |
| 127 | Find the Duplicate Number | LC 287 | Cycle in index space |
| 128 | Palindrome Linked List | LC 234 | Reverse half + compare |
| 129 | Reorder List | LC 143 | Mid + reverse + merge |

### Challenge
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 130 | Copy List with Random Pointer | LC 138 | Interleave or hashmap |
| 131 | Merge k Sorted Lists | LC 23 | K-way merge (also week 10) |
| 132 | LFU Cache | LC 460 | Frequency buckets |
| 133 | Flatten a Multilevel Doubly Linked List | LC 430 | DFS over child pointers |
| 134 | Sort List | LC 148 | Merge sort on a list |

---

## Week 6 — Stacks; queues/deque; circular queue; monotonic stack & deque; sparse matrix

Stacks, queues, deque. The monotonic stack and monotonic deque patterns. Sparse matrix representation.

Goal: model LIFO and FIFO problems cleanly, and recognize the monotonic stack, which is the pattern people most often fail to see. "Next greater", "previous smaller", histogram, and span problems all collapse to one template once you know it.

### Warmup
| # | Problem | Source | Note |
|---|---------|--------|------|
| 135 | Implement a stack | build | Array-backed and list-backed |
| 136 | Implement a queue | build | Circular buffer |
| 137 | Implement Stack using Queues | LC 225 | |
| 138 | Implement Queue using Stacks | LC 232 | Amortized O(1) |
| 139 | Baseball Game | LC 682 | Plain stack ops |

### Core — stacks
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 140 | Valid Parentheses | LC 20 | Matching stack |
| 141 | Min Stack | LC 155 | Auxiliary min |
| 142 | Evaluate Reverse Polish Notation | LC 150 | Stack eval |
| 143 | Basic Calculator | LC 224 | Stack + sign handling |
| 144 | Basic Calculator II | LC 227 | Operator precedence |
| 145 | Decode String | LC 394 | Nested stack |
| 146 | Asteroid Collision | LC 735 | Stack with collision rules |
| 147 | Simplify Path | LC 71 | Stack of path components |
| 148 | Remove All Adjacent Duplicates in String | LC 1047 | Stack collapse |

### Core — monotonic stack / deque
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 149 | Daily Temperatures | LC 739 | Monotonic decreasing stack |
| 150 | Next Greater Element I | LC 496 | Monotonic stack + map |
| 151 | Next Greater Element II | LC 503 | Circular array |
| 152 | Largest Rectangle in Histogram | LC 84 | The defining monotonic-stack problem |
| 153 | Maximal Rectangle | LC 85 | Histogram per row |
| 154 | Sliding Window Maximum | LC 239 | Monotonic deque |
| 155 | Sum of Subarray Minimums | LC 907 | Contribution via spans |
| 156 | Online Stock Span | LC 901 | Monotonic stack of spans |

### Challenge
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 157 | Trapping Rain Water | LC 42 | Monotonic-stack solution |
| 158 | Remove K Digits | LC 402 | Greedy monotonic stack |
| 159 | Maximum Frequency Stack | LC 895 | Stack of frequency groups |
| 160 | Design Circular Deque | LC 641 | Ring buffer |
| 161 | Shortest Subarray with Sum at Least K | LC 862 | Monotonic deque + prefix sums |

---

## Week 7 — Sorting; divide & conquer; binary search

Implement and analyze every classic sort. Divide-and-conquer recurrences. Modified binary search and binary search on the answer.

Goal: write each sort from memory and state its time, space, and stability; never get a binary search boundary wrong again; and spot when the answer space itself is searchable ("smallest capacity that works"). The implement-it-yourself block matters even though you will use `std::sort` in practice, because the partitioning and merging ideas reappear everywhere.

### Warmup — implement and analyze sorts
| # | Problem | Source | Note |
|---|---------|--------|------|
| 162 | Selection Sort | build | O(n²), not stable |
| 163 | Insertion Sort | build | O(n²), stable, fast on near-sorted |
| 164 | Bubble Sort | build | And why we never ship it |
| 165 | Merge Sort | build | O(n log n), stable, O(n) space |
| 166 | Quick Sort | build | Lomuto and Hoare partition |
| 167 | Heap Sort | build | O(n log n), in place |
| 168 | Counting Sort | build | O(n+k), stable |
| 169 | Radix Sort | build | LSD over digits |

### Warmup — binary search basics
| # | Problem | Source | Note |
|---|---------|--------|------|
| 170 | Sqrt(x) | LC 69 | Binary search on the answer |
| 171 | Valid Perfect Square | LC 367 | Same idea |
| 172 | Arranging Coins | LC 441 | Search on row count |
| 173 | Guess Number Higher or Lower | LC 374 | Plain bisection |

### Core — sorting applications
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 174 | Sort an Array | LC 912 | Implement, must beat O(n²) |
| 175 | Largest Number | LC 179 | Custom comparator |
| 176 | Sort Colors | LC 75 | Three-way partition |
| 177 | Wiggle Sort II | LC 324 | Sort + interleave |
| 178 | Maximum Gap | LC 164 | Bucket / radix |
| 179 | H-Index | LC 274 | Sort or counting |

### Core — binary search
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 180 | Binary Search | LC 704 | The clean template |
| 181 | Search Insert Position | LC 35 | Lower bound |
| 182 | First Bad Version | LC 278 | Boundary search |
| 183 | Find First and Last Position of Element | LC 34 | Lower and upper bound |
| 184 | Search in Rotated Sorted Array | LC 33 | Find the sorted half |
| 185 | Search in Rotated Sorted Array II | LC 81 | Duplicates edge case |
| 186 | Find Minimum in Rotated Sorted Array | LC 153 | Pivot search |
| 187 | Find Peak Element | LC 162 | Binary search on slope |
| 188 | Search a 2D Matrix | LC 74 | Flatten the index |

### Core — binary search on the answer
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 189 | Koko Eating Bananas | LC 875 | Min rate that finishes in time |
| 190 | Capacity To Ship Packages Within D Days | LC 1011 | Min capacity feasibility |
| 191 | Split Array Largest Sum | LC 410 | Min of max-subarray-sum |
| 192 | Minimum Number of Days to Make m Bouquets | LC 1482 | Feasibility on days |
| 193 | Find the Smallest Divisor Given a Threshold | LC 1283 | Search the divisor |
| 194 | Magnetic Force Between Two Balls | LC 1552 | Max-min distance |
| 195 | Minimize Max Distance to Gas Station | LC 774 | Real-valued binary search |
| 196 | Maximum Candies Allocated to K Children | LC 2226 | Search the pile size |

### Core — divide and conquer
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 197 | Maximum Subarray | LC 53 | D&C version (vs Kadane) |
| 198 | Pow(x, n) | LC 50 | D&C view of fast exponentiation |
| 199 | Different Ways to Add Parentheses | LC 241 | Split on operators |
| 200 | Construct Binary Tree from Preorder/Inorder | LC 105 | D&C lens |
| 201 | Count of Smaller Numbers After Self | LC 315 | Merge-sort D&C |
| 202 | The Skyline Problem | LC 218 | D&C merge of skylines |

### Challenge
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 203 | Median of Two Sorted Arrays | LC 4 | Partition binary search / D&C |
| 204 | Count of Range Sum | LC 327 | Merge sort + counting |
| 205 | Reverse Pairs | LC 493 | Merge sort + counting |
| 206 | Kth Smallest Element in a Sorted Matrix | LC 378 | Binary search on value |
| 207 | Find K Closest Elements | LC 658 | Binary search the window start |
| 208 | Closest Pair of Points | classic | Computational geometry D&C |
| 209 | Burst Balloons | LC 312 | D&C + DP (bridges to week 15) |
| 210 | Beautiful Array | LC 932 | Divide by parity |

---

## Week 8 — Binary trees; DFS preorder/inorder/postorder; BFS level-order

Tree traversals (DFS and BFS), tree DFS recursion where the return value carries information up.

Goal: traverse a tree any way you like and write tree recursion where the return value carries information upward. BFS for level-order and level-aware problems, DFS for structural queries and path problems. Do not rush this week — the recursion shape you build here underlies BSTs, heaps, tries, segment trees, and almost every graph algorithm that follows.

### Warmup
| # | Problem | Source | Note |
|---|---------|--------|------|
| 211 | Implement a binary tree node + insert | build | |
| 212 | Binary Tree Inorder Traversal | LC 94 | Recursive then iterative |
| 213 | Binary Tree Preorder Traversal | LC 144 | |
| 214 | Binary Tree Postorder Traversal | LC 145 | |
| 215 | Maximum Depth of Binary Tree | LC 104 | Base recursion |

### Core — tree DFS
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 216 | Same Tree | LC 100 | Parallel recursion |
| 217 | Symmetric Tree | LC 101 | Mirror recursion |
| 218 | Invert Binary Tree | LC 226 | Swap children |
| 219 | Path Sum | LC 112 | Root-to-leaf |
| 220 | Path Sum II | LC 113 | Backtrack the path |
| 221 | Diameter of Binary Tree | LC 543 | Height returns + global max |
| 222 | Balanced Binary Tree | LC 110 | Height with early exit |
| 223 | Lowest Common Ancestor of a Binary Tree | LC 236 | Post-order split |
| 224 | Binary Tree Maximum Path Sum | LC 124 | Return best downward, track global |
| 225 | Construct Binary Tree from Preorder and Inorder | LC 105 | Divide and conquer |
| 226 | Flatten Binary Tree to Linked List | LC 114 | Reverse-preorder rewire |
| 227 | Count Good Nodes in Binary Tree | LC 1448 | DFS carrying max-so-far |

### Core — tree BFS
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 228 | Binary Tree Level Order Traversal | LC 102 | Queue by level |
| 229 | Binary Tree Zigzag Level Order Traversal | LC 103 | Level order + flip |
| 230 | Binary Tree Right Side View | LC 199 | Last node per level |
| 231 | Average of Levels in Binary Tree | LC 637 | Sum per level |
| 232 | Populating Next Right Pointers in Each Node | LC 116 | Level links |

### Challenge
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 233 | Serialize and Deserialize Binary Tree | LC 297 | Preorder with null markers |
| 234 | Binary Tree Cameras | LC 968 | Greedy tree DP |

---

## Week 9 — Binary search trees; AVL & rotations

BST invariants, search/insert/delete/validate/successor. Self-balancing with AVL rotations. `std::map` internals.

Goal: reason about the BST ordering invariant, implement all four BST operations correctly, and understand why and how an AVL tree rebalances. This is the structural foundation for `std::map` and `std::set`, which you will use throughout the course.

### Warmup
| # | Problem | Source | Note |
|---|---------|--------|------|
| 235 | Validate Binary Search Tree | LC 98 | Range bounds, not just children |
| 236 | Search in a BST | LC 700 | Ordering walk |
| 237 | Insert into a BST | LC 701 | |
| 238 | Delete Node in a BST | LC 450 | Three deletion cases |

### Core — BST operations and properties
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 239 | Kth Smallest Element in a BST | LC 230 | Inorder counting |
| 240 | Lowest Common Ancestor of a BST | LC 235 | Use ordering |
| 241 | Convert Sorted Array to BST | LC 108 | Balanced build |
| 242 | Range Sum of BST | LC 938 | Pruned DFS |
| 243 | Recover Binary Search Tree | LC 99 | Find two swapped nodes |

### Challenge — AVL and advanced BST
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 244 | Implement an AVL tree | build | Rotations + insert |
| 245 | AVL delete with rebalancing | build | The hard half of AVL |
| 246 | Count of Smaller Numbers After Self | LC 315 | BST / BIT |

---

## Week 10 — Heaps; top-K; two heaps; K-way merge

Binary heaps and priority queues. Two heaps, top-K elements, K-way merge.

Goal: know heap mechanics cold, and recognize the three heap-driven patterns. When a problem says "K largest", "running median", or "merge K sorted things", the data structure is already chosen for you.

### Warmup
| # | Problem | Source | Note |
|---|---------|--------|------|
| 247 | Implement a binary min-heap | build | push / pop / heapify |
| 248 | Build heap from array in O(n) | build | Bottom-up heapify |
| 249 | Kth Largest Element in a Stream | LC 703 | Size-K min-heap |
| 250 | Last Stone Weight | LC 1046 | Max-heap simulation |

### Core — top-K and K-way merge
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 251 | Kth Largest Element in an Array | LC 215 | Heap or quickselect |
| 252 | Top K Frequent Elements | LC 347 | Count + heap/bucket |
| 253 | Top K Frequent Words | LC 692 | Heap with tie-break comparator |
| 254 | K Closest Points to Origin | LC 973 | Size-K max-heap |
| 255 | Merge k Sorted Lists | LC 23 | K-way merge with a heap |
| 256 | Sort Characters By Frequency | LC 451 | Count + heap |
| 257 | Reorganize String | LC 767 | Greedy with max-heap |
| 258 | Task Scheduler | LC 621 | Greedy heap / math |
| 259 | Ugly Number II | LC 264 | Heap or three-pointer DP |

### Core — two heaps
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 260 | Find Median from Data Stream | LC 295 | Max-heap + min-heap balance |
| 261 | Sliding Window Median | LC 480 | Two heaps + lazy deletion |
| 262 | IPO | LC 502 | Two heaps by cost and profit |
| 263 | Find Right Interval | LC 436 | Heap / binary search |

### Challenge
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 264 | Smallest Range Covering Elements from K Lists | LC 632 | K-way merge with a heap |
| 265 | The Skyline Problem | LC 218 | Heap of active heights |
| 266 | Minimum Cost to Hire K Workers | LC 857 | Sort + size-K heap |
| 267 | Maximum Performance of a Team | LC 1383 | Sort + size-K heap |
| 268 | Single-Threaded CPU | LC 1834 | Sort + heap simulation |

---

## Week 11 — Tries and union-find

Prefix trees. Disjoint set union with path compression and union by rank.

Goal: model prefix problems with a trie, and reach for union-find whenever the question is really "are these in the same group?" Both are small structures with outsized payoff on the right problems.

### Warmup
| # | Problem | Source | Note |
|---|---------|--------|------|
| 269 | Implement Trie (Prefix Tree) | LC 208 | insert / search / startsWith |
| 270 | Implement a DSU | build | Union by rank + path compression |
| 271 | Find if Path Exists in Graph | LC 1971 | DSU connectivity |
| 272 | Longest Common Prefix via trie | build | Walk the single chain |

### Core — tries
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 273 | Design Add and Search Words Data Structure | LC 211 | Trie with `.` wildcard |
| 274 | Replace Words | LC 648 | Shortest-root lookup |
| 275 | Word Search II | LC 212 | Trie + backtracking |
| 276 | Map Sum Pairs | LC 677 | Trie with prefix sums |
| 277 | Maximum XOR of Two Numbers in an Array | LC 421 | Bitwise trie |
| 278 | Search Suggestions System | LC 1268 | Trie + top-K (Project 4 preview) |

### Core — union-find
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 279 | Number of Provinces | LC 547 | Count DSU components |
| 280 | Number of Connected Components in an Undirected Graph | LC 323 | DSU |
| 281 | Redundant Connection | LC 684 | First edge forming a cycle |
| 282 | Accounts Merge | LC 721 | DSU over emails |
| 283 | Most Stones Removed with Same Row or Column | LC 947 | Union by row/col key |
| 284 | Satisfiability of Equality Equations | LC 990 | Union equals, then check not-equals |
| 285 | Number of Islands | LC 200 | DSU version (BFS/DFS in week 12) |

### Challenge
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 286 | Word Search II | LC 212 | Full optimized trie + pruning |
| 287 | Concatenated Words | LC 472 | Trie + DP |
| 288 | Swim in Rising Water | LC 778 | DSU / Dijkstra hybrid |
| 289 | Number of Islands II | LC 305 | Online DSU |
| 290 | Smallest String With Swaps | LC 1202 | DSU groups + sort within group |

---

## Week 12 — Graphs I

Representation, BFS, DFS, connected components, cycle detection, topological sort.

Goal: build a graph from raw input, traverse it both ways, order a DAG, and find components. Grid problems are graph problems in disguise, so a big chunk of this week is grids. BFS for shortest unweighted paths, DFS for reachability and structure.

### Warmup
| # | Problem | Source | Note |
|---|---------|--------|------|
| 291 | Build adjacency list and matrix from edges | build | Both representations |
| 292 | Find Center of Star Graph | LC 1791 | Degree reasoning |
| 293 | Find if Path Exists in Graph | LC 1971 | BFS/DFS reachability |

### Core — BFS/DFS on grids and graphs
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 294 | Number of Islands | LC 200 | Grid DFS/BFS flood |
| 295 | Max Area of Island | LC 695 | Flood with area count |
| 296 | Flood Fill | LC 733 | Basic flood |
| 297 | Rotting Oranges | LC 994 | Multi-source BFS |
| 298 | Walls and Gates | LC 286 | Multi-source BFS |
| 299 | 01 Matrix | LC 542 | Multi-source BFS |
| 300 | Surrounded Regions | LC 130 | Border DFS |
| 301 | Clone Graph | LC 133 | BFS/DFS with a visited map |
| 302 | Word Ladder | LC 127 | BFS shortest transformation |
| 303 | Shortest Path in Binary Matrix | LC 1091 | BFS with 8 directions |
| 304 | Pacific Atlantic Water Flow | LC 417 | Reverse multi-source DFS |
| 305 | Number of Enclaves | LC 1020 | Border flood |

### Core — topological sort and components
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 306 | Course Schedule | LC 207 | Cycle detection / Kahn |
| 307 | Course Schedule II | LC 210 | Topological order |
| 308 | Alien Dictionary | LC 269 | Build graph, then topo sort |
| 309 | Minimum Height Trees | LC 310 | Trim leaves topologically |
| 310 | Find Eventual Safe States | LC 802 | Reverse topo / DFS colors |
| 311 | Number of Provinces | LC 547 | DFS components |
| 312 | Is Graph Bipartite? | LC 785 | 2-coloring BFS/DFS |

### Challenge
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 313 | Reconstruct Itinerary | LC 332 | Hierholzer / Eulerian path |
| 314 | Critical Connections in a Network | LC 1192 | Tarjan bridges |
| 315 | Strongly Connected Components | classic | Kosaraju / Tarjan |
| 316 | Parallel Courses | LC 1136 | Topo levels |
| 317 | Sequence Reconstruction | LC 444 | Unique topological order |

---

## Week 13 — Graphs II

Weighted shortest paths (Dijkstra, Bellman-Ford, Floyd-Warshall) and minimum spanning trees (Prim, Kruskal).

Goal: pick the right shortest-path algorithm for the constraints (non-negative weights, negative edges, all-pairs, bounded hops) and build an MST two ways. Know the complexity of each, because that is usually how you choose.

### Warmup
| # | Problem | Source | Note |
|---|---------|--------|------|
| 318 | Network Delay Time | LC 743 | Dijkstra |
| 319 | Path With Minimum Effort | LC 1631 | Dijkstra on a grid |

### Core — shortest paths
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 320 | Cheapest Flights Within K Stops | LC 787 | Bellman-Ford / BFS+DP |
| 321 | Path with Maximum Probability | LC 1514 | Dijkstra variant (max product) |
| 322 | Swim in Rising Water | LC 778 | Dijkstra / DSU |
| 323 | The Maze II | LC 505 | Dijkstra with roll distance |
| 324 | Minimum Cost to Reach Destination in Time | LC 1928 | Dijkstra with a time dimension |
| 325 | Find the City With Smallest Number of Neighbors at a Threshold | LC 1334 | Floyd-Warshall |
| 326 | Number of Ways to Arrive at Destination | LC 1976 | Dijkstra + path counting |

### Core — minimum spanning tree
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 327 | Min Cost to Connect All Points | LC 1584 | Prim and Kruskal |
| 328 | Connecting Cities With Minimum Cost | LC 1135 | Kruskal + DSU |
| 329 | Optimize Water Distribution in a Village | LC 1168 | Virtual node + MST |
| 330 | Find Critical and Pseudo-Critical Edges in MST | LC 1489 | MST with edge inclusion/exclusion |

### Challenge
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 331 | Bellman-Ford with negative-cycle detection | build | Classic implementation |
| 332 | Floyd-Warshall transitive closure | build | All-pairs reachability |
| 333 | Reachable Nodes In Subdivided Graph | LC 882 | Dijkstra with edge budgets |
| 334 | Minimum Cost to Make at Least One Valid Path in a Grid | LC 1368 | 0-1 BFS |
| 335 | Bus Routes | LC 815 | BFS over routes, not stops |

---

## Week 14 — Backtracking

Systematic search. Subsets, combinations, permutations, partitions, N-Queens, Sudoku, word search, pruning.

Goal: write a clean backtracking template (choose, recurse, un-choose) and apply it to subsets, permutations, and constraint search. The three shapes — enumerate all subsets, enumerate all permutations, search under hard constraints — cover the vast majority of backtracking problems you will see.

### Warmup
| # | Problem | Source | Note |
|---|---------|--------|------|
| 336 | Generate all binary strings of length n | classic | Backtracking warmup |
| 337 | Letter Combinations of a Phone Number | LC 17 | Map-digit recursion |
| 338 | Generate Parentheses | LC 22 | Open/close counters |

### Core — subsets and combinations
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 339 | Subsets | LC 78 | Include/exclude tree |
| 340 | Subsets II | LC 90 | Skip duplicates |
| 341 | Combinations | LC 77 | Start-index backtracking |
| 342 | Combination Sum | LC 39 | Reuse allowed |
| 343 | Combination Sum II | LC 40 | Each used once, skip dups |
| 344 | Palindrome Partitioning | LC 131 | Partition + palindrome check |
| 345 | Restore IP Addresses | LC 93 | Segment partitioning |

### Core — permutations and constraint search
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 346 | Permutations | LC 46 | Used-array backtracking |
| 347 | Permutations II | LC 47 | Duplicate pruning |
| 348 | Word Search | LC 79 | Grid backtracking |
| 349 | N-Queens | LC 51 | Column/diagonal sets |
| 350 | Sudoku Solver | LC 37 | Constraint backtracking |

### Challenge
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 351 | Word Search II | LC 212 | Backtracking + trie (capstone of search) |
| 352 | Expression Add Operators | LC 282 | Backtracking with eval |
| 353 | Remove Invalid Parentheses | LC 301 | BFS or backtracking |

---

## Week 15 — Dynamic programming I

Recurrence recognition, memoization vs tabulation, 0/1 & unbounded knapsack, coin change, LIS, LCS, edit distance.

Goal: the core DP spine. For every problem: name the state, write the transition, set the base case, then optimize space if you can. DP is the topic students fear most, which is exactly why it is split into two weeks: week 15 covers the one-dimensional and sequence families; week 16 handles the multi-dimensional, tree, and interval cases together with greedy and bit manipulation.

### Warmup — 1D Fibonacci-style
| # | Problem | Source | Note |
|---|---------|--------|------|
| 354 | Climbing Stairs | LC 70 | 1D DP, O(1) space |
| 355 | House Robber | LC 198 | Take-or-skip |
| 356 | House Robber II | LC 213 | Circular variant |
| 357 | Maximum Subarray | LC 53 | DP framing of Kadane |
| 358 | Best Time to Buy and Sell Stock | LC 121 | Track min so far |

### Core — 1D DP
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 359 | Best Time to Buy and Sell Stock with Cooldown | LC 309 | State machine DP |
| 360 | Decode Ways | LC 91 | 1D with two look-backs |
| 361 | Word Break | LC 139 | DP over prefixes |
| 362 | Coin Change | LC 322 | Unbounded knapsack |
| 363 | Coin Change II | LC 518 | Count combinations |
| 364 | Combination Sum IV | LC 377 | Count ordered ways |
| 365 | Perfect Squares | LC 279 | Min coins variant |

### Core — knapsack
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 366 | Partition Equal Subset Sum | LC 416 | 0/1 knapsack (subset sum) |
| 367 | Target Sum | LC 494 | 0/1 knapsack with signs |
| 368 | Last Stone Weight II | LC 1049 | Minimize partition difference |
| 369 | Ones and Zeroes | LC 474 | 2D-capacity knapsack |

### Core — LIS / LCS / string DP
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 370 | Longest Increasing Subsequence | LC 300 | O(n²) and O(n log n) |
| 371 | Number of Longest Increasing Subsequence | LC 673 | LIS with counts |
| 372 | Russian Doll Envelopes | LC 354 | Sort + LIS |
| 373 | Longest Common Subsequence | LC 1143 | 2D DP grid |
| 374 | Edit Distance | LC 72 | Classic 2D DP |
| 375 | Distinct Subsequences | LC 115 | Counting DP |
| 376 | Longest Palindromic Subsequence | LC 516 | LCS with reverse |
| 377 | Longest Palindromic Substring | LC 5 | Expand-center / DP |
| 378 | Palindromic Substrings | LC 647 | Count via DP |
| 379 | Regular Expression Matching | LC 10 | 2D DP with `*` |
| 380 | Wildcard Matching | LC 44 | 2D DP / greedy |

### Challenge
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 381 | Maximum Profit in Job Scheduling | LC 1235 | DP + binary search |
| 382 | Frog Jump | LC 403 | DP with state = (stone, jump) |

---

## Week 16 — Dynamic programming II + greedy + bit manipulation

Grid/range/tree/bitmask DP. Exchange-argument greedy. Bit tricks including XOR. Math and number theory.

Goal: complete the DP picture with multi-dimensional states and interval recurrences, then cover the greedy and bit-manipulation patterns that sit naturally at the course's capstone. The XOR tricks here recur in interviews more than people expect.

### Core — grid / 2D DP
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 383 | Unique Paths | LC 62 | Grid counting DP |
| 384 | Unique Paths II | LC 63 | With obstacles |
| 385 | Minimum Path Sum | LC 64 | Min-cost grid |
| 386 | Maximal Square | LC 221 | DP on square side |
| 387 | Dungeon Game | LC 174 | Backward grid DP |
| 388 | Cherry Pickup | LC 741 | Two-path grid DP |

### Core — tree DP / interval DP
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 389 | House Robber III | LC 337 | DP on tree nodes |
| 390 | Binary Tree Maximum Path Sum | LC 124 | Tree DP lens |
| 391 | Burst Balloons | LC 312 | Interval DP |
| 392 | Matrix Chain Multiplication | classic | Interval DP |

### Core — greedy
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 393 | Jump Game | LC 55 | Furthest reach |
| 394 | Jump Game II | LC 45 | Greedy BFS layers |
| 395 | Gas Station | LC 134 | Running tank + reset |
| 396 | Candy | LC 135 | Two passes |
| 397 | Task Scheduler | LC 621 | Greedy fill |
| 398 | Partition Labels | LC 763 | Last-occurrence sweep |
| 399 | Non-overlapping Intervals | LC 435 | Greedy by end time |
| 400 | Minimum Number of Arrows to Burst Balloons | LC 452 | Interval overlap greedy |
| 401 | Hand of Straights | LC 846 | Greedy from smallest |

### Core — bit manipulation
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 402 | Single Number | LC 136 | XOR cancellation |
| 403 | Single Number II | LC 137 | Bit-count mod 3 |
| 404 | Single Number III | LC 260 | XOR + lowest set bit split |
| 405 | Number of 1 Bits | LC 191 | Popcount / Brian Kernighan |
| 406 | Counting Bits | LC 338 | DP on bits |
| 407 | Reverse Bits | LC 190 | Bit-by-bit |
| 408 | Missing Number | LC 268 | XOR / cyclic sort |
| 409 | Sum of Two Integers | LC 371 | Add without `+` |
| 410 | Bitwise AND of Numbers Range | LC 201 | Common prefix |

### Challenge
| # | Problem | Source | Pattern / note |
|---|---------|--------|----------------|
| 411 | Stone Game / Stone Game II | LC 877 / 1140 | Game-theory DP |
| 412 | Cherry Pickup II | LC 1463 | Two-agent grid DP |

---

**Total: 412 problems.** Every topic in the course inventory appears here, and most interview patterns show up several times across the tiers so you drill them from more than one angle.

---

## Pattern index

If you want to grind one pattern across the whole course instead of going week by week, start here. Each pattern lists its home week and a few representative problem numbers.

| Pattern | Home week | Representative problems |
|---------|-----------|-------------------------|
| Two Pointers | 3 | 60, 61, 63, 64, 65 |
| Sliding Window | 3 | 67, 68, 70, 72, 80 |
| Prefix Sums | 3 | 50, 51, 54, 58, 76 |
| Merge Intervals | 4 | 101, 102, 103, 104 |
| Cyclic Sort | 4 | 97, 98, 99, 100 |
| Fast & Slow Pointers | 5 | 124, 125, 126, 127, 128 |
| In-Place Linked-List Reversal | 5 | 114, 115, 116 |
| Monotonic Stack | 6 | 149, 152, 155, 157, 158 |
| Stack for Parsing/Matching | 6 | 140, 143, 144, 145, 147 |
| Deque/Monotonic Queue | 6 | 154, 160, 161 |
| Modified Binary Search | 7 | 183, 184, 186, 187, 203 |
| Subsets/Combinations/Permutations | 14 | 339, 341, 342, 346, 349 |
| Tree BFS | 8 | 228, 229, 230, 232 |
| Tree DFS | 8 | 221, 223, 224, 225 |
| BST-Ordered Traversal | 9 | 239, 240, 241, 243 |
| Trie | 11 | 269, 273, 275, 277 |
| Top-K Elements | 10 | 251, 252, 254, 266 |
| K-Way Merge | 10 | 255, 264 |
| Two Heaps | 10 | 260, 261, 262 |
| Graph BFS/DFS & Components | 12 | 294, 297, 299, 302 |
| Topological Sort | 12 | 306, 307, 308, 316 |
| Weighted Shortest Path & MST | 13 | 318, 320, 325, 327 |
| Union-Find | 11 | 279, 281, 282, 284 |
| 1D DP | 15 | 354, 355, 360, 361 |
| Knapsack DP | 15 | 366, 367, 368, 369 |
| String DP | 15 | 373, 374, 377, 378 |
| 2D & Grid DP | 15 | 373, 374, 383, 385 |
| Bitwise XOR & Bit Manipulation | 16 | 402, 404, 408, 409 |

See [`../docs/patterns.md`](../docs/patterns.md) for the full write-up on each pattern.

---

Practice is not reading about practice. The students who finish this course interview-ready are not the ones who read the most. They are the ones who solved the most problems with their own hands, got stuck, came back, and re-solved. The list is long on purpose. Work it.
