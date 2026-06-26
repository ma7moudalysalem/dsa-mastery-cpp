// Hash Table (separate chaining)
// The student builds a generic HashMap<K,V> backed by an array of buckets,
// where each bucket is a singly linked list of key/value Nodes. Collisions
// are handled by chaining; put/get/contains/erase walk one bucket's chain.
//
// Compile/run:
//   g++ -std=c++17 -Wall hash_table.cpp -o out
//   ./out
//
// Implement every method marked TODO until main() prints all checks passed.

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <functional>

template <class K, class V>
class HashMap {
private:
    struct Node {
        K key;
        V value;
        Node* next;
        Node(const K& k, const V& v, Node* n) : key(k), value(v), next(n) {}
    };

    std::vector<Node*> buckets_;
    int count_;

    // Map a key to a bucket index in [0, buckets_.size()).
    // Uses std::hash<K> to get a hash value, then reduces modulo the bucket
    // count. Time: O(1) plus the cost of hashing the key.
    size_t index(const K& key) const {
        return std::hash<K>{}(key) % buckets_.size();
    }

public:
    // Construct an empty map with the given number of buckets.
    // Every bucket starts as a null chain (nullptr). num_buckets must be > 0.
    explicit HashMap(int num_buckets = 8)
        : buckets_(static_cast<size_t>(num_buckets), nullptr), count_(0) {
        assert(num_buckets > 0);
    }

    // Non-copyable: copying raw Node* chains would alias and double-free.
    HashMap(const HashMap&) = delete;
    HashMap& operator=(const HashMap&) = delete;

    // Destructor: free every Node in every bucket chain so there are no leaks.
    // Walk each bucket; for each chain, delete nodes one at a time.
    // Time: O(n) over all stored entries.
    ~HashMap() {
        // TODO: walk each bucket chain and delete every Node, then you are done.
        // Left empty for now (a leak, not a crash) so the test harness can run before
        // you implement it. A destructor must never throw, so do not put a throw here.
    }

    // Number of key/value pairs currently stored. Time: O(1).
    int size() const {
        throw std::logic_error("TODO: implement HashMap::size");
    }

    // True when the map holds no pairs. Time: O(1).
    bool empty() const {
        throw std::logic_error("TODO: implement HashMap::empty");
    }

    // Insert (key, value), or update value if key already exists.
    // Compute the bucket via index(key); scan its chain for an equal key.
    // If found, overwrite value and leave count_ unchanged; otherwise prepend
    // a new Node and increment count_.
    // Time: O(1) average, O(chain length) worst case.
    // Edge case: updating an existing key must not change size().
    // Note: a production table would also rehash (grow buckets_ and
    // redistribute nodes) once the load factor count_/buckets_.size() gets
    // high, to keep chains short. Rehashing is left as an optional TODO.
    void put(const K& key, const V& value) {
        throw std::logic_error("TODO: implement HashMap::put");
    }

    // Look up key. If present, copy its value into out and return true;
    // otherwise leave out untouched and return false.
    // Time: O(1) average, O(chain length) worst case.
    bool get(const K& key, V& out) const {
        throw std::logic_error("TODO: implement HashMap::get");
    }

    // True when key is present in the map.
    // Time: O(1) average, O(chain length) worst case.
    bool contains(const K& key) const {
        throw std::logic_error("TODO: implement HashMap::contains");
    }

    // Remove key if present. Unlink its Node from the bucket chain, delete it,
    // decrement count_, and return true. Return false when key is absent.
    // Time: O(1) average, O(chain length) worst case.
    // Edge cases: removing the head of a chain; key not in the map.
    bool erase(const K& key) {
        throw std::logic_error("TODO: implement HashMap::erase");
    }

    // Read-only view of the bucket contents for debugging. Does not reveal the
    // lookup/insert algorithm; it only walks the backing chains and formats
    // them as "bucket i: k=>v -> k=>v". Safe to call at any time.
    std::string debug_to_string() const {
        std::string s;
        for (size_t i = 0; i < buckets_.size(); ++i) {
            s += "bucket " + std::to_string(i) + ":";
            for (Node* cur = buckets_[i]; cur != nullptr; cur = cur->next) {
                s += " ";
                // Rely on operator<< via a stringstream-free path: only valid
                // when K and V are streamable. Kept minimal for visualization.
                s += " ->";
            }
            s += "\n";
        }
        return s;
    }
};

int main() {
    try {
        HashMap<std::string, int> m(4);

        // Empty state.
        assert(m.size() == 0);
        assert(m.empty());
        assert(!m.contains("missing"));

        int out = -1;
        assert(!m.get("missing", out));
        assert(out == -1);  // out left untouched on miss

        // Insert several pairs.
        m.put("one", 1);
        m.put("two", 2);
        m.put("three", 3);
        assert(m.size() == 3);
        assert(!m.empty());

        // Lookup.
        assert(m.contains("one"));
        assert(m.contains("two"));
        assert(m.contains("three"));
        assert(m.get("one", out) && out == 1);
        assert(m.get("two", out) && out == 2);
        assert(m.get("three", out) && out == 3);

        // Update an existing key: value changes, size does not.
        m.put("two", 22);
        assert(m.size() == 3);
        assert(m.get("two", out) && out == 22);

        // Missing key.
        assert(!m.contains("four"));
        assert(!m.get("four", out));

        // Erase.
        assert(m.erase("two"));
        assert(!m.contains("two"));
        assert(m.size() == 2);
        assert(!m.get("two", out));

        // Erasing an absent key returns false and changes nothing.
        assert(!m.erase("two"));
        assert(m.size() == 2);

        // Remaining keys still resolve.
        assert(m.get("one", out) && out == 1);
        assert(m.get("three", out) && out == 3);

        // Force collisions: insert enough keys that some share a bucket.
        for (int i = 0; i < 20; ++i) {
            m.put("k" + std::to_string(i), i);
        }
        for (int i = 0; i < 20; ++i) {
            assert(m.get("k" + std::to_string(i), out) && out == i);
        }
        assert(m.contains("one") && m.contains("three"));

        std::cout << "All checks passed\n";
    } catch (const std::exception& e) {
        std::cerr << "FAILED (likely unimplemented): " << e.what() << "\n";
        return 1;
    }
    return 0;
}
