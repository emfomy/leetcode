// Source: https://leetcode.com/problems/min-cost-to-connect-all-points
// Title: Min Cost to Connect All Points
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array `points` representing integer coordinates of some points on a 2D-plane, where `points[i] = [x_i, y_i]`.
//
// The cost of connecting two points `[x_i, y_i]` and `[x_j, y_j]` is the **manhattan distance** between them: `|x_i - x_j| + |y_i - y_j|`, where `|val|` denotes the absolute value of `val`.
//
// Return the minimum cost to make all points connected. All points are connected if there is **exactly one** simple path between any two points.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/08/26/d.png
//
// ```
// Input: points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
// Output: 20
// Explanation:
// https://assets.leetcode.com/uploads/2020/08/26/c.png
// We can connect the points as shown above to get the minimum cost of 20.
// Notice that there is a unique path between every pair of points.
// ```
//
// **Example 2:**
//
// ```
// Input: points = [[3,12],[-2,5],[-4,1]]
// Output: 18
// ```
//
// **Constraints:**
//
// - `1 <= points.length <= 1000`
// - `-10^6 <= x_i, y_i <= 10^6`
// - All pairs `(x_i, y_i)` are distinct.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <climits>
#include <functional>
#include <numeric>
#include <queue>
#include <vector>

using namespace std;

// Kruskal's algorithm (Sort + Union-Find)
//
// Use Kruskal's algorithm to find the MST.
class Solution {
  struct UnionFind {
    mutable vector<int> parents;
    mutable vector<int> ranks;

    UnionFind(int n) : parents(n), ranks(n) {  //
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
    }
  };

  using Edge = tuple<int, int, int>;  // weight, node, node

  int getDist(const vector<int>& u, const vector<int>& v) {  //
    return abs(u[0] - v[0]) + abs(u[1] - v[1]);
  }

 public:
  int minCostConnectPoints(const vector<vector<int>>& points) {
    const int n = points.size();

    // Build and sort edges
    auto edges = vector<Edge>();
    for (int v = 0; v < n; ++v) {
      for (int u = 0; u < v; ++u) {
        edges.emplace_back(getDist(points[u], points[v]), u, v);
      }
    }
    sort(edges.begin(), edges.end());

    // Kruskal's algorithm
    auto uf = UnionFind(n);
    int mstWeight = 0;
    for (const auto [w, u, v] : edges) {
      if (uf.isConnected(u, v)) continue;

      uf.unite(u, v);
      mstWeight += w;
    }

    return mstWeight;
  }
};

// Dense Prim's algorithm (Sort)
//
// Use Prim's algorithm to find the MST.
class Solution2 {
  int getDist(const vector<int>& u, const vector<int>& v) {  //
    return abs(u[0] - v[0]) + abs(u[1] - v[1]);
  }

 public:
  int minCostConnectPoints(const vector<vector<int>>& points) {
    const int n = points.size();

    // Prepare
    auto visited = vector<bool>(n);
    auto dists = vector<int>(n, INT_MAX);
    dists[0] = 0;

    // Prims's algorithm
    int mstWeight = 0;
    for (int iter = 0; iter < n; ++iter) {
      // Find nearest unvisited point
      int u = min_element(dists.cbegin(), dists.cend()) - dists.cbegin();
      visited[u] = true;
      mstWeight += dists[u];
      dists[u] = INT_MAX;  // remove from target set

      for (int v = 0; v < n; ++v) {
        if (visited[v]) continue;
        dists[v] = min(dists[v], getDist(points[u], points[v]));
      }
    }

    return mstWeight;
  }
};
