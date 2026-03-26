// Source: https://leetcode.com/problems/all-oone-data-structure
// Title: All O`one Data Structure
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Design a data structure to store the strings' count with the ability to return the strings with minimum and maximum counts.
//
// Implement the `AllOne` class:
//
// - `AllOne()` Initializes the object of the data structure.
// - `inc(String key)` Increments the count of the string `key` by `1`. If `key` does not exist in the data structure, insert it with count `1`.
// - `dec(String key)` Decrements the count of the string `key` by `1`. If the count of `key` is `0` after the decrement, remove it from the data structure. It is guaranteed that `key` exists in the data structure before the decrement.
// - `getMaxKey()` Returns one of the keys with the maximal count. If no element exists, return an empty string `""`.
// - `getMinKey()` Returns one of the keys with the minimum count. If no element exists, return an empty string `""`.
//
// **Note** that each function must run in `O(1)` average time complexity.
//
// **Example 1:**
//
// ```
// Input:
// ["AllOne", "inc", "inc", "getMaxKey", "getMinKey", "inc", "getMaxKey", "getMinKey"]
// [[], ["hello"], ["hello"], [], [], ["leet"], [], []]
//
// Output:
// [null, null, null, "hello", "hello", null, "hello", "leet"]
//
// Explanation:
// AllOne allOne = new AllOne();
// allOne.inc("hello");
// allOne.inc("hello");
// allOne.getMaxKey(); // return "hello"
// allOne.getMinKey(); // return "hello"
// allOne.inc("leet");
// allOne.getMaxKey(); // return "hello"
// allOne.getMinKey(); // return "leet"
// ```
//
// **Constraints:**
//
// - `1 <= key.length <= 10`
// - `key` consists of lowercase English letters.
// - It is guaranteed that for each call to `dec`, `key` is existing in the data structure.
// - At most `5 * 10^4`calls will be made to `inc`, `dec`, `getMaxKey`, and `getMinKey`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iterator>
#include <list>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// Hash Map + Hash Set + Linked List
//
// We use a linked list (sorted by frequency).
// Each node stores the frequency and the keys with this value.
// We also use a hash map to map the key to node.
//
// For `inc`, we move that key to the node with new frequency.
// If target node does not exist, insert it after this node.
// We also delete the old node if it becomes zero.
//
// Similary to `dec`.
// Hash Map + Hash Set + Linked List
//
// We use a linked list (sorted by frequency).
// Each node stores the frequency and the keys with this value.
// We also use a hash map to map the key to node.
//
// For `inc`, we move that key to the node with new frequency.
// If target node does not exist, insert it after this node.
// We also delete the old node if it becomes zero.
//
// Similary to `dec`.
class AllOne {
  struct Data {
    int freq;
    unordered_set<string> keys;

    Data(int freq) : freq(freq) {}
  };

  using List = list<Data>;
  using Node = List::iterator;

  unordered_map<string, Node> key2node;
  List nodes;

 public:
  AllOne() {
    nodes.push_back(Data{0});  // sentinel node for zero frequency
  }

  void inc(const string &key) {
    // Find node
    Node oldNode = key2node.contains(key) ? key2node[key] : nodes.begin();
    Node newNode = next(oldNode);  // next might not exist
    if (newNode == nodes.cend() || newNode->freq > oldNode->freq + 1) {
      newNode = nodes.insert(newNode, Data{oldNode->freq + 1});
    }

    // Update old node, avoid delete sentinel
    oldNode->keys.erase(key);
    if (oldNode != nodes.cbegin() && oldNode->keys.empty()) {
      nodes.erase(oldNode);
    }

    // Update old node
    newNode->keys.insert(key);
    key2node[key] = newNode;
  }

  void dec(const string &key) {
    // Find node
    Node oldNode = key2node.at(key);  // ensure existence
    Node newNode = prev(oldNode);     // prev exist since freq > 0
    if (newNode->freq < oldNode->freq - 1) {
      newNode = nodes.insert(oldNode, Data{oldNode->freq - 1});
    }

    // Update old node
    oldNode->keys.erase(key);
    if (oldNode->keys.empty()) nodes.erase(oldNode);

    // Update new node
    if (newNode->freq > 0) {
      newNode->keys.insert(key);
      key2node[key] = newNode;
    } else {
      key2node.erase(key);
    }
  }

  string getMaxKey() {  //
    return key2node.empty() ? "" : prev(nodes.cend())->keys.cbegin()->data();
  }

  string getMinKey() {  //
    return key2node.empty() ? "" : next(nodes.cbegin())->keys.cbegin()->data();
  }
};
