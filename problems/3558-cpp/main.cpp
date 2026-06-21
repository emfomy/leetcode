// Source: https://leetcode.com/problems/number-of-ways-to-assign-edge-weights-i
// Title: Number of Ways to Assign Edge Weights I
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There is an undirected tree with `n` nodes labeled from 1 to `n`, rooted at node 1. The tree is represented by a 2D integer array `edges` of length `n - 1`, where `edges[i] = [u_i, v_i]` indicates that there is an edge between nodes `u_i` and `v_i`.
//
// Initially, all edges have a weight of 0. You must assign each edge a weight of either **1** or **2**.
//
// The **cost** of a path between any two nodes `u` and `v` is the total weight of all edges in the path connecting them.
//
// Select any one node `x` at the **maximum** depth. Return the number of ways to assign edge weights in the path from node 1 to `x` such that its total cost is **odd**.
//
// Since the answer may be large, return it **modulo** `10^9 + 7`.
//
// **Note:** Ignore all edges **not** in the path from node 1 to `x`.
//
// **Example 1:**
//
// https://assets.leetcode.com/uploads/2025/03/23/screenshot-2025-03-24-at-060006.png
//
// ```
// Input: edges = [[1,2]]
// Output: 1
// Explanation:
// - The path from Node 1 to Node 2 consists of one edge (`1 → 2`).
// - Assigning weight 1 makes the cost odd, while 2 makes it even. Thus, the number of valid assignments is 1.
// ```
//
// **Example 2:**
//
// https://assets.leetcode.com/uploads/2025/03/23/screenshot-2025-03-24-at-055820.png
//
// ```
// Input: edges = [[1,2],[1,3],[3,4],[3,5]]
// Output: 2
// Explanation:
// - The maximum depth is 2, with nodes 4 and 5 at the same depth. Either node can be selected for processing.
// - For example, the path from Node 1 to Node 4 consists of two edges (`1 → 3` and `3 → 4`).
// - Assigning weights (1,2) or (2,1) results in an odd cost. Thus, the number of valid assignments is 2.
// ```
//
// **Constraints:**
//
// - `2 <= n <= 10^5`
// - `edges.length == n - 1`
// - `edges[i] == [u_i, v_i]`
// - `1 <= u_i, v_i <= n`
// - `edges` represents a valid tree.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// BFS
//
// Use BFS to find tree depth.
//
// Say the depth is d.
// The first d-1 edges can be choose randomly.
// The last edge has only one choice since the sum must be odd.
class Solution {
  constexpr static int root = 0;
  constexpr static int64_t modulo = 1e9 + 7;

  using Bool = unsigned char;

  inline int64_t mod(int64_t x) {  //
    return ((x % modulo) + modulo) % modulo;
  }

  inline int64_t fastPow(int64_t x, int n) {  //
    int64_t res = 1;
    while (n > 0) {
      if (n % 2) res = mod(res * x);
      x = mod(x * x);
      n /= 2;
    }
    return res;
  }

 public:
  int assignEdgeWeights(const vector<vector<int>>& edges) {
    const int n = edges.size() + 1;

    // Build graph
    auto graph = vector<vector<int>>(n);
    for (const auto& edge : edges) {
      int u = edge[0] - 1, v = edge[1] - 1;
      graph[u].push_back(v);
      graph[v].push_back(u);
    }

    // BFS
    auto visited = vector<Bool>(n);
    auto prev = vector<int>();
    auto curr = vector<int>();
    prev.reserve(n);
    curr.reserve(n);

    visited[root] = true;
    curr.push_back(root);

    int depth = -1;
    while (!curr.empty()) {
      ++depth;
      swap(curr, prev);
      curr.clear();

      for (int u : prev) {
        for (int v : graph[u]) {
          if (visited[v]) continue;
          visited[v] = true;
          curr.push_back(v);
        }
      }
    }

    // Answer
    return fastPow(2, depth - 1);
  }
};
