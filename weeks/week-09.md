# Week 9 — Ordered Trees: BST and Self-Balancing (AVL)

Last week you traversed generic binary trees. This week the trees get an ordering rule, and that rule changes everything. A binary search tree keeps every key sorted by structure, so search, insert, and delete all run in O(h) instead of O(n). You'll build the full BST API by hand, see exactly how a sorted insert sequence degenerates it into a linked list, and then fix that for good with AVL rotations that hold the height at Theta(log n). Red-black trees and `std::map` come in at the end as the version you'll actually use in practice.

By the end of the week you can implement an ordered tree that stays fast, validate one correctly (including the bug almost everyone writes first), and explain the read-heavy versus write-heavy trade-off that decides AVL versus red-black in real systems.

Patterns this week: [BST-ordered traversal](../docs/patterns.md) and [tree DFS](../docs/patterns.md).

---

## By the end of this week

- State the BST invariant recursively (everything in the left subtree `<` node `<` everything in the right subtree), and use "inorder traversal yields sorted order" as the fact you reach for first.
- Implement O(h) search and insert, where insert always attaches a new leaf, using the return-the-new-subtree-root idiom that threads cleanly through the whole API.
- Compute predecessor, successor, floor, and ceiling on a BST, and answer range queries.
- Handle all three BST deletion cases, replacing a two-child node with its inorder successor.
- Validate a BST by passing `(min, max)` bounds down the recursion, and explain why the naive "compare to the immediate parent" check is wrong.
- Build a height-balanced BST from a sorted array in O(n) by recursively picking the middle element.
- Explain why an unbalanced BST degrades to O(n) and how the AVL balance-factor invariant forces Theta(log n) height.
- Perform left, right, left-right, and right-left rotations as O(1) pointer surgery that preserves BST order, and implement AVL insert and delete on top of them.
- Compare AVL and red-black trees as a read-heavy versus write-heavy trade-off, and know when to hand-roll a balanced tree versus reach for `std::map` / `std::set`.

---

## Lecture 33 — Binary Search Trees: Invariant, Search, Insert, Successor

A generic binary tree gives you no help finding a value. Add one ordering rule and the same shape becomes a search structure where every comparison throws away half the remaining tree. This lecture is the BST core: the invariant, O(h) search and insert, and the successor query that deletion will depend on next time.

### Objectives

- Internalize the recursive BST invariant (all-left `<` node `<` all-right) and use "inorder equals sorted" as the keystone fact.
- Implement O(h) search and insert (insert always adds a leaf) with the return-the-new-subtree-root idiom.
- Compute predecessor and successor, plus floor and ceiling, on a BST.

### Topics

- The invariant stated recursively, not as a parent-child rule. It's not enough that each node beats its two children; *every* key in the left subtree must be smaller and *every* key in the right subtree larger. That distinction is the whole reason validation is harder than it looks.
- Search in O(h): compare, then go left or right. Insert in O(h): walk down the same way until you fall off the tree, then attach the new key as a leaf. A fresh key always lands as a leaf, never in the middle.
- The return-the-new-subtree-root idiom: each recursive call returns the (possibly new) root of the subtree it was handed, and the caller reassigns `node->left` or `node->right` to it. This one convention makes insert, delete, and every rotation later compose without special-casing the parent pointer.
- Inorder traversal of a BST yields keys in sorted order. This single fact answers a surprising number of problems, kth-smallest among them.
- Inorder successor: if the node has a right child, it's the leftmost node of that right subtree; otherwise it's the lowest ancestor for which this node sits in the left subtree. Predecessor is the mirror image.
- Floor (largest key `<=` x), ceiling (smallest key `>=` x), and range queries, all in O(h) by pruning whole subtrees you can prove are out of range.
- `std::set` / `std::map` are balanced BSTs. `lower_bound` and `upper_bound` give you floor/ceiling for free. Contrast with `unordered_set`: hashing buys average O(1) lookup but throws away the ordering that makes successor, floor, and range queries possible.

```cpp
// Insert with the return-the-new-subtree-root idiom.
TreeNode* insert(TreeNode* node, int key) {
    if (!node) return new TreeNode(key);     // fell off the tree: attach as a leaf
    if (key < node->val)
        node->left = insert(node->left, key);
    else if (key > node->val)
        node->right = insert(node->right, key);
    // key == node->val: duplicate, decide your policy (here: ignore)
    return node;                              // hand the (unchanged) root back up
}
```

### Patterns

- [BST-ordered traversal](../docs/patterns.md)
- [Tree DFS](../docs/patterns.md)

### In-class problems

- Search in a Binary Search Tree
- Insert into a Binary Search Tree
- Kth Smallest Element in a BST
- Range Sum of BST

---

## Lecture 34 — BST Deletion, Validation, and Balanced Construction

Deletion is the one BST operation with real cases, and validation is where people write a plausible-looking function that passes the easy tests and fails the hard ones. We'll get both exactly right, then build a balanced BST from a sorted array, which sets up *why* balancing matters two lectures from now.

### Objectives

- Handle all three deletion cases, replacing a two-child node with its inorder successor.
- Validate a BST by propagating `(min, max)` bounds down the recursion, avoiding the immediate-parent-only bug.
- Build a height-balanced BST from a sorted array in O(n).

### Topics

- Deletion, case by case. Case 1, a leaf: just remove it. Case 2, one child: splice the node out by returning its single child to the parent. Case 3, two children: copy in the inorder successor's value (the leftmost node of the right subtree), then recursively delete that successor, which is itself always a case-1 or case-2 node.
- Validation by bounds propagation. Each node must lie strictly inside an open interval `(low, high)`; recurse left with `high = node->val` and right with `low = node->val`. The common bug is checking only `left < node < right` against the immediate children, which accepts trees that are locally fine but globally broken.
- Use `long long` bounds (or pointer/optional sentinels) so that a node holding `INT_MIN` or `INT_MAX` doesn't break the comparison against the initial bounds.
- The alternative validation: do an inorder traversal and check that the sequence is strictly increasing. Same correctness, different mechanic; knowing both is useful because each reveals a different bug.
- Build a balanced BST from a sorted array: pick the middle element as the root, recurse on the left half and the right half. O(n) total, and the result has height O(log n) by construction.
- Average height is O(log n), but a degenerate tree is O(n). Inserting already-sorted data is the worst case: it builds a spine with no branching, a linked list wearing a tree's interface. That degeneration is the entire motivation for the self-balancing trees coming next.
- Duplicate-key policy is a decision, not a default. Reject duplicates, keep a count per node, or always send equals to one side. Pick one and apply it consistently across insert, search, and delete.

```cpp
bool isValid(TreeNode* node, long long low, long long high) {
    if (!node) return true;
    if (node->val <= low || node->val >= high) return false;   // strict bounds
    return isValid(node->left,  low,        node->val)
        && isValid(node->right, node->val,  high);
}
// call: isValid(root, LLONG_MIN, LLONG_MAX);
```

### Patterns

- [BST-ordered traversal](../docs/patterns.md)
- [Tree DFS](../docs/patterns.md)

### In-class problems

- Delete Node in a BST
- Validate Binary Search Tree
- Convert Sorted Array to Balanced BST
- Lowest Common Ancestor of a BST

---

## Lecture 35 — Why Balance Matters: AVL Trees and Rotations

Last lecture ended with a BST degenerating into a linked list on sorted input. Here's the fix. AVL trees add one invariant on top of the BST rule and repair it after every insert with rotations, which are O(1) pointer rewrites that preserve sorted order. Get the four cases and the rotation mechanics solid; this is the most pointer-careful code of the week.

### Objectives

- Explain why an unbalanced BST degrades to O(n) and how the AVL balance-factor invariant guarantees Theta(log n) height.
- Perform left, right, left-right, and right-left rotations as O(1) pointer surgery that preserves the BST order.
- Implement AVL insert by walking back up and rotating the first unbalanced ancestor.

### Topics

- The AVL invariant: for every node, the balance factor (height of left subtree minus height of right subtree) stays in `{-1, 0, +1}`. Maintain that everywhere and the height is provably Theta(log n), so every BST operation is back to O(log n) worst case, not just on average.
- Left and right rotations: a constant-time relink of three nodes and at most two subtrees. The key property is that a rotation changes the shape but not the inorder order, so the BST invariant survives untouched. Draw the before/after pointer diagram until you can do it without thinking; that picture is the whole lecture.
- The four imbalance cases and how to detect each from the balance factors:

  | Case | Where the new node landed | Fix |
  |---|---|---|
  | LL | left child's left subtree | one right rotation |
  | RR | right child's right subtree | one left rotation |
  | LR | left child's right subtree | left-rotate child, then right-rotate node |
  | RL | right child's left subtree | right-rotate child, then left-rotate node |

- AVL insert: do an ordinary BST insert, then on the way back up the recursion, recompute heights and rotate the first node that has become unbalanced. One rotation (single or double) is enough to fix an insert.
- Store the height in each node and keep the `null` height at `-1` so a single leaf has height `0`. Pick that convention and never deviate, because every balance-factor calculation depends on it.
- Recompute heights after a rotation in the right order: update the children's heights first, then the new subtree root's, since the parent's height reads the children's.

```cpp
TreeNode* rotateRight(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* t = x->right;
    x->right = y;          // rotate
    y->left  = t;
    updateHeight(y);       // child first
    updateHeight(x);       // then the new subtree root
    return x;              // x is the new root of this subtree
}
```

### Patterns

- [BST-ordered traversal](../docs/patterns.md)

### In-class problems

- Implement AVL insert with LL/RR/LR/RL rotations
- Balance a Binary Search Tree
- Compute height and balance factor of every node
- Detect which rotation a given insertion triggers

---

## Lecture 36 — AVL Delete, Red-Black Overview, and `std::map`

Insert needed at most one rotation. Delete can need several, cascading all the way to the root, and that asymmetry is the practical reason red-black trees exist. We finish the balanced-tree story with AVL delete, the red-black big picture, and the honest advice: understand these, then use `std::map`.

### Objectives

- Implement AVL delete and recognize that rebalancing can cascade up multiple levels to the root.
- Compare AVL and red-black trees as a read-heavy versus write-heavy trade-off.
- Know when to hand-roll a balanced tree versus reach for `std::map` / `std::set`.

### Topics

- AVL delete: do the BST delete (the same three cases as Lecture 34), then walk back up rotating any node that fell out of balance. Unlike insert, one rotation may not be the end of it. Rebalancing one level can shorten a subtree enough to unbalance its parent, so you keep checking and rotating all the way to the root.
- Red-black trees, the big picture. Five properties: every node is red or black; the root is black; no red node has a red child (no two consecutive reds); every root-to-null path has the same number of black nodes (equal black-height); null leaves count as black. Those rules keep the tree height within 2x of optimal without the tight balance-factor bookkeeping AVL does.
- The trade-off. AVL keeps a stricter balance, so it's shorter and faster to search, which favors read-heavy workloads. Red-black allows a looser balance and so needs fewer rotations per write, which favors write-heavy workloads. `std::map` and `std::set` are red-black trees, which is why the standard library picked the write-friendly side of that trade.
- One line on B-trees and B+-trees: same balancing idea widened to many keys per node, used by databases and filesystems because they minimize disk and page reads. You'll meet them in a systems or database course, not here.
- Interview framing. Be able to explain AVL rotations and the red-black properties on a whiteboard, but in real code reach for `std::map` / `std::set` (or the unordered hash versions when you don't need ordering). Hand-rolling a balanced tree in an interview is almost always the wrong move unless the question is explicitly "implement one."

### In-class problems

- Implement AVL delete with cascading rebalance
- Count of Smaller Numbers After Self (BST / order-statistics)
- Use `std::map` `lower_bound` / `upper_bound` for floor and ceiling
- Recover Binary Search Tree (two swapped nodes)

---

## Homework

Work these between lectures. They're grouped by difficulty, not by lecture, so warm up before the hard ones. The warmups confirm the idea is in your hands; the core set is the week's real practice; the challenges are the build problems that prove you own it.

**Warmup**

- Search in a Binary Search Tree
- Insert into a Binary Search Tree
- Two Sum IV - Input is a BST
- Lowest Common Ancestor of a BST

**Core**

- Kth Smallest Element in a BST
- Validate Binary Search Tree
- Delete Node in a BST
- Convert Sorted Array to Balanced BST
- Inorder Successor in BST

**Challenge**

- Implement AVL insert with all four rotations
- Implement AVL delete
- Binary Search Tree Iterator with O(h) space

When a problem names a pattern, the [pattern reference](../docs/patterns.md) has the template and the tells for recognizing it.

---

## Before next week

- [ ] You can state the BST invariant recursively and explain why inorder traversal comes out sorted.
- [ ] You can implement search, insert, delete, and validate with the return-the-new-subtree-root idiom, and you no longer write the immediate-parent-only validation bug.
- [ ] You can find successor, predecessor, floor, and ceiling on a BST, and build a balanced BST from a sorted array.
- [ ] You can draw all four rotations (LL, RR, LR, RL) and explain why each preserves sorted order.
- [ ] You can implement AVL insert and delete, and explain why delete can cascade rotations to the root while insert needs at most one.
- [ ] You can say, in a sentence, why `std::map` is a red-black tree and when you'd reach for it over a hand-rolled AVL.
- [ ] This week's milestone is in hand: a working BST (search / insert / delete / validate / successor) and an AVL tree with rotations and self-balancing insert, all verified with assert-based tests.

Next week moves to heaps and priority queues: a different tree shape, stored in a flat array, optimized for "give me the smallest (or largest) thing fast" instead of ordered search. See [`week-10.md`](week-10.md).

---

Back to the [course README](../README.md) · Pattern reference: [docs/patterns.md](../docs/patterns.md)
