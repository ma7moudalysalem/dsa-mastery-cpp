// Recursion Fundamentals (Week 2)
// Builds a set of free-function recursion exercises (factorial, power, sums,
// string ops, Fibonacci, gcd, Tower of Hanoi, subset generation) as TODO stubs.
// Compile/run: g++ -std=c++17 -Wall recursion.cpp -o out && ./out
// Rule: Implement every method marked TODO until main() prints "All checks passed".

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

// factorial
// Purpose: compute n! = n * (n-1) * ... * 1.
// Params:  n >= 0.
// Return:  n! as long long.
// Complexity: O(n) time, O(n) recursion depth.
// Base case: factorial(0) == 1 (and factorial(1) == 1).
// Recursive case: factorial(n) == n * factorial(n - 1).
// Edge cases: n == 0 returns 1. Assumes n >= 0; result overflows long long for large n.
long long factorial(int n) {
    throw std::logic_error("TODO: implement factorial");
}

// power
// Purpose: compute base raised to exp (base^exp) for non-negative exp.
// Params:  base any long long; exp >= 0.
// Return:  base^exp as long long.
// Complexity: O(exp) time, O(exp) recursion depth (naive form).
// Base case: power(base, 0) == 1.
// Recursive case: power(base, exp) == base * power(base, exp - 1).
// Edge cases: exp == 0 returns 1 for any base (including base == 0).
long long power(long long base, int exp) {
    throw std::logic_error("TODO: implement power");
}

// sum_to_n
// Purpose: compute 1 + 2 + ... + n recursively.
// Params:  n >= 0.
// Return:  the sum as int.
// Complexity: O(n) time, O(n) recursion depth.
// Base case: sum_to_n(0) == 0.
// Recursive case: sum_to_n(n) == n + sum_to_n(n - 1).
// Edge cases: n == 0 returns 0.
int sum_to_n(int n) {
    throw std::logic_error("TODO: implement sum_to_n");
}

// sum_array
// Purpose: sum elements a[index], a[index+1], ..., a[a.size()-1].
// Params:  a vector of ints; index is the current start position (default 0).
// Return:  sum of the suffix as int.
// Complexity: O(n) time, O(n) recursion depth where n == a.size() - index.
// Base case: index == a.size() returns 0 (empty suffix).
// Recursive case: a[index] + sum_array(a, index + 1).
// Edge cases: empty vector returns 0; index past the end returns 0.
int sum_array(const std::vector<int>& a, int index = 0) {
    throw std::logic_error("TODO: implement sum_array");
}

// reverse_string
// Purpose: return s reversed, built recursively.
// Params:  s any string.
// Return:  the reversed string.
// Complexity: O(n) time, O(n) recursion depth.
// Base case: empty string returns "".
// Recursive case: reverse_string(s without first char) + first char.
// Edge cases: empty and single-character strings return a copy of s.
std::string reverse_string(const std::string& s) {
    throw std::logic_error("TODO: implement reverse_string");
}

// count_digits
// Purpose: count decimal digits of n (ignoring sign).
// Params:  n any long long.
// Return:  number of digits as int.
// Complexity: O(d) time where d is the digit count.
// Base case: |n| < 10 returns 1 (this also covers n == 0).
// Recursive case: 1 + count_digits(n / 10).
// Edge cases: count_digits(0) == 1; negative numbers count digits of |n|.
int count_digits(long long n) {
    throw std::logic_error("TODO: implement count_digits");
}

// is_palindrome
// Purpose: report whether s reads the same forwards and backwards.
// Params:  s any string.
// Return:  true if palindrome, false otherwise.
// Complexity: O(n) time, O(n) recursion depth.
// Hint: two-index recursion comparing s[lo] and s[hi], moving inward.
// Base case: lo >= hi returns true (zero or one char left in range).
// Recursive case: s[lo] == s[hi] AND the inner range [lo+1, hi-1] is a palindrome.
// Edge cases: empty and single-character strings are palindromes.
bool is_palindrome(const std::string& s) {
    throw std::logic_error("TODO: implement is_palindrome");
}

// fib
// Purpose: compute the n-th Fibonacci number via naive recursion.
// Params:  n >= 0.
// Return:  the n-th Fibonacci number as long long.
// Complexity: O(2^n) time (exponential, recomputes subproblems), O(n) depth.
// Base cases: fib(0) == 0, fib(1) == 1.
// Recursive case: fib(n) == fib(n - 1) + fib(n - 2).
// Edge cases: n == 0 and n == 1 hit the base cases directly.
long long fib(int n) {
    throw std::logic_error("TODO: implement fib");
}

// gcd
// Purpose: greatest common divisor of a and b (Euclid's algorithm).
// Params:  a, b non-negative ints, not both zero for a meaningful result.
// Return:  gcd as int.
// Complexity: O(log(min(a, b))) recursive steps.
// Base case: gcd(a, 0) == a.
// Recursive case: gcd(a, b) == gcd(b, a % b).
// Edge cases: gcd(a, 0) == a; order of arguments does not matter.
int gcd(int a, int b) {
    throw std::logic_error("TODO: implement gcd");
}

// hanoi_moves
// Purpose: minimum number of moves to solve Tower of Hanoi with n disks.
// Params:  n >= 0.
// Return:  the move count as int (equals 2^n - 1).
// Complexity: O(n) recursion depth for this count-only form.
// Base case: hanoi_moves(0) == 0.
// Recursive case: hanoi_moves(n) == 2 * hanoi_moves(n - 1) + 1.
// Edge cases: n == 0 returns 0.
int hanoi_moves(int n) {
    throw std::logic_error("TODO: implement hanoi_moves");
}

// subsets
// Purpose: generate all 2^n subsets of nums (the power set).
// Params:  nums vector of ints.
// Return:  vector of subsets; each subset is a vector<int>.
// Complexity: O(2^n) subsets, O(n * 2^n) total work.
// Hint: recurse over each index choosing to include or exclude nums[index];
//       this include/exclude pattern sets up backtracking in Week 14.
// Base case: index == nums.size() emits the accumulated subset.
// Recursive case: branch on excluding then including nums[index].
// Edge cases: empty input yields exactly one subset, the empty set.
std::vector<std::vector<int>> subsets(const std::vector<int>& nums) {
    throw std::logic_error("TODO: implement subsets");
}

int main() {
    try {
        // factorial
        assert(factorial(5) == 120);
        assert(factorial(0) == 1);

        // power
        assert(power(2, 10) == 1024);
        assert(power(7, 0) == 1);

        // sum_to_n
        assert(sum_to_n(100) == 5050);

        // sum_array
        assert(sum_array({3, 1, 4, 1, 5}) == 14);

        // reverse_string
        assert(reverse_string("recursion") == "noisrucer");

        // count_digits
        assert(count_digits(90210) == 5);
        assert(count_digits(0) == 1);

        // is_palindrome
        assert(is_palindrome("racecar") == true);
        assert(is_palindrome("hello") == false);

        // fib
        assert(fib(10) == 55);
        assert(fib(0) == 0);
        assert(fib(1) == 1);

        // gcd
        assert(gcd(48, 18) == 6);

        // hanoi_moves
        assert(hanoi_moves(3) == 7);
        assert(hanoi_moves(10) == 1023);

        // subsets: power set of a 3-element set has 2^3 == 8 members.
        std::vector<std::vector<int>> ps = subsets({1, 2, 3});
        assert(ps.size() == 8);
        // The empty subset (size 0) and the full subset (size 3) must both appear.
        bool has_empty = false;
        bool has_full = false;
        for (const std::vector<int>& sub : ps) {
            if (sub.size() == 0) has_empty = true;
            if (sub.size() == 3) has_full = true;
        }
        assert(has_empty);
        assert(has_full);

        std::cout << "All checks passed\n";
    } catch (const std::exception& e) {
        std::cerr << "FAILED (likely unimplemented): " << e.what() << "\n";
        return 1;
    }
    return 0;
}
