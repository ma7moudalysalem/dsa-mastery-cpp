# Pattern Bank

**Course:** Data Structures & Algorithms in C++ — From Fundamentals to Interview-Ready
**Format:** 64 lectures, 16 weeks. Complexity and recursion come first (weeks 1–2), then the data structures, then the algorithms.

This is the spine of the course. Almost every interview problem you will ever see is a recombination of a small set of patterns. Learn to read a problem statement and name the pattern in the first thirty seconds, and the rest is execution.

How to read each entry:

- **Definition** — what the pattern actually does.
- **Signal** — the phrases and shapes in a problem that should make you reach for it. This is the part you drill until it is reflex.
- **Skeleton** — a minimal C++ form where one helps. These are sketches, not drop-in solutions; they assume the obvious includes.
- **Complexity** — time and space, stated honestly.
- **Problems** — graded Warmup / Core / Challenge. Start at Warmup, do not stop until you can do the Challenge cold.
- **Introduced** — the week the pattern is formally taught. It then comes back, deepened, in later weeks.

A note on the week tags. Patterns that live on a data structure are introduced the week that structure is taught. A few groups (dynamic programming especially) span more than one week; the tag gives the starting week and the spread is noted inline.

---

## Table of contents

- [Group A — Array and String](#group-a--array-and-string)
  - [1. Two Pointers](#1-two-pointers)
  - [2. Sliding Window](#2-sliding-window)
  - [3. Prefix Sums and Difference Arrays](#3-prefix-sums-and-difference-arrays)
  - [4. Merge Intervals](#4-merge-intervals)
  - [5. Cyclic Sort](#5-cyclic-sort)
- [Group B — Linked List](#group-b--linked-list)
  - [6. Fast and Slow Pointers](#6-fast-and-slow-pointers)
  - [7. In-Place Linked-List Reversal](#7-in-place-linked-list-reversal)
- [Group C — Stack and Queue](#group-c--stack-and-queue)
  - [8. Monotonic Stack](#8-monotonic-stack)
  - [9. Stack for Parsing and Matching](#9-stack-for-parsing-and-matching)
  - [10. Deque and Monotonic Queue](#10-deque-and-monotonic-queue)
- [Group D — Trees](#group-d--trees)
  - [11. Tree BFS (Level-Order)](#11-tree-bfs-level-order)
  - [12. Tree DFS (Pre/In/Post-order and Path Recursion)](#12-tree-dfs-preinpost-order-and-path-recursion)
  - [13. BST-Ordered Traversal](#13-bst-ordered-traversal)
  - [14. Trie (Prefix Tree)](#14-trie-prefix-tree)
- [Group E — Heaps and Priority Queues](#group-e--heaps-and-priority-queues)
  - [15. Top-K Elements](#15-top-k-elements)
  - [16. K-Way Merge](#16-k-way-merge)
  - [17. Two Heaps](#17-two-heaps)
- [Group F — Graphs](#group-f--graphs)
  - [18. Graph BFS / DFS and Connected Components](#18-graph-bfs--dfs-and-connected-components)
  - [19. Topological Sort](#19-topological-sort)
  - [20. Weighted Shortest Path and MST](#20-weighted-shortest-path-and-mst)
  - [21. Union-Find (Disjoint Set)](#21-union-find-disjoint-set)
- [Group G — Search, Subsets, Backtracking](#group-g--search-subsets-backtracking)
  - [22. Modified Binary Search](#22-modified-binary-search)
  - [23. Subsets, Combinations, Permutations (Backtracking)](#23-subsets-combinations-permutations-backtracking)
- [Group H — Dynamic Programming](#group-h--dynamic-programming)
  - [24. 1D DP (Linear Sequence)](#24-1d-dp-linear-sequence)
  - [25. 2D and Grid DP](#25-2d-and-grid-dp)
  - [26. Knapsack DP (0/1 and Unbounded)](#26-knapsack-dp-01-and-unbounded)
  - [27. String DP (LCS, Edit Distance, Palindromes)](#27-string-dp-lcs-edit-distance-palindromes)
- [Group I — Bit Manipulation and Math](#group-i--bit-manipulation-and-math)
  - [28. Bitwise XOR and Bit Manipulation](#28-bitwise-xor-and-bit-manipulation)
- [At a glance](#at-a-glance)

---

## Group A — Array and String

### 1. Two Pointers

**Definition.** Two indices walk the array or string under a rule, either toward each other from both ends or both forward at different speeds. The point is to replace a nested loop with one linear pass.

**Signal.** A sorted array. Finding a pair or triple that meets a condition. Comparing from both ends. An in-place requirement with O(1) extra space. Palindrome checks. Partitioning or removing elements in place.

**Skeleton.** Put `l` and `r` at the two ends. At each step, a comparison tells you which pointer to move. They converge.

```cpp
int l = 0, r = n - 1;
while (l < r) {
    int s = a[l] + a[r];
    if (s == target) return {l, r};
    if (s < target) ++l;
    else            --r;
}
```

**Complexity.** Time O(n), or O(n log n) when the problem needs an initial sort. Space O(1).

**Problems.**
- *Warmup:* Valid Palindrome; Reverse String; Squares of a Sorted Array.
- *Core:* Two Sum II (sorted input); Remove Duplicates from Sorted Array; Container With Most Water; Sort Colors (Dutch national flag).
- *Challenge:* 3Sum; 3Sum Closest; Trapping Rain Water (two-pointer form).

**Introduced:** Week 3 (arrays and strings).

---

### 2. Sliding Window

**Definition.** Keep a contiguous window `[l, r]` plus a running summary of it (a sum, a count, a frequency map). Push `r` out to grow the window, pull `l` in to shrink it, and keep the summary correct as you go.

**Signal.** "Contiguous subarray or substring." "Longest, shortest, or at most K." "Window of size k." "Without repeating characters." The question is about a *range*, not a subsequence.

**Skeleton.** Grow by one, update state, then shrink from the left while the window is invalid, recording the answer when it is valid.

```cpp
int l = 0; long sum = 0; int best = INT_MAX;
for (int r = 0; r < n; ++r) {
    sum += a[r];
    while (sum >= target) {
        best = min(best, r - l + 1);
        sum -= a[l++];
    }
}
```

**Complexity.** Time O(n); every index enters and leaves the window once. Space O(1) for fixed windows, O(k) when you track a frequency map.

**Problems.**
- *Warmup:* Maximum Average Subarray I; Maximum Sum Subarray of Size K.
- *Core:* Longest Substring Without Repeating Characters; Minimum Size Subarray Sum; Longest Substring with At Most K Distinct Characters; Permutation in String.
- *Challenge:* Minimum Window Substring; Sliding Window Maximum (with a deque); Longest Repeating Character Replacement.

**Introduced:** Week 3, extended in Week 6 with hashing. The deque variant is Week 6.

---

### 3. Prefix Sums and Difference Arrays

**Definition.** Precompute cumulative sums so any range query answers in O(1). Pair this with a hash map of seen prefix values to count subarrays whose sum hits a target.

**Signal.** Many range-sum or range-aggregate queries. "Subarray sum equals K." "Count subarrays whose sum has some property." Equilibrium or pivot index. 2D region sums. A range update followed by point queries (that is the difference-array form).

**Skeleton.** `pre[i] = pre[i-1] + a[i]`, and the sum of `[i, j]` is `pre[j] - pre[i-1]`. To count subarrays summing to K, store how many times each prefix value has appeared and look for `pre - K`.

```cpp
unordered_map<long, int> cnt{{0, 1}};
long pre = 0; int ans = 0;
for (int x : a) {
    pre += x;
    ans += cnt[pre - K];
    cnt[pre]++;
}
```

**Complexity.** Build O(n), each query O(1). The counting variant is O(n) time and O(n) space.

**Problems.**
- *Warmup:* Running Sum of 1D Array; Range Sum Query – Immutable.
- *Core:* Subarray Sum Equals K; Find Pivot Index; Product of Array Except Self (prefix and suffix); Range Sum Query 2D – Immutable.
- *Challenge:* Subarray Sums Divisible by K; Contiguous Array (0/1 balance); Count of Range Sum.

**Introduced:** Week 3 (hashing).

---

### 4. Merge Intervals

**Definition.** Sort intervals by start, then sweep once, merging anything that overlaps or scheduling as you pass.

**Signal.** The input is a list of intervals or ranges with a start and an end. "Merge overlapping." "Insert an interval." "Minimum meeting rooms." "Can a person attend all meetings." Interval intersection.

**Skeleton.** Sort by start. Hold a current interval. If the next one overlaps, extend the current end; otherwise emit current and open a new one. For the room-count problem, use a min-heap of end times instead.

```cpp
sort(iv.begin(), iv.end());
vector<pair<int,int>> out{iv[0]};
for (auto& x : iv) {
    if (x.first <= out.back().second)
        out.back().second = max(out.back().second, x.second);
    else
        out.push_back(x);
}
```

**Complexity.** Time O(n log n); the sort dominates. Space O(n) for the output.

**Problems.**
- *Warmup:* Merge Intervals; Meeting Rooms (can attend all?).
- *Core:* Insert Interval; Interval List Intersections; Meeting Rooms II (min-heap).
- *Challenge:* Employee Free Time; Minimum Number of Arrows to Burst Balloons; Non-overlapping Intervals.

**Introduced:** Week 4, after sorting. The heap variant returns in Week 10.

---

### 5. Cyclic Sort

**Definition.** When the values are a known permutation of `1..n` or `0..n-1`, put each value at the index it belongs to by swapping in place. The array becomes self-indexing, and whatever index ends up holding the wrong value tells you the answer.

**Signal.** An array of n numbers drawn from `[1..n]` or `[0..n-1]`. "Find the missing number," "the duplicate," "the first missing positive." An O(1) extra-space demand where the numbers can double as indices.

**Skeleton.** While `a[i]` is not already at its home index `a[i]-1`, swap it there. Then scan for the first index whose value is wrong.

```cpp
int i = 0;
while (i < n) {
    int j = a[i] - 1;
    if (a[i] != a[j]) swap(a[i], a[j]);
    else ++i;
}
```

**Complexity.** Time O(n); each swap drops one element into its final home. Space O(1).

**Problems.**
- *Warmup:* Missing Number; Find All Numbers Disappeared in an Array.
- *Core:* Find the Duplicate Number; Find All Duplicates in an Array; Set Mismatch.
- *Challenge:* First Missing Positive; Couples Holding Hands.

**Introduced:** Week 4 (sorting).

---

## Group B — Linked List

### 6. Fast and Slow Pointers

**Definition.** Floyd's cycle detection. Run two pointers at different speeds, one step versus two. They find cycles, midpoints, and the k-th node from the end in a single pass.

**Signal.** A linked list and a question about a *cycle*, a *middle*, a *cycle start*. "Happy number." "Does this sequence loop." A constant-space requirement.

**Skeleton.** Move `slow` one and `fast` two. If they ever meet, there is a cycle. To find the cycle entrance, reset one pointer to the head and advance both one step at a time until they meet again.

```cpp
Node *s = head, *f = head;
while (f && f->next) {
    s = s->next;
    f = f->next->next;
    if (s == f) break;   // cycle
}
```

**Complexity.** Time O(n). Space O(1).

**Problems.**
- *Warmup:* Middle of the Linked List; Happy Number.
- *Core:* Linked List Cycle; Linked List Cycle II (find the start); Palindrome Linked List.
- *Challenge:* Find the Duplicate Number (read the array as a functional graph); Circular Array Loop.

**Introduced:** Week 5 (linked lists).

---

### 7. In-Place Linked-List Reversal

**Definition.** Reverse all of a list, or a sublist, or fixed-size groups, by re-pointing `next` links with three pointers and no extra storage.

**Signal.** "Reverse the list," "reverse a sublist," "reverse in groups of k," "reorder," "rotate." Any list manipulation that must run in O(1) extra space.

**Skeleton.** Walk with `prev`, `cur`, `nxt`. Point `cur->next` back at `prev`, then slide all three forward. When you fall off the end, `prev` is the new head.

```cpp
Node *prev = nullptr, *cur = head;
while (cur) {
    Node* nxt = cur->next;
    cur->next = prev;
    prev = cur;
    cur = nxt;
}
// prev is the new head
```

**Complexity.** Time O(n). Space O(1).

**Problems.**
- *Warmup:* Reverse Linked List.
- *Core:* Reverse Linked List II (sublist); Swap Nodes in Pairs; Rotate List.
- *Challenge:* Reverse Nodes in k-Group; Reorder List; Add Two Numbers (with reversal).

**Introduced:** Week 5 (linked lists).

---

## Group C — Stack and Queue

### 8. Monotonic Stack

**Definition.** A stack kept in strictly increasing or decreasing order. When a new element would break the order, you pop, and each pop resolves an answer. That is how you find the next or previous greater or smaller element in amortized O(1) per element.

**Signal.** "Next greater element," "previous greater," "next smaller." "Largest rectangle." "Span." "Days until a warmer temperature." "Remove digits to keep the smallest number." Anything about bars and visibility.

**Skeleton.** Sweep once. While the top violates the monotonic invariant against the current element, pop it and record its answer. Then push the current index.

```cpp
stack<int> st;                 // holds indices; values strictly decreasing
for (int i = 0; i < n; ++i) {
    while (!st.empty() && a[st.top()] < a[i]) {
        ans[st.top()] = i;     // a[i] is the next greater element
        st.pop();
    }
    st.push(i);
}
```

**Complexity.** Time O(n) amortized; every index is pushed and popped once. Space O(n).

**Problems.**
- *Warmup:* Next Greater Element I; Daily Temperatures.
- *Core:* Next Greater Element II (circular); Remove K Digits; Online Stock Span; Sum of Subarray Minimums.
- *Challenge:* Largest Rectangle in Histogram; Trapping Rain Water (stack form); Maximal Rectangle.

**Introduced:** Week 6 (stacks and queues).

---

### 9. Stack for Parsing and Matching

**Definition.** Use a stack to hold open or unresolved context — brackets, operators, nested expressions — and resolve each item when its closing counterpart shows up.

**Signal.** Balanced parentheses. Expression evaluation. Infix to postfix and back. Nested decoding. "Score of parentheses." Backspace or undo semantics. Path simplification.

**Skeleton.** Push opening tokens and operands. On a closing token, or an operator of lower precedence, pop and combine until the matching context is resolved.

**Complexity.** Time O(n). Space O(n).

**Problems.**
- *Warmup:* Valid Parentheses; Backspace String Compare.
- *Core:* Evaluate Reverse Polish Notation; Infix to Postfix; Score of Parentheses; Simplify Path.
- *Challenge:* Basic Calculator I and II; Decode String; Longest Valid Parentheses.

**Introduced:** Week 6 (stacks and queues).

---

### 10. Deque and Monotonic Queue

**Definition.** A double-ended queue that holds candidate indices in monotonic order, so the window's maximum or minimum is always sitting at the front.

**Signal.** "Sliding window maximum" or "minimum." "Shortest subarray with sum at least K." A bounded-window optimization where a plain heap would be too slow because you cannot cheaply evict stale entries.

**Skeleton.** Before pushing index `i`, pop from the back every element worse than `a[i]`. Pop from the front any index that has slid out of the window. The front is now the window's extreme.

**Complexity.** Time O(n) amortized. Space O(k).

**Problems.**
- *Warmup:* Moving Average from Data Stream; Implement Queue using Stacks.
- *Core:* Sliding Window Maximum; Shortest Subarray with Sum at Least K.
- *Challenge:* Jump Game VI; Constrained Subsequence Sum.

**Introduced:** Week 6 (queues and deque). Reused for DP optimization in Week 15.

---

## Group D — Trees

### 11. Tree BFS (Level-Order)

**Definition.** Process the tree one depth at a time with a queue, finishing every node on a level before touching the next.

**Signal.** "Level order." "By row or depth." "Minimum depth." "Nearest." "Right side view." "Zigzag." "Connect nodes on the same level." The shortest path in an unweighted tree.

**Skeleton.** Push the root. While the queue is non-empty, process exactly `queue.size()` nodes (that is one full level) and enqueue their children.

```cpp
queue<Node*> q;
q.push(root);
while (!q.empty()) {
    int sz = q.size();
    for (int i = 0; i < sz; ++i) {
        Node* n = q.front(); q.pop();
        // visit n
        if (n->left)  q.push(n->left);
        if (n->right) q.push(n->right);
    }
}
```

**Complexity.** Time O(n). Space O(w), where w is the maximum width.

**Problems.**
- *Warmup:* Binary Tree Level Order Traversal; Average of Levels in Binary Tree.
- *Core:* Binary Tree Zigzag Level Order Traversal; Binary Tree Right Side View; Minimum Depth of Binary Tree; Populating Next Right Pointers.
- *Challenge:* Vertical Order Traversal of a Binary Tree; Maximum Width of Binary Tree.

**Introduced:** Week 8 (binary trees).

---

### 12. Tree DFS (Pre/In/Post-order and Path Recursion)

**Definition.** Recurse into the subtrees and combine the children's results on the way up (post-order), or thread state down on the way in (pre-order). This is the backbone of most tree problems.

**Signal.** "Path sum." "Diameter." "Height" or "is it balanced." "Lowest common ancestor." "Serialize." "Count or aggregate over subtrees." "Validate the structure."

**Skeleton.** Write a helper that returns the subtree's summary (a height, a sum, a found-flag). At each node, combine the left and right results and, if needed, update a global answer.

```cpp
int dfs(Node* n) {                 // returns height; updates a global diameter
    if (!n) return 0;
    int L = dfs(n->left), R = dfs(n->right);
    best = max(best, L + R);
    return 1 + max(L, R);
}
```

**Complexity.** Time O(n). Space O(h) for the recursion stack, h being the height.

**Problems.**
- *Warmup:* Maximum Depth of Binary Tree; Same Tree; Invert Binary Tree.
- *Core:* Path Sum I and II; Diameter of Binary Tree; Validate Binary Search Tree; Lowest Common Ancestor of a Binary Tree; Balanced Binary Tree.
- *Challenge:* Binary Tree Maximum Path Sum; Serialize and Deserialize Binary Tree; Construct Binary Tree from Preorder and Inorder Traversal; House Robber III.

**Introduced:** Week 8 (binary trees). The BST specialization is Week 9; DP on trees is Week 15.

---

### 13. BST-Ordered Traversal

**Definition.** Use the BST invariant (left < node < right). An in-order walk emits values in sorted order, and search, insert, and delete each prune one subtree at every step.

**Signal.** The words "binary *search* tree." "K-th smallest or largest." "Validate a BST." "Range queries." "Floor, ceiling, successor." "Convert a sorted array to a BST."

**Skeleton.** Compare against the node and descend one side. For the k-th smallest, do an in-order traversal with a counter, ideally iteratively with an explicit stack so you can stop early.

**Complexity.** Search, insert, delete are O(h): O(log n) when balanced, O(n) in the worst case. A full in-order walk is O(n).

**Problems.**
- *Warmup:* Search in a Binary Search Tree; Insert into a Binary Search Tree.
- *Core:* Kth Smallest Element in a BST; Validate Binary Search Tree; Lowest Common Ancestor of a BST; Range Sum of BST.
- *Challenge:* Delete Node in a BST; Convert Sorted List to Binary Search Tree; Recover Binary Search Tree.

**Introduced:** Week 9 (BST and AVL).

---

### 14. Trie (Prefix Tree)

**Definition.** An n-ary tree keyed by characters, where each root-to-node path spells a prefix. It answers prefix queries in time proportional to the length of the key, independent of how many keys are stored.

**Signal.** "Prefix." "Starts with." "Dictionary" or "autocomplete." "Word search on a board." "Replace words by their root." "Maximum XOR" (that one uses a bitwise trie).

**Skeleton.** Each node holds child pointers (an array of 26, or a map) and an `isWord` flag. Insert and search walk character by character, creating nodes only on insert.

**Complexity.** Insert and search are O(L) per word, where L is its length. Space O(total characters across all words).

**Problems.**
- *Warmup:* Implement Trie (insert, search, startsWith).
- *Core:* Add and Search Word with wildcards; Replace Words; Longest Word in Dictionary.
- *Challenge:* Word Search II (trie plus backtracking); Maximum XOR of Two Numbers in an Array (bitwise trie); Design Search Autocomplete System.

**Introduced:** Week 11 (tries).

---

## Group E — Heaps and Priority Queues

### 15. Top-K Elements

**Definition.** Keep a heap of size k to surface the k largest, smallest, or most frequent items without paying for a full sort.

**Signal.** "Top K." "K largest, smallest, or closest." "K most frequent." "The k-th largest." A stream where you only care about the extremes.

**Skeleton.** For the k largest, push into a *min*-heap and pop whenever its size passes k. What remains is exactly the k largest, and its top is the k-th largest.

```cpp
priority_queue<int, vector<int>, greater<int>> pq;   // min-heap, capped at k
for (int x : a) {
    pq.push(x);
    if ((int)pq.size() > k) pq.pop();
}
```

**Complexity.** Time O(n log k). Space O(k).

**Problems.**
- *Warmup:* Kth Largest Element in a Stream; Last Stone Weight.
- *Core:* Kth Largest Element in an Array; Top K Frequent Elements; K Closest Points to Origin.
- *Challenge:* Sort Characters By Frequency; Reorganize String; Task Scheduler.

**Introduced:** Week 10 (heaps and priority queues).

---

### 16. K-Way Merge

**Definition.** Merge k sorted sequences with a min-heap seeded by each sequence's head. Repeatedly pull the global minimum and replace it with the successor from the same source.

**Signal.** "Merge k sorted lists or arrays." "Smallest range covering elements from all lists." "K-th smallest in a sorted matrix." "Merge sorted streams."

**Skeleton.** Push the first element of each list along with which list it came from. Pop the minimum, append it to the output, then push the next element from that same list.

**Complexity.** Time O(N log k) for N total elements. Space O(k).

**Problems.**
- *Warmup:* Merge Two Sorted Lists; Merge Sorted Array.
- *Core:* Merge k Sorted Lists; Kth Smallest Element in a Sorted Matrix; Find K Pairs with Smallest Sums.
- *Challenge:* Smallest Range Covering Elements from K Lists; Ugly Number II.

**Introduced:** Week 10 (heaps). Ties back to merge sort from Week 9.

---

### 17. Two Heaps

**Definition.** Split the data into a max-heap holding the lower half and a min-heap holding the upper half, kept balanced so the median is always available at the heap tops.

**Signal.** "Median of a data stream." "Balance two halves." Scheduling under a median or percentile constraint. Anything that needs the middle of a set that keeps growing.

**Skeleton.** Push onto the max-heap, then move its top to the min-heap. Rebalance so the two sizes differ by at most one. The median is the larger heap's top, or the average of the two tops when sizes are equal.

**Complexity.** Insert O(log n), median query O(1). Space O(n).

**Problems.**
- *Warmup:* Find the median of a small fixed set (a build-up exercise).
- *Core:* Find Median from Data Stream; Sliding Window Median.
- *Challenge:* IPO (a capital min-heap paired with a profit max-heap); Maximize Capital.

**Introduced:** Week 10 (heaps).

---

## Group F — Graphs

### 18. Graph BFS / DFS and Connected Components

**Definition.** Systematic exploration. BFS gives shortest hop count in an unweighted graph; DFS gives reachability, components, and structure. A visited set keeps you from revisiting.

**Signal.** A grid or an adjacency list. "Shortest path in an unweighted graph or maze." "Number of islands, provinces, or components." "Flood fill." "Can I reach." "Clone the graph." "Is it bipartite."

**Skeleton.** BFS pops from a queue and expands neighbors level by level. DFS recurses (or uses a stack), marking each node as it goes. For components, loop over every node and launch a fresh traversal from each one that is still unvisited.

```cpp
queue<int> q;
q.push(s); seen[s] = true;
while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : adj[u])
        if (!seen[v]) { seen[v] = true; q.push(v); }
}
```

**Complexity.** Time O(V + E). Space O(V).

**Problems.**
- *Warmup:* Flood Fill; Number of Islands.
- *Core:* Clone Graph; Number of Provinces; Rotting Oranges (multi-source BFS); Is Graph Bipartite?; Word Ladder.
- *Challenge:* Shortest Path in Binary Matrix; Pacific Atlantic Water Flow; Walls and Gates; Bus Routes.

**Introduced:** Week 12 (graphs).

---

### 19. Topological Sort

**Definition.** Produce a linear ordering of a directed acyclic graph so that every edge points forward. In other words, process nodes in dependency order.

**Signal.** "Order of courses, tasks, or builds with prerequisites." "Detect a cycle in a directed graph." "A valid build order." "Alien dictionary ordering."

**Skeleton (Kahn's algorithm).** Compute in-degrees. Enqueue every node with in-degree zero. Pop one, append it to the order, and decrement each neighbor's in-degree, enqueuing any that reach zero. If fewer than V nodes come out, the graph has a cycle.

```cpp
queue<int> q;
for (int i = 0; i < V; ++i) if (indeg[i] == 0) q.push(i);
while (!q.empty()) {
    int u = q.front(); q.pop();
    order.push_back(u);
    for (int v : adj[u])
        if (--indeg[v] == 0) q.push(v);
}
```

**Complexity.** Time O(V + E). Space O(V).

**Problems.**
- *Warmup:* Course Schedule (can you finish?).
- *Core:* Course Schedule II (return the order); Minimum Height Trees; Find Eventual Safe States.
- *Challenge:* Alien Dictionary; Sequence Reconstruction; Parallel Courses (longest chain).

**Introduced:** Week 12 (graphs).

---

### 20. Weighted Shortest Path and MST

**Definition.** The weighted-graph family. Dijkstra for single-source with non-negative edges; Bellman-Ford when edges can be negative or you need to detect a negative cycle; Floyd-Warshall for all pairs; Prim and Kruskal for minimum spanning trees.

**Signal.** Edges carry weights, costs, or times. "Cheapest or fastest path." "Minimum cost to connect all nodes." "Within K stops." "Negative edges." "All-pairs distances." Network and spanning-tree problems.

**Skeleton (Dijkstra).** A min-heap keyed by tentative distance. Pop the closest unfinalized node, relax its outgoing edges, and push any improved distances. Kruskal instead sorts the edges and unions endpoints with Union-Find, skipping any edge that would form a cycle.

```cpp
priority_queue<pair<long,int>, vector<pair<long,int>>, greater<>> pq;
dist[s] = 0; pq.push({0, s});
while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (d > dist[u]) continue;
    for (auto [v, w] : adj[u])
        if (d + w < dist[v]) { dist[v] = d + w; pq.push({dist[v], v}); }
}
```

**Complexity.** Dijkstra O(E log V); Bellman-Ford O(V·E); Floyd-Warshall O(V³); Kruskal O(E log E); Prim O(E log V). Space O(V + E).

**Problems.**
- *Warmup:* Network Delay Time (Dijkstra); Find the Town Judge (a degree warm-up).
- *Core:* Cheapest Flights Within K Stops (Bellman-Ford); Path With Minimum Effort; Min Cost to Connect All Points (MST); Swim in Rising Water.
- *Challenge:* The Maze III; Critical Connections in a Network (bridges); Reconstruct Itinerary (Hierholzer); Connecting Cities With Minimum Cost.

**Introduced:** Week 13 (graphs). Dijkstra, Bellman-Ford, and MST deepen in Week 14.

---

### 21. Union-Find (Disjoint Set)

**Definition.** A near-constant-time structure for two questions: which set is x in, and merge these two sets. Path compression and union by rank or size are what make it fast.

**Signal.** "Connected components" as edges arrive one at a time. "Redundant connection." "Accounts merge." "Number of provinces." "Are these two in the same group." Cycle detection in an *undirected* graph. Kruskal's MST.

**Skeleton.** `find` returns the root and compresses the path on the way back. `unite` links one root under the other. The number of distinct roots is the number of components.

```cpp
int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
void unite(int a, int b) { a = find(a); b = find(b); if (a != b) p[a] = b; }
```

**Complexity.** Near O(α(n)), effectively O(1) amortized per operation. Space O(n).

**Problems.**
- *Warmup:* Number of Provinces; Find if Path Exists in Graph.
- *Core:* Redundant Connection; Accounts Merge; Number of Connected Components in an Undirected Graph; Most Stones Removed.
- *Challenge:* Number of Islands II (online); Satisfiability of Equality Equations; Smallest String With Swaps; Kruskal's MST end to end.

**Introduced:** Week 11 (union-find). It powers Kruskal the same week.

---

## Group G — Search, Subsets, Backtracking

### 22. Modified Binary Search

**Definition.** Binary search is not only for sorted arrays. It applies to any *monotonic* predicate, including a search over a range of candidate answers where "is X feasible?" flips from false to true exactly once. That is "binary search on the answer."

**Signal.** A sorted, rotated, or partially sorted array. "Find a boundary, the first or last occurrence, an insertion point." "Minimize the maximum" or "maximize the minimum." "The smallest capacity, speed, or number of days that works." Any monotone yes/no feasibility check.

**Skeleton.** Maintain `[lo, hi]`, compute `mid`, and move the boundary based on the comparison or on `feasible(mid)`. For "on the answer," binary-search the value range and write a `feasible()` predicate.

```cpp
int lo = 0, hi = maxVal;
while (lo < hi) {
    int mid = lo + (hi - lo) / 2;
    if (feasible(mid)) hi = mid;
    else               lo = mid + 1;
}
return lo;   // smallest feasible value
```

**Complexity.** Time O(log n), or O(n log range) when each feasibility check is O(n). Space O(1).

**Problems.**
- *Warmup:* Binary Search; Search Insert Position; First Bad Version.
- *Core:* Find First and Last Position of Element in Sorted Array; Search in Rotated Sorted Array; Find Minimum in Rotated Sorted Array; Find Peak Element.
- *Challenge:* Koko Eating Bananas; Capacity to Ship Packages Within D Days; Split Array Largest Sum; Median of Two Sorted Arrays.

**Introduced:** Week 7 (binary search). The "on the answer" extension is the same week and returns in the Week 16 review.

---

### 23. Subsets, Combinations, Permutations (Backtracking)

**Definition.** Build candidate solutions incrementally with DFS. Make a choice, recurse, then undo it. Choose, explore, un-choose. You walk the entire decision tree, pruning invalid branches as early as you can.

**Signal.** "All subsets, combinations, or permutations." "Generate all valid..." "Combination sum." "Partition into..." "Place N items under constraints." "Find all paths or all solutions." The answer is a *set of configurations*, not a single number.

**Skeleton.** A recursive `backtrack(start, path)` that records a solution at the right depth, loops over the available choices (skipping duplicates and used items), appends a choice, recurses, and then pops it.

```cpp
void bt(int start, vector<int>& path) {
    res.push_back(path);
    for (int i = start; i < n; ++i) {
        path.push_back(a[i]);
        bt(i + 1, path);
        path.pop_back();        // undo
    }
}
```

**Complexity.** Exponential by nature: subsets O(2ⁿ), permutations O(n·n!). Recursion depth (space) is O(n) beyond the output itself.

**Problems.**
- *Warmup:* Subsets; Combinations; Letter Combinations of a Phone Number.
- *Core:* Permutations and Permutations II; Combination Sum and Combination Sum II; Subsets II; Generate Parentheses; Palindrome Partitioning.
- *Challenge:* N-Queens; Sudoku Solver; Word Search; Word Break II; Restore IP Addresses.

**Introduced:** Week 14 (backtracking). The recursion foundations from Week 2 are the prerequisite.

---

## Group H — Dynamic Programming

### 24. 1D DP (Linear Sequence)

**Definition.** Define `dp[i]` over a single index, where the answer at `i` depends on a constant number of earlier states. Fill it bottom-up, and often collapse the whole table to a couple of rolling variables.

**Signal.** "Number of ways to reach step or index i." "Max or min over a 1D sequence with a local choice at each step." "Can you reach..." Overlapping subproblems on one axis: climbing stairs, robbing houses, decoding a string.

**Skeleton.** Write the recurrence `dp[i] = f(dp[i-1], dp[i-2], ...)`, set the base cases, and iterate forward. When only the last few states matter, keep two scalars instead of an array.

```cpp
int a = 0, b = 1;                 // climbing stairs
for (int i = 1; i <= n; ++i) {
    int c = a + b;
    a = b; b = c;
}
return b;
```

**Complexity.** Time O(n). Space O(n), dropping to O(1) with rolling variables.

**Problems.**
- *Warmup:* Fibonacci Number; Climbing Stairs; Min Cost Climbing Stairs.
- *Core:* House Robber and House Robber II; Decode Ways; Maximum Subarray (Kadane); Word Break.
- *Challenge:* Jump Game II; Longest Increasing Subsequence (the O(n log n) variant); Partition Equal Subset Sum.

**Introduced:** Week 15 (first week of the DP block).

---

### 25. 2D and Grid DP

**Definition.** `dp[i][j]` over two indices: a grid cell, or a pair of positions in two sequences. Each state combines results from adjacent or smaller states.

**Signal.** "Paths in a grid." "Min or max cost to reach (m, n)." "Two strings compared character by character." "A matrix with obstacles." A DP table indexed by `(i, j)`.

**Skeleton.** Fill the table row by row. Each cell depends on its top, left, and diagonal neighbors. Reduce to a single rolling row when only the previous row is ever needed.

**Complexity.** Time O(m·n). Space O(m·n), dropping to O(min(m, n)) with a rolling row.

**Problems.**
- *Warmup:* Unique Paths; Minimum Path Sum.
- *Core:* Unique Paths II (obstacles); Maximal Square; Triangle; Dungeon Game.
- *Challenge:* Cherry Pickup; Minimum Falling Path Sum II; Number of paths under constraints.

**Introduced:** Week 15 (second week of the DP block).

---

### 26. Knapsack DP (0/1 and Unbounded)

**Definition.** Choose items to optimize value under a capacity or budget. 0/1 uses each item at most once; unbounded lets you reuse items. This is the canonical selection-under-constraint DP.

**Signal.** "A subset summing to (or reaching) a target." "Max value within capacity W." "Fewest coins" or "number of ways to make an amount." "Can the array be partitioned." Items with a weight and a value.

**Skeleton.** `dp[w]` is the best value at capacity `w`. For **0/1**, loop items on the outside and capacity **descending** so each item is used once. For **unbounded**, loop capacity **ascending** so items can repeat.

```cpp
for (int i = 0; i < n; ++i)                 // 0/1 knapsack
    for (int w = W; w >= wt[i]; --w)
        dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
```

**Complexity.** Time O(n·W). Space O(W) with the 1D rolling array.

**Problems.**
- *Warmup:* Partition Equal Subset Sum; Subset Sum (feasibility).
- *Core:* 0/1 Knapsack; Coin Change (minimum coins, unbounded); Coin Change II (count the ways); Target Sum; Last Stone Weight II.
- *Challenge:* Ones and Zeroes (two-dimensional capacity); Combination Sum IV; Profitable Schemes.

**Introduced:** Week 15 (DP block). Ties to the subsets pattern from Week 14.

---

### 27. String DP (LCS, Edit Distance, Palindromes)

**Definition.** Two-sequence DP, or single-sequence interval DP, where `dp[i][j]` compares prefixes or substrings to compute alignment, similarity, or the best way to split an interval.

**Signal.** Two strings and "the longest common..." "Edit or transform distance." "Minimum insertions or deletions." "Interleaving." "Wildcard or regex matching." "Longest palindromic subsequence or substring." Interval DP like burst balloons or matrix-chain multiplication.

**Skeleton.** On a match, take the diagonal `dp[i-1][j-1]` plus one. On a mismatch, combine `dp[i-1][j]` and `dp[i][j-1]` (and `dp[i-1][j-1]` for edit distance). For the longest palindromic subsequence, run LCS of the string against its reverse, or fill intervals by increasing length.

```cpp
if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1] + 1;          // LCS
else                  dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
```

**Complexity.** Time O(m·n). Space O(m·n), dropping to O(min(m, n)) with a rolling row for many of the variants.

**Problems.**
- *Warmup:* Longest Common Subsequence; Is Subsequence.
- *Core:* Edit Distance; Longest Palindromic Subsequence; Minimum ASCII Delete Sum for Two Strings; Delete Operation for Two Strings; Longest Palindromic Substring.
- *Challenge:* Regular Expression Matching; Wildcard Matching; Interleaving String; Distinct Subsequences; Burst Balloons (interval DP).

**Introduced:** Week 15 (final week of the DP block).

---

## Group I — Bit Manipulation and Math

### 28. Bitwise XOR and Bit Manipulation

**Definition.** Use bitwise operators and the XOR identities (`x ^ x = 0`, `x ^ 0 = x`, and XOR is commutative and associative) to pair off, isolate, count, or mask bits in O(1) space.

**Signal.** "Find the single, missing, or duplicate number." "Every element appears twice except one." "Count the set bits." "Is it a power of two." "Subset masks." "Swap without a temporary." Bitmask DP over roughly 20 or fewer items.

**Skeleton.** XOR everything together and the pairs cancel, leaving the unique value. To isolate the lowest set bit, use `x & -x`. To iterate the submasks of a mask, use `sub = (sub - 1) & mask`.

```cpp
int x = 0;
for (int v : a) x ^= v;   // the element that appears an odd number of times
```

**Complexity.** Time O(n), or O(1) for the single-value tricks. Space O(1).

**Problems.**
- *Warmup:* Single Number; Number of 1 Bits; Power of Two.
- *Core:* Single Number II and III; Missing Number (XOR form); Counting Bits; Sum of Two Integers (without `+`); Reverse Bits.
- *Challenge:* Maximum XOR of Two Numbers in an Array (bitwise trie); subset generation via bitmasks; bitmask DP (Travelling Salesman, assignment).

**Introduced:** Week 16 (bit manipulation and number representation).

---

## At a glance

| # | Pattern | Group | Week |
|---|---------|-------|------|
| 1 | Two Pointers | Array / String | 3 |
| 2 | Sliding Window | Array / String | 3 |
| 3 | Prefix Sums | Array / String | 3 |
| 4 | Merge Intervals | Array / String | 4 |
| 5 | Cyclic Sort | Array / String | 4 |
| 6 | Fast and Slow Pointers | Linked List | 5 |
| 7 | In-Place List Reversal | Linked List | 5 |
| 8 | Monotonic Stack | Stack / Queue | 6 |
| 9 | Stack Parsing / Matching | Stack / Queue | 6 |
| 10 | Deque / Monotonic Queue | Stack / Queue | 6 |
| 11 | Tree BFS | Trees | 8 |
| 12 | Tree DFS | Trees | 8 |
| 13 | BST-Ordered Traversal | Trees | 9 |
| 14 | Trie | Trees | 11 |
| 15 | Top-K Elements | Heaps | 10 |
| 16 | K-Way Merge | Heaps | 10 |
| 17 | Two Heaps | Heaps | 10 |
| 18 | Graph BFS / DFS and Components | Graphs | 12 |
| 19 | Topological Sort | Graphs | 12 |
| 20 | Weighted Shortest Path and MST | Graphs | 13 |
| 21 | Union-Find | Graphs | 11 |
| 22 | Modified Binary Search | Search | 7 |
| 23 | Subsets / Permutations (Backtracking) | Search | 14 |
| 24 | 1D DP | DP | 15 |
| 25 | 2D / Grid DP | DP | 15 |
| 26 | Knapsack (0/1 and Unbounded) | DP | 15 |
| 27 | String DP (LCS / Edit / Palindrome) | DP | 15 |
| 28 | Bitwise XOR and Bit Manipulation | Misc | 16 |

Twenty-eight patterns across nine groups. Every interview pattern named in the course outline is here: two pointers, sliding window, fast and slow pointers, prefix sums, merge intervals, cyclic sort, in-place linked-list reversal, monotonic stack, tree BFS, tree DFS, two heaps, top-K, K-way merge, subsets, modified binary search, backtracking, topological sort, union-find, 0/1 and unbounded knapsack, 1D DP, LCS, palindromic subsequence, and bitwise XOR, plus the deque, BST, trie, weighted-shortest-path and MST, grid-DP, and string-DP patterns that round out the set.

Work through them in week order if you are taking the course alongside this file. If you are using it as a review reference, work down each group until the Challenge problems feel routine.
