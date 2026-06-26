// Binary Search & the Predicate Framework
//
// You build the four classic binary-search routines over a sorted std::vector<int>
// (lower bound, upper bound, membership test) plus the generic predicate-search
// function first_true that locates the boundary of a monotonic predicate.
//
// Compile: g++ -std=c++17 -Wall binary_search.cpp -o out
// Run:     ./out
//
// Implement every method marked TODO until main() prints all checks passed.

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <functional>

// Returns the first index i in [0, v.size()] such that v[i] >= target.
// v must be sorted in non-decreasing order. If every element is < target,
// returns v.size() (a valid past-the-end insertion point).
// Target time complexity: O(log n).
// Edge cases: empty vector returns 0; target <= v.front() returns 0;
// target > v.back() returns v.size().
int lower_bound_index(const std::vector<int>& v, int target) {
    throw std::logic_error("TODO: implement lower_bound_index");
}

// Returns the first index i in [0, v.size()] such that v[i] > target.
// v must be sorted in non-decreasing order. If every element is <= target,
// returns v.size().
// Target time complexity: O(log n).
// Edge cases: empty vector returns 0; target < v.front() returns 0;
// target >= v.back() returns v.size(); difference from lower_bound is the
// strict vs non-strict comparison, which determines placement among duplicates.
int upper_bound_index(const std::vector<int>& v, int target) {
    throw std::logic_error("TODO: implement upper_bound_index");
}

// Returns true if target appears at least once in v, false otherwise.
// v must be sorted in non-decreasing order.
// Target time complexity: O(log n).
// Edge cases: empty vector returns false. Hint: can be derived from
// lower_bound_index by checking the index is in range and the value matches.
bool binary_search_exists(const std::vector<int>& v, int target) {
    throw std::logic_error("TODO: implement binary_search_exists");
}

// Returns the smallest x in [lo, hi] for which pred(x) is true, assuming pred
// is monotonic over the range: once it becomes true it stays true (F...FT...T).
// If pred(x) is false for every x in [lo, hi], returns hi + 1.
// Parameters: lo and hi are an inclusive search range with lo <= hi + 1;
// pred is the monotonic predicate to probe.
// Target time complexity: O(log(hi - lo + 1)) predicate evaluations.
// Edge cases: pred(lo) already true returns lo; pred never true returns hi + 1.
// Use a half-open invariant (answer lies in [lo, hi + 1]) to avoid overflow
// when computing the midpoint.
int first_true(int lo, int hi, const std::function<bool(int)>& pred) {
    throw std::logic_error("TODO: implement first_true");
}

// Renders the vector as "[a, b, c]" for visualization. Reads the array only.
std::string debug_to_string(const std::vector<int>& v) {
    std::string out = "[";
    for (std::size_t i = 0; i < v.size(); ++i) {
        out += std::to_string(v[i]);
        if (i + 1 < v.size()) out += ", ";
    }
    out += "]";
    return out;
}

int main() {
    try {
        // Sorted array with duplicates. Indices:
        //   0  1  2  3  4  5  6  7
        //   1  2  2  2  5  7  7  9
        std::vector<int> v = {1, 2, 2, 2, 5, 7, 7, 9};

        // lower_bound_index: first index with value >= target.
        assert(lower_bound_index(v, 0) == 0);   // before all
        assert(lower_bound_index(v, 1) == 0);   // equals front
        assert(lower_bound_index(v, 2) == 1);   // first of the duplicate run
        assert(lower_bound_index(v, 3) == 4);   // gap, lands on 5
        assert(lower_bound_index(v, 7) == 5);   // first 7
        assert(lower_bound_index(v, 9) == 7);   // equals back
        assert(lower_bound_index(v, 10) == 8);  // past the end == size

        // upper_bound_index: first index with value > target.
        assert(upper_bound_index(v, 0) == 0);   // before all
        assert(upper_bound_index(v, 1) == 1);   // just past the single 1
        assert(upper_bound_index(v, 2) == 4);   // just past the run of 2s
        assert(upper_bound_index(v, 3) == 4);   // gap, same as lower bound here
        assert(upper_bound_index(v, 7) == 7);   // just past the run of 7s
        assert(upper_bound_index(v, 9) == 8);   // past the end == size
        assert(upper_bound_index(v, 10) == 8);  // size

        // Count of a value == upper_bound - lower_bound.
        assert(upper_bound_index(v, 2) - lower_bound_index(v, 2) == 3);
        assert(upper_bound_index(v, 7) - lower_bound_index(v, 7) == 2);
        assert(upper_bound_index(v, 4) - lower_bound_index(v, 4) == 0); // absent

        // binary_search_exists: membership.
        assert(binary_search_exists(v, 1) == true);
        assert(binary_search_exists(v, 2) == true);
        assert(binary_search_exists(v, 5) == true);
        assert(binary_search_exists(v, 9) == true);
        assert(binary_search_exists(v, 0) == false);
        assert(binary_search_exists(v, 3) == false);
        assert(binary_search_exists(v, 10) == false);

        // Empty array behavior.
        std::vector<int> empty;
        assert(lower_bound_index(empty, 5) == 0);
        assert(upper_bound_index(empty, 5) == 0);
        assert(binary_search_exists(empty, 5) == false);

        // first_true over a monotonic predicate: smallest x with x*x >= 50.
        // 7*7 = 49 (false), 8*8 = 64 (true), so the boundary is 8.
        auto sq_ge_50 = [](int x) { return x * x >= 50; };
        assert(first_true(0, 100, sq_ge_50) == 8);

        // Boundary already satisfied at lo.
        auto always_true = [](int) { return true; };
        assert(first_true(3, 10, always_true) == 3);

        // Predicate never satisfied: returns hi + 1.
        auto always_false = [](int) { return false; };
        assert(first_true(3, 10, always_false) == 11);

        // Single-element range.
        // 5*5 = 25 < 50, so pred is false on the whole range [5,5] -> returns 6.
        assert(first_true(5, 5, sq_ge_50) == 6);

        std::cout << "All checks passed\n";
    } catch (const std::exception& e) {
        std::cerr << "FAILED (likely unimplemented): " << e.what() << "\n";
        return 1;
    }
    return 0;
}
