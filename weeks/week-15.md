# Week 15 — Dynamic Programming I — Recurrence Recognition, Knapsack, and Sequence DP

This is the hardest topic in the course, and it lands here on purpose, right after backtracking. DP is backtracking plus memoization: the same decision tree, but with the repeated work cached so you never solve a subproblem twice. The week moves from recognizing the recurrence and choosing between memoization and tabulation, through 1D DP, the 0/1 and unbounded knapsack families, and the classic sequence DPs (LIS, LCS, edit distance).

Back to the [course README](../README.md). Pattern reference: [docs/patterns.md](../docs/patterns.md).

## By the end of this week

- Spot the two things that make a problem a DP problem: overlapping subproblems and optimal substructure, and tell DP apart from divide & conquer by whether the subproblems overlap.
- Take a brute-force recursion and turn it into a top-down memoized solution, then into a bottom-up table, then space-optimize where the recurrence allows.
- Design a complete, correct state for a problem before you write a line of the transition.
- Model the take-or-skip decision of 0/1 knapsack, space-optimize to one row, and iterate capacity backwards so you don't reuse an item. Recall the loop direction from memory.
- Switch to unbounded knapsack by iterating capacity forwards, and pick the loop nesting that gives combinations versus permutations.
- Solve LIS in O(n^2), then in O(n log n) with the tails array and binary search. Build the 2D prefix tables for LCS and edit distance, and reconstruct the actual subsequence or edit script by walking the table back.

The week's milestone: you can recognize a DP problem from its overlapping-subproblem structure, design a correct state, write both top-down and bottom-up solutions, fix the forward/backward knapsack loop direction without looking it up, and reconstruct optimal solutions from sequence-DP tables.

---

## Lecture 57 — DP Intro: Recognizing the Recurrence, Memoization vs Tabulation

Most people meet DP as a bag of clever tricks and never get past memorizing solutions. That is the wrong model. DP is one idea applied over and over: find the recursion, notice it recomputes the same subproblems, and cache them. If you can write the brute-force recursion from Week 14, you are most of the way to the DP. The rest of this lecture is the mechanical pipeline that gets you the rest of the way.

**Objectives**

- Identify the two DP pillars: overlapping subproblems and optimal substructure.
- Convert a brute-force recursion into a top-down memoized solution, then into a bottom-up table.
- Design a complete, correct state, and contrast DP with divide & conquer.

**Topics covered**

- The 5-step workflow used for every DP in the course: write the brute-force recursion, identify the state, memoize it, tabulate it, then optimize space. Each step is a small, checkable transformation, not a leap of insight.
- Overlapping subproblems (DP) versus disjoint subproblems (divide & conquer). Merge sort splits into halves that never share work, so caching buys nothing. Fibonacci's two calls overlap immediately, which is exactly why memoization collapses it from exponential to linear.
- Optimal substructure: the optimal answer is built from optimal answers to subproblems. If that doesn't hold, DP doesn't apply, and you usually need greedy or full search instead.
- The memo itself: a `vector` sized to the state and initialized to a sentinel like `-1` for dense integer states, or an `unordered_map` when the keys are sparse or not small integers.
- The 1D on-ramp: Fibonacci, climbing stairs, house robber. Same shape every time, `dp[i]` depends on a constant number of earlier entries.
- Rolling-variable space: when `dp[i]` only looks back a fixed distance, drop the whole table and keep a couple of variables for O(1) space.

**Patterns**

- [1D DP (Fibonacci-style)](../docs/patterns.md)

**In-class problems**

- Climbing Stairs (recursive -> memo -> tab)
- House Robber / House Robber II
- Decode Ways
- Maximum Subarray (Kadane)

---

## Lecture 58 — 0/1 Knapsack Family: Pick or Leave

Knapsack is the first DP where the state has two dimensions, and it is the template for a whole family of interview problems that don't look like knapsack at first. The decision at each item is binary: take it or leave it. Once you can write that decision as a recurrence and then squeeze it into a single row, subset-sum, equal-partition, and target-sum all fall out of the same skeleton.

**Objectives**

- Model the take-or-skip decision with state `(index, remaining capacity)`.
- Space-optimize to one row and iterate capacity backwards to avoid reusing an item.
- Map subset-sum and partition problems onto the knapsack skeleton.

**Topics covered**

- The 2D recurrence: at item `i` with capacity `c`, either skip it (`dp[i-1][c]`) or take it if it fits (`value[i] + dp[i-1][c - weight[i]]`), and keep the max. Build the full 2D table first so the dependency is visible.
- Collapsing to 1D: each row only reads the row above, so one array suffices.
- The signature bug, and the reason this lecture exists: with a single row you must iterate capacity from high to low. A forward capacity loop reads a cell you already updated this round, which silently lets the same item be used more than once and turns 0/1 into unbounded.
- Subset sum and partition equal subset sum: ask whether some subset hits a target sum, which is knapsack with `value == weight` and a boolean table.
- Target Sum: assigning `+` or `-` to every number is the same as splitting them into two groups, so it reduces to counting subsets that reach `(total + target) / 2`.
- Overflow: when values or sums are large, the running totals can exceed `int`. Size the capacity axis correctly and use a wide enough type.

**Patterns**

- [Knapsack (0/1 + unbounded)](../docs/patterns.md)

**In-class problems**

- 0/1 Knapsack from scratch
- Partition Equal Subset Sum
- Target Sum
- Last Stone Weight II

---

## Lecture 59 — Unbounded Knapsack & Counting: Coin Change

Unbounded knapsack is one character of difference from 0/1: the capacity loop runs forwards instead of backwards. That is the exact bug from yesterday, except now reusing an item is the feature. This lecture pins down that mirror, then moves to the counting versions, where the order you nest the loops decides whether you count combinations or permutations. That distinction trips up almost everyone the first time.

**Objectives**

- Allow item reuse by iterating capacity forwards (the mirror of the 0/1 bug).
- Distinguish counting combinations versus permutations by loop-nesting order.
- Handle min-versus-count aggregation and pick a safe "infinity" sentinel.

**Topics covered**

- Unbounded knapsack: items may be used any number of times, achieved by reading from the current row as you update it, which is exactly the forward capacity loop.
- Coin Change (fewest coins) versus Coin Change II (count the ways). Same items, different aggregation: one takes a min, the other sums.
- Loop nesting decides what you count. Coins on the outer loop and amount on the inner counts combinations, because each coin is considered once for the whole run. Amount outer and coins inner counts permutations, because every coin gets a fresh chance at every amount. Internalize this rather than memorizing which problem wants which.
- The infinity sentinel: for the min version, seed unreachable amounts with `amount + 1` instead of `INT_MAX`. Adding 1 to `INT_MAX` overflows; `amount + 1` is larger than any real coin count, so it acts as infinity safely.
- Perfect Squares and Integer Break are the same machinery with the "items" being squares or factor splits.

**Patterns**

- [Knapsack (0/1 + unbounded)](../docs/patterns.md)

**In-class problems**

- Coin Change (min)
- Coin Change II (count combinations)
- Combination Sum IV (permutation count)
- Perfect Squares

---

## Lecture 60 — Sequence DP: LIS, LCS, and Edit Distance

Sequence DP is where the state stops being a number and starts being a position in a sequence, or a pair of positions in two sequences. These three problems show up constantly in interviews, and the reconstruction step, recovering the actual subsequence or list of edits rather than just its length, separates people who memorized the recurrence from people who understand it.

**Objectives**

- Solve LIS in O(n^2), then in O(n log n) using the tails array with binary search.
- Build the 2D prefix-comparison table for LCS and edit distance.
- Reconstruct the actual subsequence or operation list by walking the table.

**Topics covered**

- LIS the direct way: `dp[i] = 1 + max(dp[j])` over all `j < i` with `a[j] < a[i]`. That is O(n^2).
- LIS the fast way: keep a `tails` array where `tails[k]` is the smallest possible tail of an increasing subsequence of length `k + 1`. For each element, `lower_bound` finds where it goes; the array's length is the answer. This is patience sorting, and it runs in O(n log n).
- Strict versus non-strict subsequences: `<` versus `<=`, and `lower_bound` versus `upper_bound`. Getting this pair right is the difference between "longest increasing" and "longest non-decreasing," and the binary search variant on the answer is why this links to modified binary search.
- Subsequence versus substring: a subsequence drops elements but keeps order; a substring is contiguous. They have different recurrences, and mixing them up is a common error.
- LCS: a 2D table over the prefixes of the two strings. If the characters match, extend the diagonal; otherwise take the better of dropping one character from either string.
- Edit distance: the same prefix table with three moves, insert, delete, and replace, each costing one. The cell is the minimum over those three, plus the match-or-replace diagonal.
- Reconstruction: walk back from the bottom-right corner, following which choice produced each cell, to recover the actual subsequence or the edit script. The length alone is rarely the full ask in an interview.

**Patterns**

- [String DP (LCS / edit / palindrome)](../docs/patterns.md)
- [Modified binary search (+ on the answer)](../docs/patterns.md)

**In-class problems**

- Longest Increasing Subsequence (O(n^2) and O(n log n))
- Longest Common Subsequence
- Edit Distance
- Delete Operation for Two Strings

---

## Homework

Spread these across the week instead of batching them. The warmups confirm the 5-step pipeline is in your hands, the core set is the week's real work and where knapsack and sequence DP get drilled, and the challenge is the one to wrestle with before you look anything up.

### Warmup

- Climbing Stairs
- House Robber

### Core

- Coin Change
- Coin Change II
- Partition Equal Subset Sum
- Target Sum
- Longest Increasing Subsequence
- Longest Common Subsequence
- Edit Distance
- Word Break
- Decode Ways

### Challenge

- Combination Sum IV

---

## Before next week

- You can take a fresh problem, recognize it as DP from the overlapping-subproblem structure, and write the state before touching the transition.
- You can carry one problem through all five steps: brute recursion, memo, table, and space optimization, and explain what each step changed.
- You can write 0/1 knapsack from a blank file and explain, out loud, why the 1D capacity loop runs backwards. You can flip to unbounded by reversing that loop without thinking about it.
- You can say which loop nesting gives combinations and which gives permutations, and why, for the Coin Change II / Combination Sum IV pair.
- You can write LIS both ways, and you know which of `lower_bound`/`upper_bound` to use for strict versus non-strict.
- You can reconstruct the LCS string or the edit script from the table, not just report its length.
- The knapsack and string-DP entries in the [pattern reference](../docs/patterns.md) are worth a second look; Week 16 moves on to the rest of DP and greedy.

---

Back to the [course README](../README.md) · Pattern reference: [docs/patterns.md](../docs/patterns.md)
