# Glossary

A quick reference for the vocabulary used across the course. One sentence per term, kept correct and to the point. When a definition leans on another term, that term has its own entry. Skim it before a lecture, or use it to settle an argument about what something actually means.

Jump to a letter: [A](#a) · [B](#b) · [C](#c) · [D](#d) · [E](#e) · [F](#f) · [G](#g) · [H](#h) · [I](#i) · [K](#k) · [L](#l) · [M](#m) · [N](#n) · [O](#o) · [P](#p) · [Q](#q) · [R](#r) · [S](#s) · [T](#t) · [U](#u) · [V](#v) · [W](#w) · [X](#x)

---

## A

**Adjacency list** — A graph representation that stores, for each vertex, a list of its neighbors, using O(V + E) space and giving fast iteration over a vertex's edges.

**Adjacency matrix** — A graph representation using a V×V table where entry (i, j) records whether (or how heavily) an edge connects vertex i to vertex j, costing O(V²) space but answering "is there an edge?" in O(1).

**Amortized analysis** — A way of measuring cost per operation averaged over a sequence, so that an occasional expensive step (like a vector resize) is spread across the many cheap ones around it.

**Array** — A contiguous block of memory holding fixed-size elements, giving O(1) access by index because the address of element i is computed by arithmetic.

**AVL tree** — A self-balancing binary search tree that keeps the height of every node's two subtrees within one of each other, using rotations after insert and delete to guarantee O(log n) operations.

## B

**Backtracking** — A systematic search that builds a candidate solution one choice at a time and abandons a partial choice (backtracks) the moment it cannot lead to a valid complete solution.

**Bellman-Ford** — A single-source shortest-path algorithm that relaxes every edge V−1 times, runs in O(V·E), and unlike Dijkstra handles negative edge weights and detects negative cycles.

**Big-O notation** — An upper bound on how an algorithm's running time or space grows as input size grows, ignoring constants and lower-order terms, so O(n²) means "no worse than proportional to n² for large n."

**Big-Omega (Ω) notation** — A lower bound on growth, describing the best case or a guaranteed minimum amount of work an algorithm must do.

**Big-Theta (Θ) notation** — A tight bound used when an algorithm's growth is bounded both above and below by the same function, so Θ(n) means the cost grows exactly proportionally to n.

**Binary heap** — A complete binary tree stored in an array where every parent compares favorably to its children (min-heap or max-heap), supporting O(log n) insert and extract and O(1) peek.

**Binary search** — A search over a sorted range that halves the candidate region each step, finding a target in O(log n) by comparing against the middle element.

**Binary search on the answer** — A technique that binary-searches over the space of possible answers (not array indices) using a monotonic feasibility check, turning "find the smallest/largest value that works" into O(log range) checks.

**Binary search tree (BST)** — A binary tree where every node's left subtree holds smaller keys and its right subtree holds larger keys, giving O(h) search, insert, and delete where h is the height.

**Binary tree** — A tree in which every node has at most two children, conventionally called left and right.

**Bit manipulation** — Working directly on the binary representation of integers with operations like AND, OR, XOR, NOT, and shifts to compute results faster or with less memory.

**Bitmask** — An integer used as a compact set, where each bit position represents the presence or absence of one element, common in subset enumeration and DP over states.

**BFS (breadth-first search)** — A graph and tree traversal that visits nodes in rings of increasing distance from the source using a queue, and finds shortest paths in unweighted graphs.

## C

**Call stack** — The region of memory that tracks active function calls, where each call pushes a frame holding its parameters and locals and each return pops one, and which overflows if recursion goes too deep.

**Connected components** — The maximal groups of vertices in an undirected graph such that every vertex in a group is reachable from every other, typically found with BFS, DFS, or union-find.

**Counting sort** — A non-comparison sort that counts occurrences of each key in a bounded range and reconstructs the output, running in O(n + k) where k is the range of key values.

**Cyclic sort** — A pattern for arrays holding numbers in a known range (like 1..n) that places each value at its correct index in O(n) by repeated swapping, used to find missing or duplicate values.

## D

**Dangling pointer** — A pointer that still holds the address of memory that has already been freed, and dereferencing it is undefined behavior.

**Deque** — A double-ended queue allowing O(1) insertion and removal at both the front and the back, available in C++ as `std::deque`.

**DFS (depth-first search)** — A traversal that goes as deep as possible along each branch before backtracking, implemented with recursion or an explicit stack.

**Dijkstra's algorithm** — A single-source shortest-path algorithm for graphs with non-negative edge weights that greedily settles the closest unsettled vertex, running in O((V + E) log V) with a binary heap.

**Disjoint set** — See **Union-find**.

**Divide and conquer** — A strategy that splits a problem into independent subproblems, solves each recursively, and combines their results, as in merge sort and binary search.

**Doubly linked list** — A linked list where each node stores pointers to both its next and previous nodes, allowing O(1) removal given a node and traversal in either direction.

**Dynamic array** — An array that grows automatically when full by allocating a larger buffer (typically doubling) and copying elements, giving amortized O(1) append; `std::vector` is the C++ version.

**Dynamic programming (DP)** — Solving a problem by breaking it into overlapping subproblems and storing each subproblem's result so it is computed once, applied via top-down memoization or bottom-up tabulation.

## E

**Edit distance** — The minimum number of single-character insertions, deletions, or substitutions needed to turn one string into another, computed with 2D dynamic programming (Levenshtein distance).

**Edge** — A connection between two vertices in a graph, optionally directed and optionally carrying a weight.

## F

**Fast and slow pointers** — A two-pointer technique where one pointer advances twice as fast as the other, used to detect cycles in a linked list and to find a list's middle in one pass.

**Floyd-Warshall** — An all-pairs shortest-path algorithm that runs in O(V³) by repeatedly allowing each vertex to serve as an intermediate point on every path.

**Frame (stack frame)** — The block of data the call stack pushes for one function invocation, holding its arguments, local variables, and return address.

## G

**Graph** — A set of vertices connected by edges, used to model networks, dependencies, maps, and relationships, and which may be directed or undirected and weighted or unweighted.

**Greedy algorithm** — An approach that builds a solution by always taking the locally best choice, which yields a correct global optimum only when the problem has the right structure (an exchange argument or matroid property).

## H

**Hash function** — A function that maps a key to an integer bucket index, ideally spreading keys uniformly so collisions are rare.

**Hash map** — A key-value container backed by a hash table giving average O(1) lookup, insert, and erase; `std::unordered_map` in C++.

**Hash set** — A container of unique keys backed by a hash table with average O(1) membership testing; `std::unordered_set` in C++.

**Hash table** — A structure that stores entries in buckets chosen by a hash function, resolving collisions by chaining or open addressing, and giving average O(1) operations that degrade to O(n) in the worst case.

**Heap sort** — A comparison sort that builds a max-heap from the array and repeatedly extracts the maximum, running in O(n log n) time with O(1) extra space.

**Height (of a tree)** — The number of edges on the longest path from a node down to a leaf, with the tree's height measured from its root.

## I

**In-place** — An algorithm that transforms its input using only O(1) or O(log n) extra memory beyond the input itself, like in-place reversal or heap sort.

**In-place linked-list reversal** — A pattern that reverses a linked list (or a sublist) by re-pointing each node's next pointer as you walk through it, using O(1) extra space.

**Insertion sort** — A simple O(n²) sort that grows a sorted prefix one element at a time, shifting larger elements right to make room, and runs in O(n) on nearly sorted data.

**Iterator** — A C++ object that points into a container and is advanced with `++`, letting algorithms traverse containers uniformly without knowing their internal layout.

## K

**K-way merge** — A pattern that merges k sorted sequences into one by repeatedly pulling the smallest current element, usually with a min-heap, in O(N log k) total.

**Knapsack (0/1)** — The problem of choosing a subset of items, each used at most once, to maximize value under a weight limit, solved with 2D dynamic programming over items and capacity.

**Knapsack (unbounded)** — The knapsack variant where each item may be chosen any number of times, solved with a 1D DP that iterates capacity forward so items can repeat.

## L

**LCS (longest common subsequence)** — The longest sequence that appears in the same relative order (not necessarily contiguously) in two strings, computed with O(n·m) dynamic programming.

**LIS (longest increasing subsequence)** — The longest subsequence of an array whose values strictly increase, solvable in O(n²) with DP or O(n log n) with a patience-sorting style binary search.

**Linked list** — A linear structure of nodes where each node holds a value and a pointer to the next, giving O(1) insertion and deletion at a known position but O(n) access by index.

**Load factor** — The ratio of stored entries to buckets in a hash table, which when it climbs too high triggers a rehash into a larger table to keep operations near O(1).

## M

**Memoization** — Caching the result of a function for each set of arguments so a repeated call returns instantly, the top-down form of dynamic programming.

**Memory leak** — Heap memory that was allocated with `new` but never freed with `delete`, so it stays reserved until the program ends.

**Merge intervals** — A pattern that sorts intervals by start, then sweeps through merging any that overlap, common in scheduling and range-consolidation problems.

**Merge sort** — A stable divide-and-conquer sort that splits the array in half, sorts each half, and merges them, guaranteeing O(n log n) time with O(n) extra space.

**Min-heap / max-heap** — A binary heap whose root is always the smallest (min-heap) or largest (max-heap) element, giving O(1) access to that extreme and O(log n) updates.

**Modified binary search** — Any binary search adapted to a non-obvious monotonic structure, such as a rotated sorted array or finding the first index satisfying a condition.

**Monotonic stack** — A stack kept in increasing or decreasing order by popping elements that violate the order before pushing, which answers next-greater and next-smaller queries in amortized O(n).

**MST (minimum spanning tree)** — A subset of a connected weighted graph's edges that connects all vertices with the minimum possible total weight and no cycles, found by Prim's or Kruskal's algorithm.

## N

**Node** — A single unit of a linked structure or tree, holding a value plus one or more pointers to other nodes.

**Number theory** — The branch of math behind techniques like the greatest common divisor (Euclid's algorithm), modular arithmetic, prime sieves, and modular exponentiation that show up in algorithm problems.

## O

**Open addressing** — A hash-table collision strategy that, on a collision, probes for another open bucket within the same array (linear, quadratic, or double hashing) rather than using separate chains.

## P

**Palindromic subsequence** — A subsequence that reads the same forwards and backwards, with the longest one found by DP related to the LCS of a string and its reverse.

**Pattern (interview pattern)** — A reusable shape of solution, such as sliding window or two pointers, that maps to a whole family of problems once you learn to recognize the trigger.

**Pointer** — A variable that holds a memory address, dereferenced with `*` to read or write the value it points to, and central to how linked structures and dynamic memory work in C++.

**Prefix sum** — A precomputed array where each entry holds the running total up to that index, letting any subarray sum be answered in O(1) after O(n) setup.

**Prim's algorithm** — A minimum-spanning-tree algorithm that grows the tree one vertex at a time, always adding the cheapest edge that reaches a new vertex, typically with a priority queue.

**Priority queue** — An abstract structure that always serves the highest-priority element next, usually implemented with a binary heap; `std::priority_queue` in C++.

## Q

**Queue** — A FIFO (first-in, first-out) container where elements are added at the back and removed from the front, underlying BFS and many scheduling tasks.

**Quick sort** — A divide-and-conquer sort that partitions around a pivot and recurses on each side, averaging O(n log n) but degrading to O(n²) on bad pivots, fast in practice and in-place.

## R

**Radix sort** — A non-comparison sort that orders numbers digit by digit using a stable counting sort per digit, running in O(d·(n + k)) for d digits.

**Recurrence relation** — An equation expressing an algorithm's cost in terms of its cost on smaller inputs, like T(n) = 2T(n/2) + O(n), which the Master Theorem can often solve.

**Recursion** — A technique where a function calls itself on a smaller instance of the problem, defined by one or more base cases that stop it and a recursive case that shrinks toward them.

**Recursion-to-iteration** — Rewriting a recursive algorithm as a loop, often with an explicit stack, to avoid call-stack overhead or stack-overflow on deep inputs.

**Rotation (tree rotation)** — A local O(1) restructuring of a binary search tree that changes node heights while preserving sort order, the building block of AVL and other balanced trees.

## S

**Selection sort** — A simple O(n²) sort that repeatedly selects the smallest remaining element and swaps it into place, doing few writes but always quadratic comparisons.

**Singly linked list** — A linked list where each node points only to its successor, traversable in one direction.

**Sliding window** — A pattern that maintains a moving range over a sequence, expanding and contracting its bounds to answer subarray or substring questions in O(n).

**Space complexity** — How much extra memory an algorithm uses as a function of input size, counting auxiliary storage and, where it matters, the recursion stack.

**Stable sort** — A sort that preserves the original relative order of elements with equal keys, a property merge sort and counting sort have but quick sort and heap sort do not.

**Stack** — A LIFO (last-in, first-out) container where the most recently added element is removed first, underlying DFS, expression evaluation, and the call stack itself.

**STL (Standard Template Library)** — The part of the C++ standard library providing generic containers (`vector`, `map`, `set`), iterators, and algorithms (`sort`, `lower_bound`) built on templates.

**String** — A sequence of characters, represented in C++ by `std::string`, on which many two-pointer, sliding-window, and DP patterns operate.

**Subsets (power set)** — The collection of all possible subsets of a set, generated by backtracking or by iterating over bitmasks from 0 to 2ⁿ−1.

## T

**Tabulation** — The bottom-up form of dynamic programming that fills a table from the base cases upward, avoiding recursion entirely.

**Template** — A C++ mechanism for writing code parameterized by type, so one definition like `vector<T>` works for any element type and is instantiated by the compiler as needed.

**Top-K elements** — A pattern for finding the K largest or smallest items using a heap of size K, running in O(n log K) without fully sorting the input.

**Topological sort** — A linear ordering of a directed acyclic graph's vertices such that every edge points forward, computed by Kahn's algorithm (BFS on in-degrees) or DFS finish times.

**Traversal** — The act of visiting every node of a structure in a defined order, such as inorder, preorder, postorder, and level-order for trees.

**Tree** — A connected acyclic graph with a designated root, where every non-root node has exactly one parent.

**Trie** — A tree keyed on the characters of strings, where each path from the root spells a prefix, giving O(length) insert and lookup and efficient prefix queries.

**Two heaps** — A pattern that keeps a max-heap of the smaller half and a min-heap of the larger half of a stream so the median is available in O(1) with O(log n) inserts.

**Two pointers** — A pattern that uses two indices moving through a sequence, toward or away from each other or at different speeds, to solve pair, partition, and subarray problems in O(n).

## U

**Undefined behavior** — Program behavior the C++ standard places no constraints on, such as dereferencing a dangling pointer or reading past an array's end, which may appear to work, crash, or corrupt data.

**Union-find (disjoint set)** — A structure that tracks a partition of elements into disjoint sets and supports near-O(1) union and find with union by rank and path compression, used for connectivity and Kruskal's MST.

## V

**Vector** — The C++ dynamic array (`std::vector`) that grows on demand, stores elements contiguously, and gives O(1) indexed access plus amortized O(1) append.

**Vertex** — A node in a graph, connected to others by edges; the plural is vertices.

## W

**Weighted graph** — A graph whose edges carry numeric values (costs, distances, capacities), required by shortest-path and minimum-spanning-tree algorithms.

**Worst case** — The maximum cost an algorithm incurs over all inputs of a given size, the guarantee most often quoted in Big-O analysis.

## X

**XOR (bitwise exclusive or)** — A bit operation that yields 1 only where two bits differ, with the handy properties that x ^ x = 0 and x ^ 0 = x, used to find a unique element among pairs and to swap without a temporary.
