# Week 13 — Graphs Part 2 — Weighted Shortest Paths & Minimum Spanning Trees

Last week the edges had no cost and BFS was enough. This week every edge carries a weight, and "shortest" stops meaning "fewest hops" and starts meaning "least total cost." You'll build the five algorithms that show up over and over in interviews and in real systems: Dijkstra, Bellman-Ford, Floyd-Warshall, Prim, and Kruskal. Two of them, Bellman-Ford and Floyd-Warshall, are taught as dynamic programming on a graph, which plants the seed that Weeks 15 and 16 grow into the full DP block.

## By the end of this week

- Pick the correct weighted-graph algorithm straight from a problem's signals: are the weights non-negative, can they be negative, is there one source or do you need all pairs, how dense is the graph.
- Implement Dijkstra with a `priority_queue`, explain why it needs non-negative edges, and handle the missing decrease-key with the lazy-deletion idiom.
- Implement Bellman-Ford by relaxing every edge `V-1` times, detect a reachable negative cycle with one more pass, and say out loud why this is DP over "shortest path using at most `k` edges."
- Implement Floyd-Warshall as a three-loop DP with `k` on the outside, and explain why getting the loop order wrong silently produces wrong answers.
- Reconstruct an actual path (not just its length) with a parent array.
- State the cut property and use it to justify both Prim's and Kruskal's greedy choices, then implement each and choose between them by graph density.
- Tell an MST apart from a shortest-path tree, and know that minimizing total connection weight is a different problem from minimizing distance from a source.

Patterns this week: [Weighted Shortest Path & MST](../docs/patterns.md) and [Union-Find](../docs/patterns.md).

---

## Lecture 49 — Dijkstra's Algorithm: Single-Source Shortest Path with a Min-Heap

The default tool for shortest paths when every edge weight is non-negative. The idea is greedy: repeatedly finalize the closest unvisited vertex, because once it's the closest, nothing you reach later can make it cheaper. That last clause is exactly why a negative edge breaks the algorithm.

### Objectives

- Implement Dijkstra with a priority queue and explain why it requires non-negative edge weights.
- Use the lazy-deletion idiom (push duplicates, skip stale pops) because `std::priority_queue` has no decrease-key.
- Reconstruct the actual shortest path and apply Dijkstra to grid and cost variants.

### Topics

- Weighted graph representation: an adjacency list of `(neighbor, weight)` pairs, `vector<vector<pair<int,int>>>`.
- The greedy invariant: at each step pop the closest unfinalized vertex and finalize its distance. Because all weights are non-negative, no path discovered later can undercut it. Insert one negative edge and that guarantee dies, which is why Dijkstra is simply the wrong algorithm when negatives are present.
- The min-heap: `priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>>`, ordered by distance so the smallest sits on top.
- Lazy deletion: `std::priority_queue` can't lower a key that's already inside, so instead of decreasing a key you push a new, smaller `(dist, node)` entry and let the old one rot. When you pop, if the popped distance is larger than the best you've already recorded for that node, skip it. This keeps the code short and the complexity at O((V+E) log V).
- Path reconstruction: keep a `parent[]` array, set `parent[v] = u` whenever you relax `v` through `u`, then walk parents back from the target and reverse.
- Dijkstra on implicit grids: the graph is never built explicitly. Each cell is a vertex and its four neighbors are the edges, with the weight defined by the problem (effort, elevation, time).

### Patterns

- [Weighted Shortest Path & MST](../docs/patterns.md)

### In-class problems

- Network Delay Time
- Path with Minimum Effort
- Cheapest Flights Within K Stops (Dijkstra-with-stops framing)
- Swim in Rising Water

---

## Lecture 50 — Bellman-Ford: Negative Edges, Negative-Cycle Detection, and DP-on-Edges

When weights can go negative, Dijkstra's greedy finalize-the-closest move is no longer safe. Bellman-Ford gives that up and just relaxes every edge, over and over. It's slower than Dijkstra, but it's correct with negatives, and it can tell you when no shortest path exists at all because a negative cycle is dragging costs to minus infinity.

### Objectives

- Relax all edges `V-1` times and explain Bellman-Ford as DP over "shortest path using at most `k` edges."
- Detect a reachable negative cycle with a `V`-th relaxation pass.
- Choose Bellman-Ford over Dijkstra when negative weights are present.

### Topics

- Edge-list representation: just a list of `(u, v, w)` triples. The core operation is relaxation: `if (dist[u] + w < dist[v]) dist[v] = dist[u] + w`.
- The DP framing, and this is the important part: after round `k`, `dist[v]` holds the shortest path from the source to `v` using at most `k` edges. Round 1 settles all one-edge paths, round 2 all two-edge paths, and so on. A simple path in a graph with `V` vertices has at most `V-1` edges, which is exactly why `V-1` rounds suffice.
- Negative-cycle detection: run one more round, the `V`-th. If any edge still relaxes, some distance is still dropping after `V-1` rounds, which can only happen if a reachable negative cycle exists.
- Complexity is O(V*E), since each of the `V-1` rounds touches all `E` edges.
- SPFA, the queue-based optimization that only re-relaxes vertices whose distance actually changed. Faster in practice on many graphs, but its worst case is still O(V*E), so treat it as an optimization, not a guarantee.
- Overflow guards: skip relaxing through a vertex still at `INF` (otherwise `INF + w` overflows and corrupts a real distance), and use `long long` when weights and path lengths can be large.

### Patterns

- [Weighted Shortest Path & MST](../docs/patterns.md)

### In-class problems

- Cheapest Flights Within K Stops (bounded Bellman-Ford)
- Negative Weight Cycle detection
- Network Delay Time (Bellman-Ford version)

---

## Lecture 51 — Floyd-Warshall: All-Pairs Shortest Paths as 3-Loop DP

Sometimes you don't want one source, you want the distance between every pair of vertices. Floyd-Warshall does that in a tight triple loop, and it's one of the cleanest examples of dynamic programming you'll meet all course. Twelve lines, one recurrence, and a loop order you must get right.

### Objectives

- Derive the "`k` as intermediate" recurrence and implement Floyd-Warshall with `k` as the outermost loop.
- Compute transitive closure and detect negative cycles via the diagonal.
- Decide when all-pairs O(V^3) beats running a single-source algorithm `V` times.

### Topics

- The recurrence: `dp[i][j]` is the shortest path from `i` to `j` using only vertices `{0..k}` as intermediates. For each new allowed intermediate `k`, either you don't use it (`dp[i][j]` unchanged) or you route through it (`dp[i][k] + dp[k][j]`), and you take the smaller.
- The loop order is the whole game: `k` must be the outermost loop, with `i` and `j` inside. Put `k` inner and you'll reference intermediate sets that aren't finished yet and get wrong answers with no crash to warn you. This is the classic Floyd-Warshall bug.
- Initialization: `dp[i][i] = 0`, direct edges set to their weights, everything else `INF`. Guard against `INF + INF` overflow before adding, or use a sentinel you can safely add to.
- Negative-cycle detection: after the algorithm runs, if any `dp[i][i] < 0`, vertex `i` sits on a negative cycle.
- Transitive closure: replace `min`/`+` with boolean `OR`/`AND` and the same triple loop tells you reachability between every pair, which is "can `i` reach `j` at all."
- When to use it: `V` is small (roughly `<= 400`, since `V^3` is around 6.4e7 there), and you genuinely need all pairs. If `V` is large or you only need a few sources, run Dijkstra per source instead.

### Patterns

- [Weighted Shortest Path & MST](../docs/patterns.md)

### In-class problems

- Find the City With the Smallest Number of Neighbors at a Threshold Distance
- Course Schedule IV (reachability via transitive closure)
- All-Pairs Shortest Path on a small weighted graph

---

## Lecture 52 — Minimum Spanning Trees: Prim & Kruskal

Different question entirely: connect every vertex with the cheapest possible total edge weight, no cycles allowed. That's a minimum spanning tree, and it is not the same as a shortest-path tree. Both Prim's and Kruskal's are greedy, and both are justified by the same idea, the cut property.

### Objectives

- State the cut property and use it to justify both Prim's and Kruskal's greedy choices.
- Implement Prim's with a min-heap and Kruskal's with union-find, choosing by graph density.
- Distinguish an MST (minimize total weight) from a shortest-path tree (what Dijkstra builds).

### Topics

- MST definition: a subset of edges that connects all `V` vertices with no cycle and the minimum possible total weight. With `V` vertices an MST has exactly `V-1` edges.
- The cut property: for any way of splitting the vertices into two groups, the cheapest edge crossing that split is safe to include in some MST. Both algorithms are just this property applied repeatedly.
- Prim's: grow a tree from a seed vertex. Keep an `inMST[]` array and a min-heap of candidate crossing edges, repeatedly pull the cheapest edge that reaches a vertex not yet in the tree, and add it. O((V+E) log V), and it leans toward dense graphs.
- Kruskal's: sort all edges by weight, then walk them cheapest first, adding an edge only if its two endpoints are in different components. Union-find (with path compression and union by rank) answers "different components?" in near-constant time. O(E log E), dominated by the sort, and it leans toward sparse graphs.
- Dense vs sparse: when `E` is close to `V^2`, Prim's heap-based growth tends to win; when the graph is sparse, Kruskal's sort-and-union is usually simpler and just as fast.
- MST vs shortest-path tree: Dijkstra minimizes distance from one source to everywhere; an MST minimizes the total weight of the connecting edges. The two trees can be completely different on the same graph, and confusing them is a common interview slip.

### Patterns

- [Weighted Shortest Path & MST](../docs/patterns.md)
- [Union-Find](../docs/patterns.md)

### In-class problems

- Min Cost to Connect All Points
- Connecting Cities With Minimum Cost
- Kruskal's MST end-to-end with union-find
- Optimize Water Distribution in a Village

---

## Homework

Work these between lectures, in roughly this order. The warmups confirm the setup is in your hands; the core set is the week's real practice; the challenges are meant to stretch you.

**Warmup**

- Network Delay Time
- Find if Path Exists in Graph

**Core**

- Path with Minimum Effort
- Cheapest Flights Within K Stops
- Min Cost to Connect All Points
- Find the City With the Smallest Number of Neighbors
- Bellman-Ford negative-cycle detection from scratch
- Connecting Cities With Minimum Cost

**Challenge**

- Swim in Rising Water
- Reconstruct Itinerary

---

## Before next week

- You can look at a weighted-graph problem and pick the right algorithm from its signals: non-negative weights and one source go to Dijkstra; possible negatives or a "shortest path with at most K edges" constraint go to Bellman-Ford; all-pairs on a small graph goes to Floyd-Warshall; minimum connection cost goes to Prim or Kruskal.
- You can write Dijkstra with a min-heap and the lazy-deletion idiom, and reconstruct the path with a parent array.
- You can explain Bellman-Ford as DP over the number of edges used, and detect a reachable negative cycle with the extra pass.
- You can write Floyd-Warshall with `k` on the outside and say why the loop order matters.
- You can state the cut property and implement both Prim's and Kruskal's, and you won't confuse an MST with a shortest-path tree.
- The week's homework is done.

You're about to start dynamic programming. Bellman-Ford and Floyd-Warshall were your first real DP recurrences, even if they didn't wear the label, and that framing is exactly the lens Weeks 15 and 16 build on.

---

Back to the [course README](../README.md) · Pattern reference: [docs/patterns.md](../docs/patterns.md)
