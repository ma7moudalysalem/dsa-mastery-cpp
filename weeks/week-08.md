# Week 8 — Binary Trees: Representation, DFS & BFS Traversals

This is where the course turns from linear to nonlinear. You stop thinking in sequences and start thinking in branches: a node, its two children, and the recursion that falls naturally out of that shape. The week nails tree mechanics first (terminology, height versus depth, the array representation that later becomes a heap), then drills the two traversal families that everything downstream is built on: depth-first search in all three orders, recursive and iterative, and breadth-first level-order with the level-size snapshot idiom. By Friday you own the [Tree DFS](../docs/patterns.md) and [Tree BFS](../docs/patterns.md) patterns, the same two patterns that power BSTs, heaps, and graphs in the weeks ahead.

## By the end of this week

You should be able to:

- Use tree terminology precisely, and never confuse height with depth again.
- Read and write the array representation of a complete tree (`2i+1` / `2i+2` for children, `(i-1)/2` for the parent) and explain why it is the bridge to heaps.
- Free a tree without leaking by writing a post-order recursive destructor, and build a test tree from level-order input.
- Implement all three DFS orders from one recursive template by moving a single line, and state what each order is good for.
- Convert every recursive traversal to an iterative one with an explicit `std::stack`, including the hard post-order case.
- Implement BFS with a `std::queue` using the level-size snapshot to process exactly one level per outer iteration, and solve the level-order variants (zigzag, right-side view, level averages, next-pointers).
- State the cost of every traversal as O(n) time, and reason about O(h) call-stack space for DFS versus O(w) queue space for BFS, choosing the right one for the problem.
- Decide, from the wording of a problem, whether information bubbles up from children (DFS) or is organized by level (BFS), and pick the traversal before writing code.

---

## Lecture 29 — Binary Trees: Representation, Terminology & Memory

### Objectives

- Define tree terminology precisely: height versus depth, and the full/complete/perfect/balanced/degenerate family.
- Use the array representation of a complete tree (children at `2i+1` and `2i+2`, parent at `(i-1)/2`) as the bridge to heaps.
- Free a tree safely with a post-order recursive destructor, and build test trees from level-order input.

### Topics covered

- `TreeNode { int val; TreeNode* left; TreeNode* right; }`. A tree is just a pointer to its root, or `nullptr` when empty.
- Vocabulary: root, leaf, internal node, ancestor and descendant. Height is measured up from the leaves, depth down from the root. We use height `-1` for the empty tree and `0` for a single node, and we hold that convention all term.
- Tree shapes: full (every node has 0 or 2 children), complete (filled left to right, last level may be partial), perfect (all leaves at the same depth), balanced (heights of subtrees differ by at most a constant), and degenerate/pathological (a linked list wearing a tree costume).
- Counting facts: a tree of height `h` holds at most `2^(h+1) - 1` nodes. For `n` nodes, the minimum height is `floor(log2(n))` and the maximum is `n - 1`. That gap between `log n` and `n` is the entire reason balancing matters, which is next week's problem.
- Array representation of a complete tree: store level by level, no pointers. Child indices `2i+1` and `2i+2`, parent `(i-1)/2`. This is exactly how a binary heap is laid out, so learn it now and Week 10 is half done.
- Memory: a post-order `deleteTree` destructor frees both children before the node itself, because freeing a node before its children orphans the subtree. Build a tree from a level-order array like `[1, 2, 3, null, null, 4, 5]`. Use `nullptr`, not `NULL`.

```cpp
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

// Post-order: free children, then self. Any other order leaks or
// dereferences freed memory.
void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}
```

### Patterns

None new. This lecture builds the object the rest of the week operates on.

### In-class problems

- Maximum Depth of Binary Tree
- Same Tree
- Invert / Mirror Binary Tree
- Build a tree from a level-order array and free it with a post-order destructor

---

## Lecture 30 — DFS Traversals: Preorder, Inorder, Postorder (Recursive & Iterative)

### Objectives

- Implement all three DFS orders as one template, moving only the visit line, and explain what each order is for.
- Convert recursive traversals to iterative ones with an explicit `std::stack`, including the hard post-order case.
- Analyze traversal cost as O(n) time and O(h) call-stack space, and name the skewed-tree stack-overflow risk.

### Topics covered

- The three orders and where each earns its keep. Preorder (root, left, right) for serializing or copying a tree. Inorder (left, root, right), which visits a BST in sorted order, a fact we lean on hard next week. Postorder (left, right, root) for deletion and for any computation where a node needs its children's results first.
- One recursive template. The structure is identical across all three; only the position of the visit line changes. See it once and you have seen all three.

```cpp
void inorder(TreeNode* node, std::vector<int>& out) {
    if (node == nullptr) return;
    inorder(node->left, out);
    out.push_back(node->val);   // move this line up for preorder,
    inorder(node->right, out);  // down for postorder
}
```

- Iterative preorder with a `std::stack`: push the root, then on each pop record the node and push its right child before its left, so left comes off the stack first.
- Iterative inorder: walk left pushing every node, pop and visit, then move right and repeat. This is the one that trips people up, so we trace it on the board node by node.
- Iterative postorder: the genuinely awkward one. Two clean methods. The two-stack method, and the single-stack method that tracks a `lastVisited` pointer to decide whether a node's right subtree is already done.
- Morris traversal as a challenge aside: inorder in O(1) extra space by threading the tree. Worth seeing once so you know it exists; not something you reach for in an interview.
- A performance trap we kill on sight: pass the accumulator by reference. Returning and concatenating `vector`s up the recursion is O(n^2) because each concat copies. One shared output vector keeps it O(n).

### Patterns

- [Tree DFS](../docs/patterns.md)

### In-class problems

- Binary Tree Inorder Traversal (iterative)
- Binary Tree Postorder Traversal (iterative)
- Path Sum (root-to-leaf target)
- Diameter of Binary Tree

---

## Lecture 31 — BFS Level-Order Traversal & the Tree-BFS Pattern

### Objectives

- Implement BFS with a queue using the level-size snapshot idiom so each outer iteration processes exactly one level.
- Solve the level-order variants: zigzag, right-side view, level averages, and connecting next-pointers.
- Articulate the DFS O(h) versus BFS O(w) space trade-off and when to choose each.

### Topics covered

- BFS with `std::queue`. The whole trick is one line at the top of each level: snapshot `int sz = q.size()` before you process the level, then loop exactly `sz` times. That snapshot is what cleanly separates one level from the next, and it is the heart of the [Tree BFS](../docs/patterns.md) pattern.

```cpp
std::vector<std::vector<int>> levelOrder(TreeNode* root) {
    std::vector<std::vector<int>> levels;
    if (root == nullptr) return levels;
    std::queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int sz = q.size();              // snapshot the level boundary
        std::vector<int> level;
        for (int i = 0; i < sz; ++i) {
            TreeNode* node = q.front();
            q.pop();
            level.push_back(node->val);
            if (node->left)  q.push(node->left);
            if (node->right) q.push(node->right);
        }
        levels.push_back(level);
    }
    return levels;
}
```

- Level order as `vector<vector<int>>`. Once you have the snapshot loop, the variants are small edits on top of it. Zigzag (spiral) by reversing alternate levels or by using a deque. Right-side view by taking the last node of each level. Level averages, bottom-up level order, and connecting each node to its right sibling.
- Complexity: O(n) time, every node enqueued and dequeued once. Space is O(w) where `w` is the maximum width, which can reach about `n/2` at the last level of a full tree. That is the trade-off against DFS, which is O(h).
- Two C++ gotchas we hammer. `queue::pop()` returns `void`, so read `front()` first and pop second. And never read `q.size()` in the middle of processing a level; you already snapshotted it, and the size is changing as you push children.

### Patterns

- [Tree BFS](../docs/patterns.md)

### In-class problems

- Binary Tree Level Order Traversal
- Binary Tree Zigzag (Spiral) Level Order Traversal
- Binary Tree Right Side View
- Minimum Depth of Binary Tree

---

## Lecture 32 — Tree DFS & BFS Patterns: Path, Subtree & Structure Problems

### Objectives

- Recognize when information bubbles up from children (DFS) versus is organized by level (BFS), and pick the traversal accordingly.
- Use a recursive helper that returns a subtree summary while updating a global answer.
- Serialize and deserialize a tree, and solve LCA, balance, and symmetry with the two traversal patterns.

### Topics covered

- The workhorse shape of hard tree problems: a DFS helper that returns one summary value (a height, a sum, a found-flag) while updating a global best on the side. Diameter is the canonical example: the helper returns subtree height, but the answer it updates is the longest path through any node.
- A tour of the classics through this lens. All root-to-leaf paths summing to a target, diameter, the balanced-height check (return height, return a sentinel the moment a subtree is unbalanced), and lowest common ancestor.
- Symmetric tree and same tree via paired recursion: walk two nodes in lockstep and compare. Same structure, two pointers instead of one.
- Serialize and deserialize a tree. We do both a DFS encoding (preorder with explicit null markers) and a BFS encoding (level order), so you see that the choice of traversal is also a choice of format.
- The decision drill, run until it is reflexive. Words like *level*, *depth*, *nearest*, or *shortest in an unweighted tree* point to BFS. Words like *path*, *subtree*, or any *aggregate computed from a node's children* point to DFS. Naming the traversal is half the solution.
- A timed mixed mock set spanning the [Tree DFS](../docs/patterns.md) and [Tree BFS](../docs/patterns.md) patterns, so you practice choosing under pressure, not just executing once the choice is made.

### Patterns

- [Tree DFS](../docs/patterns.md)
- [Tree BFS](../docs/patterns.md)

### In-class problems

- Lowest Common Ancestor of a Binary Tree
- Balanced Binary Tree
- Symmetric Tree
- Serialize and Deserialize Binary Tree

---

## Homework

Work these between lectures. The warmups confirm you have the mechanics; the core set is where the patterns get installed; the challenge set is interview-grade and worth the extra time.

### Warmup

- Maximum Depth of Binary Tree
- Invert Binary Tree
- Average of Levels in Binary Tree

### Core

- Binary Tree Level Order Traversal
- Binary Tree Zigzag Level Order Traversal
- Path Sum II (all root-to-leaf paths equal to the target)
- Diameter of Binary Tree
- Lowest Common Ancestor of a Binary Tree

### Challenge

- Binary Tree Maximum Path Sum
- Serialize and Deserialize Binary Tree
- Construct Binary Tree from Preorder and Inorder Traversal

---

## Before next week

- You can write all three DFS orders from the one recursive template, moving only the visit line, without looking it up.
- You can write iterative inorder and iterative postorder with an explicit `std::stack` from a blank page.
- You can write level-order BFS with the `int sz = q.size()` snapshot from memory, and you remember that `pop()` returns `void`.
- You can state the space cost of a traversal correctly: O(h) for recursive DFS, O(w) for BFS, and you know which is worse on a skewed tree versus a full one.
- Given a new tree problem, you can decide DFS versus BFS from the wording before writing any code.
- You finished the core homework set and attempted at least one challenge problem.

Back to the [course README](../README.md). Pattern reference: [docs/patterns.md](../docs/patterns.md).
