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
#include <queue>
#include <vector>

using namespace std;

// Minimal Span Tree (Heap)
class Solution {
  using Edge = pair<int, int>;  // -cost, node id

 public:
  int minimumCost(int n, vector<vector<int>>& edges) {
    auto graph = vector<vector<Edge>>(n);
    for (auto& edge : edges) {
      auto x = edge[0] - 1, y = edge[1] - 1, w = edge[2];
      graph[x].emplace_back(-w, y);
      graph[y].emplace_back(-w, x);
    }

    auto heap = priority_queue<Edge>();
    auto visited = vector<bool>(n);
    auto ans = 0;
    auto count = 0;

    heap.push({0, 0});
    while (!heap.empty()) {
      auto [nCost, node] = heap.top();
      heap.pop();

      if (visited[node]) continue;
      visited[node] = true;
      ans -= nCost;
      ++count;

      for (auto edge : graph[node]) {
        if (visited[edge.second]) continue;
        heap.push(edge);
      }
    }

    return (count < n) ? -1 : ans;
  }
};

// Minimal Span Tree (Union Find)
class Solution2 {
  struct UnionFind {
    vector<int> parent;
    vector<int> rank;
    int size;

    UnionFind(int n) : parent(n), rank(n), size(n) {  //
      iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
      if (parent[x] != x) {
        parent[x] = find(parent[x]);
      }
      return parent[x];
    }

    bool merge(int x, int y) {
      x = find(x);
      y = find(y);
      if (x == y) return false;

      // Ensure rank(x) >= rank(y)
      if (rank[x] < rank[y]) swap(x, y);

      // Merge y into x
      parent[y] = x;
      if (rank[x] == rank[y]) ++rank[x];
      --size;
      return true;
    }
  };

 public:
  int minimumCost(int n, vector<vector<int>>& edges) {
    auto uf = UnionFind(n);

    // Sort by cost
    sort(edges.begin(), edges.end(), [](auto& a, auto& b) { return a[2] < b[2]; });

    // Loop
    auto ans = 0;
    for (auto& edge : edges) {
      auto x = edge[0] - 1, y = edge[1] - 1, w = edge[2];
      if (uf.merge(x, y)) ans += w;
    }

    return (uf.size > 1) ? -1 : ans;
  }
};
