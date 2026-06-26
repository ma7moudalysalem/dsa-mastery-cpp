# Projects & Capstones

These are the build-it-yourself projects for *Data Structures & Algorithms in C++ — From Fundamentals to Interview-Ready*. Solving problems on a judge teaches you to recognize patterns under pressure. Building real software teaches you something the judge can't: how these structures behave when they have to live together, hold state, and survive contact with messy input. Both matter. The problem bank trains the reflex; the projects make it stick.

There are six. Each one unlocks the week after its prerequisite topics are taught, so you're never asked to build something on top of material you haven't seen. Every project is plain C++17, compiles standalone with no external dependencies, and is validated the way everything in this repo is validated:

```bash
g++ -std=c++17 main.cpp -o app
./app
```

Tests are inline `<cassert>` harnesses plus the debug methods you've been writing all along (`debug_to_string()`, `debug_verify_invariants()`, and friends). No framework, no setup. If `main()` returns 0, your asserts passed.

## How to use this page

Each project lists five things: the **goal** (what you're building and why it's worth building), the **structures and algorithms it exercises**, the **week it unlocks**, the **milestones** (build it in this order — each milestone compiles and passes its own tests before you move on), and **stretch goals** for when you want to push past the baseline.

Read the milestones as a contract with yourself. Milestone 1 should compile and pass before you write a line of milestone 2. The whole point of staging them is that you're never debugging more than one new idea at a time.

## What counts for the certificate

You need **Project 1 or Project 2** (an early integration project, due once you've seen linked lists and stacks) **and the Capstone, Project 6**. Each must come with a passing `<cassert>` harness and a short README of your own describing how to build and run it.

Projects 3, 4, and 5 are optional but strongly recommended. Finishing any two of them, on top of the required pair, earns completion *with Distinction*. They're also the projects most worth talking about in an interview, because each one is a small system rather than a single function.

| # | Project | Unlocks after | Core topics | Required? |
|---|---------|---------------|-------------|-----------|
| 1 | LRU + LFU Cache Library | Week 5 | Hashing, doubly linked list, amortized analysis | One of {1, 2} |
| 2 | Expression Evaluator & Calculator | Week 6 | Stacks, recursion, parsing, strings | One of {1, 2} |
| 3 | Maze & Path-Finder Visualizer | Week 13 | Graphs, BFS, Dijkstra, A*, heaps | Distinction |
| 4 | Key-Value Store with Trie Autocomplete | Week 11 | Hashing, tries, heaps / top-K | Distinction |
| 5 | Sparse Matrix Engine | Week 7 | Dynamic arrays, hashing, sorting, complexity | Distinction |
| 6 | Mini Search & Recommendation Engine | Week 16 | Everything | Yes |

---

## Project 1 — LRU + LFU Cache Library

**Unlocks after Week 5** (hashing in Week 4, doubly linked lists in Week 5)

### Goal

Build a generic, templated cache `Cache<K, V>` with O(1) `get` and `put`, and two interchangeable eviction policies: least-recently-used and least-frequently-used. This is the project where the hashmap-plus-linked-list trick finally clicks. You've solved LRU Cache (146) on the judge as a single class; here you build it as a small library you'd actually be willing to reuse, with the eviction strategy pulled out so you can swap LRU for LFU without touching the lookup path.

The reason caches show up in interviews so often is that the naive answer (scan to find the oldest entry) is O(n), and getting to O(1) forces you to combine two structures so each covers the other's weakness. The hashmap gives you O(1) lookup but no notion of order. The doubly linked list gives you O(1) move-to-front and O(1) removal but no lookup. Wire them together and you have both.

### Structures and algorithms exercised

- Hashing: `std::unordered_map` from key to node pointer
- Doubly linked list with sentinel (dummy head/tail) nodes
- Pointer surgery: unlink and relink a node in O(1)
- For LFU: a map from frequency to a list of nodes at that frequency, plus a tracked minimum frequency
- Amortized analysis: argue why every operation is O(1)

### Milestones

1. **Doubly linked list with sentinels.** A list that uses dummy head and tail nodes so you never special-case the empty list or the ends. Implement `push_front`, `remove(node)`, and `move_to_front(node)`, each O(1) and pointer-clean. Write `debug_to_string()` and an assert harness that hammers insert/remove in random order and checks the forward and backward chains stay consistent.
2. **LRU cache.** `Cache<K, V>` with a fixed capacity. `get` returns the value and marks the key most-recently-used; `put` inserts or updates and evicts the least-recently-used key when full. Lookups go through `unordered_map<K, Node*>`; recency is the list order. Test: a known access sequence with a known eviction trace (the classic 146 example is a good fixture).
3. **LFU cache.** Same interface, different policy. Track each key's access count, keep one list per frequency, and maintain `min_freq` so eviction is O(1). The subtle part is the tie-break: among keys with the lowest frequency, evict the least-recently-used, which is why each frequency bucket is itself an ordered list. Test the case the judge loves: a key that gets promoted out of the min bucket and changes which key is next to go.
4. **Policy as a choice and a test harness.** Make the eviction policy selectable (a constructor flag or a template parameter — your call) so the same `Cache` type serves both. Round out the `<cassert>` harness: capacity 1, updating an existing key, capacity 0 as a documented edge case, and a `debug_to_string()` that dumps both the map size and the list order so failures are readable.

### Stretch goals

- **TTL expiry.** Give entries a time-to-live. Expire lazily on access, and add an active sweep that purges dead entries. Decide what `get` returns for an expired-but-not-yet-swept key.
- **Thread-safe wrapper.** Wrap the cache in a type that guards every operation with a `std::mutex`. Note in your README where the lock granularity would hurt under contention.
- **Strategy-pattern policy.** Refactor eviction into a policy object with `on_access`, `on_insert`, and `evict` hooks, so adding a new policy (FIFO, random, MRU) means writing one class and changing nothing else.

---

## Project 2 — Expression Evaluator & Mini Calculator

**Unlocks after Week 6** (stacks and queues week)

### Goal

Parse and evaluate arithmetic expressions: the four operators plus exponent (`^`), parentheses, unary minus, and named variables. Input like `3 + 4 * 2`, `-(2 ^ 3) + 1`, or `x = 5; x * x + 1` goes in; the right number comes out, with operator precedence and associativity respected.

This is the project that turns the Basic Calculator problems (224, 227) from "memorize the stack trick" into "I understand what a parser is doing." You'll build it twice, two different ways, because seeing the same grammar handled by an explicit stack and then by recursion is one of the cleanest illustrations of the recursion-iteration duality you learned in Week 2.

### Structures and algorithms exercised

- Stacks: an operator stack and an operand stack
- The shunting-yard algorithm for infix-to-postfix conversion
- Postfix (reverse Polish) evaluation with a single stack
- Recursion: a recursive-descent parser that mirrors the grammar
- String processing: tokenization, handling whitespace and multi-digit numbers
- Trees: an abstract syntax tree as the output of the recursive parser

### Milestones

1. **Tokenizer.** Turn a raw string into a vector of tokens: numbers, operators, parentheses, identifiers. Handle whitespace, multi-digit and decimal numbers, and the distinction between binary minus (`a - b`) and unary minus (`-a`), which you'll resolve by looking at the previous token. Test against strings with awkward spacing and back-to-back operators.
2. **Shunting-yard: infix to postfix.** Convert the token stream to postfix using an operator stack, encoding precedence (`^` above `*` `/` above `+` `-`) and associativity (`^` is right-associative, the rest left). Test that `2 + 3 * 4` becomes `2 3 4 * +` and that `2 ^ 3 ^ 2` groups right.
3. **Postfix evaluation.** Walk the postfix output with one operand stack and produce the answer. With milestones 2 and 3 chained you have a working calculator. Test it against a table of expressions with hand-computed results, including deep parenthesization.
4. **Recursive-descent parser and AST.** Build the second path. Write `parseExpression` / `parseTerm` / `parseFactor` functions whose call structure *is* the precedence grammar, and have them build an AST of `Node` objects rather than evaluating inline. Then evaluate the tree recursively. Confirm both engines agree on the same fixture set.
5. **Variables and assignment.** Support `x = 3; y = x * 2; y + 1`. Keep a symbol table (`unordered_map<string, double>`), evaluate statements left to right, and return the value of the last one. Test that later statements see earlier bindings and that referencing an unbound variable is reported cleanly rather than crashing.

### Stretch goals

- **Functions.** Add `sin`, `cos`, `sqrt`, `max`, `min`, `gcd`. This means extending the tokenizer to recognize identifiers followed by `(`, and the parser to handle argument lists.
- **Error recovery with positions.** Report syntax errors with a line and column and a caret under the offending token, instead of failing on the first bad character.
- **Compile to bytecode.** Walk the AST once to emit a flat instruction list for a tiny stack-based virtual machine, then run that. You'll have built the front half of a real interpreter.

---

## Project 3 — Maze & Path-Finder Visualizer

**Unlocks after Week 13** (graphs and BFS in Week 12; Dijkstra in Week 13)

### Goal

Load a grid maze, find the shortest path from start to goal three different ways (BFS, Dijkstra, A*), and render the search to the console so you can *watch* each algorithm explore. The grid is a graph; that reframing is the whole lesson. Once you see the maze as nodes (cells) and edges (adjacency between open cells), the same traversals you wrote on abstract graphs apply directly.

The reason to implement all three on the same map is that the differences become physical. BFS expands in expanding rings. Dijkstra does the same on a uniform grid but reshapes around terrain costs. A* with a good heuristic drives straight at the goal and touches a fraction of the cells. Counting node expansions side by side makes "A* is Dijkstra plus a heuristic" concrete instead of a slogan.

### Structures and algorithms exercised

- Graph modeling: a grid as an implicit graph, neighbors generated on the fly
- BFS for unweighted shortest path, with parent pointers for path reconstruction
- Dijkstra with a priority queue (the binary heap from Week 10) and per-cell terrain weights
- A* with the Manhattan-distance heuristic, and a check that the heuristic is admissible
- Path reconstruction by following parent pointers back from the goal

### Milestones

1. **Grid loader and neighbor model.** Read a maze from a text file (`#` walls, `.` open, `S` start, `G` goal). Write a `neighbors(cell)` function returning the open 4-directional neighbors, and a renderer that prints the grid. This is the foundation every algorithm shares; get the coordinate math right once.
2. **BFS shortest path.** Find the shortest path on the unweighted maze with a queue and a `visited` set, recording parent pointers. Reconstruct and overlay the path on the rendered grid. Test on a maze with a known optimal length and on a maze with no path at all.
3. **Dijkstra with terrain.** Add per-cell movement costs (open `1`, mud `5`, water `10`). Run Dijkstra with a min-heap keyed on accumulated cost. On an all-`1` grid its path length must match BFS; with terrain, confirm it routes around expensive cells. This is where the heap you built in Week 10 earns its place.
4. **A\* with Manhattan heuristic.** Add `f = g + h` with `h` as Manhattan distance to the goal. Verify A* returns the same optimal cost as Dijkstra (because the heuristic is admissible) while expanding fewer nodes.
5. **Compare expansions.** Run all three on the same maze and print a table: path cost and number of nodes expanded for each. Seeing BFS and Dijkstra agree, and A* match the cost while doing less work, is the deliverable that makes this project worth presenting.

### Stretch goals

- **Diagonal movement.** Allow 8-directional moves with cost √2 for diagonals, and switch the A* heuristic to octile distance so it stays admissible.
- **Maze generation.** Generate solvable mazes with a recursive-backtracker carve or randomized Kruskal on the grid (your union-find from Week 11 fits here directly).
- **Multi-goal search.** Given several goals, find the path to the nearest one in a single search.
- **Animated export.** Write each search frame as a PPM image (trivial to emit by hand) so you can flip through the frontier growing.

---

## Project 4 — In-Memory Key-Value Store with Trie Autocomplete

**Unlocks after Week 11** (tries and union-find in Week 11; heaps / top-K in Week 10)

### Goal

A small Redis-flavored store driven by a command loop: `SET key value`, `GET key`, `DEL key`, and the interesting one, `AUTOCOMPLETE prefix`, which returns the top-K stored keys that start with that prefix, ranked by how often they've been accessed. The KV core is a hashmap. The autocomplete is a trie. The ranking is a top-K heap. Three structures you learned separately, doing one job together.

This is the project that shows why a trie beats a hashmap for prefix queries. A hashmap can answer "is this exact key present" in O(1) but can't enumerate everything under a prefix without scanning all keys. The trie walks to the prefix node in O(prefix length) and the entire subtree under it is exactly the set of completions.

### Structures and algorithms exercised

- Hashing: the `unordered_map<string, string>` backing the store
- Tries: insert, prefix lookup, and subtree collection of all words under a node
- Heaps: a size-K min-heap to keep the top-K completions by frequency
- Strings and a small command parser for the REPL

### Milestones

1. **KV store and REPL.** A hashmap-backed store with `SET`, `GET`, `DEL` driven by a read-eval-print loop that parses one command per line. Track an access count per key (you'll need it for ranking). Test the command parser against malformed input so a bad line reports an error instead of crashing.
2. **Trie insert and search.** Build a trie over the keys. On `SET`, insert the key; on `DEL`, remove it (handle the case where a deleted key's nodes are shared with a still-present key). Implement `startsWith(prefix)` to find the node where a prefix ends, or report that no key has it. Test insert/search/delete interleavings.
3. **Prefix collection.** From the prefix node, DFS the subtree to gather every complete key beneath it. Test that `AUTOCOMPLETE ca` over `{cat, car, cart, dog}` returns exactly the three `ca` keys in some order.
4. **Top-K ranking.** Rank the collected completions by access frequency and return the best K using a min-heap of size K (push, and pop when the heap exceeds K, so you keep the K largest). Break ties by lexicographic order so output is deterministic. Test that frequency changes from repeated `GET`s actually reorder the suggestions.
5. **Persistence.** Append every mutating command to a log file, and on startup replay the log to rebuild the store and the trie. Test the full cycle: run commands, restart, confirm state and access counts are restored.

### Stretch goals

- **Fuzzy autocomplete.** Also return completions within edit distance 1 of the prefix, using the edit-distance idea from Week 15's DP.
- **Eviction tie-in.** Bound the store's size and reuse Project 1's LRU policy to evict cold keys, keeping the trie in sync.
- **Ternary search tree.** Implement the autocomplete a second way with a ternary search tree and benchmark its memory against the trie on a real word list. Tries are fast but node-heavy; this makes the trade-off measurable.

---

## Project 5 — Sparse Matrix Engine

**Unlocks after Week 7** (sorting in Week 7; builds on arrays from Week 3 and hashing from Week 4)

### Goal

Most large matrices in practice are mostly zeros. Storing them densely wastes memory proportional to `rows × cols` when only the nonzeros (`nnz`) carry information. Build a `SparseMatrix` that stores only what's there, in both coordinate (COO) and compressed-sparse-row (CSR) form, and supports add, multiply, and transpose with cost that scales with `nnz` rather than the full grid.

This project is where complexity analysis stops being a homework exercise and becomes the reason the code exists. Every operation here has a sparse bound and a dense bound, and the whole point is to hit the sparse one. You'll prove your multiply is output-sensitive, then benchmark it against a dense implementation across sparsity levels and watch the crossover happen.

### Structures and algorithms exercised

- Dynamic arrays: the parallel `values` / `column-index` / `row-pointer` arrays of CSR
- Hashing: a `map<pair<int,int>, value>` for accumulating during multiply (and a reason to write a custom hash for a pair key, straight from Week 4)
- Sorting: counting sort on row indices to convert COO to CSR in linear time
- Complexity analysis: sparsity-aware bounds for every operation, stated and defended

### Milestones

1. **COO triplet store.** Represent the matrix as a list of `(row, col, value)` triplets. Implement construction, element access, and a `to_dense()` for testing against a plain 2D vector. Test round-trips: dense → COO → dense returns the original.
2. **COO to CSR.** Convert to CSR (a `values` array, a parallel `col_index` array, and a `row_ptr` array of length `rows + 1`). Build `row_ptr` with a counting sort over row indices so the conversion is O(nnz + rows), not O(nnz log nnz). Verify CSR and COO agree element-for-element.
3. **Sparse multiply.** Multiply two sparse matrices, accumulating partial products in a hashmap keyed on the output coordinate, then compacting to CSR. Test against a dense reference multiply on small random matrices so correctness is unambiguous before you chase speed.
4. **Transpose in O(nnz).** Transpose a CSR matrix in time proportional to its nonzeros using the same counting-sort idea on column indices. Test that transposing twice is the identity.
5. **Benchmark vs dense.** Generate matrices at 50%, 10%, 1%, and 0.1% density and time sparse vs dense multiply at each. Report the crossover density where sparse starts winning. This table is the payoff: it's complexity analysis you can see in milliseconds.

### Stretch goals

- **Sparse Gaussian elimination.** Solve `Ax = b` for a sparse `A`, and watch fill-in turn zeros into nonzeros as elimination proceeds.
- **Blocked multiply.** Reorganize the multiply to be cache-friendlier and measure whether it actually helps.
- **Graph adjacency as a sparse matrix.** Represent a graph's adjacency matrix in CSR and run BFS as repeated sparse matrix-vector products. The connection between linear algebra and graph traversal is one of the prettier ideas in the course.

---

## Project 6 — Capstone: Mini Search & Recommendation Engine

**Unlocks after Week 16** (dynamic programming II, greedy, and bit/math in Week 16; integrative across the whole course)

### Goal

Index a folder of text documents and answer ranked keyword queries the way a small search engine does: build an inverted index, score results with TF-IDF, support boolean queries, offer autocomplete, and recommend documents that are similar to a given one. This is the capstone because it pulls in nearly everything. The inverted index is a hashmap of posting lists. Boolean queries are sorted-list intersections. Ranking is a top-K heap. Autocomplete is the trie from Project 4. Similarity clustering is a graph with connected components. Typo tolerance is edit-distance DP. No single piece is hard now; the work is making them cooperate.

A search engine is the right capstone for a DSA course because every classic structure earns its place for a concrete reason, and you can feel the reason. Use a list instead of a hashmap for the index and queries crawl. Skip the heap and you sort the whole result set to show ten links. The structure choices are the engineering.

### Structures and algorithms exercised

- Hashing: the inverted index, a map from term to its posting list
- Sorting and two-pointer / binary-search merge: boolean query intersection over sorted posting lists
- Heaps: a top-K heap over scored documents
- Tries: query autocomplete, reusing Project 4
- Graphs: a document-similarity graph plus connected components (your union-find from Week 11) for clustering
- Dynamic programming: edit distance for typo-tolerant matching
- Binary search: locating document IDs within sorted posting lists

### Milestones

1. **Tokenizer and inverted index.** Read the corpus, tokenize and normalize each document (lowercase, strip punctuation), and build an inverted index mapping each term to a sorted list of the document IDs containing it. Test that a known term maps to exactly the right document set.
2. **Boolean queries.** Support `term1 AND term2`, `OR`, and `NOT` by intersecting, unioning, and complementing posting lists. Because the lists are sorted, intersection is a linear two-pointer merge (and you can use binary search to skip ahead when one list is much shorter). Test each operator against hand-checked results.
3. **TF-IDF ranking.** Score each matching document by term frequency times inverse document frequency, and return the top K with a size-K heap rather than sorting every match. Test that a document mentioning a rare query term outranks one that only has common terms.
4. **Autocomplete.** Drop in the trie from Project 4 so partial queries suggest completions from the indexed vocabulary, ranked by document frequency. Reusing that code here is the point: well-separated components compose.
5. **Similarity graph and clustering.** Build a graph where documents are nodes and an edge connects two documents whose shared-term overlap exceeds a threshold. Find connected components with union-find to cluster related documents, and answer "more like this" by returning a document's neighbors. Test clustering on a corpus you've seeded with two obviously distinct topics.
6. **Typo-tolerant search.** When a query term isn't in the vocabulary, find the closest indexed terms by edit distance (the Week 15 DP) and search those instead. Test that a one-character typo still finds the right documents.

### Stretch goals

- **BM25 ranking.** Replace TF-IDF with BM25 and compare result orderings on the same queries.
- **PageRank.** If your documents link to each other, build the link graph and rank by PageRank, blending it with the text score.
- **Compressed posting lists.** Store gaps between document IDs instead of the IDs themselves, then varint-encode them, and measure the index-size drop.
- **Concurrent index build.** Index documents in parallel across threads and merge the partial indexes, with attention to where the shared structures need guarding.

---

## A note on finishing

The required pair (one of Project 1 or 2, plus the Capstone) is the floor, not the target. The students who get the most out of this course build at least four. Each project is small enough to finish in the week it unlocks and substantial enough to put on a resume and talk through in an interview. When someone asks you to "tell me about something you built," a sparse matrix engine with a measured crossover point or a search engine you can explain structure by structure is a far better answer than a list of problems you solved.

Build them in order. Keep your asserts. Write the short README for each one as you go, while you still remember why you made the choices you made.
