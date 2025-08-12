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
// Input
//
// ["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
// [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
// Output
//
// [null, null, null, 1, null, -1, null, -1, 3, 4]
//
// Explanation
//
// LRUCache lRUCache = new LRUCache(2);
// lRUCache.put(1, 1); // cache is {1=1}
// lRUCache.put(2, 2); // cache is {1=1, 2=2}
// lRUCache.get(1);    // return 1
// lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
// lRUCache.get(2);    // returns -1 (not found)
// lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
// lRUCache.get(1);    // return -1 (not found)
// lRUCache.get(3);    // return 3
// lRUCache.get(4);    // return 4
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
#include <unordered_map>
#include <utility>

#include "../../utils/print.hpp"

using namespace std;

// Use Hash-Map + Double-Linked-List
class LRUCache {
  class Node {
   public:
    int key;
    int value;
    Node* prev;
    Node* next;

    Node(int key, int value) : key(key), value(value) {}
  };

  Node* head;
  Node* tail;
  unordered_map<int, Node*> nodeMap;
  int capacity;

  void remove(Node* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
  }

  void insert(Node* node) {
    auto next = tail;
    auto prev = tail->prev;

    prev->next = node;
    node->prev = prev;
    node->next = next;
    next->prev = node;
  }

 public:
  LRUCache(int capacity) {
    this->capacity = capacity;
    head = new Node(-1, -1);
    tail = new Node(-1, -1);
    head->next = tail;
    tail->prev = head;
  }

  int get(int key) {
    auto it = nodeMap.find(key);
    if (it == nodeMap.cend()) return -1;
    auto curr = it->second;
    remove(curr);
    insert(curr);
    return curr->value;
  }

  void put(int key, int value) {
    // Remove old node
    auto it = nodeMap.find(key);
    if (it != nodeMap.cend()) {
      remove(it->second);
    }

    // Insert new node
    auto node = new Node(key, value);
    insert(node);
    nodeMap[key] = node;

    // Remove oldest node
    if (nodeMap.size() > capacity) {
      auto old = head->next;
      remove(old);
      nodeMap.erase(old->key);
    }
  }
};

// Use Hash-Map + List (builtin)
class LRUCache2 {
  typedef pair<int, int> int2;  // (key, value)

  unordered_map<int, list<int2>::iterator> nodeMap;
  list<int2> nodeList;
  int capacity;

 public:
  LRUCache2(int capacity) : capacity(capacity) {}

  int get(int key) {
    auto it = nodeMap.find(key);
    if (it == nodeMap.cend()) return -1;
    auto value = it->second->second;

    // Remove old node
    nodeList.erase(it->second);
    nodeMap.erase(it);

    // Insert new node
    nodeList.push_front({key, value});
    nodeMap[key] = nodeList.begin();

    return value;
  }

  void put(int key, int value) {
    // Remove old node
    auto it = nodeMap.find(key);
    if (it != nodeMap.cend()) {
      nodeList.erase(it->second);
      nodeMap.erase(it);
    }

    // Insert new node
    nodeList.push_front({key, value});
    nodeMap[key] = nodeList.begin();

    // Remove oldest node
    if (nodeMap.size() > capacity) {
      auto it = nodeMap.find(nodeList.crbegin()->first);
      nodeMap.erase(it);
      nodeList.pop_back();
    }
  }
};
