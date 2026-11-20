// Source: https://leetcode.com/problems/implement-trie-ii-prefix-tree
// Title: Implement Trie II (Prefix Tree)
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A **trie** (pronounced as "try") or **prefix tree** is a tree data structure used to efficiently store and retrieve keys in a dataset of strings. There are various applications of this data structure, such as autocomplete and spellchecker.
//
// Implement the Trie class:
//
// - `Trie()` Initializes the trie object.
// - `void insert(String word)` Inserts the string `word` into the trie.
// - `int countWordsEqualTo(String word)` Returns the number of instances of the string `word` in the trie.
// - `int countWordsStartingWith(String prefix)` Returns the number of strings in the trie that have the string `prefix` as a prefix.
// - `void erase(String word)` Erases the string `word` from the trie.
//
// **Example 1:**
//
// ```
// Input:
// ["Trie", "insert", "insert", "countWordsEqualTo", "countWordsStartingWith", "erase", "countWordsEqualTo", "countWordsStartingWith", "erase", "countWordsStartingWith"]
// [[], ["apple"], ["apple"], ["apple"], ["app"], ["apple"], ["apple"], ["app"], ["apple"], ["app"]]
//
// Output:
// [null, null, null, 2, 2, null, 1, 1, null, 0]
//
// Explanation:
// Trie trie = new Trie();
// trie.insert("apple");               // Inserts "apple".
// trie.insert("apple");               // Inserts another "apple".
// trie.countWordsEqualTo("apple");    // There are two instances of "apple" so return 2.
// trie.countWordsStartingWith("app"); // "app" is a prefix of "apple" so return 2.
// trie.erase("apple");                // Erases one "apple".
// trie.countWordsEqualTo("apple");    // Now there is only one instance of "apple" so return 1.
// trie.countWordsStartingWith("app"); // return 1
// trie.erase("apple");                // Erases "apple". Now the trie is empty.
// trie.countWordsStartingWith("app"); // return 0
// ```
//
// **Constraints:**
//
// - `1 <= word.length, prefix.length <= 2000`
// - `word` and `prefix` consist only of lowercase English letters.
// - At most `3 * 10^4` calls **in total** will be made to `insert`, `countWordsEqualTo`, `countWordsStartingWith`, and `erase`.
// - It is guaranteed that for any function call to `erase`, the string `word` will exist in the trie.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

using namespace std;

class Trie {
  struct Node {
    Node* children[26] = {};
    int wordCount = 0;
    int prefixCount = 0;
  };

  Node root;

 public:
  Trie() {}

  void insert(const string& word) {
    Node* node = &root;
    for (const char ch : word) {
      ++node->prefixCount;
      Node*& child = node->children[ch - 'a'];
      if (!child) child = new Node();
      node = child;
    }
    ++node->prefixCount;
    ++node->wordCount;
  }

  void erase(const string& word) {
    Node* node = &root;
    for (const char ch : word) {
      --node->prefixCount;
      node = node->children[ch - 'a'];  // we guaranteed that word exist
    }
    --node->prefixCount;
    --node->wordCount;
  }

  int countWordsEqualTo(const string& word) const {
    const Node* node = &root;
    for (const char ch : word) {
      const Node* const& child = node->children[ch - 'a'];
      if (!child) return 0;
      node = child;
    }
    return node->wordCount;
  }

  int countWordsStartingWith(const string& prefix) const {
    const Node* node = &root;
    for (const char ch : prefix) {
      const Node* const& child = node->children[ch - 'a'];
      if (!child) return 0;
      node = child;
    }
    return node->prefixCount;
  }
};

class Trie2 {
  struct Node {
    int children[26] = {};
    int wordCount = 0;
    int prefixCount = 0;
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
      ++nodes[id].prefixCount;
      if (!nodes[id].children[ch]) nodes[id].children[ch] = newNode();
      id = nodes[id].children[ch];
    }
    ++nodes[id].prefixCount;
    ++nodes[id].wordCount;
  }

  void erase(const string& word) {
    int id = 0;
    for (char ch : word) {
      ch -= 'a';
      --nodes[id].prefixCount;
      id = nodes[id].children[ch];  // we guaranteed that word exist
    }
    --nodes[id].prefixCount;
    --nodes[id].wordCount;
  }

  int countWordsEqualTo(const string& word) const {
    int id = 0;
    for (char ch : word) {
      ch -= 'a';
      if (!nodes[id].children[ch]) return 0;
      id = nodes[id].children[ch];
    }
    return nodes[id].wordCount;
  }

  int countWordsStartingWith(const string& prefix) const {
    int id = 0;
    for (char ch : prefix) {
      ch -= 'a';
      if (!nodes[id].children[ch]) return 0;
      id = nodes[id].children[ch];
    }
    return nodes[id].prefixCount;
  }
};
