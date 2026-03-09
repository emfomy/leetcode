// Source: https://leetcode.com/problems/longest-word-in-dictionary
// Title: Longest Word in Dictionary
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of strings `words` representing an English Dictionary, return the longest word in `words` that can be built one character at a time by other words in `words`.
//
// If there is more than one possible answer, return the longest word with the smallest lexicographical order. If there is no answer, return the empty string.
//
// Note that the word should be built from left to right with each additional character being added to the end of a previous word.
//
// **Example 1:**
//
// ```
// Input: words = ["w","wo","wor","worl","world"]
// Output: "world"
// Explanation: The word "world" can be built one character at a time by "w", "wo", "wor", and "worl".
// ```
//
// **Example 2:**
//
// ```
// Input: words = ["a","banana","app","appl","ap","apply","apple"]
// Output: "apple"
// Explanation: Both "apply" and "apple" can be built from other words in the dictionary. However, "apple" is lexicographically smaller than "apply".
// ```
//
// **Constraints:**
//
// - `1 <= words.length <= 1000`
// - `1 <= words[i].length <= 30`
// - `words[i]` consists of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

// Hash Set + Topology Sort
//
// Sort the words by their lengths.
//
// We use a hash set for the constructable words.
// We finst put a empty string in to the set since it is the prefix of single letter.
// Next loop through the words, check if word[:-1] is in the set.
// If so, then put this word into it.
//
// The longest word int the is the answer.
class Solution {
 public:
  string longestWord(vector<string>& words) {
    // Guard
    if (words.empty()) return "";

    // Sort
    const auto comp = [](const string& a, const string& b) -> bool {
      return a.size() != b.size() ? a.size() < b.size() : a > b;
    };
    sort(words.begin(), words.end(), comp);

    // Guard, we need single letter words to start building
    if (words.front().size() != 1) return "";

    // Topology Sort
    auto visited = unordered_set<string_view>();
    visited.reserve(words.size() + 1);
    visited.insert("");
    string ans;
    for (const string& word : words) {
      string_view prefix = string_view(word).substr(0, word.size() - 1);
      if (visited.contains(prefix)) {
        visited.insert(word);
        ans = word;
      }
    }

    return ans;
  }
};

// Trie + Topology Sort
//
// Use trie instead of hash set.
class Solution2 {
  struct Trie {
    struct Node {
      Node* children[26] = {nullptr};
      bool isWord = false;

      ~Node() {
        for (auto child : children) {
          delete child;
        }
      }
    };

    Node* root;

    Trie() : root(new Node()) {};
    ~Trie() { delete root; }

    void insert(const string_view word) {
      Node* node = root;
      for (const auto ch : word) {
        Node*& next = node->children[ch - 'a'];
        if (!next) next = new Node();
        node = next;
      }
      node->isWord = true;
    }

    bool contains(const string_view word) {
      Node* node = root;
      for (const auto ch : word) {
        Node*& next = node->children[ch - 'a'];
        if (!next) return false;
        node = next;
      }
      return node->isWord;
    }
  };

 public:
  string longestWord(vector<string>& words) {
    // Guard
    if (words.empty()) return "";

    // Sort
    const auto comp = [](const string& a, const string& b) -> bool {
      return a.size() != b.size() ? a.size() < b.size() : a > b;
    };
    sort(words.begin(), words.end(), comp);

    // Guard, we need single letter words to start building
    if (words.front().size() != 1) return "";

    // Topology Sort
    Trie trie;
    trie.insert("");
    string ans;
    for (const string& word : words) {
      string_view prefix = string_view(word).substr(0, word.size() - 1);
      if (trie.contains(prefix)) {
        trie.insert(word);
        ans = word;
      }
    }

    return ans;
  }
};

// Trie + DFS
//
// We can create the trie at the beginning for all the strings.
// Next run DFS on the trie to find the maximum constructable string.
class Solution3 {
  struct Node {
    Node* children[26] = {nullptr};
    bool isWord = false;

    ~Node() {
      for (auto child : children) {
        delete child;
      }
    }
  };

  struct Trie {
    Node* root;

    Trie() : root(new Node()) {};
    ~Trie() { delete root; }

    void insert(const string_view word) {
      Node* node = root;
      for (const auto ch : word) {
        Node*& next = node->children[ch - 'a'];
        if (!next) next = new Node();
        node = next;
      }
      node->isWord = true;
    }
  };

 public:
  string longestWord(const vector<string>& words) {
    // Guard
    if (words.empty()) return "";

    // Build trie
    Trie trie;
    for (const auto& word : words) {
      trie.insert(word);
    }

    // DFS
    string word = "";
    string ans = "";
    dfs(trie.root, word, ans);

    return ans;
  }

  void dfs(const Node* node, string& word, string& ans) {
    if (ans.size() < word.size() || ans.size() == word.size() && ans > word) {
      ans = word;
    }
    for (int i = 0; i < 26; ++i) {
      const Node* child = node->children[i];
      if (!child || !child->isWord) continue;
      word.push_back('a' + i);
      dfs(child, word, ans);
      word.pop_back();
    }
  }
};
