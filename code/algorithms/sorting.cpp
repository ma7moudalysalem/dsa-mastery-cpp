// Sorting Algorithms
//
// The student builds four in-place ascending sorts over std::vector<int>:
// insertion sort, merge sort, quick sort, and heap sort. A given is_sorted
// helper and an assert-based driver check each one against std::sort.
//
// Compile/run:
//   g++ -std=c++17 -Wall sorting.cpp -o out
//   ./out
//
// Implement every method marked TODO until main() prints all checks passed.

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>  // std::sort, std::is_permutation (driver only)

// -----------------------------------------------------------------------------
// Given helper: returns true if v is in non-decreasing order. O(n).
// -----------------------------------------------------------------------------
bool is_sorted(const std::vector<int>& v) {
    for (std::size_t i = 1; i < v.size(); ++i) {
        if (v[i] < v[i - 1]) return false;
    }
    return true;
}

// -----------------------------------------------------------------------------
// Sort functions the STUDENT implements. All sort v ascending, in place.
// -----------------------------------------------------------------------------

// insertion_sort: sort v ascending in place.
// Param: v - the array to sort (modified in place).
// Time: O(n^2) worst/average, O(n) on already-sorted input. Stable.
// Edge cases: empty vector and single element are already sorted (no-op).
void insertion_sort(std::vector<int>& v) {
    throw std::logic_error("TODO: implement insertion_sort");
}

// merge_sort: sort v ascending in place (allocate scratch buffers as needed).
// Param: v - the array to sort (modified in place).
// Time: O(n log n) in all cases. Stable. Uses O(n) extra space for merging.
// Edge cases: empty vector and single element are already sorted (no-op).
void merge_sort(std::vector<int>& v) {
    throw std::logic_error("TODO: implement merge_sort");
}

// quick_sort: sort v ascending in place.
// Param: v - the array to sort (modified in place).
// Time: O(n log n) average, O(n^2) worst case. Not stable.
// Note: pick any correct pivot strategy; recursion or an explicit stack are
//       both fine. Partitioning must move all elements < pivot before it and
//       all elements > pivot after it.
// Edge cases: empty vector, single element, all-equal elements must terminate.
void quick_sort(std::vector<int>& v) {
    throw std::logic_error("TODO: implement quick_sort");
}

// heap_sort: sort v ascending in place using a binary max-heap.
// Param: v - the array to sort (modified in place).
// Time: O(n log n) in all cases. Not stable. O(1) extra space.
// Approach: build a max-heap over v, then repeatedly swap the root to the end
//           and sift down the reduced heap.
// Edge cases: empty vector and single element are already sorted (no-op).
void heap_sort(std::vector<int>& v) {
    throw std::logic_error("TODO: implement heap_sort");
}

// -----------------------------------------------------------------------------
// Test driver (given). For each sort function and each input case, checks:
//   1. the result is sorted ascending (is_sorted), and
//   2. the result is a permutation of std::sort applied to a copy
//      (same multiset of elements, i.e. nothing lost, added, or corrupted).
// -----------------------------------------------------------------------------
static void check_sort(void (*sort_fn)(std::vector<int>&), const char* name) {
    const std::vector<std::vector<int>> cases = {
        {},                                  // empty
        {42},                                // single element
        {1, 2, 3, 4, 5},                     // already sorted
        {5, 4, 3, 2, 1},                     // reverse sorted
        {3, 1, 2, 3, 1, 2, 3},               // with duplicates
        {7, 7, 7, 7},                        // all equal
        {9, -3, 0, 14, -3, 8, 2, 11, -50, 6} // mixed including negatives
    };

    for (const auto& input : cases) {
        std::vector<int> expected = input;
        std::sort(expected.begin(), expected.end());

        std::vector<int> actual = input;
        sort_fn(actual);

        assert(is_sorted(actual));
        assert(actual.size() == expected.size());
        // Permutation of the std::sort result: same elements, same multiplicity.
        assert(std::is_permutation(actual.begin(), actual.end(),
                                   expected.begin()));
        // Once sorted and a permutation, it must equal the reference order.
        assert(actual == expected);
    }

    std::cout << name << " passed\n";
}

int main() {
    try {
        check_sort(insertion_sort, "insertion_sort");
        check_sort(merge_sort, "merge_sort");
        check_sort(quick_sort, "quick_sort");
        check_sort(heap_sort, "heap_sort");

        std::cout << "All checks passed\n";
    } catch (const std::exception& e) {
        std::cerr << "FAILED (likely unimplemented): " << e.what() << "\n";
        return 1;
    }
    return 0;
}
