// Source: https://leetcode.com/problems/connecting-cities-with-minimum-cost
// Title: Connecting Cities With Minimum Cost
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There are `n` cities labeled from `1` to `n`. You are given the integer `n` and an array `connections` where `connections[i] = [x_i, y_i, cost_i]` indicates that the cost of connecting city `x_i` and city `y_i` (bidirectional connection) is `cost_i`.
//
// Return the minimum **cost** to connect all the `n` cities such that there is at least one path between each pair of cities. If it is impossible to connect all the `n` cities, return `-1`,
//
// The **cost** is the sum of the connections' costs used.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2019/04/20/1314_ex2.png
//
// ```
// Input: n = 3, connections = [[1,2,5],[1,3,6],[2,3,1]]
// Output: 6
// Explanation: Choosing any 2 edges will connect all cities so we choose the minimum 2.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2019/04/20/1314_ex1.png
//
// ```
// Input: n = 4, connections = [[1,2,3],[3,4,4]]
// Output: -1
// Explanation: There is no way to connect all cities even if all edges are used.
// ```
//
// **Constraints:**
//
// - `1 <= n <= 10^4`
// - `1 <= connections.length <= 10^4`
// - `connections[i].length == 3`
// - `1 <= x_i, y_i <= n`
// - `x_i != y_i`
// - `0 <= cost_i <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

// Kruskal (Sort + Union Find)
//
// Use Kruskal's algorithm to find MST.
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
  int minimumCost(int n, vector<vector<int>>& edges) {
    // Sort edges
    auto comp = [](const vector<int>& a, const vector<int>& b) -> bool { return a[2] < b[2]; };
    sort(edges.begin(), edges.end(), comp);

    // Kruskal
    UnionFind uf(n);
    int mstWeight = 0;
    for (const auto& edge : edges) {
      // Early stop
      if (uf.count == 1) break;

      // Merge
      int u = edge[0] - 1, v = edge[1] - 1, w = edge[2];
      if (uf.isConnected(u, v)) continue;
      uf.unite(u, v);
      mstWeight += w;
    }

    return (uf.count == 1) ? mstWeight : -1;
  }
};
