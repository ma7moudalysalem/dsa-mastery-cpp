# Week 1 — Complexity Analysis & The Problem-Solving Framework

This is the first lens of the course: how to measure work and compare algorithms before you write a line of code. You'll learn operation counting, asymptotic notation, space and amortized analysis, and the repeatable five-step UPSCR problem-solving framework (Understand, Pattern, Strategy, Code, Review) you'll reuse on every problem for the next sixteen weeks. By Friday you'll also have the daily C++/STL toolset and the assert-based testing habit that the rest of the course leans on.

We teach this before any data structure on purpose. Complexity is how you'll read every topic that follows, and the framework is how you'll attack every problem in the bank. Get fluent here and the rest of the course is easier.

[← Back to the course README](../README.md)

## By the end of this week

You can:

- Run the five-step UPSCR framework end to end on a fresh problem: Understand, Pattern, Strategy, Code, Review.
- Read input constraints and name the target complexity before you start (for example, `n ≤ 20` points at exponential, `n ≤ 1e6` at O(n) or O(n log n)).
- State the formal definitions of O, Ω, and Θ, and use them as upper, lower, and tight bounds without getting lost in the math.
- Analyze single, nested, triangular, and halving loops and place any snippet on the growth ladder.
- Separate the *case* axis (best/worst/average) from the *notation* axis (O/Ω/Θ), and explain why we usually quote worst case.
- Account for total vs. auxiliary space, including the recursion call stack as O(depth).
- Derive why doubling growth gives amortized O(1) `push_back` while constant `+k` growth gives amortized O(n).
- Use references, pointers, and `const&` correctly, pair every `new` with one `delete` (and `new[]` with `delete[]`), and work comfortably in the DSA-relevant STL subset.
- Write assert-based tests against a disciplined edge-case checklist.

The week's milestone: state and justify the Big-O/Θ of any loop-based snippet (time, space, and amortized), apply the five-step UPSCR framework end to end, and be fluent in the daily STL subset and assert-based testing.

---

## Lecture 1 — Course Kickoff, the Problem-Solving Framework & Measuring Work

How the course works, why complexity and recursion come first, and the five-step UPSCR framework you'll use on everything after. Then the foundation underneath all of it: counting operations and reading constraints.

**Objectives**

- Internalize the five-step UPSCR framework (Understand, Pattern, Strategy, Code, Review) and reuse it on every later problem.
- Count operations under the RAM model and read input constraints to guess the target complexity.
- Recognize `int` overflow (roughly 2.1 × 10⁹) and reach for `long long` early.

**Topics**

- Course mechanics and philosophy: problem-heavy, pattern-based, and why complexity plus recursion are taught before any structure.
- The five-step UPSCR framework, taught explicitly and then used live on a warmup.
- The RAM model and operation counting as a function of `n`.
- Reading constraints to guess complexity:

  | Constraint | Likely target |
  |---|---|
  | `n ≤ 20` | exponential, O(2ⁿ) or O(n!) |
  | `n ≤ 5000` | O(n²) |
  | `n ≤ 1e6` | O(n) or O(n log n) |
  | `n ≤ 1e9` | O(log n) or O(√n) |

- `int` vs. `long long` overflow, and the `g++ -std=c++17 -O2 -Wall` compile/run loop.
- First touch of `<chrono>` `steady_clock` for empirical timing.

**Patterns**

- [Complexity estimation from constraints](../docs/patterns.md)

**In-class problems**

- Solve one warmup end to end through all five UPSCR steps.
- Given constraints (`n ≤ 20` / `5000` / `1e6` / `1e9`), name the target complexity for each.
- Demonstrate `int` overflow in a factorial and fix it with `long long`.

---

## Lecture 2 — Big-O, Big-Omega, Big-Theta & Loop Analysis

The notation, made precise and then made usable. Most of the lecture is loop analysis, because that's where you'll actually apply it.

**Objectives**

- State the formal definitions of O, Ω, and Θ, and de-formalize them as upper, lower, and tight bounds.
- Analyze single, nested, triangular, and halving loops and place them on the growth ladder.
- Separate the case axis (best/worst/average) from the notation axis (O/Ω/Θ).

**Topics**

- Formal O/Ω/Θ definitions plus the intuition; dropping constants and lower-order terms.
- Loop recipes:

  | Shape | Cost |
  |---|---|
  | single loop | O(n) |
  | nested loops | O(n·m) |
  | triangular (`j = i..n`) | O(n²) |
  | halving (`i *= 2`) | O(log n) |
  | halving outer × linear inner | O(n log n) |

- The growth ladder: O(1) < log n < √n < n < n log n < n² < n³ < 2ⁿ < n!.
- Best/worst/average case vs. notation, and why we usually quote worst case.
- Sequential blocks take the max, not the sum. Log base is irrelevant asymptotically.
- Empirical validation with `<chrono>`, and the catch that `-O2` can optimize a dead loop away entirely.

**In-class problems**

- Time complexity of a triangular loop (`j = i..n`).
- Time complexity of a halving loop (`i *= 2`).
- Best, worst, and average case of linear search.
- Classify each snippet into the growth ladder (a mixed set of 10).

---

## Lecture 3 — Space Complexity, Amortized Analysis & the Memory Model

Time is only half of cost. This lecture covers space (including the call stack), the amortized argument behind dynamic arrays, and the stack-vs-heap model you'll rely on all course.

**Objectives**

- Distinguish total vs. auxiliary space, and account for the recursion call stack as O(depth) space.
- Derive why geometric (doubling) growth gives amortized O(1) `push_back` while constant `+k` growth gives amortized O(n).
- Explain the stack vs. heap model and the difference between a vector's `size()` and `capacity()`.

**Topics**

- Auxiliary vs. total space; the call-stack space of a recursive function.
- Amortized analysis as the average cost over a worst-case sequence, not a probabilistic average.
- Dynamic-array doubling: the aggregate argument that `n` pushes cost at most `2n` copies.
- Doubling vs. `+1` growth; `reserve()` changes the constants, not the Big-O.
- Stack vs. heap, automatic vs. dynamic lifetime.
- `std::vector`: `size()` vs. `capacity()`, `reserve()`, `shrink_to_fit()`; `push_back` invalidates iterators, pointers, and references; the `vector<bool>` caveat.

**In-class problems**

- Amortized cost of `n` `push_back`s with doubling vs. `+1` growth.
- Space complexity of recursive vs. iterative array reversal.
- Empirically validate O(n²) by doubling the input and timing with `<chrono>`.
- Vector growth demo: observe `size()` vs. `capacity()` as elements are added.

---

## Lecture 4 — C++ Essentials, STL Survey & Testing Discipline

The working toolkit. The slice of C++ and STL you'll use every week, plus the testing habit that catches your bugs before the instructor does.

**Objectives**

- Use references vs. pointers vs. `const&` correctly, and pair every `new` with exactly one `delete` (and `new[]` with `delete[]`).
- Work fluently in the DSA-relevant STL subset: `vector`, `array`, `string`, `pair`, iterators, ranged-for, and the `<algorithm>` basics.
- Write assert-based tests against a disciplined edge-case checklist.

**Topics**

- References (an alias, never null, no rebinding) vs. pointers (nullable, support arithmetic) vs. `const&` for passing big objects cheaply.
- `new`/`delete`, `new[]`/`delete[]`, and templates (`template<typename T>`).
- STL: `vector`, `array`, `string`, `pair`/`tuple`, structured bindings, half-open `[begin, end)` ranges, `sort`/`reverse`/`min`/`max`/`accumulate`/`lower_bound`, and lambda comparators.
- `assert()` for invariants, plus the edge-case checklist: empty, size 1, all-equal, duplicates, already sorted, reverse sorted, negatives and zero, max size, overflow.
- Gotchas: dangling references, double free, off-by-one with `end()`, silent O(n) by-value copies, and signed/unsigned `size()` pitfalls.

```cpp
template <typename T>
T myMax(const std::vector<T>& v) {
    assert(!v.empty());            // invariant: max of empty is undefined
    T best = v[0];
    for (size_t i = 1; i < v.size(); ++i)  // size_t, not int: no signed/unsigned mismatch
        if (v[i] > best) best = v[i];
    return best;
}
```

**In-class problems**

- Build a tiny `MyVector` with doubling `push_back`.
- Write a `template<typename T> myMax(...)`.
- Write an assert-based test harness plus a full edge-case checklist for a `reverse` function.
- Sort a `vector<pair<int,int>>` by the second element with a lambda comparator.

---

## Homework

Work these between lectures. They're grouped by difficulty, not by lecture, so you can warm up before the harder ones.

**Warmup**

- Time complexity of a single `for` loop.
- Time complexity of two nested loops.
- Sequential blocks: an O(n) block followed by an O(n²) block. What's the total, and why?
- Pass a `vector` by value vs. by `const&` and measure the copy cost.

**Core**

- Find the memory bug: a dangling reference, and `delete` vs. `delete[]` misuse.
- Classify each snippet into the growth ladder (a mixed set of 10).

**Challenge**

- Why is `string::substr` inside a loop O(n²)? Identify the cost and fix it.
- Iterator invalidation: spot the bug in a `push_back`-while-iterating loop.

When a problem names a pattern, the [pattern reference](../docs/patterns.md) has the template and the tells for recognizing it.

## Before next week

- [ ] You can run all five UPSCR steps on a problem without looking at notes.
- [ ] Given a constraint like `n ≤ 1e6`, you name the target complexity in a few seconds.
- [ ] You can analyze single, nested, triangular, and halving loops and place each on the growth ladder.
- [ ] You can explain, out loud, why doubling growth makes `push_back` amortized O(1).
- [ ] Your `g++ -std=c++17 -O2 -Wall` compile/run loop is set up and working on your machine.
- [ ] You've written at least one assert-based test with a full edge-case checklist.

Next week is recursion: the call stack, recurrence relations, recursion-to-iteration, and a first look at memoization and the backtracking shape. The space analysis you did this week is exactly what makes recursive cost obvious. See [`week-02.md`](week-02.md).
