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

#include <numeric>
#include <queue>
#include <vector>

using namespace std;

// Sort + Union-Find
//
// Sort all edge by length.
// For each edge, connect them if two ends are in different components.
class Solution {
  struct UnionFind {
    vector<int> parent;
    vector<int> rank;

    UnionFind(int n) : parent(n), rank(n) {  //
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

      // Ensure rank(x) > rank(y)
      if (rank[x] < rank[y]) {
        swap(x, y);
      }

      // Merge y into x
      parent[y] = x;
      if (rank[x] == rank[y]) ++rank[x];
      return true;
    }
  };

  using Point = tuple<int, int, int>;  // length, p, q

 public:
  int minCostConnectPoints(vector<vector<int>>& points) {
    int n = points.size();

    // Edges
    auto edges = vector<Point>();
    for (auto p = 0; p < n; ++p) {
      auto px = points[p][0], py = points[p][1];
      for (auto q = p + 1; q < n; ++q) {
        auto qx = points[q][0], qy = points[q][1];
        auto len = abs(px - qx) + abs(py - qy);
        edges.emplace_back(len, p, q);
      }
    }
    sort(edges.begin(), edges.end());

    // Loop
    auto ans = 0;
    auto uf = UnionFind(n);
    for (auto [len, p, q] : edges) {
      if (uf.merge(p, q)) ans += len;
    }

    return ans;
  }
};

// Heap
//
// Pick an point as start.
// For each point added, put all its non-visited neighbor into the heap.
// Always pick the nearest non-visited point as next point.
class Solution2 {
  using Point = pair<int, int>;  // -distance, point

 public:
  int minCostConnectPoints(vector<vector<int>>& points) {
    int n = points.size();

    // Helper
    auto getDist = [&](int p, int q) -> int {  // distance of points
      return abs(points[p][0] - points[q][0]) + abs(points[p][1] - points[q][1]);
    };

    // Prepare
    auto heap = priority_queue<Point>();  // min-heap for "distance"
    auto visited = vector<bool>(n);
    heap.emplace(0, 0);

    // Loop
    auto ans = 0;
    while (!heap.empty()) {
      auto [negDist, point] = heap.top();
      heap.pop();

      if (visited[point]) continue;
      visited[point] = true;
      ans -= negDist;

      for (auto next = 0; next < n; ++next) {
        if (visited[next]) continue;
        heap.emplace(-getDist(point, next), next);
      }
    }

    return ans;
  }
};
