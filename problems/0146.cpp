// Source: https://leetcode.com/problems/lru-cache
// Title: LRU Cache
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Design a data structure that follows the constraints of a **Least Recently Used (LRU) cache** (https://en.wikipedia.org/wiki/Cache_replacement_policies#LRU).
//
// Implement the `LRUCache` class:
//
// - `LRUCache(int capacity)` Initialize the LRU cache with **positive** size `capacity`.
// - `int get(int key)` Return the value of the `key` if the key exists, otherwise return `-1`.
// - `void put(int key, int value)` Update the value of the `key` if the `key` exists. Otherwise, add the `key-value` pair to the cache. If the number of keys exceeds the `capacity` from this operation, **evict** the least recently used key.
//
// The functions `get` and `put` must each run in `O(1)` average time complexity.
//
// **Example 1:**
//
// ```
// Input:
//   ["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
//   [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
// Output:
//   [null, null, null, 1, null, -1, null, -1, 3, 4]
// Explanation:
//   LRUCache lRUCache = new LRUCache(2);
//   lRUCache.put(1, 1); // cache is {1=1}
//   lRUCache.put(2, 2); // cache is {1=1, 2=2}
//   lRUCache.get(1);    // return 1
//   lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
//   lRUCache.get(2);    // returns -1 (not found)
//   lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
//   lRUCache.get(1);    // return -1 (not found)
//   lRUCache.get(3);    // return 3
//   lRUCache.get(4);    // return 4
// ```
//
// **Constraints:**
//
// - `1 <= capacity <= 3000`
// - `0 <= key <= 10^4`
// - `0 <= value <= 10^5`
// - At most `2 * 10^5` calls will be made to `get` and `put`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <list>
#include <map>
#include <unordered_map>
#include <utility>

using namespace std;

// Hash Map + Tree Map
//
// Use a incremental id as timestamp.
//
// Use a hashmap to store key -> (value, timestamp).
// Use a treemap to store timestamp -> key.
//
// After any operation (get/put), increate the timestamp.
// If reach the capacity, drop the oldest data by timestamp.
class LRUCache {
  const int capacity;
  int now = 0;

  unordered_map<int, pair<int, int>> key2val;  // key -> (val, ts)
  map<int, int> ts2key;                        // ts -> key

 public:
  LRUCache(int capacity) : capacity(capacity) {
    key2val.reserve(capacity);  //
  }

  int get(int key) {
    ++now;

    // Search
    const auto it = key2val.find(key);
    if (it == key2val.cend()) return -1;

    // Get
    const auto [val, ts] = it->second;

    // Update
    it->second.second = now;
    ts2key.erase(ts);
    ts2key[now] = key;

    return val;
  }

  void put(int key, int value) {
    ++now;

    const auto it = key2val.find(key);
    if (it != key2val.cend()) {
      // Update
      const auto [oldVal, oldTs] = it->second;
      it->second = {value, now};
      ts2key.erase(oldTs);
      ts2key[now] = key;
    } else {
      // Evict
      if (key2val.size() == capacity) {
        const auto evictIt = ts2key.cbegin();
        int evictKey = evictIt->second;
        ts2key.erase(evictIt);
        key2val.erase(evictKey);
      }

      // Insert
      key2val[key] = {value, now};
      ts2key[now] = key;
    }
  }
};

// Hash Map + Linked List
//
// Use a hashmap to store key -> node.
// Use a linked list to store data.
class LRUCache2 {
  const int capacity;
  int now = 0;

  struct Data {
    int key;
    int value;
  };

  using List = list<Data>;
  using Node = List::iterator;

  unordered_map<int, Node> key2node;  // key -> node
  List nodes;                         // newest at front

 public:
  LRUCache2(int capacity) : capacity(capacity) {
    key2node.reserve(capacity);  //
  }

  int get(int key) {
    const auto it = key2node.find(key);
    if (it == key2node.cend()) return -1;

    // Update
    const Node& node = it->second;
    nodes.splice(nodes.cbegin(), nodes, node);
    return node->value;
  }

  void put(int key, int value) {
    const auto it = key2node.find(key);
    if (it != key2node.cend()) {
      // Update
      Node& node = it->second;
      nodes.splice(nodes.cbegin(), nodes, node);
      node->value = value;
    } else {
      // Evict
      if (nodes.size() == capacity) {
        const int evictKey = nodes.back().key;
        nodes.pop_back();
        key2node.erase(evictKey);
      }

      // Insert
      nodes.push_front({key, value});
      key2node[key] = nodes.begin();
    }
  }
};
