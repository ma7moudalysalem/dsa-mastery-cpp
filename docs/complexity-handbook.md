# Complexity Handbook

A reference for the thing every later topic in this course leans on: how much time and space an algorithm costs as the input grows. Read it once now, then come back to the cheat-sheet tables whenever you need a number.

We teach complexity before any data structure on purpose. You cannot honestly compare a `vector` to a `list`, a hash map to a balanced tree, or merge sort to quicksort without it. Once you have this lens, every later lecture can say "this is O(...)" and you already know what that means and what it costs.

## Contents

- [What we are measuring](#what-we-are-measuring)
- [Asymptotic notation: O, Ω, Θ](#asymptotic-notation-o-omega-theta)
- [Best, worst, and average case](#best-worst-and-average-case)
- [Analyzing loops](#analyzing-loops)
- [Analyzing recursion](#analyzing-recursion)
- [The Master Theorem](#the-master-theorem)
- [Amortized analysis](#amortized-analysis)
- [Space complexity](#space-complexity)
- [Reading constraints to pick a target](#reading-constraints-to-pick-a-target)
- [Cheat sheet: growth classes](#cheat-sheet-growth-classes)
- [Cheat sheet: data-structure operations](#cheat-sheet-data-structure-operations)
- [Cheat sheet: sorting algorithms](#cheat-sheet-sorting-algorithms)
- [Common mistakes](#common-mistakes)

## What we are measuring

We count the number of basic operations an algorithm performs as a function of the input size `n`. A basic operation is something the machine does in roughly constant time: an addition, a comparison, an array index, an assignment, following a pointer.

This sits on top of a simplifying assumption called the **RAM model**: every primitive operation costs one unit of time, and any memory cell can be read or written in one unit. Real hardware is messier (caches, branch prediction, memory hierarchy), but for picking the right algorithm the model is good enough, and it is what interviewers expect you to reason in.

We do not measure wall-clock seconds. Seconds depend on the machine, the compiler, the optimization flags, and what else is running. Operation counts depend only on the algorithm and the input size, which is exactly what we want to compare.

Two things we deliberately throw away:

- **Constant factors.** An algorithm doing `3n` operations and one doing `100n` operations are both "linear." The constant matters in practice, but it does not change how the cost scales, and scaling is what kills you at large `n`.
- **Lower-order terms.** `n² + 5n + 20` is dominated by `n²` once `n` is large. We keep only the term that grows fastest.

So `3n² + 5n + 7` becomes Θ(n²). That is the whole game: find the fastest-growing term, drop its constant.

## Asymptotic notation: O, Ω, Θ

Three symbols, three different statements about how a function `f(n)` grows. People say "Big-O" loosely to mean "the complexity," but the three are not interchangeable, and knowing the difference is a common interview discriminator.

### Big-O — upper bound (at most)

`f(n) = O(g(n))` means: there exist positive constants `c` and `n₀` such that

```
f(n) ≤ c · g(n)   for all n ≥ n₀
```

In words: past some input size, `f` grows no faster than `g`, up to a constant factor. Big-O is a ceiling. When we say an algorithm is "O(n log n)," we mean it never does meaningfully more work than that.

One subtlety students trip on: Big-O is only an upper bound, not a tight one. An O(n) algorithm is *also* O(n²) and O(2ⁿ), because those are all valid (if useless) ceilings. Saying "O(n²)" about a linear algorithm is technically true and practically a lie of omission. When you want to say "this is exactly how it grows," reach for Θ.

### Big-Ω — lower bound (at least)

`f(n) = Ω(g(n))` means there exist positive `c` and `n₀` such that

```
f(n) ≥ c · g(n)   for all n ≥ n₀
```

This is a floor. The algorithm does *at least* this much work past some size. For example, any comparison-based sort is Ω(n log n): no matter how clever, it cannot beat that bound in the worst case.

### Big-Θ — tight bound (exactly)

`f(n) = Θ(g(n))` means `f` is both O(g(n)) and Ω(g(n)). The function is sandwiched: it grows exactly like `g`, up to constants.

```
c₁ · g(n) ≤ f(n) ≤ c₂ · g(n)   for all n ≥ n₀
```

Θ is the precise statement. When the upper and lower bounds match, use Θ. When you only know a ceiling, use O. Most of the course writes O out of habit and convention, but when accuracy matters, Θ is the honest notation.

A picture of the relationship:

```
Ω(g):   f never dips below   c₁·g   (floor)
Θ(g):   f hugs               g      (floor and ceiling agree)
O(g):   f never rises above  c₂·g   (ceiling)
```

### A note on log bases

You will see `log n` with no base. That is on purpose. Changing the base of a logarithm only multiplies it by a constant (`log₂ n = log₁₀ n / log₁₀ 2`), and we drop constants. So O(log₂ n), O(log₁₀ n), and O(ln n) are the same asymptotic class. Write `log n` and move on.

## Best, worst, and average case

This is the single most common confusion in this whole topic, so read carefully: **case** and **notation** are two separate axes.

- **Case** (best / worst / average) is about *which input* you are looking at.
- **Notation** (O / Ω / Θ) is about *how you are bounding* the cost on that input.

They are independent. You can give a Θ bound for the best case, an O bound for the worst case, whatever you need. "Big-O means worst case" is wrong. Big-O is a kind of bound; worst case is a kind of input.

Take linear search for a value in an unsorted array of size `n`:

- **Best case:** the value is at index 0. One comparison. Θ(1).
- **Worst case:** the value is absent or last. `n` comparisons. Θ(n).
- **Average case:** assuming the value is present and equally likely anywhere, about `n/2` comparisons. Θ(n).

By default, when someone asks "what is the complexity," they mean the **worst case**, because that is the guarantee you can actually rely on. Best case is rarely interesting (any algorithm gets lucky sometimes). Average case requires assumptions about the input distribution, which is why we quote it less often and always state the assumption.

## Analyzing loops

Loops are where Big-O is concrete and countable. A few recipes cover almost everything you will meet.

**Single loop, fixed step.** Runs `n` times, constant work inside. O(n).

```cpp
for (int i = 0; i < n; i++)
    sum += a[i];                 // O(n)
```

**Sequential loops — add, then take the max.** Two loops one after another are O(n) + O(n) = O(n). A loop followed by a nested loop is O(n) + O(n²), and the sum collapses to the larger term: O(n²). You add sequential blocks, then keep the dominant one.

```cpp
for (int i = 0; i < n; i++) { ... }          // O(n)
for (int i = 0; i < n; i++)                  // O(n^2)
    for (int j = 0; j < n; j++) { ... }
// total: O(n) + O(n^2) = O(n^2)
```

**Nested independent loops — multiply.** The inner loop runs fully for each outer step.

```cpp
for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
        ...                      // O(n * m), or O(n^2) when m = n
```

**Triangular loop.** The inner loop's length depends on the outer index. The work is `n + (n-1) + ... + 1 = n(n+1)/2`, which is Θ(n²). The triangle is half the square, but half is a constant factor, so it does not change the class.

```cpp
for (int i = 0; i < n; i++)
    for (int j = i; j < n; j++)
        ...                      // O(n^2)
```

**Multiplicative step — logarithmic.** When the loop variable multiplies or divides by a constant, the count is how many times you can do that before crossing `n`, which is `log n`.

```cpp
for (int i = 1; i < n; i *= 2)
    ...                          // O(log n)
```

**Linearithmic pattern.** A halving outer loop with a linear inner loop gives O(n log n). You will see this shape constantly: the outer structure splits or halves (`log n` levels), and each level does O(n) total work. Merge sort is the canonical example.

```cpp
for (int i = 1; i < n; i *= 2)   // log n iterations
    for (int j = 0; j < n; j++)  // n each
        ...                      // O(n log n)
```

Two nested halving loops give O(log² n). Recognizing these patterns by shape is faster than deriving from scratch every time.

## Analyzing recursion

A recursive function's cost is described by a **recurrence relation**: `T(n)` written in terms of `T` on smaller inputs, plus the non-recursive work done in the current call. Two methods turn a recurrence into a closed-form complexity: unrolling it, and drawing the recursion tree.

The first rule: account for the work *outside* the recursive calls. A call that does O(1) of its own work and recurses once is very different from one that does O(n) of its own work. Forgetting the per-call work is the number-one mistake here.

### Common recurrences and their answers

| Recurrence | Closed form | Shape it describes |
|---|---|---|
| `T(n) = T(n−1) + O(1)` | Θ(n) | Linear recursion, constant work per frame (factorial, sum) |
| `T(n) = T(n−1) + O(n)` | Θ(n²) | Linear recursion, linear work per frame |
| `T(n) = 2T(n−1) + O(1)` | Θ(2ⁿ) | Two calls, shrink by one (naive subsets, Hanoi) |
| `T(n) = T(n/2) + O(1)` | Θ(log n) | Halve and do constant work (binary search) |
| `T(n) = T(n/2) + O(n)` | Θ(n) | Halve, linear work (sum of geometric series) |
| `T(n) = 2T(n/2) + O(1)` | Θ(n) | Two halves, constant combine |
| `T(n) = 2T(n/2) + O(n)` | Θ(n log n) | Two halves, linear combine (merge sort) |

Notice `2T(n/2)` means **two** subproblems of half the size, not one. Counting it as a single call is a frequent error and gives the wrong answer.

### The recursion-tree method

To see *why* `T(n) = 2T(n/2) + O(n)` is Θ(n log n), draw the tree of calls and sum the work level by level.

```
Level 0:                 n                      work = n
Level 1:          n/2          n/2              work = n/2 + n/2 = n
Level 2:      n/4    n/4    n/4    n/4          work = 4 · n/4   = n
   ...
Level k:   ... (2^k nodes of size n/2^k) ...    work = n
```

Each level does O(n) total work (the subproblems halve in size but double in number, so the per-level total stays `n`). The recursion stops when the subproblem size hits 1, which takes `log₂ n` levels. Total work = work-per-level × number-of-levels = n × log n = Θ(n log n).

The same picture explains the exponential cases. For `T(n) = 2T(n−1) + O(1)`, each level doubles the number of nodes but the size only shrinks by one, so the tree has `n` levels and `2ⁿ` leaves: Θ(2ⁿ). That is exactly why naive recursive Fibonacci is so slow, and why memoization (covered in the recursion materials and again in DP) collapses it back to O(n).

### Unrolling

For the simple linear cases you can just expand:

```
T(n) = T(n−1) + c
     = T(n−2) + c + c
     = T(n−3) + c + c + c
     ...
     = T(0) + n·c
     = Θ(n)
```

Same technique on `T(n) = T(n−1) + n` gives `n + (n−1) + ... + 1 = Θ(n²)`.

## The Master Theorem

For divide-and-conquer recurrences of the form

```
T(n) = a · T(n/b) + f(n)        with a ≥ 1, b > 1
```

where `a` is the number of subproblems, `n/b` is the subproblem size, and `f(n)` is the work to split and combine, the Master Theorem reads off the answer by comparing `f(n)` against `n^(log_b a)`. Call that threshold exponent `c = log_b a`.

There are three cases:

1. **`f(n)` grows slower** than `n^c` (specifically `f(n) = O(n^(c−ε))` for some ε > 0): the leaves dominate. **T(n) = Θ(n^c).**
2. **`f(n)` grows at the same rate**, `f(n) = Θ(n^c)`: every level costs the same, and there are `log n` levels. **T(n) = Θ(n^c · log n).**
3. **`f(n)` grows faster** than `n^c` (with a regularity condition): the root dominates. **T(n) = Θ(f(n)).**

Worked examples:

- **Merge sort:** `T(n) = 2T(n/2) + Θ(n)`. Here `a=2, b=2`, so `c = log₂ 2 = 1`, and `f(n) = Θ(n) = Θ(n¹)`. Case 2. **Θ(n log n).**
- **Binary search:** `T(n) = T(n/2) + Θ(1)`. Here `a=1, b=2`, so `c = log₂ 1 = 0`, and `f(n) = Θ(1) = Θ(n⁰)`. Case 2. **Θ(log n).**
- **Naive recursive matrix-pair traversal / Karatsuba-style splits:** `T(n) = 4T(n/2) + Θ(n)` gives `c = log₂ 4 = 2`, and `f(n) = Θ(n)` grows slower than `n²`. Case 1. **Θ(n²).**

The Master Theorem only covers this specific divide-and-conquer shape with equal-sized subproblems. It says nothing about, for example, `T(n) = T(n−1) + n` (that is not a `T(n/b)` recurrence) or `T(n) = T(n/3) + T(2n/3) + n` (unequal splits). For those, fall back to the recursion tree. The full treatment, including the gaps between the three cases, lives in the Divide & Conquer track; this section is the working summary you will reach for most often.

## Amortized analysis

Sometimes a single operation is occasionally expensive but cheap on average across a sequence. Amortized analysis is how we charge for that honestly. It is the *average cost per operation over a worst-case sequence of operations*. That is different from average-case analysis, which averages over a probability distribution of inputs. Amortized makes no probabilistic assumption; it is a guarantee about any sequence.

The textbook example is the growable array (`std::vector`).

### Vector `push_back` is O(1) amortized

A `vector` stores its elements in a contiguous block of some `capacity`. While `size < capacity`, `push_back` just writes one element: O(1). When the block fills up, `push_back` has to allocate a bigger block, copy everything over, and free the old one: O(n) for that one call.

So an individual `push_back` is O(n) in the worst case. Yet we say `push_back` is O(1) amortized. Both statements are true, and reconciling them is the whole point.

The trick is the growth strategy: when the array is full, the capacity **doubles**. Suppose we do `n` pushes into an array that doubles, starting from capacity 1. The resizes happen at sizes 1, 2, 4, 8, ..., up to `n`. The total number of element copies across all resizes is

```
1 + 2 + 4 + 8 + ... + n  <  2n
```

That is a geometric series; it sums to less than `2n`. Add the `n` cheap writes themselves, and `n` pushes cost under `3n` operations total. Divide by `n` operations: under `3` per push. Constant. **Amortized O(1).**

### Why doubling, and not "grow by a fixed amount"

If instead you grew the capacity by a fixed amount each time (say +1, or +10), the resizes happen far more often, and the copy costs add up to a triangular sum:

```
grow by +1:  1 + 2 + 3 + ... + n  =  n(n+1)/2  =  Θ(n²) total
```

That is Θ(n) **per push** amortized, which is terrible. Geometric growth (×2, or ×1.5, both work) is what buys the O(1). The exact factor is implementation-defined in the standard library, but it is always geometric for this reason.

A quick way to confirm the growth with `std::vector`:

```cpp
std::vector<int> v;
size_t cap = v.capacity();
for (int i = 0; i < 1000; i++) {
    v.push_back(i);
    if (v.capacity() != cap) {           // a reallocation just happened
        cap = v.capacity();
        std::cout << "size " << v.size()
                  << " -> capacity " << cap << '\n';
    }
}
```

You will see capacity jump in a geometric pattern, not climb by one.

Two related points worth fixing in your head now:

- **`reserve(n)` does not change the asymptotic complexity** of an algorithm that fills a vector. It changes the constant factor by eliminating intermediate reallocations. Useful, but it is not a Big-O improvement.
- A reallocation **invalidates all iterators, pointers, and references** into the vector. This is a bug that haunts people across the whole course. If you hold a pointer into a vector and then `push_back`, that pointer may now dangle.

## Space complexity

Space complexity is the memory an algorithm uses as a function of `n`, analyzed with the same notation as time. Split it into two parts:

- **Total space** = input space + auxiliary space.
- **Auxiliary space** = everything the algorithm allocates *beyond* the input.

We almost always quote **auxiliary** space, because the input had to exist regardless. An in-place sort that uses a handful of temporary variables is O(1) auxiliary space even though the array it sorts is O(n); the array is the input, not the algorithm's overhead.

### The recursion stack counts

The trap that catches everyone: recursion uses memory even when it allocates nothing explicitly. Every active function call holds a **stack frame** (its parameters, local variables, and return address) on the call stack. A recursion `d` levels deep has `d` frames live at once, so it uses **O(d) auxiliary space** for the stack alone.

Recursive array reversal is the classic gotcha. It swaps in place and allocates no array, so people call it O(1) space. It is not. It recurses to depth `n/2`, so it is **O(n)** auxiliary space on the call stack. The iterative two-pointer version is genuinely O(1).

| Operation | Time | Auxiliary space |
|---|---|---|
| Reverse array, iterative two-pointer | O(n) | O(1) |
| Reverse array, recursive | O(n) | O(n) — call stack |
| Binary search, iterative | O(log n) | O(1) |
| Binary search, recursive | O(log n) | O(log n) — call stack |
| Merge sort | O(n log n) | O(n) — merge buffer |
| Quicksort (in-place) | O(n log n) avg | O(log n) avg — recursion |

A second trap specific to C++: passing a large object **by value** into a recursive function copies it into every frame. A `vector` passed by value into a recursion of depth `d` costs O(n·d) time *and* space in copies alone. Pass by `const&` (or `&` when you mutate) so each frame shares the one object. The same goes for `string` and for indexing into a string with positions rather than calling `substr`, which copies.

Default stack size is typically 1–8 MB, which translates to a recursion depth limit somewhere around 10⁵ to 10⁶ frames before you overflow. For deeper recursion you convert to an explicit stack on the heap, which moves the space to O(d) heap instead of call stack and dodges the overflow.

## Reading constraints to pick a target

Before writing a line of code, look at the input bounds. They telegraph the intended complexity. This is one of the most useful interview and contest habits there is.

| Constraint on `n` | Affordable complexity | Typical technique |
|---|---|---|
| n ≤ 12 | O(n!) | Permutations, brute-force all orderings |
| n ≤ 20–25 | O(2ⁿ) | Subsets, bitmask, backtracking |
| n ≤ 500 | O(n³) | Triple loops, Floyd-Warshall, some DP |
| n ≤ 5,000 | O(n²) | Nested loops, basic DP |
| n ≤ 10⁶ | O(n) or O(n log n) | Single pass, sort, sliding window, hashing |
| n ≤ 10⁹ | O(log n) or O(√n) | Binary search on the answer, math, sieve |
| n ≤ 10¹⁸ | O(log n) or O(1) | Closed-form math, fast exponentiation |

A rough rule of thumb for time limits: assume the machine does on the order of 10⁸ simple operations per second in a tight loop. If `n = 10⁶` and you are eyeing an O(n²) solution, that is 10¹² operations, far too slow. The constraint is telling you to find something better.

## Cheat sheet: growth classes

Ordered from fastest-growing (worst) at the bottom to slowest-growing (best) at the top. Memorize this ladder; you will refer to it constantly.

| Notation | Name | `n = 1,000` | `n = 1,000,000` | Example |
|---|---|---|---|---|
| O(1) | Constant | 1 | 1 | Array index, hash lookup |
| O(log n) | Logarithmic | ~10 | ~20 | Binary search |
| O(√n) | Root | ~32 | 1,000 | Primality test, sqrt-decomposition |
| O(n) | Linear | 1,000 | 1,000,000 | Single scan |
| O(n log n) | Linearithmic | ~10,000 | ~2×10⁷ | Merge sort, heapsort |
| O(n²) | Quadratic | 10⁶ | 10¹² | Nested loops, bubble sort |
| O(n³) | Cubic | 10⁹ | 10¹⁸ | Triple loops, naive matrix multiply |
| O(2ⁿ) | Exponential | astronomically large | — | Subsets, naive Fibonacci |
| O(n!) | Factorial | beyond astronomical | — | Permutations, brute-force TSP |

The ordering, compactly:

```
O(1) < O(log n) < O(√n) < O(n) < O(n log n) < O(n²) < O(n³) < O(2ⁿ) < O(n!)
```

## Cheat sheet: data-structure operations

Time complexity of core operations. "Average" assumes good hashing or balanced/random structure; "worst" is the pathological case. These are the numbers behind every "use a hash map here" decision you will make.

| Structure | Access | Search | Insert | Delete | Notes |
|---|---|---|---|---|---|
| Array / `std::vector` (by index) | O(1) | O(n) | O(n)* | O(n) | *push_back is O(1) amortized; insert/erase in the middle is O(n) |
| Dynamic array, push_back/pop_back | — | — | O(1) amortized | O(1) | End operations only |
| Singly linked list | O(n) | O(n) | O(1)** | O(1)** | **O(1) given the node/position; finding it is O(n) |
| Doubly linked list | O(n) | O(n) | O(1)** | O(1)** | O(1) at a known node; bidirectional |
| Stack (`std::stack`) | — | — | O(1) | O(1) | push / pop / top |
| Queue (`std::queue`) | — | — | O(1) | O(1) | enqueue / dequeue |
| Deque (`std::deque`) | O(1) | O(n) | O(1) | O(1) | Both ends O(1); index O(1) |
| Hash table (`unordered_map/set`) | — | O(1) avg, O(n) worst | O(1) avg, O(n) worst | O(1) avg, O(n) worst | Worst case is many collisions |
| Balanced BST (`map/set`, red-black) | — | O(log n) | O(log n) | O(log n) | Keeps keys ordered |
| Binary heap (`priority_queue`) | O(1) find-min/max | O(n) | O(log n) | O(log n) | Top is O(1); push/pop are O(log n) |
| Trie (m = key length) | — | O(m) | O(m) | O(m) | Independent of the number of keys |
| Union-Find (with path compression + union by rank) | — | ~O(α(n)) | — | — | α is the inverse Ackermann function, effectively constant |

Space for all of these is O(n) in the number of elements stored (a trie is O(total characters across keys)).

A few decisions these numbers drive:

- **Need fast lookup by key, do not care about order?** Hash table, O(1) average. **Need keys sorted, or range queries?** Balanced BST, O(log n).
- **Inserting/removing only at the ends?** A `vector` (back) or `deque` (both ends) beats a linked list in practice because of cache locality, even though both are O(1).
- **Repeatedly pulling the smallest/largest?** A heap gives O(log n) per operation; do not sort the whole thing each time.

## Cheat sheet: sorting algorithms

The complete picture for every comparison sort and the linear-time integer sorts covered in the Sorting track. "Stable" means equal elements keep their original relative order.

| Algorithm | Best | Average | Worst | Space (aux) | Stable | Notes |
|---|---|---|---|---|---|---|
| Selection sort | O(n²) | O(n²) | O(n²) | O(1) | No | Always n²; minimal swaps (O(n) swaps) |
| Insertion sort | O(n) | O(n²) | O(n²) | O(1) | Yes | Fast on nearly-sorted input; good for tiny arrays |
| Bubble sort | O(n) | O(n²) | O(n²) | O(1) | Yes | Best O(n) only with an early-exit flag; teaching tool, not for real use |
| Merge sort | O(n log n) | O(n log n) | O(n log n) | O(n) | Yes | Predictable; the standard stable sort; needs a buffer |
| Quicksort | O(n log n) | O(n log n) | O(n²) | O(log n) | No | Worst case on bad pivots; fast in practice; in-place |
| Heapsort | O(n log n) | O(n log n) | O(n log n) | O(1) | No | Guaranteed n log n, in-place, but poor cache behavior |
| Counting sort | O(n + k) | O(n + k) | O(n + k) | O(n + k) | Yes | k = value range; only for small-integer keys |
| Radix sort | O(d·(n + k)) | O(d·(n + k)) | O(d·(n + k)) | O(n + k) | Yes | d = number of digits, k = base; integers/fixed-length keys |

Reading the table:

- **Selection sort is O(n²) in every case**, even best. It does not get faster on sorted input, unlike insertion. Its one virtue is doing only O(n) swaps, which matters when a swap is expensive.
- **Insertion sort hits O(n) on already-sorted data** and is genuinely the right choice for very small or nearly-sorted arrays. Real library sorts switch to it below a size threshold.
- **Quicksort's O(n²) worst case** comes from consistently bad pivots (for example, always picking the first element on already-sorted input). Randomized or median-of-three pivots make that case vanishingly unlikely, which is why quicksort is the usual default despite the scary worst case.
- **Merge sort and heapsort both guarantee O(n log n)**. Merge sort is stable but needs O(n) extra space; heapsort is in-place but unstable and cache-unfriendly. Pick based on whether you need stability or tight memory.
- **Counting and radix sort beat the O(n log n) comparison-sort lower bound** because they do not compare elements; they exploit the structure of integer keys. They only apply when keys are integers (or fixed-length) in a bounded range. The `k` and `d` terms are doing real work in those complexities; ignore them and the analysis is a lie.

The lower bound worth remembering: any sort that works purely by **comparing** elements is Ω(n log n) in the worst case. You cannot do better than n log n with comparisons alone. To go faster, you have to stop comparing and start exploiting the keys, which is exactly what counting and radix sort do.

## Common mistakes

A checklist of the errors that show up over and over. Most lost points in interviews trace back to one of these.

- **"Big-O means worst case."** No. O/Ω/Θ are bounds; best/worst/average are cases. They combine freely. You can state a Θ bound on the best case.
- **Treating O as a tight bound.** O(n) is *also* O(n²), correctly but uselessly. Use Θ when you mean "exactly this."
- **Adding sequential complexities instead of taking the max.** O(n) followed by O(n²) is O(n²), not O(n² + n). Add the blocks, keep the dominant term.
- **Forgetting the recursion stack in space analysis.** Recursive in-place reverse is O(n) space, not O(1). Depth-`d` recursion is O(d) auxiliary space no matter what.
- **Ignoring per-call work when building a recurrence.** `T(n) = 2T(n/2) + O(n)` and `T(n) = 2T(n/2) + O(1)` are O(n log n) and O(n) respectively. The combine cost decides it.
- **Miscounting the branching factor.** `2T(n/2)` is two subproblems, not one. Count the recursive calls.
- **Confusing amortized with average-case.** Amortized is a guarantee over any worst-case sequence; average-case assumes a distribution. A single `push_back` can still be O(n); amortized speaks to the sequence.
- **Thinking `reserve()` changes the Big-O.** It changes the constant by avoiding reallocations. The algorithm's complexity class is unchanged.
- **Passing big objects by value into recursion.** A `vector` or `string` copied into every frame is a silent O(n·depth) blowup. Pass by reference. Index into strings instead of calling `substr` in a loop, which is O(n) per call and turns a linear scan into O(n²).
- **Counting lines of code instead of operations as a function of `n`.** A three-line function with a hidden O(n) library call is not O(1).

When in doubt, fall back to first principles: write the recurrence or count the loop iterations, draw the tree if you need to, sum the work, drop constants and lower-order terms. Every result in the tables above comes from exactly that process.
