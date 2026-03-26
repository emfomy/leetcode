// Source: https://leetcode.com/problems/lfu-cache
// Title: LFU Cache
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Design and implement a data structure for a **Least Frequently Used (LFU)** (https://en.wikipedia.org/wiki/Least_frequently_used) cache.
//
// Implement the `LFUCache` class:
//
// - `LFUCache(int capacity)` Initializes the object with the `capacity` of the data structure.
// - `int get(int key)` Gets the value of the `key` if the `key` exists in the cache. Otherwise, returns `-1`.
// - `void put(int key, int value)` Update the value of the `key` if present, or inserts the `key` if not already present. When the cache reaches its `capacity`, it should invalidate and remove the **least frequently used** key before inserting a new item. For this problem, when there is a **tie** (i.e., two or more keys with the same frequency), the **least recently used** `key` would be invalidated.
//
// To determine the least frequently used key, a **use counter** is maintained for each key in the cache. The key with the smallest **use counter** is the least frequently used key.
//
// When a key is first inserted into the cache, its **use counter** is set to `1` (due to the `put` operation). The **use counter** for a key in the cache is incremented either a `get` or `put` operation is called on it.
//
// The functions`get`and`put`must each run in `O(1)` average time complexity.
//
// **Example 1:**
//
// ```
// Input
//
// ["LFUCache", "put", "put", "get", "put", "get", "get", "put", "get", "get", "get"]
// [[2], [1, 1], [2, 2], [1], [3, 3], [2], [3], [4, 4], [1], [3], [4]]
// Output
//
// [null, null, null, 1, null, -1, 3, null, -1, 3, 4]
//
// Explanation
//
// // cnt(x) = the use counter for key x
// // cache=[] will show the last used order for tiebreakers (leftmost element is  most recent)
// LFUCache lfu = new LFUCache(2);
// lfu.put(1, 1);   // cache=[1,_], cnt(1)=1
// lfu.put(2, 2);   // cache=[2,1], cnt(2)=1, cnt(1)=1
// lfu.get(1);      // return 1
//                  // cache=[1,2], cnt(2)=1, cnt(1)=2
// lfu.put(3, 3);   // 2 is the LFU key because cnt(2)=1 is the smallest, invalidate 2.
//                 // cache=[3,1], cnt(3)=1, cnt(1)=2
// lfu.get(2);      // return -1 (not found)
// lfu.get(3);      // return 3
//                  // cache=[3,1], cnt(3)=2, cnt(1)=2
// lfu.put(4, 4);   // Both 1 and 3 have the same cnt, but 1 is LRU, invalidate 1.
//                  // cache=[4,3], cnt(4)=1, cnt(3)=2
// lfu.get(1);      // return -1 (not found)
// lfu.get(3);      // return 3
//                  // cache=[3,4], cnt(4)=1, cnt(3)=3
// lfu.get(4);      // return 4
//                  // cache=[4,3], cnt(4)=2, cnt(3)=3
// ```
//
// **Constraints:**
//
// - `1 <= capacity<= 10^4`
// - `0 <= key <= 10^5`
// - `0 <= value <= 10^9`
// - At most `2 * 10^5`calls will be made to `get` and `put`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <list>
#include <map>
#include <unordered_map>
#include <utility>

using namespace std;

// Hash Map + Tree Map
//
// Use a hashmap to store key -> (value, frequency).
// Use a treemap to store frequency -> key.
class LFUCache {
  const int capacity;
  int now = 0;

  using Label = pair<int, int>;  // (freq, ts)

  unordered_map<int, pair<int, Label>> data;  // key -> (val, label)
  map<Label, int> label2key;                  // label -> key

 public:
  LFUCache(int capacity) : capacity(capacity) {}

  int get(int key) {
    ++now;

    // Search
    const auto it = data.find(key);
    if (it == data.cend()) return -1;

    // Get
    const int val = it->second.first;
    Label &label = it->second.second;

    // Update
    label2key.erase(label);
    ++label.first;       // freq
    label.second = now;  // ts
    label2key[label] = key;

    return val;
  }

  void put(int key, int value) {
    ++now;

    const auto it = data.find(key);
    if (it != data.cend()) {
      // Update
      it->second.first = value;
      Label &label = it->second.second;
      label2key.erase(label);
      ++label.first;       // freq
      label.second = now;  // ts
      label2key[label] = key;
    } else {
      // Evict
      if (data.size() == capacity) {
        const auto evictIt = label2key.cbegin();
        int evictKey = evictIt->second;
        label2key.erase(evictIt);
        data.erase(evictKey);
      }

      // Insert
      Label label{1, now};
      data[key] = {value, label};
      label2key[label] = key;
    }
  }
};

// Hash Map + Linked List
//
// Use a hashmap to store key -> node
// Use a hashmap to store frequency -> linked list of data.
class LFUCache2 {
  const int capacity;
  int minFreq;

  struct Data {
    int key;
    int val;
    int freq;
  };
  using List = list<Data>;
  using Node = List::iterator;
  using KeyMap = unordered_map<int, Node>;

  unordered_map<int, Node> key2node;    // key -> node
  unordered_map<int, List> freq2nodes;  // freq -> list (newest at first)

  void updateNode(Node &node) {
    const int oldFreq = node->freq;
    const int newFreq = ++node->freq;
    freq2nodes[newFreq].splice(freq2nodes[newFreq].cbegin(), freq2nodes[oldFreq], node);
    if (freq2nodes[minFreq].empty()) {
      ++minFreq;  // =newFreq, must not be empty
    }
  }

 public:
  LFUCache2(int capacity) : capacity(capacity), minFreq(0) {
    key2node.reserve(capacity);
    freq2nodes.reserve(capacity);
  }

  int get(int key) {
    // Search
    const auto it = key2node.find(key);
    if (it == key2node.cend()) return -1;

    // Update
    auto &node = it->second;
    updateNode(node);

    return node->val;
  }

  void put(int key, int value) {
    const auto it = key2node.find(key);
    if (it != key2node.cend()) {
      // Update
      auto &node = it->second;
      node->val = value;
      updateNode(node);
    } else {
      // Evict
      if (key2node.size() == capacity) {
        const int evictKey = freq2nodes[minFreq].back().key;
        freq2nodes[minFreq].pop_back();
        key2node.erase(evictKey);
      }

      // Insert
      freq2nodes[1].push_front({key, value, 1});
      key2node[key] = freq2nodes[1].begin();
      minFreq = 1;
    }
  }
};
