# Week 11 — Tries and Union-Find: Prefix and Partition Structures

Two specialized structures that show up constantly once you know to look for them. A trie shares prefixes across a whole dictionary, so insert, search, and `startsWith` cost O(L) in the length of the word, not the size of the dictionary. Union-find tracks a partition of elements into disjoint sets and answers "are these two connected?" in near-constant time, which makes it the right tool for connectivity, cycle detection, and the engine inside Kruskal's MST that you'll meet in the graph track.

By the end of the week you've shipped both from scratch, asserted them against edge cases, and used the trie to solve Word Search II and union-find to solve connected components and undirected cycle detection.

## By the end of this week

- Build a trie node with a children map and an `isEndOfWord` flag, and implement insert, search, and `startsWith`, each O(L) and independent of how many words the trie holds.
- Distinguish exact search (the path exists *and* ends a word) from prefix search (the path exists at all), and never confuse the two.
- Choose between an `array[26]` and an `unordered_map<char, Node*>` for children based on alphabet size and density, and explain the memory-versus-speed trade.
- Support wildcard matching by branching a DFS over a node's children when you hit a `.`.
- Combine a trie with backtracking to solve Word Search II, pruning grid paths by trie edges instead of brute-forcing every word.
- Use a bitwise trie of bits to answer maximum-XOR queries.
- Implement union-find with `find` and `union`, always operating on roots, and apply union-by-rank/size plus path compression to reach O(alpha(n)) amortized per operation.
- Maintain a live component count, decrementing it on every successful union.
- Detect a cycle in an undirected graph by unioning endpoints and checking whether they already shared a root.
- Recognize when union-find beats BFS/DFS: edges arriving over time, and online connectivity queries.

Patterns this week: [Trie (Prefix Tree) Traversal](../docs/patterns.md), [Subsets / Backtracking](../docs/patterns.md), [Union-Find (Disjoint Set)](../docs/patterns.md), and [Graph BFS/DFS & Components](../docs/patterns.md).

---

## Lecture 41 — Tries: Prefix Trees, Insert, Search, startsWith

A trie is a tree where the path from the root to a node spells a string. Words that share a prefix share the nodes for that prefix, so a dictionary of ten thousand words that all start with `inter` stores those five characters once. That sharing is the whole point, and it's why every operation costs O(L) regardless of dictionary size.

### Objectives

- Explain how shared prefixes share nodes, making insert, search, and `startsWith` O(L) and independent of the number of words stored.
- Implement a trie node with children plus an `isEndOfWord` flag, and distinguish exact search from prefix search.
- Choose between an `array[26]` and a hash-map children representation based on alphabet size and density.

### Topics

- The structure: each edge is labeled with a character, and the path from the root to a node spells a prefix. A node is just a set of child pointers plus a boolean. There is no character stored *in* the node; the character lives on the edge.
- `isEndOfWord` is what separates a stored word from a prefix that merely passes through. Insert `apple` and `app`, and both nodes carry the flag; insert only `apple`, and the node at `app` is a transit node, not a word.
- The three operations, all O(L):
  - `insert(word)`: walk character by character, creating child nodes that don't exist yet, and set `isEndOfWord` on the final node.
  - `search(word)`: walk the path; if any character has no child you fail, and if you reach the end you must *also* check `isEndOfWord`. Reaching the last node is not enough.
  - `startsWith(prefix)`: walk the path; success is simply that every character had a child. You do not check `isEndOfWord`.
- Children representation. `array[26]` of pointers is the fast choice for a fixed lowercase alphabet: O(1) indexing, no hashing, but 26 pointers per node whether or not they're used, which is memory-heavy on sparse tries. `unordered_map<char, Node*>` is compact (only the children that exist) and handles arbitrary character sets, at the cost of hashing on every step.
- Value-initialize child pointers to `nullptr` so an absent child is unambiguous. A recursive destructor frees the subtree: delete every child, then delete the node.
- Delete as a challenge: unmark `isEndOfWord` on the target, then prune leaf nodes back up the path, stopping the moment you hit a node that still has children or is itself the end of another word.

### Patterns

- [Trie (Prefix Tree) Traversal](../docs/patterns.md)

### In-class problems

- Implement Trie (insert/search/startsWith)
- Longest Word in Dictionary (built one character at a time)
- Replace Words (dictionary roots)
- Count words with a given prefix

---

## Lecture 42 — Trie Applications: Wildcards, Word Search II, Max-XOR

Once the trie exists, the interesting work is what you walk it *with*. A wildcard turns a single path walk into a branching DFS. Word Search II turns a grid search inside out by walking the dictionary instead of the words. And a trie built over the *bits* of a number answers maximum-XOR in O(32) per query.

### Objectives

- Support wildcard matching by branching a DFS over a node's children whenever the pattern character is a `.`.
- Combine a trie with backtracking to solve Word Search II efficiently on a grid.
- Use a bitwise trie to find the maximum XOR of two numbers in an array.

### Topics

- Wildcard `.` matching. Search stops being a single path walk and becomes a DFS. On a concrete character, follow that one child if it exists. On a `.`, recurse into *every* existing child and succeed if any branch reaches an `isEndOfWord` node at the end of the pattern.
- Word Search II. The brute force runs DFS from every cell for every word, which is roughly O(W * cells * 4^L). Instead, build a trie of all the words, then DFS the grid once, advancing through the trie as you step between adjacent cells. The trie edges *are* your pruning: if the current cell's letter has no child at the current trie node, that whole branch of the grid is dead and you stop immediately. The shared prefix walk means a hundred words sharing a stem cost that stem once. Mark a word found when you land on an `isEndOfWord` node, and trim that node from the trie once collected so you don't re-report it.
- Bitwise trie for maximum XOR. Insert each number as a path of its bits from most significant to least, so the trie is binary (one child for 0, one for 1). To maximize XOR against a query number, walk the trie greedily taking the *opposite* bit at each level whenever that child exists, since an opposing bit sets that position to 1 in the result. This turns the O(n^2) all-pairs scan into n insertions plus n queries, each O(32).
- Memory note: a standard trie can be pointer-heavy. Compressed or radix tries (Patricia tries) collapse chains of single-child nodes into one edge labeled with a substring, trading a little code complexity for a large memory win on sparse dictionaries.

### Patterns

- [Trie (Prefix Tree) Traversal](../docs/patterns.md)
- [Subsets / Backtracking](../docs/patterns.md)

### In-class problems

- Add and Search Words Data Structure (wildcard `.`)
- Word Search II
- Maximum XOR of Two Numbers in an Array (bitwise trie)
- Design a prefix-based autocomplete

---

## Lecture 43 — Union-Find: Union by Rank and Path Compression

Union-find (also called disjoint-set union, or DSU) maintains a partition of n elements into disjoint sets and supports two operations: `find(x)`, which returns the representative of x's set, and `union(x, y)`, which merges the two sets. The whole structure is a forest where each element points to a parent, and the root of a tree is the set's representative. Two elements are in the same set exactly when they have the same root.

### Objectives

- Implement `find` and `union` over a forest, always operating on roots.
- Apply union-by-rank/size and path compression to reach O(alpha(n)) amortized per operation.
- Maintain a running component count, decrementing it on each successful union.

### Topics

- The forest model. `parent[x]` points to x's parent; a root points to itself. `find(x)` follows parent pointers until it reaches a root. `union(x, y)` finds both roots and, if they differ, attaches one to the other. You never union or compare raw elements; you always resolve to roots first.
- Union by rank or size. Attach the smaller tree under the larger one so trees stay shallow. Rank is an upper bound on tree height; size is the element count. Either keeps `find` paths short. Attaching the larger tree under the smaller one is the classic mistake that lets a tree degrade into a chain.
- Path compression. While returning from a `find`, repoint nodes directly at the root so the next `find` is faster. Two common forms: recursive full compression (`parent[x] = find(parent[x])`), which flattens the entire path, and iterative path-halving (`parent[x] = parent[parent[x]]`), which compresses every other link in a single loop with no recursion.
- Combined cost. Union-by-rank with path compression gives O(alpha(n)) amortized per operation, where alpha is the inverse Ackermann function. For any n you will ever see, alpha(n) <= 4, so each operation is effectively constant.
- Initialization and index mapping. Initialize `parent` with `std::iota` so every element is its own root, and set all ranks to 0. Map arbitrary labels (strings, names) to integer indices with a hash map, and flatten a 2D grid to 1D with `r * cols + c` so cells become DSU elements.
- Component count. Start the count at n and decrement it on every union that actually merges two distinct sets. A union where both endpoints already share a root changes nothing and must not decrement the count.

### Patterns

- [Union-Find (Disjoint Set)](../docs/patterns.md)

### In-class problems

- Implement Union-Find with union-by-rank and path compression
- Number of Connected Components in an Undirected Graph
- Number of Provinces (Friend Circles)
- Find if Path Exists in Graph

---

## Lecture 44 — Union-Find Applications and the Bridge to Graphs

Union-find is at its best when edges arrive over time and you need to answer connectivity as you go. This lecture works the application set (cycle detection, redundant connection, account merging, grid components), draws the line on what DSU can and can't do, and previews Kruskal's MST, where DSU is the engine that drives the whole algorithm.

### Objectives

- Use DSU for cycle detection in undirected graphs and for incremental, dynamic connectivity.
- Recognize when DSU beats BFS/DFS: edges arriving over time, and online connectivity queries.
- Connect DSU to Kruskal's MST and to grid-component problems as a preview of the graph track.

### Topics

- Cycle detection in an undirected graph. For each edge, find the roots of its two endpoints. If they already share a root, adding this edge closes a cycle, so report it. Otherwise union them. Processing every edge this way detects the first cycle in near-linear time.
- The application set. Redundant Connection finds the edge that creates a cycle in a tree-plus-one-edge graph. Accounts Merge unions accounts that share an email and then groups by root. Satisfiability of Equality Equations unions all `==` constraints first, then checks every `!=` constraint against the resulting partition. Number of Islands unions adjacent land cells on a grid and counts distinct roots.
- What DSU cannot do. It is merge-only: there is no efficient split or deletion of an element from a set once merged. Rollback (undoing the last union) is possible if you skip path compression and keep a stack of changes, but that's an advanced aside, not the default structure.
- When DSU beats DFS. If the graph is fixed and you need one traversal, BFS/DFS is fine. DSU wins when edges are added incrementally and you must answer "connected yet?" between additions (dynamic connectivity), or when you can process all unions first and answer queries afterward (offline merging). Those are cases where re-running a traversal per query would be wasteful.
- Kruskal's MST preview. Sort edges by weight, then add each edge whose endpoints are in different sets, unioning as you go and skipping any edge that would form a cycle. DSU is exactly the cycle check that makes Kruskal's correct and fast. You'll build the full algorithm in the graph track; this is the setup.

### Patterns

- [Union-Find (Disjoint Set)](../docs/patterns.md)
- [Graph BFS/DFS & Components](../docs/patterns.md)

### In-class problems

- Redundant Connection
- Accounts Merge
- Satisfiability of Equality Equations
- Number of Islands via union-find

---

## Homework

Work these between lectures, in roughly this order. The warmups confirm the structures are in your hands; the core set is the week's real practice; the challenges combine the two structures with backtracking and string handling.

**Warmup**

- Implement Union-Find from scratch with both optimizations
- Number of Provinces
- Find if Path Exists in Graph

**Core**

- Implement Trie (insert/search/startsWith)
- Add and Search Words Data Structure
- Replace Words
- Redundant Connection
- Number of Connected Components in an Undirected Graph
- Satisfiability of Equality Equations

**Challenge**

- Word Search II
- Maximum XOR of Two Numbers in an Array
- Accounts Merge

---

## Before next week

- You can implement a trie with insert, search, and `startsWith`, and you reliably check `isEndOfWord` on exact search while skipping it on prefix search.
- You can explain the `array[26]` versus hash-map children trade and pick the right one for the alphabet in front of you.
- You can extend search to wildcards with a branching DFS, and you can describe why a trie collapses Word Search II's brute force into one shared prefix walk.
- You can implement union-find with union-by-rank and path compression, keep a correct component count, and detect an undirected cycle with it.
- You can name at least two situations where DSU beats re-running BFS/DFS, and you can sketch how Kruskal's MST uses DSU as its cycle check.
- The week's homework is done, and the milestone build (a from-scratch trie with wildcard support solving Word Search II, plus an assert-tested union-find used for connected components and cycle detection) compiles and passes its checks.

Redundant Connection and Accounts Merge are the two worth reworking if the union-find application set still feels uncertain. Week 12 opens the graph track, where DSU reappears as the cycle check inside Kruskal's MST.

---

Back to the [course README](../README.md) · Pattern reference: [docs/patterns.md](../docs/patterns.md)
