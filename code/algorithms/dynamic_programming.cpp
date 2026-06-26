// Dynamic Programming (Week 15)
//
// What's built:
//   A set of classic dynamic programming exercises left as TODO stubs:
//   Fibonacci (memoized and tabulated), climbing stairs, minimum-coin change,
//   0/1 knapsack, longest increasing subsequence, longest common subsequence,
//   and edit distance. Each function carries a contract describing its state
//   definition and recurrence; implement every body marked TODO until main()
//   prints "All checks passed."
//
// Compile / run:
//   g++ -std=c++17 -Wall dynamic_programming.cpp -o out
//   ./out
//
// Top-down memoization vs bottom-up tabulation:
//   Top-down memoization starts from the original problem and recurses into
//   subproblems on demand, caching each result the first time it is computed so
//   repeated calls are answered in O(1). Only the subproblems actually reached
//   are evaluated, at the cost of recursion-stack depth. Bottom-up tabulation
//   instead fills a table in an order where every dependency is computed before
//   the entry that needs it, replacing recursion with iteration; it visits the
//   whole state space but uses no call stack and often allows space reduction by
//   keeping only the most recent rows/columns.

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <algorithm>

// Purpose: compute the n-th Fibonacci number using top-down memoization.
// Params:  n - index in the sequence, n >= 0.
// Return:  F(n) where F(0)=0, F(1)=1, F(n)=F(n-1)+F(n-2).
// State:   memo[k] caches F(k); recursion descends from n and stores each
//          result the first time it is produced.
// Complexity: O(n) time, O(n) space (cache plus recursion depth).
// Edge cases: n==0 returns 0; n==1 returns 1; reject n<0.
long long fib_memo(int n) {
    throw std::logic_error("TODO: implement fib_memo");
}

// Purpose: compute the n-th Fibonacci number using bottom-up tabulation.
// Params:  n - index in the sequence, n >= 0.
// Return:  F(n) where F(0)=0, F(1)=1, F(n)=F(n-1)+F(n-2).
// State:   iterate k from 2 to n, combining the two previous values; only the
//          last two need to be retained.
// Complexity: O(n) time, O(1) space when keeping just two running values.
// Edge cases: n==0 returns 0; n==1 returns 1; reject n<0.
long long fib_tab(int n) {
    throw std::logic_error("TODO: implement fib_tab");
}

// Purpose: count the distinct ways to climb n stairs taking 1 or 2 steps.
// Params:  n - number of stairs, n >= 0.
// Return:  number of step sequences that sum to n.
// State:   ways(k) = ways(k-1) + ways(k-2), the same recurrence as Fibonacci
//          with ways(0)=1 and ways(1)=1.
// Complexity: O(n) time, O(1) space with two running values.
// Edge cases: n==0 returns 1 (the empty climb); reject n<0.
int climb_stairs(int n) {
    throw std::logic_error("TODO: implement climb_stairs");
}

// Purpose: find the fewest coins whose values sum exactly to amount.
// Params:  coins  - available denominations, each usable any number of times;
//          amount - target sum, amount >= 0.
// Return:  minimum coin count reaching amount, or -1 if it cannot be formed.
// State:   best[a] = min over coins c of best[a-c] + 1 for a-c >= 0; best[0]=0.
// Complexity: O(amount * coins.size()) time, O(amount) space.
// Edge cases: amount==0 returns 0; empty coins with amount>0 returns -1;
//             ignore coin values greater than the current sub-amount.
int coin_change_min(const std::vector<int>& coins, int amount) {
    throw std::logic_error("TODO: implement coin_change_min");
}

// Purpose: maximize total value of items packed without exceeding capacity,
//          using each item at most once.
// Params:  weights  - per-item weights;
//          values   - per-item values, parallel to weights (same length);
//          capacity - weight budget, capacity >= 0.
// Return:  maximum achievable value.
// State:   best[i][w] = max value using the first i items within budget w;
//          best[i][w] = max(best[i-1][w], best[i-1][w-weights[i-1]]+values[i-1])
//          when weights[i-1] <= w, otherwise best[i-1][w].
// Complexity: O(items * capacity) time, O(capacity) space with a rolling row.
// Edge cases: capacity==0 or no items yields 0; items heavier than capacity are
//             never selected.
int knapsack_01(const std::vector<int>& weights, const std::vector<int>& values, int capacity) {
    throw std::logic_error("TODO: implement knapsack_01");
}

// Purpose: length of the longest strictly increasing subsequence of a.
// Params:  a - input sequence (order matters, elements need not be contiguous).
// Return:  length of the longest subsequence whose values strictly increase.
// State:   lis[i] = 1 + max(lis[j]) over all j < i with a[j] < a[i], else 1;
//          the answer is the maximum entry of lis.
// Complexity: O(n^2) time, O(n) space.
// Edge cases: empty input returns 0; a single element returns 1.
int longest_increasing_subsequence(const std::vector<int>& a) {
    throw std::logic_error("TODO: implement longest_increasing_subsequence");
}

// Purpose: length of the longest common subsequence of strings a and b.
// Params:  a, b - input strings (subsequence keeps order, skips allowed).
// Return:  length of the longest sequence appearing in both, in order.
// State:   lcs[i][j] = lcs[i-1][j-1]+1 when a[i-1]==b[j-1], otherwise
//          max(lcs[i-1][j], lcs[i][j-1]); empty prefixes give 0.
// Complexity: O(a.size() * b.size()) time, O(min(sizes)) space with a rolling row.
// Edge cases: either string empty returns 0.
int longest_common_subsequence(const std::string& a, const std::string& b) {
    throw std::logic_error("TODO: implement longest_common_subsequence");
}

// Purpose: minimum single-character insert, delete, or replace operations to
//          transform a into b (Levenshtein distance).
// Params:  a - source string; b - target string.
// Return:  minimum number of edits turning a into b.
// State:   dist[i][j] = edits between a's first i chars and b's first j chars;
//          if a[i-1]==b[j-1] then dist[i-1][j-1], else
//          1 + min(dist[i-1][j], dist[i][j-1], dist[i-1][j-1]).
// Complexity: O(a.size() * b.size()) time, O(min(sizes)) space with a rolling row.
// Edge cases: empty a needs b.size() inserts; empty b needs a.size() deletes.
int edit_distance(const std::string& a, const std::string& b) {
    throw std::logic_error("TODO: implement edit_distance");
}

int main() {
    try {
        assert(fib_memo(10) == 55);
        assert(fib_tab(10) == 55);
        assert(fib_tab(0) == 0);
        assert(fib_tab(1) == 1);

        assert(climb_stairs(5) == 8);

        assert(coin_change_min({1, 2, 5}, 11) == 3);
        assert(coin_change_min({2}, 3) == -1);
        assert(coin_change_min({1}, 0) == 0);

        assert(knapsack_01({1, 3, 4, 5}, {1, 4, 5, 7}, 7) == 9);

        assert(longest_increasing_subsequence({10, 9, 2, 5, 3, 7, 101, 18}) == 4);

        assert(longest_common_subsequence("abcde", "ace") == 3);

        assert(edit_distance("horse", "ros") == 3);
        assert(edit_distance("", "abc") == 3);

        std::cout << "All checks passed" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "FAILED: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
