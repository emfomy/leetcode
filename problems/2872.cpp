// Source: https://leetcode.com/problems/maximum-number-of-k-divisible-components
// Title: Maximum Number of K-Divisible Components
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There is an undirected tree with `n` nodes labeled from `0` to `n - 1`. You are given the integer `n` and a 2D integer array `edges` of length `n - 1`, where `edges[i] = [a_i, b_i]` indicates that there is an edge between nodes `a_i` and `b_i` in the tree.
//
// You are also given a **0-indexed** integer array `values` of length `n`, where `values[i]` is the **value** associated with the `i^th` node, and an integer `k`.
//
// A **valid split** of the tree is obtained by removing any set of edges, possibly empty, from the tree such that the resulting components all have values that are divisible by `k`, where the **value of a connected component** is the sum of the values of its nodes.
//
// Return the **maximum number of components** in any valid split.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2023/08/07/example12-cropped2svg.jpg
//
// ```
// Input: n = 5, edges = [[0,2],[1,2],[1,3],[2,4]], values = [1,8,1,4,4], k = 6
// Output: 2
// Explanation: We remove the edge connecting node 1 with 2. The resulting split is valid because:
// - The value of the component containing nodes 1 and 3 is values[1] + values[3] = 12.
// - The value of the component containing nodes 0, 2, and 4 is values[0] + values[2] + values[4] = 6.
// It can be shown that no other valid split has more than 2 connected components.```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2023/08/07/example21svg-1.jpg
//
// ```
// Input: n = 7, edges = [[0,1],[0,2],[1,3],[1,4],[2,5],[2,6]], values = [3,0,6,1,5,2,1], k = 3
// Output: 3
// Explanation: We remove the edge connecting node 0 with 2, and the edge connecting node 0 with 1. The resulting split is valid because:
// - The value of the component containing node 0 is values[0] = 3.
// - The value of the component containing nodes 2, 5, and 6 is values[2] + values[5] + values[6] = 9.
// - The value of the component containing nodes 1, 3, and 4 is values[1] + values[3] + values[4] = 6.
// It can be shown that no other valid split has more than 3 connected components.
// ```
//
// **Constraints:**
//
// - `1 <= n <= 3 * 10^4`
// - `edges.length == n - 1`
// - `edges[i].length == 2`
// - `0 <= a_i, b_i < n`
// - `values.length == n`
// - `0 <= values[i] <= 10^9`
// - `1 <= k <= 10^9`
// - Sum of `values` is divisible by `k`.
// - The input is generated such that `edges` represents a valid tree.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <queue>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

// Greedy
//
// Put all leaves into a queue.
// For each leaf, if it is dividable by k, then delete its edge.
// If not, then merge it into its neighbor.
// If the neighbor becomes a leaf, put it into the queue, too.
class Solution {
 public:
  int maxKDivisibleComponents(int n, vector<vector<int>>& edges, vector<int>& values, int k) {
    for (auto v = 0; v < n; ++v) {
      values[v] %= k;
    }

    auto graph = vector(n, unordered_set<int>());
    for (auto& edge : edges) {
      auto a = edge[0], b = edge[1];
      graph[a].insert(b);
      graph[b].insert(a);
    }

    auto que = queue<int>();
    for (auto v = 0; v < n; ++v) {
      if (graph[v].size() == 1) que.push(v);
    }

    auto ans = 1;
    while (!que.empty()) {
      auto v = que.front();
      que.pop();

      // check
      if (graph[v].empty()) continue;

      // find neighbor
      auto w = *graph[v].begin();

      // Merge node
      if (values[v] % k == 0) {
        ++ans;
      } else {
        values[w] += values[v];
      }

      // Update neighbor
      graph[w].erase(v);
      if (graph[w].size() == 1) que.push(w);
    }

    return ans;
  }
};

// DFS
class Solution2 {
 public:
  int maxKDivisibleComponents(int n, vector<vector<int>>& edges, vector<int>& values, int k) {
    // Graph
    auto graph = vector(n, vector<int>());
    for (auto& edge : edges) {
      auto a = edge[0], b = edge[1];
      graph[a].push_back(b);
      graph[b].push_back(a);
    }

    // DFS
    auto ans = 0;
    _dfs(0, -1, graph, values, k, &ans);

    return ans;
  }

  int _dfs(int curr, int prev, vector<vector<int>>& graph, vector<int>& values, int k, int* ans) {
    auto value = values[curr] % k;
    for (auto next : graph[curr]) {
      if (next == prev) continue;
      value += _dfs(next, curr, graph, values, k, ans);
    }

    value %= k;
    if (value == 0) ++(*ans);
    return value;
  }
};
