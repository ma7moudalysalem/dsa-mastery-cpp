// Backtracking: choose / explore / un-choose (Week 14)
//
// What's built:
//   A small set of classic backtracking exercises. Each function is a TODO
//   stub for students to implement; main() runs assert-based checks and prints
//   "All checks passed" once every method is implemented correctly.
//
//   Functions:
//     - subsets(nums)        : the power set of nums
//     - permutations(nums)   : every ordering of nums
//     - combinations(n, k)   : every k-element subset of {1..n}
//     - count_n_queens(n)    : number of distinct N-Queens placements
//     - word_search(board,w) : whether w traces a 4-directionally adjacent path
//
// Compile / run:
//   g++ -std=c++17 -Wall backtracking.cpp -o out
//   ./out
//
// Implement every method marked TODO until main() prints All checks passed.
//
// General backtracking template
// -----------------------------
// Backtracking explores a decision tree. At each step you extend a partial
// solution by one choice, recurse, then undo that choice so the next branch
// starts from a clean state.
//
//   void backtrack(State& state, Result& out) {
//       if (is_complete(state)) {        // reached a full candidate
//           out.record(state);
//           return;
//       }
//       for (candidate : candidates(state)) {
//           if (!is_valid(state, candidate)) continue;  // pruning
//           state.choose(candidate);     // choose
//           backtrack(state, out);       // explore
//           state.unchoose(candidate);   // un-choose (restore state)
//       }
//   }
//
// The "un-choose" step is what makes a single mutable buffer reusable across
// every branch. Pruning (skipping invalid candidates early) is what keeps the
// search from visiting branches that cannot lead to a valid solution.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// subsets
// Purpose: build the power set of nums (every subset, including the empty set
//          and the full set).
// Params : nums - input values (assume distinct for a clean power set).
// Return : all subsets; for n inputs there are 2^n of them.
// Target complexity: O(n * 2^n) total work to emit 2^n subsets.
// Decision/branching: at each index decide include-or-exclude that element,
//          then recurse on the next index. Un-choose by popping the element
//          you pushed before exploring the "exclude" branch. No pruning is
//          needed since every leaf is a valid subset.
std::vector<std::vector<int>> subsets(const std::vector<int>& nums) {
    throw std::logic_error("TODO: implement subsets");
}

// permutations
// Purpose: build every ordering of the elements of nums.
// Params : nums - input values (assume distinct for n! distinct orderings).
// Return : all permutations; for n inputs there are n! of them.
// Target complexity: O(n * n!) total work to emit n! permutations.
// Decision/branching: at each position pick one not-yet-used element, recurse
//          on the next position, then un-choose by marking it unused again.
//          Track used elements with a boolean array (or swap into place).
std::vector<std::vector<int>> permutations(const std::vector<int>& nums) {
    throw std::logic_error("TODO: implement permutations");
}

// combinations
// Purpose: build every k-element subset of {1, 2, ..., n}.
// Params : n - upper bound of the value range (values 1..n).
//          k - size of each combination (0 <= k <= n).
// Return : all k-subsets; there are C(n, k) of them, each in increasing order.
// Target complexity: O(k * C(n, k)) total work to emit C(n, k) combinations.
// Decision/branching: walk candidate values in increasing order, choose the
//          next value, recurse from the value after it (so combinations stay
//          ordered and unique), then un-choose. Pruning hint: stop early when
//          not enough values remain to reach size k.
std::vector<std::vector<int>> combinations(int n, int k) {
    throw std::logic_error("TODO: implement combinations");
}

// count_n_queens
// Purpose: count distinct ways to place n queens on an n x n board so that no
//          two share a row, column, or diagonal.
// Params : n - board size and number of queens.
// Return : the number of valid distinct placements.
// Target complexity: exponential in n; place one queen per row.
// Decision/branching: process rows top to bottom. For each row try every
//          column, keeping sets of used columns and used diagonals. Pruning
//          hint: a column is valid only if its column, its "/" diagonal
//          (row + col), and its "\" diagonal (row - col) are all unused;
//          choose, recurse to the next row, then un-choose those markers.
int count_n_queens(int n) {
    throw std::logic_error("TODO: implement count_n_queens");
}

// word_search
// Purpose: decide whether word can be spelled by a path through the grid that
//          moves only between 4-directionally adjacent cells and never reuses
//          a cell.
// Params : board - rectangular grid of characters.
//          word  - target string to trace through the grid.
// Return : true if such a path exists, false otherwise.
// Target complexity: O(rows * cols * 4^len(word)) in the worst case.
// Decision/branching: try each cell as a starting point. From a matching cell,
//          mark it visited, recurse into the four neighbors for the next
//          character, then un-mark it so other paths may reuse it. Pruning
//          hint: stop a branch as soon as the current cell does not match the
//          expected character or falls outside the grid.
bool word_search(const std::vector<std::vector<char>>& board, const std::string& word) {
    throw std::logic_error("TODO: implement word_search");
}

int main() {
    try {
        // subsets: power set of 3 elements has 2^3 = 8 members.
        assert(subsets({1, 2, 3}).size() == 8);
        // The empty input still yields one subset: the empty set.
        assert(subsets({}).size() == 1);

        // permutations: 3 distinct elements yield 3! = 6 orderings.
        assert(permutations({1, 2, 3}).size() == 6);

        // combinations: choosing 2 from {1,2,3,4} yields C(4,2) = 6.
        assert(combinations(4, 2).size() == 6);

        // N-Queens distinct solution counts for a few board sizes.
        assert(count_n_queens(1) == 1);
        assert(count_n_queens(4) == 2);
        assert(count_n_queens(8) == 92);

        // word_search over a fixed 3 x 4 board.
        std::vector<std::vector<char>> board = {
            {'A', 'B', 'C', 'E'},
            {'S', 'F', 'C', 'S'},
            {'A', 'D', 'E', 'E'}};
        assert(word_search(board, "ABCCED") == true);
        assert(word_search(board, "SEE") == true);
        assert(word_search(board, "ABCB") == false);

        std::cout << "All checks passed\n";
    } catch (const std::exception& e) {
        std::cerr << "FAILED (likely unimplemented): " << e.what() << "\n";
        return 1;
    }
    return 0;
}
