// Source: https://leetcode.com/problems/longest-common-suffix-queries
// Title: Longest Common Suffix Queries
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two arrays of strings `wordsContainer` and `wordsQuery`.
//
// For each `wordsQuery[i]`, you need to find a string from `wordsContainer` that has the **longest common suffix** with `wordsQuery[i]`. If there are two or more strings in `wordsContainer` that share the longest common suffix, find the string that is the **smallest** in length. If there are two or more such strings that have the **same** smallest length, find the one that occurred **earlier** in `wordsContainer`.
//
// Return an array of integers `ans`, where `ans[i]` is the index of the string in `wordsContainer` that has the **longest common suffix** with `wordsQuery[i]`.
//
// **Example 1:**
//
// ```
// Input: wordsContainer = ["abcd","bcd","xbcd"], wordsQuery = ["cd","bcd","xyz"]
// Output: [1,1,1]
// Explanation:
// Let's look at each `wordsQuery[i]` separately:
// - For `wordsQuery[0] = "cd"`, strings from `wordsContainer` that share the longest common suffix `"cd"` are at indices 0, 1, and 2. Among these, the answer is the string at index 1 because it has the shortest length of 3.
// - For `wordsQuery[1] = "bcd"`, strings from `wordsContainer` that share the longest common suffix `"bcd"` are at indices 0, 1, and 2. Among these, the answer is the string at index 1 because it has the shortest length of 3.
// - For `wordsQuery[2] = "xyz"`, there is no string from `wordsContainer` that shares a common suffix. Hence the longest common suffix is `""`, that is shared with strings at index 0, 1, and 2. Among these, the answer is the string at index 1 because it has the shortest length of 3.
// ```
//
// **Example 2:**
//
// ```
// Input: wordsContainer = ["abcdefgh","poiuygh","ghghgh"], wordsQuery = ["gh","acbfgh","acbfegh"]
// Output: [2,0,2]
// Explanation:
// Let's look at each `wordsQuery[i]` separately:
// - For `wordsQuery[0] = "gh"`, strings from `wordsContainer` that share the longest common suffix `"gh"` are at indices 0, 1, and 2. Among these, the answer is the string at index 2 because it has the shortest length of 6.
// - For `wordsQuery[1] = "acbfgh"`, only the string at index 0 shares the longest common suffix `"fgh"`. Hence it is the answer, even though the string at index 2 is shorter.
// - For `wordsQuery[2] = "acbfegh"`, strings from `wordsContainer` that share the longest common suffix `"gh"` are at indices 0, 1, and 2. Among these, the answer is the string at index 2 because it has the shortest length of 6.
// ```
//
// **Constraints:**
//
// - `1 <= wordsContainer.length, wordsQuery.length <= 10^4`
// - `1 <= wordsContainer[i].length <= 5 * 10^3`
// - `1 <= wordsQuery[i].length <= 5 * 10^3`
// - `wordsContainer[i]` consists only of lowercase English letters.
// - `wordsQuery[i]` consists only of lowercase English letters.
// - Sum of `wordsContainer[i].length` is at most `5 * 10^5`.
// - Sum of `wordsQuery[i].length` is at most `5 * 10^5`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <vector>

using namespace std;

// Trie
//
// For each trie node, store the word with common suffix.
// We also store the word index and length.
// Note that we want shorter word and smaller index.
class Solution {
  using WordMeta = pair<int, int>;  // len, idx

  struct Trie {
    struct Node {
      int children[26] = {};
      WordMeta meta = {INT_MAX, 0};
    };

    vector<Node> nodes;

    Trie() : nodes(1) {}  // initialized with root node

    void insert(const string& word, int wordIdx) {
      const int wordLen = word.size();
      const WordMeta meta = {wordLen, wordIdx};
      int id = 0;
      for (int i = wordLen - 1; i >= 0; --i) {
        const int ch = word[i] - 'a';
        if (!nodes[id].children[ch]) {
          const int newId = nodes.size();
          nodes.emplace_back();
          nodes[id].children[ch] = newId;
        }
        nodes[id].meta = min(nodes[id].meta, meta);
        id = nodes[id].children[ch];
      }
      nodes[id].meta = min(nodes[id].meta, meta);
    }

    WordMeta query(const string& word) {
      const int wordLen = word.size();
      int id = 0;
      for (int i = wordLen - 1; i >= 0; --i) {
        const int ch = word[i] - 'a';
        if (!nodes[id].children[ch]) break;
        id = nodes[id].children[ch];
      }
      return nodes[id].meta;
    }
  };

 public:
  vector<int> stringIndices(const vector<string>& wordsContainer, const vector<string>& wordsQuery) {
    const int n = wordsContainer.size();

    // Build trie
    Trie trie;
    for (int i = 0; i < n; ++i) {
      trie.insert(wordsContainer[i], i);
    }

    // Query
    auto idxs = vector<int>();
    idxs.reserve(wordsQuery.size());
    for (const string& query : wordsQuery) {
      const auto [_, idx] = trie.query(query);
      idxs.push_back(idx);
    }
    return idxs;
  }
};
