# Week 4 — Hashing, Cyclic Sort & Merge Intervals

This is the payoff week for the array and string track. Hashing turns the O(n^2) scans you fought through last week into O(n) for membership, counting, and grouping. You build a chaining hash table by hand, learn where `unordered_map` and `unordered_set` quietly bite you, then add two more array patterns you'll own for the rest of the course: cyclic sort and merge intervals.

By the end of the week you've finished the contiguous-memory and hashing foundation, and you're ready to move on to pointer-based structures.

## By the end of this week

- Reach for hashing on instinct when a problem asks about membership, counting, deduplication, or grouping, and turn those into O(n) instead of O(n^2).
- Explain why collisions are inevitable, resolve them with separate chaining, and reason about load factor and rehashing. Implement a chaining hash table from scratch.
- State the honest cost of hashing: expected and amortized O(1), but O(n) worst case under adversarial collisions.
- Choose deliberately between `unordered_map`/`unordered_set` (hash, average O(1), no order) and `map`/`set` (balanced tree, O(log n), sorted), and know when each is the right call.
- Avoid the `operator[]` default-insert bug, and supply a custom hash for `pair`, `tuple`, or `struct` keys.
- Apply cyclic sort to place values into their home indices in O(n) time and O(1) space when the values are a permutation of `1..n`, then read off missing, duplicate, or first-missing-positive in one scan.
- Sort intervals by start and sweep once to merge overlapping ranges, and handle the insert-interval and meeting-rooms variants.

Patterns this week: [hashing for dedup/count/group](../docs/patterns.md), [cyclic sort](../docs/patterns.md), and [merge intervals](../docs/patterns.md).

---

## Lecture 13 — Hashing I: Hash Functions, Collisions & Build a Hash Table

The single most useful trade in interview problems: spend O(n) space to buy O(1) lookup. Before you reach for `unordered_map`, you build the thing yourself so you know exactly what it costs and where it breaks.

### Objectives

- Explain what a hash function does, why collisions are inevitable, and how to resolve them with separate chaining (with open addressing covered conceptually for contrast).
- Implement a chaining hash table by hand and reason about load factor and rehashing.
- State that hash operations are expected and amortized O(1), but O(n) in the worst case under adversarial collisions.

### Topics

- A hash function maps a key to a bucket index. Two different keys can land in the same bucket. The pigeonhole principle guarantees collisions once you have more keys than buckets, and the birthday paradox tells you they show up far sooner than intuition expects.
- Separate chaining: each bucket holds a list (or vector) of entries. Collisions append to the bucket's list.
- Open addressing covered conceptually as the alternative: linear probing, quadratic probing, and double hashing all store entries directly in the table and probe for the next free slot.
- Load factor `alpha = n / buckets` is what drives performance. When it climbs past a threshold you rehash into a larger table. Expected cost is O(1); worst case, when everything collides into one bucket, degrades to O(n).
- When hashing wins: membership, deduplication, counting, and grouping, all in O(n). When it loses: anything that needs ordering, range queries, or sorted iteration, which is where a balanced tree (`map`/`set`) is the right tool instead.
- The build: a hand-rolled chaining table as `vector<list<pair<K, V>>>`, with a debug method that prints the bucket distribution so you can *see* the load factor and the collisions.

### Patterns

- [Hashing for dedup/count/group](../docs/patterns.md)

### In-class problems

- Two Sum
- Contains Duplicate
- Design HashMap (build a hash table by hand)
- First Unique Character in a String

---

## Lecture 14 — Hashing II: `unordered_map`/`set`, Custom Keys & Pitfalls

Now that you've built one, switch to the STL version and treat it as the professional default. This lecture is mostly about the traps, because the STL hash containers have a few that cost people real bugs.

### Objectives

- Choose deliberately between `unordered_map`/`unordered_set` (hash, average O(1), unordered) and `map`/`set` (balanced tree, O(log n), sorted).
- Avoid the `operator[]` default-insert bug, and use `find`, `count`, or `contains` for pure lookups.
- Supply a custom hash for `pair`, `tuple`, or `struct` keys, and tune with `reserve` and `max_load_factor`.

### Topics

- `unordered_map`/`set` versus `map`/`set`: average O(1) versus O(log n), and no iteration order from the unordered versions. That order is not just unspecified, it changes on rehash, so never rely on it.
- The `operator[]` default-insert bug: indexing an `unordered_map` with a key that isn't present *inserts* it with a value-initialized value. That silently mutates the container during a read. For pure lookups use `.find()`, `.count()`, or (C++20) `.contains()`.
- Custom keys need a `std::hash` specialization or a hash functor passed to the container. `pair` and `tuple` have no standard hash, so a map keyed on coordinates won't compile until you provide one.
- `reserve(n)` and `max_load_factor` cut rehashing when you know roughly how many elements you'll insert. Useful detail: in `unordered_map`, references and pointers to elements stay valid across a rehash; only iterators are invalidated. That's the opposite of `vector`, where a reallocation invalidates everything.
- When the key space is small and bounded, skip the hash container entirely. An `int[26]` indexed by letter, or an `int[128]` indexed by ASCII, is faster and simpler than `unordered_map<char, int>`.

### Patterns

- [Hashing for dedup/count/group](../docs/patterns.md)

### In-class problems

- Group Anagrams
- Top K Frequent Elements
- Longest Consecutive Sequence
- Isomorphic Strings

---

## Lecture 15 — Cyclic Sort & Index-as-Hash on Values in [1..n]

A pattern that looks like a trick the first time you see it and like the obvious move every time after. When your values are a permutation of `1..n`, the array index *is* a hash. You don't need a hash table at all.

### Objectives

- Apply cyclic sort to place each value at its correct index in O(n) time and O(1) space when the values are a known permutation of `1..n`.
- Use the placed array to find the missing number, the duplicate, or the first missing positive in a single linear scan.
- Write the swap condition correctly so the loop always terminates.

### Topics

- The mechanism: while `a[i]` is not sitting at index `a[i] - 1`, swap it to where it belongs. After one pass every value that can be home is home, and a single scan finds the first index that's wrong.
- The precondition: this only works when values fall in `[1..n]` (or `[0..n-1]`). Outside that range, the index-as-hash trick doesn't apply.
- The swap condition is the part people get wrong. You must check the target slot doesn't already hold the correct value, or you spin forever swapping two equal values back and forth: `while (a[i] != i + 1 && a[i] != a[a[i] - 1])`.
- In-place swaps with `std::swap`, no extra memory. Worth contrasting with the XOR-based missing-number trick, which solves the single-missing case in O(1) space a different way.

### Patterns

- [Cyclic sort](../docs/patterns.md)

### In-class problems

- Missing Number
- Find All Numbers Disappeared in an Array
- Find the Duplicate Number
- First Missing Positive

---

## Lecture 16 — Merge Intervals & Arrays/Strings/Hashing Workshop

The last owned array pattern of the block, then a mixed drill that pulls the whole week together before the course pivots to pointer-based structures.

### Objectives

- Sort intervals by start and sweep once to merge overlapping ranges, choosing `<` versus `<=` consistently and deliberately.
- Solve the insert-interval and minimum-meeting-rooms variants.
- Consolidate the week's patterns in a mixed problem drill before moving on.

### Topics

- Merge intervals: sort by start time, then walk the list keeping a "current" interval. While the next interval's start is within the current end (`next.start <= cur.end`), extend the current end; otherwise, close out the current interval and start a new one.
- The variants worth knowing: insert interval into an already-sorted list, interval-list intersection, and meeting rooms (minimum number of rooms via a sweep, with a heap-based approach previewed for next time).
- The mechanics: sort with a lambda comparator, and represent intervals as `vector<vector<int>>` or `pair<int, int>`. Be deliberate about `<` versus `<=` at the boundary, since `[1,2]` and `[2,3]` either touch or they don't depending on your convention, and the problem statement decides which.
- Workshop: a mixed set of arrays, strings, and hashing drills that consolidates the contiguous-memory and hashing half of the structures track in one sitting.

### Patterns

- [Merge intervals](../docs/patterns.md)
- [Hashing for dedup/count/group](../docs/patterns.md)

### In-class problems

- Merge Intervals
- Insert Interval
- Interval List Intersections
- Mixed mock set: arrays + strings + hashing rapid drill

---

## Homework

Work these between lectures, in roughly this order. The warmup confirms the idea is in your hands; the core set is the week's real practice; the challenges are meant to stretch you.

**Warmup**

- Valid Anagram

**Core**

- Longest Common Prefix
- Set Mismatch
- Find All Duplicates in an Array
- Non-overlapping Intervals
- Minimum Number of Arrows to Burst Balloons

**Challenge**

- Meeting Rooms II
- Subarrays with K Different Integers

---

## Before next week

- You can implement a chaining hash table from scratch and explain load factor, rehashing, and why the worst case is O(n).
- You can state, without hesitating, when to use `unordered_map`/`set` versus `map`/`set`, and you no longer reach for `operator[]` on a lookup.
- You can write cyclic sort with a correct, terminating swap condition and use it to answer missing, duplicate, and first-missing-positive questions.
- You can merge intervals correctly, including getting the boundary convention right, and adapt it to insert-interval and meeting-rooms.
- The week's homework is done, and you can take a fresh array, string, or hashing problem and recognize the pattern before you start coding.

If any of those is shaky, rework the problems for that lecture before Week 5. The pointer-based structures that come next assume this foundation is solid.

---

Back to the [course README](../README.md) · Pattern reference: [docs/patterns.md](../docs/patterns.md)
