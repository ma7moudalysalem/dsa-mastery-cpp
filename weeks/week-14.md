# Week 14 — Backtracking — Exhaustive Search with Pruning

Backtracking is one recursive template applied everywhere: make a choice, explore, then undo the choice. This week you drill it across enumeration (subsets, permutations, combinations) and constraint satisfaction (N-Queens, Sudoku, word search), with duplicate handling and pruning treated as first-class skills rather than afterthoughts. It comes right before dynamic programming on purpose, because DP is backtracking plus memoization, and you can't memoize a recursion you can't write.

Back to the [course README](../README.md). Pattern reference: [docs/patterns.md](../docs/patterns.md).

## By the end of this week

- Write the choose / explore / un-choose template from a blank file for any enumeration or constraint problem, and draw the state-space (decision) tree it walks.
- Generate subsets, combinations, and permutations correctly, including the duplicate-handling rule (sort, then skip `i > start && a[i] == a[i-1]`).
- Record a solution at a leaf by copying the path, not storing a reference to the mutable working buffer.
- Encode constraints (columns, both diagonals, row/col/box sets) for O(1) feasibility checks, and use early checks to prune dead branches.
- DFS a grid with in-place visited-marking and restore-on-backtrack, and combine a trie with grid backtracking to share prefixes across many search words.
- State a general pruning checklist (feasibility, ordering, bounding) and apply it to keep exponential searches tractable.

The week's milestone: you can write the choose/explore/un-choose template from scratch for any enumeration or constraint problem, handle duplicates correctly, and add pruning that keeps an exponential search fast enough to pass, ready to convert exhaustive recursion into memoized DP next week.

---

## Lecture 53 — Backtracking Fundamentals: Subsets, Combinations, Permutations

Every backtracking problem is the same recursion with the choices swapped out. We spend this lecture on the three canonical enumerations so the template becomes muscle memory before any constraints get involved. The mechanic that makes it backtracking and not just plain recursion is the undo: you push a choice, recurse, then pop it so the buffer is clean for the next branch.

**Objectives**

- Apply the choose/explore/un-choose template and draw the state-space (decision) tree for a small input.
- Generate subsets, combinations, and permutations, with correct duplicate handling.
- Explain why "undo the choice" is the defining mechanic, and what breaks if you forget the pop.

**Topics covered**

- The template: pick a choice, mark it taken, recurse on the rest, then unmark it. The unmark is what lets the same buffer serve every branch of the tree.
- The decision tree as the mental model. Each node is a partial solution, each edge is one choice, and the leaves are complete candidates. Runtime is roughly the number of nodes you visit.
- Subsets two ways: the include/exclude binary recursion (each element is in or out, 2^n leaves) versus the start-index loop that builds subsets in lexicographic order. Both are correct; the start-index form generalizes more cleanly to combinations.
- Combinations and combination sum: a start index stops you from reusing earlier elements and from generating the same set in a different order. Combination Sum lets you reuse an element by recursing with the same index; Combination Sum II does not.
- Permutations two ways: a `used[]` boolean array, or swap-in-place where you swap each candidate into the current position and swap it back on the way out.
- Duplicate dedup: sort the input first, then within a single recursion level skip a value equal to its predecessor with `i > start && a[i] == a[i-1]`. Sorting is what makes equal values adjacent so the skip is local.

```cpp
// Subsets via the start-index loop. Note the push_back / pop_back pairing
// around the recursive call: that pop is the "un-choose" step.
void subsets(vector<int>& a, int start, vector<int>& path,
             vector<vector<int>>& out) {
    out.push_back(path);                 // every node is a valid subset
    for (int i = start; i < (int)a.size(); ++i) {
        path.push_back(a[i]);            // choose
        subsets(a, i + 1, path, out);    // explore
        path.pop_back();                 // un-choose
    }
}
```

**Patterns**

- [Subsets / Permutations (Backtracking)](../docs/patterns.md)

**In-class problems**

- Subsets / Subsets II
- Permutations / Permutations II
- Combination Sum / Combination Sum II
- Letter Combinations of a Phone Number

---

## Lecture 54 — Backtracking on Strings & Partitions

String problems are where the "copy the path at a leaf" rule earns its keep. The path is a single buffer you mutate as you descend, so when you reach a valid solution you have to copy its current contents into the result. Store a reference and every entry in your output ends up pointing at the same empty buffer after the recursion unwinds. We also start pruning in earnest here: a cheap validity check at the top of a call kills whole subtrees before you waste time on them.

**Objectives**

- Backtrack over string-splitting and validity-checking problems.
- Record solutions at leaves by copying the path, not by storing a reference to it.
- Add early validity checks that prune dead branches before recursing.

**Topics covered**

- The path is passed by reference and mutated with `push_back` / `pop_back` (or by tracking a substring start index) around each recursive call.
- `result.push_back(path)` copies the path by value, and that copy is the point. The working buffer keeps changing as the recursion continues; the result must hold a snapshot.
- Palindrome Partitioning: try every cut position, but only recurse on a prefix that is itself a palindrome. The palindrome check is the pruning step, and it cuts most branches immediately.
- Generate Parentheses: track open and close counts. You may add `(` while opens remain, and `)` only while closes used is below opens. Those two constraints alone keep you inside the set of valid strings, so no validity filter at the leaf is needed.
- Restore IP Addresses: split into four segments, pruning any segment that is empty, longer than three digits, has a leading zero, or exceeds 255. Segment-validity pruning is what keeps this from blowing up.
- Word Break II: backtrack over prefixes that are dictionary words, building each full sentence. This is also the natural place to notice repeated subproblems, which is the memoization handoff to next week.

**Patterns**

- [Subsets / Permutations (Backtracking)](../docs/patterns.md)

**In-class problems**

- Generate Parentheses
- Palindrome Partitioning
- Restore IP Addresses
- Word Break II

---

## Lecture 55 — Constraint Backtracking: N-Queens & Sudoku

Constraint problems are where pruning stops being an optimization and becomes the whole game. A naive N-Queens that places a queen anywhere and checks validity at the end is hopeless past about eight rows. Encode the constraints so a placement is an O(1) check and an O(1) update, and the same search runs in milliseconds. The lesson of this lecture is that strong, early pruning is the difference between timing out and passing.

**Objectives**

- Encode column and both-diagonal constraints for O(1) feasibility checks.
- Solve Sudoku with constraint sets and an MRV-style cell choice (fill the most constrained cell first).
- Show concretely why early pruning is what makes these searches finish.

**Topics covered**

- N-Queens: place one queen per row, so you only track which columns and diagonals are occupied. The two diagonal families are indexed by `r + c` (anti-diagonal, range `0..2n-2`) and `r - c + n` (main diagonal, shifted to stay non-negative).
- Occupancy stored as three `bitset`s or `vector<bool>`s: columns, `r + c`, and `r - c + n`. Set on choose, clear on un-choose. A bitmask version of the same idea is teased here and built fully in Week 16.
- Sudoku solver: keep a constraint set per row, per column, and per 3x3 box. A digit is legal in a cell only if it is absent from all three. Place it, mark all three, recurse, and unmark on backtrack.
- Feasibility checks and bounding as pruning. Checking legality before you descend (rather than at the leaf) prunes the subtree at the earliest possible point, which is the cheapest place to prune.
- MRV (minimum remaining values): pick the empty cell with the fewest legal digits next. Choosing the most constrained cell first collapses the branching factor near the root and is the single biggest speedup for Sudoku.
- Counting versus listing: N-Queens II only needs the number of solutions, so you increment a counter at each leaf instead of copying a board. Same search, cheaper leaves.

**Patterns**

- [Subsets / Permutations (Backtracking)](../docs/patterns.md)

**In-class problems**

- N-Queens
- N-Queens II (count solutions)
- Sudoku Solver
- Valid Sudoku (constraint-set warmup)

---

## Lecture 56 — Grid Backtracking & Pruning Mastery (Word Search) + Trie Synthesis

The week closes by combining tools. Grid DFS with backtracking introduces the in-place visited trick: mark a cell with a sentinel as you enter, restore it as you leave, no separate visited array needed. Then Word Search II ties the week back to the trie from Week 13. Searching a board for hundreds of words one at a time is wasteful because they share prefixes; put the words in a trie and a single DFS walks every shared prefix once. We finish with a general pruning checklist you can carry into any search problem.

**Objectives**

- DFS a grid with in-place visited-marking and restore-on-backtrack.
- Combine a trie with grid backtracking to share prefixes across many search words.
- State and apply a general pruning checklist: feasibility, ordering, and bounding.

**Topics covered**

- Word Search: at each step try the four neighbors, but only step onto a cell that matches the next character and has not been used on the current path. Mutate the cell to a sentinel (such as `#`) on entry and restore the original character on return.
- Why a separate visited array is avoidable: the sentinel both blocks revisits and is undone by the same backtracking that undoes every other choice, so the grid is exactly as you found it once the call returns.
- Word Search II: build a trie of all search words, then DFS the grid once, advancing through the trie by edges. A board path that has no matching trie edge is dead immediately, so the trie itself does the pruning.
- The payoff: brute force is O(W · cells · 4^L) where you re-walk the board for each of W words of length L. The trie turns that into one shared prefix walk over the board, paying for each shared prefix a single time.
- A general pruning checklist. Feasibility: can this partial solution still become valid? Ordering: choose the most constrained option first to shrink branching early. Bounding: if a cheap bound says no branch below here can beat the current best, stop.

**Patterns**

- [Subsets / Permutations (Backtracking)](../docs/patterns.md)
- [Trie Traversal](../docs/patterns.md)

**In-class problems**

- Word Search
- Word Search II (trie + backtracking)
- Number of Islands (DFS framing)
- Combinations review under a time limit

---

## Homework

Spread these across the week rather than batching them. The warmups confirm the template is in your hands, the core set is the week's real work, and the challenges are the ones worth fighting before you look anything up. Two of the challenges (Sudoku Solver, Word Search II) are the kind of problem that separates people who can write backtracking from people who can write backtracking that finishes in time.

### Warmup

- Subsets
- Combinations
- Letter Combinations of a Phone Number

### Core

- Permutations II
- Combination Sum II
- Generate Parentheses
- Palindrome Partitioning
- Restore IP Addresses
- Word Search

### Challenge

- N-Queens
- Sudoku Solver
- Word Search II

---

## Before next week

- You can write the choose/explore/un-choose template from a blank file, with the `push_back` / `pop_back` (or swap / swap-back) pairing correct around the recursive call.
- You handle duplicates by sorting first and skipping `i > start && a[i] == a[i-1]`, and you can say why sorting is what makes that skip work.
- You copy the path into the result at a leaf, and you can explain what goes wrong if you store a reference instead.
- N-Queens uses O(1) column and diagonal checks via `r + c` and `r - c + n`, and you can explain why those two expressions identify the diagonals.
- Word Search restores the grid on backtrack, and you can articulate the trie-plus-DFS idea behind Word Search II even if you needed help finishing it.
- You can state the feasibility / ordering / bounding pruning checklist from memory.
- Skim the [pattern reference](../docs/patterns.md) entries for backtracking and trie traversal before Week 15, where memoization turns these exhaustive searches into dynamic programming.

---

Back to the [course README](../README.md) · Pattern reference: [docs/patterns.md](../docs/patterns.md)
