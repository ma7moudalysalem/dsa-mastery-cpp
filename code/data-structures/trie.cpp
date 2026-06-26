// Trie (prefix tree)
//
// The student builds a prefix tree over lowercase letters 'a'..'z' that
// stores whole words and answers exact-word and prefix queries.
// Compile/run: g++ -std=c++17 -Wall trie.cpp -o out && ./out
//
// Implement every method marked TODO until main() prints all checks passed.

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>

class Trie {
private:
    struct Node {
        Node* children[26];
        bool is_word;
        Node() {
            for (auto& c : children) c = nullptr;
            is_word = false;
        }
    };

    Node* root_;

    // Recursively delete the subtree rooted at node (including node itself).
    // Used by the destructor. Safe to call on nullptr.
    static void free_subtree(Node* node) {
        if (node == nullptr) return;
        for (Node* child : node->children) {
            free_subtree(child);
        }
        delete node;
    }

public:
    // Construct an empty trie containing no words. The root is a sentinel
    // node that is never itself a word.
    Trie() {
        root_ = new Node();
    }

    // Destructor: release every node in the trie.
    // TODO: free memory. Replace the throw with a recursive traversal that
    // deletes the whole tree (free_subtree(root_) is provided as a helper).
    // A destructor must NOT throw in real code; this stub only flags the
    // unimplemented state during development.
    ~Trie() {
        // TODO: free memory, e.g. free_subtree(root_);
    }

    // Non-copyable: copying raw owning pointers would double-free.
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;

    // Insert word into the trie, walking from the root and creating any
    // missing child nodes, then marking the final node as a complete word.
    // Parameters: word, non-empty, characters in 'a'..'z'.
    // Returns: nothing.
    // Time complexity: O(L) where L = word.size().
    // Edge cases: inserting an already-present word is a no-op in effect;
    // a prefix of an existing word (e.g. "car" before "card") must not be
    // marked as a word unless inserted itself.
    void insert(const std::string& word) {
        throw std::logic_error("TODO: implement Trie::insert");
    }

    // Report whether word was inserted as a complete word.
    // Parameters: word to look up.
    // Returns: true iff the exact word exists (final node reached and its
    // is_word flag is set); false if any character has no child or the
    // final node is only a prefix of other words.
    // Time complexity: O(L) where L = word.size().
    // Edge cases: a stored prefix such as "ca" must return false unless it
    // was itself inserted; an empty string returns false here.
    bool search(const std::string& word) const {
        throw std::logic_error("TODO: implement Trie::search");
    }

    // Report whether any stored word begins with prefix.
    // Parameters: prefix to test.
    // Returns: true iff every character of prefix can be followed from the
    // root (the prefix node exists); the is_word flag is irrelevant here.
    // Time complexity: O(L) where L = prefix.size().
    // Edge cases: an empty prefix matches any non-empty trie; a prefix that
    // diverges from all stored words returns false.
    bool starts_with(const std::string& prefix) const {
        throw std::logic_error("TODO: implement Trie::starts_with");
    }
};

int main() {
    try {
        Trie t;

        t.insert("cat");
        t.insert("car");
        t.insert("card");
        t.insert("dog");

        // Exact-word hits.
        assert(t.search("cat"));
        assert(t.search("car"));
        assert(t.search("card"));
        assert(t.search("dog"));

        // Exact-word misses: stored prefixes are not words on their own.
        assert(!t.search("ca"));
        assert(!t.search("c"));
        assert(!t.search("cards"));
        assert(!t.search("do"));
        assert(!t.search("cot"));

        // Prefix queries.
        assert(t.starts_with("car"));
        assert(t.starts_with("ca"));
        assert(t.starts_with("c"));
        assert(t.starts_with("do"));
        assert(!t.starts_with("ba"));
        assert(!t.starts_with("cards"));

        std::cout << "All checks passed\n";
    } catch (const std::exception& e) {
        std::cerr << "FAILED (likely unimplemented): " << e.what() << "\n";
        return 1;
    }
    return 0;
}
