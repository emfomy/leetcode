// Source: https://leetcode.com/problems/implement-trie-prefix-tree
// Title: Implement Trie (Prefix Tree)
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A **trie** (pronounced as "try") or **prefix tree** is a tree data structure used to efficiently store and retrieve keys in a dataset of strings. There are various applications of this data structure, such as autocomplete and spellchecker.
//
// Implement the Trie class:
//
// - `Trie()` Initializes the trie object.
// - `void insert(String word)` Inserts the string `word` into the trie.
// - `boolean search(String word)` Returns `true` if the string `word` is in the trie (i.e., was inserted before), and `false` otherwise.
// - `boolean startsWith(String prefix)` Returns `true` if there is a previously inserted string `word` that has the prefix `prefix`, and `false` otherwise.
//
// **Example 1:**
//
// ```
// Input:
// ["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
// [[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
//
// Output:
// [null, null, true, false, true, null, true]
//
// Explanation:
// Trie trie = new Trie();
// trie.insert("apple");
// trie.search("apple");   // return True
// trie.search("app");     // return False
// trie.startsWith("app"); // return True
// trie.insert("app");
// trie.search("app");     // return True
// ```
//
// **Constraints:**
//
// - `1 <= word.length, prefix.length <= 2000`
// - `word` and `prefix` consist only of lowercase English letters.
// - At most `3 * 10^4` calls **in total** will be made to `insert`, `search`, and `startsWith`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

using namespace std;

class Trie {
  struct Node {
    Node* children[26] = {};
    bool isWord = false;
  };

  Node root;

 public:
  Trie() {}

  void insert(const string& word) {
    Node* node = &root;
    for (const char ch : word) {
      Node*& child = node->children[ch - 'a'];
      if (!child) child = new Node();
      node = child;
    }
    node->isWord = true;
  }

  bool search(const string& word) const {
    const Node* node = &root;
    for (const char ch : word) {
      Node* const& child = node->children[ch - 'a'];
      if (!child) return false;
      node = child;
    }
    return node->isWord;
  }

  bool startsWith(const string& prefix) const {
    const Node* node = &root;
    for (const char ch : prefix) {
      Node* const& child = node->children[ch - 'a'];
      if (!child) return false;
      node = child;
    }
    return true;
  }
};

class Trie2 {
  struct Node {
    int children[26] = {};
    bool isWord = false;
  };

  vector<Node> nodes;

  int newNode() {
    int id = nodes.size();
    nodes.emplace_back();
    return id;
  }

 public:
  // Initialized with root with id=0
  Trie2() : nodes(1) {}

  void insert(const string& word) {
    int id = 0;
    for (char ch : word) {
      ch -= 'a';
      if (!nodes[id].children[ch]) nodes[id].children[ch] = newNode();
      id = nodes[id].children[ch];
    }
    nodes[id].isWord = true;
  }

  bool search(const string& word) const {
    int id = 0;
    for (char ch : word) {
      ch -= 'a';
      if (!nodes[id].children[ch]) return false;
      id = nodes[id].children[ch];
    }
    return nodes[id].isWord;
  }

  bool startsWith(const string& prefix) const {
    int id = 0;
    for (char ch : prefix) {
      ch -= 'a';
      if (!nodes[id].children[ch]) return false;
      id = nodes[id].children[ch];
    }
    return true;
  }
};
