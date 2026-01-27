// Source: https://leetcode.com/problems/minimum-cost-path-with-edge-reversals
// Title: Minimum Cost Path with Edge Reversals
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a directed, weighted graph with `n` nodes labeled from 0 to `n - 1`, and an array `edges` where `edges[i] = [u_i, v_i, w_i]` represents a directed edge from node `u_i` to node `v_i` with cost `w_i`.
//
// Each node `u_i` has a switch that can be used **at most once**: when you arrive at `u_i` and have not yet used its switch, you may activate it on one of its incoming edges `v_i → u_i` reverse that edge to `u_i → v_i` and **immediately** traverse it.
//
// The reversal is only valid for that single move, and using a reversed edge costs `2 * w_i`.
//
// Return the **minimum** total cost to travel from node 0 to node `n - 1`. If it is not possible, return -1.
//
// **Example 1:**
//
// ```
// Input: n = 4, edges = [[0,1,3],[3,1,1],[2,3,4],[0,2,2]]
// Output: 5
// Explanation:
// https://assets.leetcode.com/uploads/2025/05/07/e1drawio.png
// - Use the path `0 → 1` (cost 3).
// - At node 1 reverse the original edge `3 → 1` into `1 → 3` and traverse it at cost `2 * 1 = 2`.
// - Total cost is `3 + 2 = 5`.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 4, edges = [[0,2,1],[2,1,1],[1,3,1],[2,3,3]]
// Output: 3
// Explanation:
// - No reversal is needed. Take the path `0 → 2` (cost 1), then `2 → 1` (cost 1), then `1 → 3` (cost 1).
// - Total cost is `1 + 1 + 1 = 3`.
// ```
//
// **Constraints:**
//
// - `2 <= n <= 5 * 10^4`
// - `1 <= edges.length <= 10^5`
// - `edges[i] = [u_i, v_i, w_i]`
// - `0 <= u_i, v_i <= n - 1`
// - `1 <= w_i <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <vector>

using namespace std;

// BFS + Heap
//
// Since it is no need to traverse a node or an edge twice,
// we can add the reverse edges into the graph at the beginning.
class Solution {
 public:
  int minCost(int n, vector<vector<int>>& edges) {
    // Init
    auto graph = vector(n, vector<pair<int, int>>());  // from -> (to, weight)
    for (auto& edge : edges) {
      auto u = edge[0], v = edge[1], w = edge[2];
      graph[u].push_back({v, w});
      graph[v].push_back({u, 2 * w});
    }

    // BFS
    auto heap = priority_queue(greater(), std::move(vector<pair<int, int>>()));  // min-heap, (cost, node)
    auto visited = vector<bool>(n);
    heap.push({0, 0});
    while (!heap.empty()) {
      auto [c, u] = heap.top();
      heap.pop();

      // End
      if (u == n - 1) return c;

      // Visited
      if (visited[u]) continue;
      visited[u] = true;

      // Traverse
      for (auto [v, w] : graph[u]) {
        if (!visited[v]) heap.push({c + w, v});
      }
    }

    return -1;
  }
};
