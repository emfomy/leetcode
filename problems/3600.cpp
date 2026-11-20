// Source: https://leetcode.com/problems/maximize-spanning-tree-stability-with-upgrades
// Title: Maximize Spanning Tree Stability with Upgrades
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer `n`, representing `n` nodes numbered from 0 to `n - 1` and a list of `edges`, where `edges[i] = [u_i, v_i, s_i, must_i]`:
//
// - `u_i` and `v_i` indicates an undirected edge between nodes `u_i` and `v_i`.
// - `s_i` is the strength of the edge.
// - `must_i` is an integer (0 or 1). If `must_i == 1`, the edge **must** be included in the** ****spanning tree**. These edges **cannot** be **upgraded**.
//
// You are also given an integer `k`, the **maximum** number of upgrades you can perform. Each upgrade **doubles** the strength of an edge, and each eligible edge (with `must_i == 0`) can be upgraded **at most** once.
//
// The **stability** of a spanning tree is defined as the **minimum** strength score among all edges included in it.
//
// Return the **maximum** possible stability of any valid spanning tree. If it is impossible to connect all nodes, return `-1`.
//
// **Note**: A **spanning tree** of a graph with `n` nodes is a subset of the edges that connects all nodes together (i.e. the graph is **connected**) without forming any cycles, and uses **exactly** `n - 1` edges.
//
// **Example 1:**
//
// ```
// Input: n = 3, edges = [[0,1,2,1],[1,2,3,0]], k = 1
// Output: 2
// Explanation:
// - Edge `[0,1]` with strength = 2 must be included in the spanning tree.
// - Edge `[1,2]` is optional and can be upgraded from 3 to 6 using one upgrade.
// - The resulting spanning tree includes these two edges with strengths 2 and 6.
// - The minimum strength in the spanning tree is 2, which is the maximum possible stability.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 3, edges = [[0,1,4,0],[1,2,3,0],[0,2,1,0]], k = 2
// Output: 6
// Explanation:
// - Since all edges are optional and up to `k = 2` upgrades are allowed.
// - Upgrade edges `[0,1]` from 4 to 8 and `[1,2]` from 3 to 6.
// - The resulting spanning tree includes these two edges with strengths 8 and 6.
// - The minimum strength in the tree is 6, which is the maximum possible stability.
// ```
//
// **Example 3:**
//
// ```
// Input: n = 3, edges = [[0,1,1,1],[1,2,1,1],[2,0,1,1]], k = 0
// Output: -1
// Explanation:
// - All edges are mandatory and form a cycle, which violates the spanning tree property of acyclicity. Thus, the answer is -1.
// ```
//
// **Constraints:**
//
// - `2 <= n <= 10^5`
// - `1 <= edges.length <= 10^5`
// - `edges[i] = [u_i, v_i, s_i, must_i]`
// - `0 <= u_i, v_i < n`
// - `u_i != v_i`
// - `1 <= s_i <= 10^5`
// - `must_i` is either `0` or `1`.
// - `0 <= k <= n`
// - There are no duplicate edges.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <climits>
#include <numeric>
#include <queue>
#include <vector>

using namespace std;

// Kruskal (Union-Find)
//
// We use union-find for the tree structure.
//
// First connect put all the `must` edges and throws error if cycle detected.
// Next remove all the used edges.
// Denote the minimal edge in the tree as `minEdge`.
// We kept update it during below algorithm.
//
// Now sort the remaining edges, and loop them from the largest.
// Skip the connected edges.
// If the edge is greater then minEdge, then no need to upgrade it.
// Otherwise, insert it into the tree, upgrade it, and push it into the a queue.
// The queue is kept with size k (represent the upgraded edges).
// When the queue is full, we pop an edge and degrade it.
// Since the pop edge is larger then the new edge, degrading doesn't effect `minEdge`.
class Solution {
  struct UnionFind {
    mutable vector<int> parents;
    mutable vector<int> ranks;
    int count;  // connected components

    UnionFind(int n) : parents(n), ranks(n), count(n) {  //
      iota(parents.begin(), parents.end(), 0);
    }

    int find(int x) const {
      if (parents[x] != x) {
        parents[x] = find(parents[x]);
      }
      return parents[x];
    }

    bool isConnected(int x, int y) const {  //
      return find(x) == find(y);
    }

    void unite(int x, int y) {
      x = find(x);
      y = find(y);
      if (x == y) return;

      // Ensure rank(x) >= rank(y)
      if (ranks[x] < ranks[y]) swap(x, y);

      // Merge y into x
      if (ranks[x] == ranks[y]) ++ranks[x];
      parents[y] = x;
      --count;
    }
  };

 public:
  int maxStability(const int n, vector<vector<int>>& edges, int k) {
    const int m = edges.size();

    // Prepare
    auto uf = UnionFind(n);
    int minEdge = INT_MAX;

    // Insert `must` edges
    auto ids = vector<int>();
    ids.reserve(m);
    for (int i = 0; i < m; ++i) {
      const int u = edges[i][0], v = edges[i][1], w = edges[i][2], must = edges[i][3];
      if (must) {
        if (uf.isConnected(u, v)) return -1;  // impossible
        uf.unite(u, v);
        minEdge = min(minEdge, w);
      } else {
        ids.push_back(i);
      }
    }
    if (uf.count == 1) return minEdge;  // early stop

    // Sort other edges
    const auto comp = [&](int i, int j) -> bool {  //
      return edges[i][2] > edges[j][2];
    };
    sort(ids.begin(), ids.end(), comp);

    // Loop
    auto upgraded = queue<int>();  // upgraded edge's original weights
    for (int i : ids) {
      if (uf.count == 1) break;  // early stop

      // Unite
      int u = edges[i][0], v = edges[i][1], w = edges[i][2];
      if (uf.isConnected(u, v)) continue;
      uf.unite(u, v);

      // Upgrade
      if (w >= minEdge) continue;
      minEdge = min(minEdge, 2 * w);
      upgraded.push(w);

      // Degrade
      while (upgraded.size() > k) {
        minEdge = min(minEdge, upgraded.front());
        upgraded.pop();
      }
    }

    return (uf.count == 1) ? minEdge : -1;
  }
};
