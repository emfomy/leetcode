// Source: https://leetcode.com/problems/minimum-cost-to-convert-string-i
// Title: Minimum Cost to Convert String I
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two **0-indexed** strings `source` and `target`, both of length `n` and consisting of **lowercase** English letters. You are also given two **0-indexed** character arrays `original` and `changed`, and an integer array `cost`, where `cost[i]` represents the cost of changing the character `original[i]` to the character `changed[i]`.
//
// You start with the string `source`. In one operation, you can pick a character `x` from the string and change it to the character `y` at a cost of `z` **if** there exists **any** index `j` such that `cost[j] == z`, `original[j] == x`, and `changed[j] == y`.
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
// Explanation: To convert the string "abcd" to string "acbe":
// - Change value at index 1 from 'b' to 'c' at a cost of 5.
// - Change value at index 2 from 'c' to 'e' at a cost of 1.
// - Change value at index 2 from 'e' to 'b' at a cost of 2.
// - Change value at index 3 from 'd' to 'e' at a cost of 20.
// The total cost incurred is 5 + 1 + 2 + 20 = 28.
// It can be shown that this is the minimum possible cost.
// ```
//
// **Example 2:**
//
// ```
// Input: source = "aaaa", target = "bbbb", original = ["a","c"], changed = ["c","b"], cost = [1,2]
// Output: 12
// Explanation: To change the character 'a' to 'b' change the character 'a' to 'c' at a cost of 1, followed by changing the character 'c' to 'b' at a cost of 2, for a total cost of 1 + 2 = 3. To change all occurrences of 'a' to 'b', a total cost of 3 * 4 = 12 is incurred.
// ```
//
// **Example 3:**
//
// ```
// Input: source = "abcd", target = "abce", original = ["a"], changed = ["e"], cost = [10000]
// Output: -1
// Explanation: It is impossible to convert source to target because the value at index 3 cannot be changed from 'd' to 'e'.
// ```
//
// **Constraints:**
//
// - `1 <= source.length == target.length <= 10^5`
// - `source`, `target` consist of lowercase English letters.
// - `1 <= cost.length == original.length == changed.length <= 2000`
// - `original[i]`, `changed[i]` are lowercase English letters.
// - `1 <= cost[i] <= 10^6`
// - `original[i] != changed[i]`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <climits>
#include <cstdint>
#include <functional>
#include <queue>
#include <source_location>
#include <unordered_map>
#include <vector>

using namespace std;

// BFS + Heap (Dijkstra)
//
// First loop through the source and target strings and list all character pairs.
// Next loop through all starting characters, run BFS to find the minimal cost to each target.
class Solution {
 public:
  long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
    int n = source.size(), m = original.size();

    // Count pairs
    auto pairs = unordered_map<char, unordered_map<char, int>>();  // (source, target) -> count
    for (auto i = 0; i < n; ++i) {
      auto s = source[i], t = target[i];
      ++pairs[s][t];
    }

    // Build graph
    auto graph = unordered_map<char, unordered_map<char, int64_t>>();  // (original, changed) -> cost
    for (auto j = 0; j < m; ++j) {
      auto o = original[j], c = changed[j];
      int64_t w = cost[j];
      if (graph[o].contains(c)) {
        graph[o][c] = min(graph[o][c], w);
      } else {
        graph[o][c] = w;
      }
    }

    // BFS
    int64_t ans = 0;
    for (auto& [s, sMap] : pairs) {
      auto nodeCosts = vector<int64_t>(128, -1);
      auto heap = priority_queue(greater(), std::move(vector<pair<int64_t, char>>()));  // min-heap, (cost, node)
      heap.push({0, s});

      while (!heap.empty()) {
        auto [currCost, curr] = heap.top();
        heap.pop();

        if (nodeCosts[curr] != -1) continue;
        nodeCosts[curr] = currCost;

        for (auto [next, nextCost] : graph[curr]) {
          if (nodeCosts[next] != -1) continue;
          heap.push({currCost + nextCost, next});
        }
      }

      for (auto [t, count] : sMap) {
        if (nodeCosts[t] == -1) return -1;  // can't reach
        ans += nodeCosts[t] * count;
      }
    }

    return ans;
  }
};

// BFS + Heap (Dijkstra)
//
// We can early stop the BFS.
class Solution2 {
 public:
  long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
    int n = source.size(), m = original.size();

    // Count pairs
    auto pairs = vector(26, vector(26, 0));  // (source, target -> count
    for (auto i = 0; i < n; ++i) {
      auto s = (source[i] - 'a'), t = (target[i] - 'a');
      if (s != t) ++pairs[s][t];
    }

    // Build graph
    auto graph = vector(26, vector(26, int64_t(INT_MAX)));  // (original, changed) -> cost
    for (auto j = 0; j < m; ++j) {
      auto o = (original[j] - 'a'), c = (changed[j] - 'a');
      int64_t w = cost[j];
      graph[o][c] = min(graph[o][c], w);
    }

    // BFS
    int64_t ans = 0;
    for (auto s = 0; s < 26; ++s) {
      auto& tCounts = pairs[s];
      if (tCounts.empty()) continue;

      auto visited = vector<bool>(128);
      auto heap = priority_queue(greater(), std::move(vector<pair<int64_t, char>>()));  // min-heap, (cost, node)
      heap.push({0, s});

      while (!heap.empty() && !tCounts.empty()) {
        auto [currCost, curr] = heap.top();
        heap.pop();

        // Visited
        if (visited[curr]) continue;
        visited[curr] = true;

        // Found target
        if (tCounts[curr] > 0) {
          ans += currCost * tCounts[curr];
          tCounts[curr] = 0;
        }

        for (auto next = 0; next < 26; ++next) {
          auto nextCost = graph[curr][next];
          if (nextCost == INT_MAX || visited[next]) continue;
          heap.push({currCost + nextCost, next});
        }
      }

      for (auto count : tCounts) {
        if (count > 0) return -1;  // can't reach
      }
    }

    return ans;
  }
};

// Floyd–Warshall
class Solution3 {
 public:
  long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
    int n = source.size(), m = original.size();

    // Build graph
    auto graph = vector(26, vector(26, int64_t(INT_MAX)));  // (original, changed) -> cost
    for (auto i = 0; i < 26; ++i) {
      graph[i][i] = 0;
    }
    for (auto j = 0; j < m; ++j) {
      auto o = (original[j] - 'a'), c = (changed[j] - 'a');
      int64_t w = cost[j];
      graph[o][c] = min(graph[o][c], w);
    }

    // Floyd–Warshall
    for (auto k = 0; k < 26; ++k) {
      for (auto i = 0; i < 26; ++i) {
        for (auto j = 0; j < 26; ++j) {
          if (graph[i][j] > graph[i][k] + graph[k][j]) graph[i][j] = graph[i][k] + graph[k][j];
        }
      }
    }

    // Loop
    int64_t ans = 0;
    for (auto i = 0; i < n; ++i) {
      auto s = (source[i] - 'a'), t = (target[i] - 'a');
      if (graph[s][t] >= INT_MAX) return -1;
      ans += graph[s][t];
    }

    return ans;
  }
};
