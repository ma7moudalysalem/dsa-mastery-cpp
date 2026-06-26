// Graph (adjacency list) with BFS & DFS
//
// The student builds an undirected graph stored as an adjacency list and
// implements breadth-first search, depth-first search, and a connected-
// components count.
//
// Compile & run:
//   g++ -std=c++17 -Wall graph.cpp -o out && ./out
//
// Implement every method marked TODO until main() prints all checks passed.

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>

class Graph {
public:
    // Build a graph with n vertices labeled 0..n-1 and no edges.
    // Leaves the object in a valid empty (edge-free) state.
    explicit Graph(int n) : n_(n), adj_(n) {
        assert(n >= 0);
    }

    ~Graph() = default;  // adj_ owns no raw memory; vector cleans itself up.

    // Add an undirected edge between u and v (push both directions).
    // Given. O(1) amortized.
    void add_edge(int u, int v) {
        assert(u >= 0 && u < n_);
        assert(v >= 0 && v < n_);
        adj_[u].push_back(v);
        adj_[v].push_back(u);
    }

    // Number of vertices.
    int size() const { return n_; }

    // Breadth-first search from `start`.
    // Returns the vertices in the order they are first visited, beginning
    // with `start`. Only vertices reachable from `start` appear.
    // Use a queue and a visited array.
    // Parameters: start in [0, n_).
    // Target time complexity: O(V + E).
    // Edge cases: isolated start returns {start}; each vertex appears once.
    std::vector<int> bfs(int start) {
        throw std::logic_error("TODO: implement Graph::bfs");
    }

    // Depth-first search from `start` (recursive or explicit stack).
    // Returns the vertices in visit order, beginning with `start`. Only
    // vertices reachable from `start` appear, each exactly once.
    // Parameters: start in [0, n_).
    // Target time complexity: O(V + E).
    // Edge cases: isolated start returns {start}.
    std::vector<int> dfs(int start) {
        throw std::logic_error("TODO: implement Graph::dfs");
    }

    // Count the connected components of the (undirected) graph.
    // Run a traversal from every not-yet-visited vertex; each launch is a
    // new component.
    // Return value: number of connected components (0 when n_ == 0).
    // Target time complexity: O(V + E).
    // Edge cases: empty graph -> 0; n_ isolated vertices -> n_ components.
    int connected_components() {
        throw std::logic_error("TODO: implement Graph::connected_components");
    }

    // Read-only view of a vertex's neighbor list (for visualization).
    std::string debug_to_string() const {
        std::string s;
        for (int u = 0; u < n_; ++u) {
            s += std::to_string(u) + ":";
            for (int v : adj_[u]) s += " " + std::to_string(v);
            s += "\n";
        }
        return s;
    }

private:
    int n_;                              // number of vertices
    std::vector<std::vector<int>> adj_;  // adj_[u] = neighbors of u
};

// Returns a sorted copy so visited SETs can be compared regardless of the
// traversal order an implementation happens to produce.
static std::vector<int> sorted_copy(std::vector<int> v) {
    std::sort(v.begin(), v.end());
    return v;
}

int main() {
    try {
        // Two components:
        //   Component A: 0 - 1 - 2, with 0 - 2 closing a triangle.
        //   Component B: 3 - 4.
        //   Vertex 5 is isolated -> its own component.
        Graph g(6);
        g.add_edge(0, 1);
        g.add_edge(1, 2);
        g.add_edge(0, 2);
        g.add_edge(3, 4);

        // BFS / DFS from vertex 0 visit exactly component A = {0, 1, 2}.
        const std::vector<int> compA = {0, 1, 2};

        std::vector<int> b0 = g.bfs(0);
        assert(b0.size() == 3);
        assert(b0.front() == 0);                 // traversal starts at `start`
        assert(sorted_copy(b0) == compA);        // visits exactly {0,1,2}

        std::vector<int> d0 = g.dfs(0);
        assert(d0.size() == 3);
        assert(d0.front() == 0);
        assert(sorted_copy(d0) == compA);

        // From an isolated vertex, traversal returns only that vertex.
        std::vector<int> b5 = g.bfs(5);
        assert((b5 == std::vector<int>{5}));
        std::vector<int> d5 = g.dfs(5);
        assert((d5 == std::vector<int>{5}));

        // Component B reachable set from vertex 3 is {3, 4}.
        std::vector<int> b3 = g.bfs(3);
        assert(sorted_copy(b3) == (std::vector<int>{3, 4}));

        // Three components total: {0,1,2}, {3,4}, {5}.
        assert(g.connected_components() == 3);

        // A graph with no edges has one component per vertex.
        Graph empty_edges(4);
        assert(empty_edges.connected_components() == 4);

        // A graph with zero vertices has zero components.
        Graph none(0);
        assert(none.connected_components() == 0);

        std::cout << "All checks passed\n";
    } catch (const std::exception& e) {
        std::cerr << "FAILED (likely unimplemented): " << e.what() << "\n";
        return 1;
    }
    return 0;
}
