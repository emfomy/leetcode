// Source: https://leetcode.com/problems/minimum-cost-to-convert-string-ii
// Title: Minimum Cost to Convert String II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two **0-indexed** strings `source` and `target`, both of length `n` and consisting of **lowercase** English characters. You are also given two **0-indexed** string arrays `original` and `changed`, and an integer array `cost`, where `cost[i]` represents the cost of converting the string `original[i]` to the string `changed[i]`.
//
// You start with the string `source`. In one operation, you can pick a **substring** `x` from the string, and change it to `y` at a cost of `z` **if** there exists **any** index `j` such that `cost[j] == z`, `original[j] == x`, and `changed[j] == y`. You are allowed to do **any** number of operations, but any pair of operations must satisfy **either** of these two conditions:
//
// - The substrings picked in the operations are `source[a..b]` and `source[c..d]` with either `b < c` **or** `d < a`. In other words, the indices picked in both operations are **disjoint**.
// - The substrings picked in the operations are `source[a..b]` and `source[c..d]` with `a == c` **and** `b == d`. In other words, the indices picked in both operations are **identical**.
//
// Return the **minimum** cost to convert the string `source` to the string `target` using **any** number of operations. If it is impossible to convert `source` to `target`, return `-1`.
//
// **Note** that there may exist indices `i`, `j` such that `original[j] == original[i]` and `changed[j] == changed[i]`.
//
// **Example 1:**
//
// ```
// Input: source = "abcd", target = "acbe", original = ["a","b","c","c","e","d"], changed = ["b","c","b","e","b","e"], cost = [2,5,5,1,2,20]
// Output: 28
// Explanation: To convert "abcd" to "acbe", do the following operations:
// - Change substring source[1..1] from "b" to "c" at a cost of 5.
// - Change substring source[2..2] from "c" to "e" at a cost of 1.
// - Change substring source[2..2] from "e" to "b" at a cost of 2.
// - Change substring source[3..3] from "d" to "e" at a cost of 20.
// The total cost incurred is 5 + 1 + 2 + 20 = 28.
// It can be shown that this is the minimum possible cost.
// ```
//
// **Example 2:**
//
// ```
// Input: source = "abcdefgh", target = "acdeeghh", original = ["bcd","fgh","thh"], changed = ["cde","thh","ghh"], cost = [1,3,5]
// Output: 9
// Explanation: To convert "abcdefgh" to "acdeeghh", do the following operations:
// - Change substring source[1..3] from "bcd" to "cde" at a cost of 1.
// - Change substring source[5..7] from "fgh" to "thh" at a cost of 3. We can do this operation because indices [5,7] are disjoint with indices picked in the first operation.
// - Change substring source[5..7] from "thh" to "ghh" at a cost of 5. We can do this operation because indices [5,7] are disjoint with indices picked in the first operation, and identical with indices picked in the second operation.
// The total cost incurred is 1 + 3 + 5 = 9.
// It can be shown that this is the minimum possible cost.
// ```
//
// **Example 3:**
//
// ```
// Input: source = "abcdefgh", target = "addddddd", original = ["bcd","defgh"], changed = ["ddd","ddddd"], cost = [100,1578]
// Output: -1
// Explanation: It is impossible to convert "abcdefgh" to "addddddd".
// If you select substring source[1..3] as the first operation to change "abcdefgh" to "adddefgh", you cannot select substring source[3..7] as the second operation because it has a common index, 3, with the first operation.
// If you select substring source[3..7] as the first operation to change "abcdefgh" to "abcddddd", you cannot select substring source[1..3] as the second operation because it has a common index, 3, with the first operation.
// ```
//
// **Constraints:**
//
// - `1 <= source.length == target.length <= 1000`
// - `source`, `target` consist only of lowercase English characters.
// - `1 <= cost.length == original.length == changed.length <= 100`
// - `1 <= original[i].length == changed[i].length <= source.length`
// - `original[i]`, `changed[i]` consist only of lowercase English characters.
// - `original[i] != changed[i]`
// - `1 <= cost[i] <= 10^6`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cstdint>
#include <vector>

using namespace std;

// Trie + Floyd–Warshall + DP
//
// We first group the patterns by their length.
// Next do DP on the source string.
// DP[i] is the minimal cost of changing source[:i] to target[:i].
//
// We use Trie to speed up string matching.
class Solution {
  struct Trie {
    struct Node {
      vector<Node*> children;
      int id;
      Node() : id(-1), children(26, nullptr) {}

      inline Node*& child(char ch) { return children[ch - 'a']; }
    };

    int size;
    Node* root;

    Trie() : size(0), root(new Node()) {}

    int add(string& word) {
      // Insert
      auto node = root;
      for (auto ch : word) {
        if (node->child(ch) == nullptr) node->child(ch) = new Node();
        node = node->child(ch);
      }

      // Assign ID
      if (node->id == -1) node->id = size++;
      return node->id;
    }
  };

 public:
  long long minimumCost(string source, string target, vector<string>& original, vector<string>& changed, vector<int>& cost) {
    int n = source.size(), m = original.size();

    auto trie = Trie();

    // Init graph
    auto graph = vector(2 * m, vector(2 * m, INT64_MAX));
    for (auto i = 0; i < m; ++i) {
      auto o = original[i], c = changed[i];
      auto oid = trie.add(original[i]);
      auto cid = trie.add(changed[i]);
      int64_t w = cost[i];
      graph[oid][cid] = min(graph[oid][cid], w);
    }
    m = trie.size;

    // Floyd–Warshall
    for (auto k = 0; k < m; ++k) {
      for (auto i = 0; i < m; ++i) {
        for (auto j = 0; j < m; ++j) {
          if (graph[i][k] != INT64_MAX && graph[k][j] != INT64_MAX) {
            graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
          }
        }
      }
    }

    // DP
    auto dp = vector(n + 1, INT64_MAX);
    dp[0] = 0;
    for (auto i = 0; i < n; ++i) {
      if (dp[i] == INT64_MAX) continue;

      // Handle same character
      if (source[i] == target[i]) {
        dp[i + 1] = min(dp[i + 1], dp[i]);
      }

      // Try pattern
      auto sNode = trie.root, tNode = trie.root;
      for (auto j = i; j < n; ++j) {
        sNode = sNode->child(source[j]);
        tNode = tNode->child(target[j]);
        if (sNode == nullptr || tNode == nullptr) break;  // pattern not found
        auto sid = sNode->id, tid = tNode->id;
        if (sid >= 0 && tid >= 0 && graph[sid][tid] != INT64_MAX) {
          dp[j + 1] = min(dp[j + 1], dp[i] + graph[sid][tid]);
        }
      }
    }

    return (dp[n] == INT64_MAX) ? -1 : dp[n];
  }
};
