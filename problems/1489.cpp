// Source: https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree
// Title: Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a weighted undirected connected graph with `n`vertices numbered from `0` to `n - 1`,and an array `edges`where `edges[i] = [a_i, b_i, weight_i]` represents a bidirectional and weighted edge between nodes`a_i`and `b_i`. A minimum spanning tree (MST) is a subset of the graph's edges that connects all vertices without cyclesand with the minimum possible total edge weight.
//
// Find all the critical and pseudo-critical edges in the given graph's minimum spanning tree (MST). An MST edge whose deletion from the graph would cause the MST weight to increase is called acritical edge. Onthe other hand, a pseudo-critical edge is that which can appear in some MSTs but not all.
//
// Note that you can return the indices of the edges in any order.
//
// **Example 1:**
//
// https://assets.leetcode.com/uploads/2020/06/04/ex1.png
//
// ```
// Input: n = 5, edges = [[0,1,1],[1,2,1],[2,3,2],[0,3,2],[0,4,3],[3,4,3],[1,4,6]]
// Output: [[0,1],[2,3,4,5]]
// Explanation: The figure above describes the graph.
// The following figure shows all the possible MSTs:
// https://assets.leetcode.com/uploads/2020/06/04/msts.png
// Notice that the two edges 0 and 1 appear in all MSTs, therefore they are critical edges, so we return them in the first list of the output.
// The edges 2, 3, 4, and 5 are only part of some MSTs, therefore they are considered pseudo-critical edges. We add them to the second list of the output.
// ```
//
// **Example 2:**
//
// https://assets.leetcode.com/uploads/2020/06/04/ex2.png
//
// ```
// Input: n = 4, edges = [[0,1,1],[1,2,1],[2,3,1],[0,3,1]]
// Output: [[],[0,1,2,3]]
// Explanation: We can observe that since all 4 edges have equal weight, choosing any 3 edges from the given 4 will yield an MST. Therefore all 4 edges are pseudo-critical.
// ```
//
// **Constraints:**
//
// - `2 <= n <= 100`
// - `1 <= edges.length <= min(200, n * (n - 1) / 2)`
// - `edges[i].length == 3`
// - `0 <= a_i < b_i < n`
// - `1 <= weight_i<= 1000`
// - All pairs `(a_i, b_i)` are **distinct**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

// Kruskal's Algorithm
//
// We first use Kruskal's algorithm to find the weight of the MST.
//
// Next check if an edge is critical.
// For each edge, rerun the Kruskal's algorithm without that edge
// to check if the final weight increases.
//
// Next check if an edge is pseudo-critical.
// For each edge, we first pick that edge and rerun the Kruskal's algorithm,
// to check if the final weight is unchanged.
class Solution {
  struct UnionFind {
    mutable vector<int> parents;
    vector<int> ranks;

    UnionFind(int n) : parents(n), ranks(n) {  //
      reset();
    }

    void reset() {
      const int n = parents.size();
      iota(parents.begin(), parents.end(), 0);
      fill(ranks.begin(), ranks.end(), 0);
    }

    int find(int x) const {
      if (parents[x] != x) {
        parents[x] = find(parents[x]);
      }
      return parents[x];
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
    }

    bool isConnected(int x, int y) const {  //
      return find(x) == find(y);
    }

    bool isAllConnected() const {  //
      const int n = parents.size();
      for (int x = 1; x < n; ++x) {
        if (!isConnected(0, x)) return false;
      }
      return true;
    }
  };

  using Edge = tuple<int, int, int, int>;  // w, u, v, index

 public:
  vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, const vector<vector<int>>& rawEdges) {
    const int m = rawEdges.size();

    // Sort edges
    auto edges = vector<Edge>();
    edges.reserve(m);
    for (int e = 0; e < m; ++e) {
      const int u = rawEdges[e][0], v = rawEdges[e][1], w = rawEdges[e][2];
      edges.emplace_back(w, u, v, e);
    }
    sort(edges.begin(), edges.end());

    // Prepare
    auto uf = UnionFind(n);

    // MST
    const int minWeight = findMST(uf, edges);

    // Find criticals and pseudo criticals
    auto criticals = vector<int>();
    auto pseudos = vector<int>();
    criticals.reserve(m);
    pseudos.reserve(m);
    for (const auto [w, u, v, e] : edges) {
      // Check critical
      uf.reset();
      if (findMST(uf, edges, e) > minWeight || !uf.isAllConnected()) {
        criticals.push_back(e);
        continue;
      }

      // Check pseudo critical
      uf.reset();
      uf.unite(u, v);
      if (w + findMST(uf, edges, e) == minWeight) {
        pseudos.push_back(e);
      }
    }

    return {criticals, pseudos};
  }

  // edge should be sorted
  int findMST(UnionFind& uf, const vector<Edge>& edges, int skipEdge = -1) {
    const int m = edges.size();

    int totalWeight = 0;
    for (const auto [w, u, v, e] : edges) {
      if (e == skipEdge) continue;
      if (uf.isConnected(u, v)) continue;

      uf.unite(u, v);
      totalWeight += w;
    }

    return totalWeight;
  }
};
