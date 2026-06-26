# Week 2 — Recursion: the Universal Control Structure

This week installs the second lens: confident recursion. You master the call stack, base and recursive cases, recursion on numbers, arrays, and strings, recurrence-tree analysis, the common recursion shapes, and recursion-to-iteration conversion. It closes with the memoization and backtracking seeds that the later Dynamic Programming and Backtracking tracks build on directly.

Recursion is not a trick you reach for when a loop feels awkward. It is the control structure underneath tree traversal, divide and conquer, backtracking, and most of dynamic programming. Get it solid now and half the second half of the course stops being intimidating. Skip it and Week 8 onward turns into memorization.

## By the end of this week

You should be able to:

- Trace any recursion frame by frame on the call stack, and name its base case, recursive case, and the strictly-smaller subproblem it moves toward.
- Apply the recursive leap of faith: verify the base case and the single combination step, and trust the rest.
- Write number recursions, including fast power in O(log b), without tripping the missing-base-case stack overflow.
- Recurse over arrays and strings by index rather than by copying substrings, so you don't turn an O(n) algorithm into O(n^2).
- Build and solve a recurrence relation from a recursion tree, and recognize the five recurrence shapes that cover almost everything you'll meet.
- Tell head from tail recursion, and linear from tree from mutual recursion, and explain the cost difference.
- Convert tail recursion to a loop and general recursion to an explicit `std::stack` simulation, without changing the space class.
- Apply top-down memoization with a cache plus a sentinel to turn an exponential recursion into a linear one.
- Recognize the choose / explore / un-choose backtracking template on subsets and permutations.

The milestone for the week: you can write, trace, and analyze recursion confidently (recurrences and space included), convert it to iteration with an explicit stack, and you have already seen the memoization and backtracking templates, so Dynamic Programming and Backtracking later build on recognition rather than first contact.

---

## Lecture 5 — Recursion Fundamentals & Recursion on Numbers

**Objectives**

- Trace the call stack frame by frame and identify the base case, the recursive case, and the strictly-smaller subproblem.
- Apply the recursive leap of faith: verify only the base case and the single combination step.
- Write number recursions including fast power in O(log b), and avoid the missing-base-case stack overflow.

**Topics covered**

- Anatomy of recursion: base case (or cases), recursive case, and always moving toward the base.
- The call stack and stack frames. We draw `factorial(4)` frame by frame, watch the stack grow on the way down and unwind on the way up.
- The recursive leap of faith, and the failure mode: if the base case is unreachable, the stack grows until the program crashes.
- `factorial`, `power(a, b)`, fast power via `a^b = (a^(b/2))^2`, `sum_of_digits`, `gcd` by Euclid's algorithm, and printing `1..n` and `n..1`.
- Cost model: each frame costs O(depth) stack space, so depth is your space bound. Pass large objects by reference to avoid an O(n) copy per frame, and use `long long` where the result overflows `int`.

**Patterns**

- [Recursive decomposition (shrink the input)](../docs/patterns.md)
- [Fast exponentiation (halving)](../docs/patterns.md)

**In-class problems**

- Factorial, recursive.
- Fast power `a^b` in O(log b).
- GCD by the Euclidean algorithm, recursive.
- Print `1..n` and `n..1`, where the order falls out of where you place the print relative to the recursive call.

The fast-power problem is the first time halving an input cuts the work from linear to logarithmic. That same move comes back in binary search, merge sort, and balanced trees, so it is worth slowing down on here.

---

## Lecture 6 — Recursion on Arrays/Strings & Recurrence Relations

**Objectives**

- Apply the shrink-the-input pattern over arrays and strings using indices, not substrings.
- Build and solve recurrence relations and the recursion tree for a recursive cost.
- Recognize the common recurrence shapes and their solutions: linear, halving, and two-halves.

**Topics covered**

- Shrink the input: process index `i`, then recurse on `i + 1` or on a range `[lo, hi]`. Decide whether you build the answer on the way down or combine it on the way up.
- Array sum and max, reverse in place with two indices, linear search, string reverse, palindrome check with `(i, n - 1 - i)`, and counting occurrences.
- Recurrences and their closed forms:

| Recurrence | Solves to | Where you see it |
|---|---|---|
| `T(n) = T(n-1) + O(1)` | O(n) | linear recursion, array sum |
| `T(n) = T(n-1) + O(n)` | O(n^2) | substring-copy recursion, naive work per frame |
| `T(n) = T(n/2) + O(1)` | O(log n) | binary search, fast power |
| `T(n) = 2T(n/2) + O(n)` | O(n log n) | merge sort |
| `T(n) = 2T(n/2) + O(1)` | O(n) | tree-shaped recursion over a balanced split |

- The recursion-tree method for deriving these, with the Master theorem stated as a preview for Week 7.
- The substring trap: recursing with `s.substr(i)` copies the rest of the string on every call, which silently turns O(n) into O(n^2). Recurse with `(s, i)` and pass the string by reference instead.

**Patterns**

- [Recurrence + recursion-tree analysis](../docs/patterns.md)
- [Two-index recursion (i, n - 1 - i)](../docs/patterns.md)

**In-class problems**

- Reverse an array in place recursively, using two indices that march toward each other.
- Valid Palindrome, recursively with `(i, n - 1 - i)`.
- Recursive binary search, which sets up the binary-search track in Week 7.
- Derive and solve `T(n) = 2T(n/2) + O(n)` from its recursion tree.

---

## Lecture 7 — Recursion Shapes & Recursion-to-Iteration Conversion

**Objectives**

- Distinguish head from tail recursion, and linear from tree from mutual recursion.
- Convert tail recursion to a loop, and general recursion to an explicit `std::stack` simulation.
- Explain why tree recursion (naive Fibonacci) explodes, and why the explicit-stack conversion avoids a call-stack overflow without changing the space class.

**Topics covered**

- Head recursion does its work on the way back up. Tail recursion does its work on the way down, with the recursive call last, which is what makes it convertible to a plain loop.
- Linear recursion (one call per frame) versus tree recursion (multiple calls per frame). Naive Fibonacci is tree recursion and runs in O(phi^n). Mutual recursion ties two functions together and needs a forward declaration.
- Tail recursion converts to a `while` loop. General recursion converts to an explicit stack: you push the state you would otherwise have passed to the recursive call.
- `std::stack` mechanics: `push`, `top`, `pop`. Note that `pop` returns `void`, so read `top()` first and then `pop()`. The explicit stack uses the same O(depth) space the call stack did; you are moving the storage, not removing it.
- Forward-declaration syntax for mutual recursion, shown on `isEven` and `isOdd`.

**Patterns**

- [Recursion to iteration via an explicit stack](../docs/patterns.md)

**In-class problems**

- Convert tail-recursive factorial to an iterative loop.
- Convert recursive array sum to iterative form with an explicit stack.
- Mutual recursion: `isEven` / `isOdd`.
- Simulate a recursive traversal by hand with a manual stack, live.

The reason to learn the explicit-stack conversion is not style. Deep recursion can overflow the real call stack, and converting to an explicit stack on the heap sidesteps that limit while keeping the same asymptotic space. It is also the bridge to the iterative tree traversals in Week 8.

---

## Lecture 8 — Memoization Preview, Backtracking Shape & Capstone Clinic

**Objectives**

- Identify overlapping subproblems and apply top-down memoization with a cache plus a sentinel to turn exponential into linear.
- Recognize the choose / explore / un-choose backtracking template on subsets and permutations skeletons.
- Synthesize the complexity and recursion lenses on fresh capstone problems.

**Topics covered**

- Overlapping subproblems: naive `fib(n)` recomputes the same values an exponential number of times. We draw the tree and count the repeats.
- Top-down memoization: cache keyed by the arguments, with sentinel `-1` meaning "not computed yet". This brings Fibonacci to O(n) time and O(n) space. The two conditions that make a problem a DP candidate are optimal substructure and overlapping subproblems, and this is the bridge into Week 15.
- The backtracking shape, previewed: choose, explore, un-choose, on subsets and permutations skeletons. The recursion tree here is a decision tree, which is exactly how Week 14 frames it.
- A capstone clinic where we re-derive the complexity of each problem on the spot and name the pattern before writing code.
- Cache mechanics: a `vector<int> memo(n + 1, -1)` passed by reference, never by value, so you don't copy the cache on every call. Use `unordered_map` when the keys are sparse, and `long long` for Fibonacci past about n = 46, where the result overflows a 32-bit `int`.

**Patterns**

- [Fibonacci / 1-D memoization (the DP seed)](../docs/patterns.md)
- [Subsets / permutations skeleton (the backtracking seed)](../docs/patterns.md)

**In-class problems**

- Naive Fibonacci: draw the tree and count the repeated calls.
- Memoized Fibonacci with a `vector` cache and sentinel `-1`.
- Climbing Stairs, recursive first, then memoized.
- All subsets / power set: print all of them with the backtracking skeleton.

---

## Homework

Work these between lectures. Warmups confirm you have the shape down; Core problems are the ones you should be able to write cleanly under light time pressure; Challenges stretch you toward the patterns the second half of the course leans on.

**Warmup**

- Sum of digits.
- Recursive array maximum.

**Core**

- Decimal to binary via recursion.
- Check whether an array is sorted, recursively.

**Challenge**

- Tower of Hanoi: produce both the move count and the move sequence.
- String permutations: print all of them.
- Iterative traversal of a recursive process using `std::stack`.
- Coin Change: the recursive formulation plus memoization, as a preview only. We come back to it properly in Week 15.

The Coin Change problem is intentionally a preview. You are not expected to nail the optimal DP yet. The point is to feel the recursive formulation and watch memoization collapse the repeated work, so when it returns in the DP block it is recognition, not first contact.

---

## Before next week

- You can trace `factorial(4)` and naive `fib(5)` on paper, frame by frame, without running them.
- You can write fast power in O(log b) and explain why halving the exponent gives the log factor.
- You can state which of the five recurrence shapes a given recursion matches, and the cost it implies.
- You can convert one tail recursion to a loop and one general recursion to an explicit-stack version on your own.
- You can write memoized Fibonacci from a blank file, sentinel and all, and explain why the cache is passed by reference.
- You have skimmed the [pattern reference](../docs/patterns.md) entries for recursive decomposition, recurrence analysis, and the memoization and backtracking seeds, so the names are familiar when they recur.

Back to the [course README](../README.md) · previous: [Week 1](week-01.md) · next: [Week 3](week-03.md)
