// Binary Search Tree
// The student builds a pointer-based BST over ints: insert, contains, remove
// (0/1/2 children via inorder successor), min/max, sorted inorder traversal,
// and a min/max-bounded validity check.
// Compile: g++ -std=c++17 -Wall binary_search_tree.cpp -o out
// Run:     ./out
// Implement every method marked TODO until main() prints all checks passed.

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    explicit TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

class BST {
public:
    BST() : root_(nullptr) {}

    // Destructor: release every node in the tree.
    // TODO: free memory (post-order delete of all nodes). A leak here does not
    // fail the asserts, but a correct BST owns its nodes.
    ~BST() {
        // TODO: free memory
    }

    // No copying: the default copy would share raw pointers and double-free.
    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    // Insert val into the tree, keeping BST order (left < node < right).
    // Duplicates are ignored (no second node for an existing value).
    // Time: O(h), h = tree height.
    // Edge cases: empty tree (val becomes root); inserting an existing value.
    void insert(int val) {
        throw std::logic_error("TODO: implement BST::insert");
    }

    // Return true iff val is present in the tree.
    // Time: O(h). Edge case: empty tree returns false.
    bool contains(int val) const {
        throw std::logic_error("TODO: implement BST::contains");
    }

    // Remove one node holding val, preserving BST order. No-op if val is absent.
    // Handle all three cases:
    //   - leaf (0 children): detach and delete it.
    //   - one child: splice the child into the removed node's slot.
    //   - two children: replace val with the inorder successor (smallest value
    //     in the right subtree), then remove that successor node.
    // Time: O(h). Edge cases: removing the root; removing an absent value.
    void remove(int val) {
        throw std::logic_error("TODO: implement BST::remove");
    }

    // Return the smallest value in the tree (leftmost node).
    // Time: O(h). Edge case: throws std::runtime_error on an empty tree.
    int min() const {
        throw std::logic_error("TODO: implement BST::min");
    }

    // Return the largest value in the tree (rightmost node).
    // Time: O(h). Edge case: throws std::runtime_error on an empty tree.
    int max() const {
        throw std::logic_error("TODO: implement BST::max");
    }

    // Return all values in ascending order via an inorder traversal.
    // For a valid BST this output is sorted.
    // Time: O(n). Edge case: empty tree returns an empty vector.
    std::vector<int> inorder() const {
        throw std::logic_error("TODO: implement BST::inorder");
    }

    // Return true iff the tree satisfies the BST property everywhere: every
    // node's value is strictly greater than all values in its left subtree and
    // strictly less than all values in its right subtree. Validate by passing
    // (min, max) bounds down the recursion, not just by comparing parent/child.
    // Time: O(n). Edge case: empty tree is a valid BST (returns true).
    bool is_valid_bst() const {
        throw std::logic_error("TODO: implement BST::is_valid_bst");
    }

private:
    TreeNode* root_;
};

int main() {
    try {
        BST t;

        // Empty-tree invariants.
        assert(t.contains(5) == false);
        assert(t.inorder().empty());
        assert(t.is_valid_bst() == true);

        // Insert several values (deliberately unsorted insertion order).
        for (int v : {50, 30, 70, 20, 40, 60, 80, 65}) {
            t.insert(v);
        }

        // contains: present and absent.
        assert(t.contains(50) == true);
        assert(t.contains(65) == true);
        assert(t.contains(20) == true);
        assert(t.contains(80) == true);
        assert(t.contains(99) == false);
        assert(t.contains(0) == false);

        // Duplicate insert is ignored; inorder stays sorted with no repeat.
        t.insert(50);

        // inorder comes out sorted.
        {
            std::vector<int> in = t.inorder();
            std::vector<int> expected = {20, 30, 40, 50, 60, 65, 70, 80};
            assert(in == expected);
        }

        // min / max.
        assert(t.min() == 20);
        assert(t.max() == 80);
        assert(t.is_valid_bst() == true);

        // Remove a leaf (20 has no children).
        t.remove(20);
        assert(t.contains(20) == false);
        {
            std::vector<int> in = t.inorder();
            std::vector<int> expected = {30, 40, 50, 60, 65, 70, 80};
            assert(in == expected);
        }
        assert(t.is_valid_bst() == true);
        assert(t.min() == 30);

        // Remove a node with one child (60 has only the right child 65).
        t.remove(60);
        assert(t.contains(60) == false);
        assert(t.contains(65) == true);
        {
            std::vector<int> in = t.inorder();
            std::vector<int> expected = {30, 40, 50, 65, 70, 80};
            assert(in == expected);
        }
        assert(t.is_valid_bst() == true);

        // Remove a node with two children (50 is the root with both subtrees).
        // Inorder successor of 50 is 65.
        t.remove(50);
        assert(t.contains(50) == false);
        {
            std::vector<int> in = t.inorder();
            std::vector<int> expected = {30, 40, 65, 70, 80};
            assert(in == expected);
        }
        assert(t.is_valid_bst() == true);
        assert(t.min() == 30);
        assert(t.max() == 80);

        // Removing an absent value is a no-op.
        t.remove(12345);
        {
            std::vector<int> in = t.inorder();
            std::vector<int> expected = {30, 40, 65, 70, 80};
            assert(in == expected);
        }
        assert(t.is_valid_bst() == true);

        std::cout << "All checks passed\n";
    } catch (const std::exception& e) {
        std::cerr << "FAILED (likely unimplemented): " << e.what() << "\n";
        return 1;
    }
    return 0;
}
