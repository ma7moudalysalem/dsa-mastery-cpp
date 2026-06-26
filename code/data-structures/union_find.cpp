// Union-Find (Disjoint Set Union)
//
// You build a disjoint-set structure over the integers 0..n-1: find the
// representative of an element's set (with path compression) and merge two
// sets (union by rank), tracking the number of distinct components.
//
// Compile & run:
//   g++ -std=c++17 -Wall union_find.cpp -o union_find && ./union_find
//
// Implement every method marked TODO until main() prints all checks passed.

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class UnionFind {
public:
    // Construct n singleton sets: parent_[i] = i, rank_[i] = 0, n components.
    // Requires n >= 0.
    explicit UnionFind(int n)
        : parent_(static_cast<std::size_t>(n)),
          rank_(static_cast<std::size_t>(n), 0),
          components_(n) {
        for (int i = 0; i < n; ++i) {
            parent_[static_cast<std::size_t>(i)] = i;
        }
    }

    ~UnionFind() = default;  // vectors free themselves; nothing to do.

    // Return the representative (root) of the set containing x, applying path
    // compression so visited nodes point directly at the root afterward.
    // Parameter: x in [0, size()). Amortized near-constant time (inverse
    // Ackermann) once combined with union by rank.
    // Edge cases: out-of-range x is caller error (asserts/UB are acceptable);
    // a root element (parent_[x] == x) returns itself.
    int find(int x) {
        throw std::logic_error("TODO: implement UnionFind::find");
    }

    // Merge the sets containing a and b using union by rank: attach the
    // shorter tree under the taller; on equal rank pick one root and increment
    // its rank. Decrement the component count on a successful merge.
    // Parameters: a, b in [0, size()).
    // Returns: true if a and b were in different sets (a merge happened),
    //          false if they were already in the same set (no change).
    // Target: amortized near-constant time. Edge case: unite(x, x) returns false.
    bool unite(int a, int b) {
        throw std::logic_error("TODO: implement UnionFind::unite");
    }

    // Return true if a and b are in the same set. Given: defers to find().
    // Parameters: a, b in [0, size()).
    bool connected(int a, int b) {
        return find(a) == find(b);
    }

    // Return the current number of disjoint components. Given: O(1).
    int count() const {
        return components_;
    }

    // Number of elements the structure was built over. Given: O(1).
    int size() const {
        return static_cast<int>(parent_.size());
    }

    // Render the raw parent array, e.g. "[0, 0, 2, 2, 4, 4]". Reads backing
    // storage only; does not run find() so it does not compress paths.
    std::string debug_to_string() const {
        std::string out = "[";
        for (std::size_t i = 0; i < parent_.size(); ++i) {
            if (i) out += ", ";
            out += std::to_string(parent_[i]);
        }
        out += "]";
        return out;
    }

private:
    std::vector<int> parent_;  // parent_[i] = parent of i; root if equal to i.
    std::vector<int> rank_;    // upper bound on tree height per root.
    int components_;           // number of disjoint sets.
};

int main() {
    try {
        UnionFind uf(6);

        // Start: six singletons, all separate.
        assert(uf.size() == 6);
        assert(uf.count() == 6);
        for (int i = 0; i < 6; ++i) {
            assert(uf.find(i) == i);
            assert(uf.connected(i, i));
        }
        assert(!uf.connected(0, 1));

        // Merge 0-1 and 2-3.
        assert(uf.unite(0, 1) == true);
        assert(uf.count() == 5);
        assert(uf.connected(0, 1));
        assert(!uf.connected(0, 2));

        assert(uf.unite(2, 3) == true);
        assert(uf.count() == 4);
        assert(uf.connected(2, 3));
        assert(!uf.connected(1, 2));

        // Bridge the two pairs: {0,1} + {2,3} -> {0,1,2,3}.
        assert(uf.unite(1, 2) == true);
        assert(uf.count() == 3);
        assert(uf.connected(0, 3));
        assert(uf.connected(1, 3));

        // Uniting within the same set returns false and changes nothing.
        assert(uf.unite(0, 3) == false);
        assert(uf.count() == 3);
        assert(uf.unite(3, 0) == false);
        assert(uf.count() == 3);
        assert(uf.unite(4, 4) == false);
        assert(uf.count() == 3);

        // Remaining singletons 4 and 5 stay separate from the big set.
        assert(!uf.connected(0, 4));
        assert(!uf.connected(4, 5));

        // Merge the last two; final layout is {0,1,2,3} and {4,5}.
        assert(uf.unite(4, 5) == true);
        assert(uf.count() == 2);
        assert(uf.connected(4, 5));
        assert(!uf.connected(3, 5));

        // find() is a function on elements: same set -> same representative.
        assert(uf.find(0) == uf.find(1));
        assert(uf.find(0) == uf.find(2));
        assert(uf.find(0) == uf.find(3));
        assert(uf.find(4) == uf.find(5));
        assert(uf.find(0) != uf.find(4));

        std::cout << "All checks passed\n";
    } catch (const std::exception& e) {
        std::cerr << "FAILED (likely unimplemented): " << e.what() << "\n";
        return 1;
    }
    return 0;
}
