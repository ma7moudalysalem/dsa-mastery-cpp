# Build-By-Hand Code

This folder holds the starter C++ files for the course: one file per data structure or algorithm, written for you to implement yourself. Each file ships with a complete assert-based test harness. Your job is to fill in the methods marked `TODO` until the file compiles, runs, and prints `All checks passed`.

You don't write the tests, and you don't write `main()`. You write the structure. When every assertion holds, you know your implementation is correct.

## How a file works

Open any file and you'll find the public interface already declared, a `main()` full of assertions at the bottom, and method bodies left for you to complete. Unimplemented methods throw:

```cpp
throw std::logic_error("TODO: implement push_back");
```

That convention matters. A fresh, untouched file still compiles cleanly. When you run it, the first unimplemented method it reaches throws, and the message tells you exactly which method to write next. Implement that one, recompile, run again, and the harness walks you to the next gap. You're never guessing what to do; the file tells you.

When the last `TODO` is gone and every assertion passes, you'll see `All checks passed` on stdout.

## Compile and run

Use a C++17 compiler. From the repository root:

```bash
g++ -std=c++17 -Wall code/data-structures/singly_linked_list.cpp -o sll && ./sll
```

The same command works on macOS and Linux. On Windows, use `g++` from MinGW, or run the command inside WSL.

`-Wall` is there on purpose. The warnings catch the mistakes that assertions don't.

## Start with the worked reference

`code/data-structures/dynamic_array.cpp` is a fully implemented file. It is the model: it shows the style, the naming, the level of commenting, and the standard of correctness every other file is meant to reach. Read it first, front to back. Then treat the rest as practice and bring them up to the same standard.

The full reference solutions for the remaining scaffolds are walked through on camera in the course. This repository is the public practice scaffold.

## Files

### Data structures

| File | Week | Topic |
| --- | --- | --- |
| `code/data-structures/dynamic_array.cpp` | Week 3 | Dynamic Array (your own `std::vector`) — fully worked model |
| `code/data-structures/singly_linked_list.cpp` | Week 5 | Singly Linked List |
| `code/data-structures/doubly_linked_list.cpp` | Week 5 | Doubly Linked List |
| `code/data-structures/hash_table.cpp` | Week 4 | Hash Table (separate chaining) |
| `code/data-structures/stack.cpp` | Week 6 | Stack (array-backed) |
| `code/data-structures/queue_deque.cpp` | Week 6 | Circular Queue (ring buffer) |
| `code/data-structures/binary_tree.cpp` | Week 8 | Binary Tree & Traversals |
| `code/data-structures/binary_search_tree.cpp` | Week 9 | Binary Search Tree |
| `code/data-structures/avl_tree.cpp` | Week 9 | AVL Tree (self-balancing BST) |
| `code/data-structures/binary_heap.cpp` | Week 10 | Binary Min-Heap / Priority Queue |
| `code/data-structures/trie.cpp` | Week 11 | Trie (prefix tree) |
| `code/data-structures/union_find.cpp` | Week 11 | Union-Find (Disjoint Set Union) |
| `code/data-structures/graph.cpp` | Week 12 | Graph (adjacency list) with BFS & DFS |

### Algorithms

| File | Week | Topic |
| --- | --- | --- |
| `code/algorithms/recursion.cpp` | Week 2 | Recursion Fundamentals |
| `code/algorithms/sorting.cpp` | Week 7 | Sorting Algorithms |
| `code/algorithms/binary_search.cpp` | Week 7 | Binary Search & the Predicate Framework |
| `code/algorithms/graph_algorithms.cpp` | Weeks 12–13 | Weighted Graph Algorithms (topological sort, Dijkstra, Bellman-Ford, MST) |
| `code/algorithms/backtracking.cpp` | Week 14 | Backtracking (choose / explore / un-choose) |
| `code/algorithms/dynamic_programming.cpp` | Week 15 | Dynamic Programming (knapsack, LIS, LCS, edit distance) |
| `code/algorithms/bit_manipulation.cpp` | Week 16 | Bit Manipulation |

## See also

- [../README.md](../README.md) — repository overview
- [../CURRICULUM.md](../CURRICULUM.md) — week-by-week curriculum
