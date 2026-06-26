# Week 12 — Graphs Part 1: Representation, Traversal, and Ordering

Graphs are where the patterns from the first eleven weeks come together. This week you represent them three ways and pick deliberately between them, traverse with DFS and BFS in both recursive and iterative form, and apply traversal to the questions that traversal actually answers: connected components, cycle detection in undirected and directed graphs, and topological sort of a DAG. By the end you have a reusable adjacency-list graph module and the judgment to know which traversal a new problem wants before you start typing.

Almost every grid problem you've already seen is a graph problem in disguise. Once you see the cell-as-node, neighbor-as-edge mapping, "number of islands" and "shortest path in a binary matrix" stop being separate tricks and become the same two algorithms with a different adjacency function.

## By the end of this week

You should be able to:

- Choose between adjacency list, adjacency matrix, and edge list based on whether the graph is dense or sparse and what queries you need, and state the cost of each: O(V+E) space for a list, O(V^2) for a matrix.
- Implement DFS recursively and iteratively with an explicit `std::stack`, marking visited on entry or push rather than on pop, so a node is never queued or recursed into twice.
- Treat a grid as an implicit graph, with cells as nodes and the 4 or 8 neighbors as edges, and reuse the same traversal code for flood fill and island counting.
- Count connected components in an undirected graph by counting DFS launches from unvisited nodes.
- Detect cycles correctly: parent exclusion in undirected graphs, and the gray-node back-edge rule (3-color DFS) in directed graphs, without falling for the false-positive undirected cycle bug.
- Run BFS with a queue to get the shortest path by edge count on an unweighted graph, marking visited on enqueue so nodes are never enqueued twice.
- Seed BFS with every source at distance 0 for multi-source problems, and use a deque for 0-1 BFS when edges carry weight 0 or 1.
- Produce a topological order two ways: Kahn's indegree-based BFS, which reports a cycle when fewer than V nodes come out, and DFS reverse-finish order.

The milestone for the week: a reusable graph module (adjacency list with recursive and iterative DFS, BFS, and multi-source BFS) that you use to solve connected components, directed and undirected cycle detection, and topological sort via both Kahn's and DFS, leaving you ready for the weighted-graph algorithms in the next track.

The patterns introduced this week are in the [pattern reference](../docs/patterns.md): [Graph BFS/DFS & components](../docs/patterns.md), [Tree DFS](../docs/patterns.md), [Tree BFS](../docs/patterns.md), [Multi-source BFS](../docs/patterns.md), and [Topological sort](../docs/patterns.md). Keep it open while you solve.

---

## Lecture 45 — Graph Representation and Depth-First Search

Before any algorithm, you have to decide how the graph lives in memory. That single choice decides whether your traversal is O(V+E) or O(V^2), so it is not a detail. Then DFS, the workhorse you'll use for the next two weeks.

### Objectives

- Choose between adjacency list, adjacency matrix, and edge list by graph density and the queries you need.
- Implement DFS both recursively and iteratively with an explicit stack, with disciplined visited marking.
- Treat grids as implicit graphs: cells as nodes, 4 or 8 neighbors as edges.

### Topics covered

- Vocabulary first: directed versus undirected, weighted versus unweighted, what makes a graph a DAG, and dense versus sparse. These terms decide every later choice, so we pin them down before writing code.
- Adjacency list as `vector<vector<int>>`: O(V+E) space, fast to iterate a node's neighbors, the default for sparse graphs (which is most of them). Adjacency matrix as `vector<vector<int>>` of size V×V: O(V^2) space, O(1) edge-existence checks, worth it only when the graph is dense or you query edges constantly. Edge list as a flat `vector<array<int,3>>`: compact, and the natural input form for Kruskal's MST next track.
- Recursive DFS, the short version, and iterative DFS with `std::stack` so deep or adversarial graphs don't overflow the real call stack. The two are the same traversal; the iterative one just moves the frames onto the heap.
- The discipline that prevents the most common graph bug: mark a node visited when you *enter* it (recursive) or when you *push* it (iterative), not when you pop it. Marking on pop lets the same node sit on the stack many times and get processed repeatedly.
- Grids as implicit graphs. A cell `(r, c)` is a node; its neighbors are the in-bounds cells among the 4 (or 8) directions. You never build an explicit adjacency list; the neighbor function *is* the graph. Flood fill and counting islands are DFS over this implicit graph.
- One STL trap: `vector<bool>` is a bit-packed specialization, so its elements are proxies, not real `bool&`. For a `visited` array it works, but the moment you want a reference or a pointer to an element, reach for `vector<char>` instead.

### Patterns

- [Graph BFS/DFS & components](../docs/patterns.md)
- [Tree DFS](../docs/patterns.md)

### In-class problems

- Number of Islands
- Flood Fill
- Clone Graph
- Iterative DFS of an adjacency list

---

## Lecture 46 — Connected Components and Cycle Detection

DFS gives you two structural facts almost for free: how many pieces the graph is in, and whether it has a cycle. The cycle question is where people get burned, because the correct rule is different for undirected and directed graphs.

### Objectives

- Count connected components in an undirected graph by repeated DFS launches from unvisited nodes (union-find is the alternative).
- Detect cycles correctly: parent exclusion in undirected graphs, gray-node back-edge (3-color) detection in directed graphs.
- Use DFS discovery and finish timestamps, and recognize the false-positive undirected cycle bug.

### Topics covered

- Connected components: loop over all nodes, and every time you find an unvisited one, launch a DFS and increment a counter. The number of launches is the number of components. The same count falls out of union-find by counting distinct roots, which is why this problem shows up in both tracks.
- Edge classification on the DFS tree (tree edge, back edge, forward edge, cross edge). The one that matters here: a back edge to an ancestor still on the active path means a cycle.
- Directed cycle detection with three colors. White means unvisited, gray means on the current recursion path, black means fully explored. Reaching a gray node is a back edge and proves a cycle. A gray array (or `state[]` with values 0/1/2) is all you need.
- Undirected cycle detection by parent check: during DFS, an edge back to an already-visited node is a cycle *unless* that node is the parent you just came from. The false-positive bug is forgetting to exclude the parent, which flags every single edge as a cycle. Union-find is the clean alternative: if both endpoints of an edge already share a root, that edge closes a cycle.
- Discovery and finish times as the general framework underneath all of this, with bridges and articulation points named as the natural next step (covered conceptually now, in depth later).

### Patterns

- [Graph BFS/DFS & components](../docs/patterns.md)

### In-class problems

- Number of Provinces (DFS version)
- Detect Cycle in a Directed Graph (3-color)
- Detect Cycle in an Undirected Graph
- Pacific Atlantic Water Flow

---

## Lecture 47 — Breadth-First Search and Shortest Paths on Unweighted Graphs

DFS goes deep; BFS goes wide, one ring at a time. That layer-by-layer expansion is exactly what gives you the shortest path by edge count, and it is the reason BFS, not DFS, is the tool for unweighted shortest paths.

### Objectives

- Use BFS with a queue to find the shortest path (fewest edges) on an unweighted graph, marking visited on enqueue.
- Apply multi-source BFS by seeding the queue with every source at distance 0.
- Use 0-1 BFS with a deque for graphs whose edges have weight 0 or 1.

### Topics covered

- BFS expands in distance layers: all nodes at distance 1, then all at distance 2, and so on. The first time you reach a node is along a shortest path in edges, which is the whole point.
- Mark visited on enqueue, never on dequeue. If you wait until dequeue, the same node gets enqueued by several neighbors before it's processed, and the queue blows up. This is the BFS twin of the DFS "mark on push" rule.
- Why BFS is not a substitute for Dijkstra on a weighted graph: BFS counts edges, so it finds the path with the fewest hops, which is not the cheapest path once edges carry different weights. That distinction is the bridge into next track.
- Multi-source BFS: push every starting cell into the queue at distance 0 before the loop, then run one ordinary BFS. The frontier expands from all sources at once, which is exactly what "rotting oranges" and "nearest exit" need.
- 0-1 BFS with a `std::deque`: for edges of weight 0 or 1, push 0-weight moves to the front and 1-weight moves to the back. This keeps the deque sorted by distance and gives Dijkstra-quality answers in O(V+E) on this restricted class of graph.
- Encoding a grid cell `(r, c)` as the single integer `r * cols + c` when you want to store visited or distance in a flat structure or use a cell as a map key.

### Patterns

- [Graph BFS/DFS & components](../docs/patterns.md)
- [Tree BFS](../docs/patterns.md)
- [Multi-source BFS](../docs/patterns.md)

### In-class problems

- Rotting Oranges (multi-source BFS)
- Word Ladder
- Shortest Path in Binary Matrix
- Walls and Gates

---

## Lecture 48 — Topological Sort of a DAG

If your nodes have dependencies (this task before that one, this course before its sequel), you want an ordering that respects every edge. That ordering exists exactly when the graph has no cycle, and you can produce it two different ways. Both also tell you, as a side effect, whether the graph was a DAG at all.

### Objectives

- Produce a topological ordering with Kahn's indegree-based BFS, detecting a cycle when fewer than V nodes are emitted.
- Produce a topological ordering via DFS reverse-finish order.
- Apply topological sort to dependency and prerequisite problems, and recognize that it sets up DAG dynamic programming.

### Topics covered

- A topological order is a linear ordering of the nodes where every edge points forward. It exists if and only if the graph is acyclic, which is why these problems double as cycle detection.
- Kahn's algorithm: compute the indegree of every node, push all indegree-0 nodes into a queue, then repeatedly pop a node, append it to the order, and decrement its neighbors' indegrees, enqueuing any that hit 0. If you emit fewer than V nodes, the leftover nodes are tangled in a cycle. The cycle check is free.
- DFS-based topological sort: run DFS, and when a node finishes (all its descendants are done), push it onto a stack. The reverse of finish order is a topological order. With a `state[]` array you also catch a cycle via the gray-node rule from Lecture 46.
- For the lexicographically smallest valid order, swap Kahn's plain queue for a `std::priority_queue` or `std::set` so you always extract the smallest available indegree-0 node.
- Where this lands in practice: course scheduling, build-order resolution, and package dependency ordering. The forward link is to longest-path DP on a DAG, which processes nodes in topological order so every dependency is already solved when you reach a node.

### Patterns

- [Topological sort](../docs/patterns.md)
- [Graph BFS/DFS & components](../docs/patterns.md)

### In-class problems

- Course Schedule (cycle detection)
- Course Schedule II (topological order)
- Alien Dictionary
- Minimum Height Trees

---

## Homework

Work these between lectures, in roughly this order. The warmups confirm the traversal is in your hands; the core set is the week's real practice; the challenges push you onto the harder graph modeling and the directed-cycle rule.

**Warmup**

- Number of Islands
- Flood Fill
- Find if Path Exists in Graph

**Core**

- Clone Graph
- Number of Provinces
- Course Schedule
- Course Schedule II
- Rotting Oranges
- Word Ladder
- Pacific Atlantic Water Flow

**Challenge**

- Alien Dictionary
- Detect Cycle in a Directed Graph with 3-color DFS

---

## Before next week

- You can build an adjacency list from an edge list, and say in one sentence when a matrix is the better representation and what it costs.
- You can write DFS both recursively and iteratively, and you mark visited on entry or push every time, without thinking about it.
- You can count connected components, and you can detect a cycle correctly in both an undirected graph (parent exclusion) and a directed graph (3-color back edge), including why the naive undirected check produces false positives.
- You can write BFS for unweighted shortest paths, marking visited on enqueue, and you can seed it for multi-source problems.
- You can produce a topological order with both Kahn's algorithm and DFS reverse-finish order, and use either one to detect a cycle.
- The week's homework is done, and you can take a fresh graph or grid problem and decide DFS versus BFS versus topological sort before you write a line.

The next track (Dijkstra, Bellman-Ford, MST) is built directly on this traversal foundation, so a shaky grasp of cycle detection or topological sort will show up there first. Both reward a second pass now over a scramble later.

---

Back to the [course README](../README.md) · Pattern reference: [docs/patterns.md](../docs/patterns.md)
