# Week 16 — DP Finale, Greedy, Bit/Math & Interview-Ready Capstone

The last week closes the loop. You finish dynamic programming with the variants that show up most in interviews (grid, range, tree, bitmask), then add the three topics that round out a complete toolkit: greedy with an honest account of when it provably fails and you must fall back to DP, bit manipulation, and the math and number theory that interviewers actually ask. The week ends with two timed mock interviews, a capstone problem, and a curated top-150 review that drills DP one more time so the pattern is fresh when you walk into a real loop.

Back to the [course README](../README.md). Pattern reference: [docs/patterns.md](../docs/patterns.md).

## By the end of this week

- Solve grid DP (counting paths, minimum path sum, maximal square, and the backward "dungeon" formulation), and shrink the table to two rolling rows when only the previous row matters.
- Set up range DP by looping on increasing interval length with an inner split point `k`, the O(n³) template behind burst balloons, matrix-chain multiplication, and palindrome partitioning.
- Extend DP onto trees with a post-order DFS that returns a small tuple per subtree, and onto subsets with a bitmask state, tying both back to DAG DP over a topological order.
- Apply the greedy template to interval scheduling and prove it correct with an exchange argument, and state precisely why fractional knapsack yields to greedy while 0/1 knapsack needs DP.
- Use XOR identities and bit tricks (`x & -x`, `x & (x-1)`, the power-of-two test) for O(1)-space answers and subset enumeration, and apply GCD/LCM, modular arithmetic, fast modular exponentiation, and the Sieve of Eratosthenes without falling into the overflow, precedence, and negative-modulo traps.
- Run the full interview loop under time pressure (clarify, brute force, optimize, code, test, state complexity), map input constraints to the right technique from a decision-tree cheat sheet, and recognize the correct pattern from problem signals across all 28 of the course's patterns.

Milestone: you finish the course interview-ready. You can read a problem, name the right pattern across all 28, solve graph, backtracking, DP, greedy, bit, and math problems fluently, and hold up under timed mock-interview conditions, with DP reinforced one final time through the curated top-150 review.

---

## Lecture 61 — DP II: Grid, Range, Tree & Bitmask DP

Week 15 gave you the DP machinery: define the state, write the recurrence, decide top-down versus bottom-up, get the base cases right. This lecture spends that machinery on the four shapes you will keep meeting. The states change; the discipline does not.

### Objectives

- Solve grid DP for path counting, minimum path sum, maximal square, and the backward "dungeon" variant, and roll the table down to two rows.
- Apply interval/range DP by looping on increasing length with an inner split point, the O(n³) template.
- Extend DP onto trees with a post-order DFS, onto subsets with a bitmask, and connect both to longest-path DP over a topological order on a DAG.

### Topics covered

- Grid DP. Most grid problems reduce to "the answer at `(i, j)` is built from the cells above and to the left." Unique Paths counts ways with `dp[i][j] = dp[i-1][j] + dp[i][j-1]`; Minimum Path Sum takes a `min` of the same two neighbors plus the cell's cost. When a transition only reads the previous row, keep two rows (or one, scanned carefully) and drop the space from O(mn) to O(n).
- Maximal Square. `dp[i][j]` is the side length of the largest all-ones square whose bottom-right corner is `(i, j)`, and it is `1 + min(up, left, up-left)` when the cell is 1. A small recurrence with a satisfying geometric reason behind the `min`.
- The backward grid. Some problems are cleaner filled from the bottom-right corner toward the start (the "dungeon" formulation, where you track the minimum health needed to reach the goal). The lesson is that the direction of the fill is a choice, and the right direction is the one where the dependency points the way you scan.
- Range DP. The state is an interval `dp[i][j]`, and you build it by increasing length: fix `len`, let `i` run, set `j = i + len - 1`, and try every split `k` in `[i, j]`. That triple loop is O(n³). Burst Balloons, matrix-chain multiplication, and palindrome partitioning all wear this shape; the trick in Burst Balloons is to think about the *last* balloon popped in a range, not the first.
- Tree DP. Run a post-order DFS so every node sees its children's answers before computing its own. House Robber III returns a pair per node: the best total if you rob this node, and the best if you skip it. Rerooting is the follow-up technique when you need every node's answer as a root, computed in two passes instead of n.
- Bitmask DP. When `n` is small (roughly `n ≤ 20`), a subset of `n` items fits in an integer, and the state becomes "which items are used." This is the engine behind TSP-style problems. Guard the shift: `1 << n` overflows a 32-bit `int` for `n ≥ 31`, so use `1LL << n` when the count can be large.
- Counting DP and DAG DP. When a problem counts arrangements, keep every addition under `% MOD` so the running total never overflows. Longest path on a DAG is just DP evaluated in topological order, the same idea from the graphs week, now recognized as DP on a directed acyclic graph.

```cpp
// Range DP skeleton: build intervals by increasing length, split at k.
for (int len = 2; len <= n; ++len) {
    for (int i = 0; i + len - 1 < n; ++i) {
        int j = i + len - 1;
        for (int k = i; k <= j; ++k) {          // split point
            dp[i][j] = std::max(dp[i][j], dp[i][k] + dp[k][j] + gain(i, k, j));
        }
    }
}
```

### Patterns

- [2D / grid DP](../docs/patterns.md)
- [String DP (LCS / edit distance / palindrome)](../docs/patterns.md)
- [Tree DFS](../docs/patterns.md)
- [Bitwise XOR & bit manipulation](../docs/patterns.md)

### In-class problems

- Unique Paths II / Minimum Path Sum (grid DP, rolling row)
- Maximal Square (grid DP)
- Burst Balloons (range DP)
- House Robber III (tree DP, post-order)

---

## Lecture 62 — Greedy: Exchange Arguments and When NOT to Be Greedy

Greedy is the most over-applied technique in interviews. It is short, it feels clever, and on the wrong problem it is confidently wrong. This lecture teaches the template, teaches you to *prove* it when it works, and spends real time on the cases where a local choice silently fails so you stop reaching for greedy on problems that need DP.

### Objectives

- Apply the greedy template to interval scheduling and prove correctness with an exchange argument.
- Contrast fractional knapsack (greedy is optimal) with 0/1 knapsack (greedy fails, DP is required), with a concrete counterexample.
- Recognize problems where a local choice silently loses, so you reach for DP instead.

### Topics covered

- When greedy is allowed. A problem is safe for greedy when it has the greedy-choice property (a locally optimal pick is part of some global optimum) and optimal substructure (the rest of the problem, after that pick, is the same kind of problem). Both have to hold. If you cannot argue the first, assume greedy is wrong until proven otherwise.
- Interval scheduling. To pick the maximum number of non-overlapping intervals, sort by finish time and greedily take each interval that starts after the last one you kept. Sorting by start time or by length both fail, and showing why is the point.
- The exchange argument. The standard proof: assume an optimal solution differs from the greedy one, then show you can swap an element of the optimal for the greedy choice without making it worse. Repeat until the optimal *is* the greedy solution. "Greedy stays ahead" is the sibling argument, where you show the greedy partial solution dominates any other at every step.
- The interval family. Merge Intervals (sort by start, fold overlaps), Non-overlapping Intervals (the scheduling problem in disguise: count what you must remove), and Minimum Number of Arrows (sort by end, shoot at each new end). One sort key, three answers.
- Fractional vs 0/1 knapsack. With fractions allowed, sorting by value-per-weight and filling greedily is optimal, because you can always top off with a slice of the best remaining item. Remove fractions and that argument breaks: the counterexample is small and worth memorizing, and it is exactly why 0/1 knapsack needs the DP from Week 15.
- Huffman coding. Build an optimal prefix code by repeatedly merging the two least-frequent nodes with a min-heap. This is a greedy algorithm with a clean exchange-argument proof, and it ties back to the heap from the trees track.

```cpp
// Interval scheduling: sort by finish time, take what fits.
std::sort(iv.begin(), iv.end(), [](auto& a, auto& b) { return a.end < b.end; });
int kept = 0, lastEnd = INT_MIN;
for (auto& x : iv) {
    if (x.start >= lastEnd) {     // no overlap with the last kept interval
        ++kept;
        lastEnd = x.end;
    }
}
```

### Patterns

- [Merge intervals](../docs/patterns.md)
- [Weighted shortest path & MST](../docs/patterns.md)

### In-class problems

- Non-overlapping Intervals (interval scheduling)
- Merge Intervals
- Jump Game II (greedy reach)
- Task Scheduler (greedy with counts)

---

## Lecture 63 — Bit Manipulation & Math / Number Theory

A handful of bit and number-theory tricks turn a class of problems from "needs a hash set" into "one pass, O(1) space," and they come up often enough that not knowing them is a tell. This lecture is mostly small, sharp tools and the pitfalls that make them dangerous when used carelessly.

### Objectives

- Use XOR identities and bit tricks for O(1)-space solutions and subset enumeration.
- Apply GCD/LCM, modular arithmetic, fast modular exponentiation, and the sieve.
- Avoid the common overflow, operator-precedence, and negative-modulo pitfalls.

### Topics covered

- The bit operators. AND, OR, XOR, NOT, and left/right shifts, with the three identities that matter most: `x ^ x == 0`, `x ^ 0 == x`, and XOR is commutative and associative, so a long XOR chain cancels every value that appears an even number of times.
- The standard bit tricks. `x & -x` isolates the lowest set bit, `x & (x-1)` clears it (count set bits by counting how many times you can do this), and `x > 0 && (x & (x-1)) == 0` tests for a power of two. These are the building blocks; memorize them.
- The XOR pattern. Single Number (every element appears twice except one, so XOR the whole array) and Missing Number (XOR the indices against the values). Iterating subsets of a mask with `for (int s = mask; s; s = (s-1) & mask)` is the bridge straight to the bitmask DP from Lecture 61.
- GCD and LCM. Euclid's algorithm gives `gcd` in O(log min(a, b)), and `lcm(a, b) = a / gcd(a, b) * b`, with the division done *before* the multiply to keep the intermediate from overflowing.
- Modular arithmetic. Keep every partial result under `% MOD`: addition and multiplication distribute over the modulus, so reduce as you go rather than at the end. This is what keeps counting-DP answers from overflowing.
- Fast modular exponentiation. Compute `x^n mod m` in O(log n) by squaring the base and halving the exponent (binary exponentiation), instead of multiplying n times.
- Sieve of Eratosthenes. Mark composites in O(n log log n) to list every prime up to n, the standard tool behind Count Primes.
- The pitfalls, stated plainly. `1 << 31` is undefined behavior on a 32-bit signed `int` (use `1u` or `1LL`); `&`, `|`, and `^` have lower precedence than `==`, so `a & b == c` parses as `a & (b == c)` and you must parenthesize; and C++'s `%` can return a negative result, so normalize with `((x % m) + m) % m` whenever `x` might be negative.

```cpp
// Fast modular exponentiation: x^n mod m in O(log n).
long long powmod(long long x, long long n, long long m) {
    long long result = 1 % m;
    x %= m;
    while (n > 0) {
        if (n & 1) result = result * x % m;   // multiply when the bit is set
        x = x * x % m;                          // square the base
        n >>= 1;                                // drop the low bit
    }
    return result;
}
```

### Patterns

- [Bitwise XOR & bit manipulation](../docs/patterns.md)

### In-class problems

- Single Number / Single Number II (XOR, bit counting)
- Missing Number (XOR)
- Count Primes (sieve)
- Pow(x, n) (fast exponentiation)

---

## Lecture 64 — Capstone: Two Timed Mock Interviews + Top-150 Pattern Review

The final lecture is the rehearsal. Two timed mock interviews run under realistic conditions, then a review that pulls the whole course back into one frame: a table that maps a problem's signals to the pattern that solves it, and a curated top-150 set that drills DP one last time. The goal is not to learn anything new. It is to make recall fast under pressure.

### Objectives

- Run the full interview loop (clarify, brute force, optimize, code, test, state complexity) under time pressure.
- Map input constraints to the right technique with a decision-tree cheat sheet.
- Reinforce DP and all 28 of the course's patterns through a curated top-150 mixed set.

### Topics covered

- Two timed mock interviews. Realistic conditions: a stated time box, think out loud, no peeking at solutions. One mixes graphs and DP, the other backtracking and greedy, so you practice switching tracks cold. The debrief after each one is where the learning is.
- Constraint-to-technique mapping. The size of the input often names the technique before you have read the whole problem. A working cheat sheet:

  | Constraint | What it usually points to |
  | --- | --- |
  | `n ≤ 20` | bitmask DP or backtracking (exponential is fine) |
  | `n ≤ 500` | O(n³) is acceptable; range DP, Floyd-Warshall |
  | `n ≤ 5000` | O(n²) DP or two-pointer over pairs |
  | `n ≤ 10^5` | O(n log n); sort, heap, binary search, or a single-pass pattern |
  | `n ≤ 10^9`, no array given | O(log n) or O(√n); math, binary search on the answer |
  | "minimize the maximum" / "maximize the minimum" | binary search on the answer |

- The reach-for-it pattern table. A one-page index across all 28 patterns: the signal in the prompt, the pattern it triggers, and a canonical problem for each. This is the artifact to keep open during practice until the mapping is automatic. See [docs/patterns.md](../docs/patterns.md) for the full reference.
- Curated top-150 review. A mixed set spanning the whole course, weighted toward DP because it is the topic students lose first. Treat it as spaced repetition, not a one-time pass.
- The capstone synthesis problem. Best Time to Buy and Sell Stock with Cooldown, a state-machine DP that pulls together state definition, transitions, and base cases under interview framing.

### Patterns

- [1D DP (Fibonacci-style)](../docs/patterns.md)
- [Knapsack (0/1 + unbounded)](../docs/patterns.md)
- [String DP (LCS / edit distance / palindrome)](../docs/patterns.md)
- [Modified binary search (+ on the answer)](../docs/patterns.md)
- [Subsets / permutations (backtracking)](../docs/patterns.md)

### In-class problems

- Timed Mock Interview A (graph + DP, mixed)
- Timed Mock Interview B (backtracking + greedy, mixed)
- Best Time to Buy and Sell Stock with Cooldown (capstone, state-machine DP)
- Top-150 lightning round (mixed patterns)

---

## Homework

Spread these across the week. The warmup confirms one mechanic, the core set is the real practice, and the challenges are where the week's milestone is won. The top-150 self-assessment is the one to take seriously: it is your honest read on interview readiness, not a graded exercise. See the full bank in [problems/README.md](../problems/README.md).

### Warmup

- Counting Bits

### Core

- Unique Paths II
- Maximal Square
- Non-overlapping Intervals
- Jump Game II
- Single Number III
- Count Primes

### Challenge

- Burst Balloons
- House Robber III
- Best Time to Buy and Sell Stock with Cooldown
- Regular Expression Matching
- Curated top-150 self-assessment set (mixed difficulty)

A note on the top-150 set: do not grind it in one sitting. Work it in blocks, and after each block, write down which problems you recognized the pattern for immediately and which ones you stalled on. The stalls are your study list for the days after the course ends.

---

## Before next week

This is the last week, so the checklist is a graduation gate rather than a setup for what's next.

- [ ] You can write the range-DP triple loop (length, left index, split `k`) from memory and explain why it is O(n³).
- [ ] You can solve a tree-DP problem with a post-order DFS that returns a small tuple per node, House Robber III being the model.
- [ ] You can state the greedy-choice property and optimal substructure, sketch an exchange argument for interval scheduling, and give the 0/1-knapsack counterexample that shows greedy failing.
- [ ] You can reproduce `x & -x`, `x & (x-1)`, the power-of-two test, and fast modular exponentiation without a reference, and name all three of the bit/math pitfalls.
- [ ] You completed both timed mock interviews and can articulate, for each, where the clock cost you and what you would do differently.
- [ ] You can take a fresh problem, read its constraints, and name the likely technique from the cheat-sheet table before you have finished reading the statement.
- [ ] You finished the curated top-150 self-assessment and have an honest list of the patterns that still need work.

That is the course. You have built every structure on the syllabus by hand, drilled all 28 patterns, and sat real timed interviews. The [pattern reference](../docs/patterns.md) stays useful long after the cohort ends, and the [course overview](../README.md) lays out how the whole thing fits together.
