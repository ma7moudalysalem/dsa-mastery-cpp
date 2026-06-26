// Weighted Graph Algorithms (Weeks 12-13)
//
// Builds four classic graph routines over directed and undirected graphs:
//   - topological_sort : Kahn's algorithm on a directed graph (cycle detection)
//   - dijkstra         : single-source shortest paths with non-negative weights
//   - bellman_ford     : single-source shortest paths allowing negative weights,
//                        with negative-cycle detection
//   - mst_kruskal      : minimum spanning tree total weight via union-find
//
// Compile and run:
//   g++ -std=c++17 -Wall graph_algorithms.cpp -o out
//   ./out
//
// Implement every method marked TODO until main() prints All checks passed.

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

// Edge with endpoints u, v and integer weight w.
// Used by bellman_ford (directed edges) and mst_kruskal (undirected edges).
struct Edge {
    int u, v, w;
};

// topological_sort
// Purpose: produce a linear ordering of the vertices of a directed graph such
//          that for every directed edge u -> v, u appears before v.
// Params:
//   n   : number of vertices, labeled 0 .. n-1.
//   adj : adjacency list; adj[u] holds the destinations of edges leaving u.
// Representation: directed graph as an adjacency list.
// Return value: a vector of size n giving one valid topological order. If the
//   graph contains a directed cycle (no valid ordering exists), return an empty
//   vector.
// Target complexity: O(n + m), where m is the number of edges.
// Edge cases: n == 0 yields an empty order (valid); graphs with isolated
//   vertices include those vertices in the output; ties broken by Kahn's queue.
std::vector<int> topological_sort(int n, const std::vector<std::vector<int>>& adj) {
    throw std::logic_error("TODO: implement topological_sort");
}

// dijkstra
// Purpose: compute the shortest-path distance from a source vertex to every
//          other vertex in a graph with non-negative edge weights.
// Params:
//   n   : number of vertices, labeled 0 .. n-1.
//   adj : adjacency list; adj[u] holds pairs (neighbor, weight) with weight >= 0.
//   src : source vertex, 0 <= src < n.
// Representation: directed or undirected graph as a weighted adjacency list.
// Return value: a vector of size n where entry i is the minimum total weight of
//   a path from src to i, or INT_MAX if i is unreachable from src.
// Target complexity: O((n + m) log n) using a binary-heap priority queue.
// Edge cases: distance to src itself is 0; unreachable vertices keep INT_MAX;
//   duplicate heap entries for a vertex are skipped once it is finalized.
std::vector<int> dijkstra(int n, const std::vector<std::vector<std::pair<int,int>>>& adj, int src) {
    throw std::logic_error("TODO: implement dijkstra");
}

// bellman_ford
// Purpose: compute single-source shortest-path distances on a directed graph
//          that may contain negative edge weights, and report whether a negative
//          cycle is reachable from the source.
// Params:
//   n                  : number of vertices, labeled 0 .. n-1.
//   edges              : directed edge list; each Edge is u -> v with weight w.
//   src                : source vertex, 0 <= src < n.
//   has_negative_cycle : output flag set to true when some vertex's distance can
//                        still be reduced after n-1 relaxation passes (a negative
//                        cycle reachable from src exists), false otherwise.
// Representation: directed graph as an edge list (negative weights allowed).
// Return value: a vector<long long> of size n where entry i is the shortest
//   distance from src to i, or LLONG_MAX if i is unreachable. Distances are only
//   meaningful when has_negative_cycle is false.
// Target complexity: O(n * m).
// Edge cases: distance to src is 0; unreachable vertices keep LLONG_MAX and are
//   never relaxed; long long avoids overflow when summing negative weights.
std::vector<long long> bellman_ford(int n, const std::vector<Edge>& edges, int src, bool& has_negative_cycle) {
    throw std::logic_error("TODO: implement bellman_ford");
}

// mst_kruskal
// Purpose: compute the total weight of a minimum spanning tree of a connected,
//          undirected, weighted graph using Kruskal's algorithm.
// Params:
//   n     : number of vertices, labeled 0 .. n-1.
//   edges : undirected edge list; each Edge connects u and v with weight w.
//           (Taken by value so the routine may sort it in place.)
// Representation: connected undirected graph as an edge list with an inline
//   union-find (disjoint-set) structure to detect cycles.
// Return value: the sum of edge weights of a minimum spanning tree.
// Target complexity: O(m log m) dominated by sorting the edges.
// Edge cases: n <= 1 yields total weight 0; parallel edges and self-loops are
//   handled because union-find rejects any edge whose endpoints already share a
//   set.
long long mst_kruskal(int n, std::vector<Edge> edges) {
    throw std::logic_error("TODO: implement mst_kruskal");
}

// ---------------------------------------------------------------------------
// Test helper: confirm that a candidate ordering is a valid topological order
// for the given directed edges. Returns true when every edge u -> v has u
// positioned strictly before v in the order, and the order lists all n vertices.
static bool topo_order_respects_edges(int n,
                                      const std::vector<int>& order,
                                      const std::vector<std::pair<int,int>>& edges) {
    if (static_cast<int>(order.size()) != n) return false;
    std::vector<int> position(n, -1);
    for (int i = 0; i < n; ++i) {
        int v = order[i];
        if (v < 0 || v >= n) return false;   // value out of range
        if (position[v] != -1) return false; // duplicate vertex
        position[v] = i;
    }
    for (const auto& e : edges) {
        if (position[e.first] >= position[e.second]) return false;
    }
    return true;
}

int main() {
    try {
        // --- topological_sort ----------------------------------------------
        {
            // DAG with 6 vertices and the listed directed edges.
            std::vector<std::pair<int,int>> edges = {
                {5, 2}, {5, 0}, {4, 0}, {4, 1}, {2, 3}, {3, 1}
            };
            int n = 6;
            std::vector<std::vector<int>> adj(n);
            for (const auto& e : edges) adj[e.first].push_back(e.second);

            std::vector<int> order = topological_sort(n, adj);
            assert(static_cast<int>(order.size()) == 6);
            assert(topo_order_respects_edges(n, order, edges));

            // Directed graph containing a cycle: 0 -> 1 -> 2 -> 0.
            std::vector<std::vector<int>> cyclic(3);
            cyclic[0].push_back(1);
            cyclic[1].push_back(2);
            cyclic[2].push_back(0);
            std::vector<int> cyclic_order = topological_sort(3, cyclic);
            assert(cyclic_order.empty());
        }

        // --- dijkstra ------------------------------------------------------
        {
            // 5 vertices. Vertex 4 is isolated (unreachable from src 0).
            // Edges (directed): 0->1 (10), 0->2 (3), 2->1 (1), 2->3 (8),
            //                   1->3 (2).
            // Shortest distances from 0:
            //   d[0] = 0
            //   d[2] = 3
            //   d[1] = 4   (0->2->1 = 3+1)
            //   d[3] = 6   (0->2->1->3 = 3+1+2)
            //   d[4] = INT_MAX (unreachable)
            int n = 5;
            std::vector<std::vector<std::pair<int,int>>> adj(n);
            adj[0].push_back({1, 10});
            adj[0].push_back({2, 3});
            adj[2].push_back({1, 1});
            adj[2].push_back({3, 8});
            adj[1].push_back({3, 2});

            std::vector<int> dist = dijkstra(n, adj, 0);
            assert(static_cast<int>(dist.size()) == 5);
            assert(dist[0] == 0);
            assert(dist[1] == 4);
            assert(dist[2] == 3);
            assert(dist[3] == 6);
            assert(dist[4] == INT_MAX);
        }

        // --- bellman_ford --------------------------------------------------
        {
            // 5 vertices, directed edges with one negative (non-cycle) weight.
            // Edges: 0->1 (6), 0->2 (7), 1->2 (8), 1->3 (5), 1->4 (-4),
            //        2->3 (-3), 2->4 (9), 3->1 (-2), 4->3 (7), 4->0 (2).
            // Shortest distances from 0 (no negative cycle):
            //   d[0] = 0
            //   d[1] = 2    (0->2->3->1 = 7 + -3 + -2)
            //   d[2] = 7    (0->2)
            //   d[3] = 4    (0->2->3 = 7 + -3)
            //   d[4] = -2   (0->2->3->1->4 = 7 + -3 + -2 + -4)
            int n = 5;
            std::vector<Edge> edges = {
                {0, 1, 6}, {0, 2, 7}, {1, 2, 8}, {1, 3, 5}, {1, 4, -4},
                {2, 3, -3}, {2, 4, 9}, {3, 1, -2}, {4, 3, 7}, {4, 0, 2}
            };
            bool neg = true;
            std::vector<long long> dist = bellman_ford(n, edges, 0, neg);
            assert(neg == false);
            assert(static_cast<int>(dist.size()) == 5);
            assert(dist[0] == 0);
            assert(dist[1] == 2);
            assert(dist[2] == 7);
            assert(dist[3] == 4);
            assert(dist[4] == -2);

            // Graph with a negative cycle reachable from src 0:
            //   0 -> 1 (1), 1 -> 2 (-1), 2 -> 1 (-1).
            // The cycle 1 -> 2 -> 1 has total weight -2.
            std::vector<Edge> cyc = { {0, 1, 1}, {1, 2, -1}, {2, 1, -1} };
            bool neg2 = false;
            std::vector<long long> dist2 = bellman_ford(3, cyc, 0, neg2);
            (void)dist2;
            assert(neg2 == true);
        }

        // --- mst_kruskal ---------------------------------------------------
        {
            // 5 vertices, undirected weighted graph.
            // Edges: (0,1,2), (0,3,6), (1,2,3), (1,3,8), (1,4,5),
            //        (2,4,7), (3,4,9).
            // A minimum spanning tree uses edges
            //   (0,1,2), (1,2,3), (1,4,5), (0,3,6) -> total 2+3+5+6 = 16.
            int n = 5;
            std::vector<Edge> edges = {
                {0, 1, 2}, {0, 3, 6}, {1, 2, 3}, {1, 3, 8},
                {1, 4, 5}, {2, 4, 7}, {3, 4, 9}
            };
            long long total = mst_kruskal(n, edges);
            assert(total == 16);
        }

        std::cout << "All checks passed" << std::endl;
        return 0;
    } catch (const std::exception& ex) {
        std::cout << "FAILED: " << ex.what() << std::endl;
        return 1;
    }
}
