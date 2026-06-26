// Binary Tree & Traversals
//
// The student builds the four traversals (preorder, inorder, postorder,
// level-order) plus height and node count for a binary tree of ints.
// The tree is constructed for you from a level-order array (INT_MIN = null).
//
// Compile & run:
//   g++ -std=c++17 -Wall binary_tree.cpp -o out && ./out
//
// Implement every method marked TODO until main() prints all checks passed.

#include <cassert>
#include <climits>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    // Build an empty tree.
    BinaryTree() : root_(nullptr) {}

    // Build a tree from a level-order list. INT_MIN marks a missing child.
    // The vector is read breadth-first: index 0 is the root, then for each
    // dequeued non-null node the next two entries are its left and right
    // children (which may themselves be INT_MIN). This builder is given so
    // the tests have a known tree to traverse.
    explicit BinaryTree(const std::vector<int>& level_values) : root_(nullptr) {
        if (level_values.empty() || level_values[0] == INT_MIN) {
            return;
        }
        root_ = new TreeNode(level_values[0]);
        std::queue<TreeNode*> q;
        q.push(root_);
        size_t i = 1;
        while (!q.empty() && i < level_values.size()) {
            TreeNode* node = q.front();
            q.pop();
            if (i < level_values.size()) {
                int lv = level_values[i++];
                if (lv != INT_MIN) {
                    node->left = new TreeNode(lv);
                    q.push(node->left);
                }
            }
            if (i < level_values.size()) {
                int rv = level_values[i++];
                if (rv != INT_MIN) {
                    node->right = new TreeNode(rv);
                    q.push(node->right);
                }
            }
        }
    }

    // No copying: the tree owns raw pointers and a shallow copy would
    // double-free. Disable the copy operations to keep ownership clear.
    BinaryTree(const BinaryTree&) = delete;
    BinaryTree& operator=(const BinaryTree&) = delete;

    ~BinaryTree() {
        // TODO: free memory
        // Recursively delete every node (e.g. post-order) to avoid leaks.
        // Leaving this empty leaks but does not crash, so tests still run.
    }

    // Preorder traversal (node, left, right), recursive.
    // Returns the values in visit order.
    // Time: O(n). Edge case: empty tree returns an empty vector.
    std::vector<int> preorder() const {
        throw std::logic_error("TODO: implement BinaryTree::preorder");
    }

    // Inorder traversal (left, node, right), recursive.
    // Returns the values in visit order.
    // Time: O(n). Edge case: empty tree returns an empty vector.
    std::vector<int> inorder() const {
        throw std::logic_error("TODO: implement BinaryTree::inorder");
    }

    // Postorder traversal (left, right, node), recursive.
    // Returns the values in visit order.
    // Time: O(n). Edge case: empty tree returns an empty vector.
    std::vector<int> postorder() const {
        throw std::logic_error("TODO: implement BinaryTree::postorder");
    }

    // Level-order traversal (breadth-first, left-to-right per level), using
    // a queue. Returns the values in visit order.
    // Time: O(n). Edge case: empty tree returns an empty vector.
    std::vector<int> level_order() const {
        throw std::logic_error("TODO: implement BinaryTree::level_order");
    }

    // Height = number of edges on the longest root-to-leaf path.
    // A single-node tree has height 0; an empty tree has height -1.
    // Time: O(n).
    int height() const {
        throw std::logic_error("TODO: implement BinaryTree::height");
    }

    // Total number of nodes in the tree.
    // Time: O(n). Edge case: empty tree returns 0.
    int count_nodes() const {
        throw std::logic_error("TODO: implement BinaryTree::count_nodes");
    }

    // Reads the links and prints the tree shape (root marked, children
    // indented). Visualization only; does not reveal any traversal order.
    std::string debug_to_string() const {
        std::string out;
        _debug_append(root_, 0, out);
        return out;
    }

    void debug_print() const { std::cout << debug_to_string(); }

private:
    TreeNode* root_;

    static void _debug_append(TreeNode* node, int depth, std::string& out) {
        if (node == nullptr) {
            return;
        }
        out += std::string(static_cast<size_t>(depth) * 2, ' ');
        out += std::to_string(node->val);
        out += '\n';
        _debug_append(node->left, depth + 1, out);
        _debug_append(node->right, depth + 1, out);
    }
};

int main() {
    try {
        // Tree built from this level-order array (INT_MIN = null):
        /*
                     1
                   /   \
                  2     3
                 / \     \
                4   5     6
        */
        const int N = INT_MIN;
        std::vector<int> level = {1, 2, 3, 4, 5, N, 6};
        BinaryTree tree(level);

        std::vector<int> expected_pre = {1, 2, 4, 5, 3, 6};
        assert(tree.preorder() == expected_pre);

        std::vector<int> expected_in = {4, 2, 5, 1, 3, 6};
        assert(tree.inorder() == expected_in);

        std::vector<int> expected_post = {4, 5, 2, 6, 3, 1};
        assert(tree.postorder() == expected_post);

        std::vector<int> expected_level = {1, 2, 3, 4, 5, 6};
        assert(tree.level_order() == expected_level);

        assert(tree.count_nodes() == 6);
        assert(tree.height() == 2);

        // Single-node tree: height 0, one node, all traversals just {7}.
        BinaryTree single(std::vector<int>{7});
        assert(single.count_nodes() == 1);
        assert(single.height() == 0);
        assert(single.preorder() == std::vector<int>{7});
        assert(single.inorder() == std::vector<int>{7});
        assert(single.postorder() == std::vector<int>{7});
        assert(single.level_order() == std::vector<int>{7});

        // Empty tree: height -1, zero nodes, all traversals empty.
        BinaryTree empty;
        assert(empty.count_nodes() == 0);
        assert(empty.height() == -1);
        assert(empty.preorder().empty());
        assert(empty.inorder().empty());
        assert(empty.postorder().empty());
        assert(empty.level_order().empty());

        std::cout << "All checks passed\n";
    } catch (const std::exception& e) {
        std::cerr << "FAILED (likely unimplemented): " << e.what() << "\n";
        return 1;
    }
    return 0;
}
