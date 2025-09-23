// Source: https://leetcode.com/problems/max-points-on-a-line
// Title: Max Points on a Line
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of `points` where `points[i] = [x_i, y_i]` represents a point on the **X-Y** plane, return the maximum number of points that lie on the same straight line.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/02/25/plane1.jpg
//
// ```
// Input: points = [[1,1],[2,2],[3,3]]
// Output: 3
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/02/25/plane2.jpg
//
// ```
// Input: points = [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
// Output: 4
// ```
//
// **Constraints:**
//
// - `1 <= points.length <= 300`
// - `points[i].length == 2`
// - `-10^4 <= x_i, y_i <= 10^4`
// - All the `points` are **unique**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include <numeric>
#include <unordered_map>
#include <vector>

using namespace std;

// Use Hash Map + Union Find
//
// Compute slope of each point pairs.
// Group pair by slopes, and use union find to group the pairs with common point.
class Solution {
  struct UnionFind {
    vector<int> parents;
    vector<int> sizes;
    int maxSize;

    UnionFind(int n) : parents(vector(n, 0)), sizes(vector(n, 1)), maxSize(1) {  //
      iota(parents.begin(), parents.end(), 0);
    }

    int find(int x) {
      if (parents[x] != x) {
        parents[x] = find(parents[x]);
      }
      return parents[x];
    }

    int union_(int x, int y) {
      x = find(x);
      y = find(y);
      if (x == y) return sizes[x];

      // WLOG, assume size(x) >= size(y)
      if (sizes[x] < sizes[y]) {
        swap(x, y);
      }

      // Merge y into x
      parents[y] = x;
      sizes[x] += sizes[y];
      return sizes[x];
    }
  };

 public:
  int maxPoints(vector<vector<int>>& points) {
    int n = points.size();

    // Pairs
    auto pairMap = unordered_map<double, vector<pair<int, int>>>();  // slope -> (i, j);
    for (auto i = 0; i < n; ++i) {
      for (auto j = i + 1; j < n; ++j) {
        double dx = points[i][0] - points[j][0], dy = points[i][1] - points[j][1];
        auto slope = dx ? dy / dx : INFINITY;
        pairMap[slope].emplace_back(i, j);
      }
    }

    auto ans = 1;
    for (auto& item : pairMap) {
      auto pairs = item.second;
      auto uf = UnionFind(n);
      for (auto [i, j] : pairs) {
        auto s = uf.union_(i, j);
        ans = max(ans, s);
      }
    }

    return ans;
  }
};

// Use Hash Map
//
// Loop for all point.
// Compute slope to each other points.
// Group them by slopes.
class Solution2 {
 public:
  int maxPoints(vector<vector<int>>& points) {
    int n = points.size();

    auto ans = 1;
    for (int i = 0; i < n; ++i) {
      auto slopeCount = unordered_map<double, int>();
      for (auto j = i + 1; j < n; ++j) {
        double dx = points[i][0] - points[j][0], dy = points[i][1] - points[j][1];
        auto slope = dx ? dy / dx : INFINITY;
        slopeCount[slope]++;
        ans = max(ans, 1 + slopeCount[slope]);
      }
    }

    return ans;
  }
};
