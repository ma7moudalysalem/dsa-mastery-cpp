// AVL Tree (self-balancing BST)
// The student builds a binary search tree that keeps itself balanced after
// every insertion using single and double rotations, so search/insert stay
// O(log n) even when keys arrive in sorted order.
// Compile: g++ -std=c++17 -Wall avl_tree.cpp -o out
// Run:     ./out
// Implement every method marked TODO until main() prints all checks passed.

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// Single tree node. height is the height of the subtree rooted here:
// a leaf has height 0; a null subtree is treated as height -1 (see node_height).
struct Node {
    int val;
    int height;
    Node* left;
    Node* right;

    explicit Node(int v) : val(v), height(0), left(nullptr), right(nullptr) {}
};

class AVLTree {
public:
    AVLTree() : root_(nullptr) {}

    ~AVLTree() {
        destroy(root_);
        root_ = nullptr;
    }

    // No copying: nodes are raw-owned, a shallow copy would double-free.
    AVLTree(const AVLTree&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;

    // --- Given helpers (small, non-algorithmic) ---------------------------

    // Height of the subtree rooted at n. A null subtree has height -1, so a
    // leaf (with two null children) computes a height of 0. O(1).
    static int node_height(Node* n) {
        return n == nullptr ? -1 : n->height;
    }

    // Balance factor = height(left) - height(right). Positive means
    // left-heavy, negative means right-heavy. Defined as 0 for null. O(1).
    static int balance_factor(Node* n) {
        if (n == nullptr) return 0;
        return node_height(n->left) - node_height(n->right);
    }

    // Recompute n->height from its children's heights. Call after any change
    // to n's children (e.g. at the end of a rotation or insert). O(1).
    static void update_height(Node* n) {
        if (n == nullptr) return;
        int lh = node_height(n->left);
        int rh = node_height(n->right);
        n->height = (lh > rh ? lh : rh) + 1;
    }

    // --- Methods the STUDENT implements -----------------------------------

    // Left rotation around pivot x (x is right-heavy). Its right child y
    // becomes the new subtree root; y's left subtree becomes x's right child.
    /*
        Before:  x              After:    y
                  \                       / \
                   y        =>           x   T3
                  / \                     \
                T2   T3                    T2
    */
    // Update the heights of x then y (order matters) and return y, the new
    // subtree root. Assumes x and x->right are non-null. O(1).
    Node* rotate_left(Node* x) {
        throw std::logic_error("TODO: implement AVLTree::rotate_left");
    }

    // Right rotation around pivot x (x is left-heavy). Its left child y
    // becomes the new subtree root; y's right subtree becomes x's left child.
    /*
        Before:    x            After:    y
                  /                       / \
                 y         =>           T1   x
                / \                         /
              T1   T2                     T2
    */
    // Update the heights of x then y (order matters) and return y, the new
    // subtree root. Assumes x and x->left are non-null. O(1).
    Node* rotate_right(Node* x) {
        throw std::logic_error("TODO: implement AVLTree::rotate_right");
    }

    // Insert val into the subtree rooted at node and return the (possibly new)
    // root of that subtree after rebalancing. Steps:
    //   1. If node is null, return new Node(val).
    //   2. Recurse left if val < node->val, right if val > node->val. Treat an
    //      equal value as already present (no insert, no duplicate).
    //   3. update_height(node).
    //   4. Inspect balance_factor(node) and fix the four cases with rotations:
    //        LL: bf > 1  and val < node->left->val   -> rotate_right(node)
    //        RR: bf < -1 and val > node->right->val   -> rotate_left(node)
    //        LR: bf > 1  and val > node->left->val    -> rotate_left(left) then rotate_right(node)
    //        RL: bf < -1 and val < node->right->val   -> rotate_right(right) then rotate_left(node)
    //   5. Return the resulting subtree root.
    // O(log n) for a single insert. Edge case: inserting an existing value
    // leaves the tree unchanged.
    Node* insert(Node* node, int val) {
        throw std::logic_error("TODO: implement AVLTree::insert(Node*, int)");
    }

    // Public insert: insert val into the tree, keeping it balanced. Set root_
    // to the value returned by insert(root_, val). O(log n).
    void insert(int val) {
        throw std::logic_error("TODO: implement AVLTree::insert(int)");
    }

    // Return the keys in ascending (in-order) order. Build the vector with a
    // left-node-right traversal. For a correct BST the result is sorted.
    // O(n) time, O(n) output. Empty tree returns an empty vector.
    std::vector<int> inorder() const {
        throw std::logic_error("TODO: implement AVLTree::inorder");
    }

    // Height of the whole tree: node_height(root_). An empty tree is -1, a
    // single node is 0. O(1).
    int height() const {
        throw std::logic_error("TODO: implement AVLTree::height");
    }

    // Return true if every node satisfies the AVL invariant |balance_factor|
    // <= 1. An empty tree is balanced. O(n).
    bool is_balanced() const {
        throw std::logic_error("TODO: implement AVLTree::is_balanced");
    }

    // --- Given debug helper (reads links only) ----------------------------

    // Parenthesized structure: (left val right). Empty subtrees print "_".
    // Reads links only; does not reveal balancing logic.
    std::string debug_to_string() const {
        return to_string(root_);
    }

private:
    Node* root_;

    static void destroy(Node* n) {
        if (n == nullptr) return;
        destroy(n->left);
        destroy(n->right);
        delete n;
    }

    static std::string to_string(Node* n) {
        if (n == nullptr) return "_";
        return "(" + to_string(n->left) + " " + std::to_string(n->val) +
               " " + to_string(n->right) + ")";
    }
};

int main() {
    try {
        // Empty tree.
        AVLTree t;
        assert(t.height() == -1);
        assert(t.is_balanced());
        assert(t.inorder().empty());

        // Ascending inserts 1..7 would form a degenerate right chain in a
        // plain BST (height 6). The AVL tree must rebalance to height <= 3.
        for (int v = 1; v <= 7; ++v) {
            t.insert(v);
        }

        // In-order traversal is sorted.
        std::vector<int> in = t.inorder();
        std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7};
        assert(in == expected);

        // Balanced, and height is logarithmic (7 nodes -> height 2, well <= 3).
        assert(t.is_balanced());
        assert(t.height() <= 3);
        assert(t.height() == 2);

        // Inserting a duplicate is a no-op: same contents, same height.
        t.insert(4);
        assert(t.inorder() == expected);
        assert(t.height() == 2);
        assert(t.is_balanced());

        // Descending inserts also stay balanced.
        AVLTree d;
        for (int v = 10; v >= 1; --v) {
            d.insert(v);
        }
        std::vector<int> d_in = d.inorder();
        for (size_t i = 0; i + 1 < d_in.size(); ++i) {
            assert(d_in[i] < d_in[i + 1]);  // strictly sorted, no duplicates
        }
        assert(d_in.size() == 10);
        assert(d.is_balanced());
        assert(d.height() <= 3);  // 10 nodes: balanced height is 3

        std::cout << "All checks passed\n";
    } catch (const std::exception& e) {
        std::cerr << "FAILED (likely unimplemented): " << e.what() << "\n";
        return 1;
    }
    return 0;
}
