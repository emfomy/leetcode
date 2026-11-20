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

#include <algorithm>
#include <cmath>
#include <numeric>
#include <unordered_map>
#include <vector>

using namespace std;

// Hash Map + Union Find
//
// Pick a line of points.
// All pairs of these points has the same slope.
//
// We loop through all pairs of the points, and group them by their slopes.
// For each slope group, use union find the group them into lines.
class Solution {
  struct UnionFind {
    vector<int> parents;
    vector<int> sizes;
    int maxSize;

    UnionFind(int n) : parents(n), sizes(n, 1), maxSize(1) {  //
      iota(parents.begin(), parents.end(), 0);
    }

    void reset() {
      iota(parents.begin(), parents.end(), 0);
      fill(sizes.begin(), sizes.end(), 1);
      maxSize = 1;
    }

    int find(int x) {
      if (parents[x] != x) {
        parents[x] = find(parents[x]);
      }
      return parents[x];
    }

    void unite(int x, int y) {
      x = find(x);
      y = find(y);
      if (x == y) return;

      // Ensure size(x) >= size(y)
      if (sizes[x] < sizes[y]) swap(x, y);

      // Merge y into x
      sizes[x] += sizes[y];
      parents[y] = x;
      maxSize = max(maxSize, sizes[x]);
    }
  };

 public:
  int maxPoints(const vector<vector<int>>& points) {
    const int n = points.size();
    if (n <= 2) return n;  // trivial

    // Group by slopes
    // We use INF for vertical line
    auto slopeGroups = unordered_map<double, vector<pair<int, int>>>();
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < i; ++j) {
        int x1 = points[i][0], y1 = points[i][1];
        int x2 = points[j][0], y2 = points[j][1];
        int dx = x2 - x1, dy = y2 - y1;
        double slope =            //
            dy == 0   ? 0.0       // avoid +0.0 & -0.0
            : dx == 0 ? INFINITY  // avoid +INF & -INF
                      : double(dy) / double(dx);
        slopeGroups[slope].emplace_back(i, j);
      }
    }

    // Loop for slopes
    int maxLine = 2;
    auto uf = UnionFind(n);
    for (auto& [slope, pairs] : slopeGroups) {
      uf.reset();
      for (auto [x, y] : pairs) {
        uf.unite(x, y);
      }
      maxLine = max(maxLine, uf.maxSize);
    }

    return maxLine;
  }
};

// Hash Map
//
// Instead of handling all pairs at ones, we focus on lines passing a point.
// Fix a point (we call it anchor),
// loop for all other points to find the slopes.
// We group the slopes using hash map.
// All points with the same slopes are in a line.
//
// Since the maximum point must pass one of these points,
// this algorithm guarantees to find the answer.
class Solution2 {
 public:
  int maxPoints(vector<vector<int>>& points) {
    const int n = points.size();
    if (n <= 2) return n;  // trivial

    // Prepare slope counter
    auto counter = unordered_map<double, int>();
    counter.reserve(n);

    // Loop all points
    int maxCount = 1;
    for (int i = 0; i < n; ++i) {
      counter.clear();
      int x1 = points[i][0], y1 = points[i][1];

      // no need to check previous points
      for (int j = i + 1; j < n; ++j) {
        int x2 = points[j][0], y2 = points[j][1];
        int dx = x2 - x1, dy = y2 - y1;
        double slope =            //
            dy == 0   ? 0.0       // avoid +0.0 & -0.0
            : dx == 0 ? INFINITY  // avoid +INF & -INF
                      : double(dy) / double(dx);

        maxCount = max(maxCount, ++counter[slope]);
      }
    }

    return maxCount + 1;  // add one for the anchor point
  }
};

// Hash Map
//
// Use GCD for slope.
class Solution3 {
 public:
  int maxPoints(vector<vector<int>>& points) {
    const int n = points.size();
    if (n <= 2) return n;  // trivial

    // Prepare slope counter
    auto counter = unordered_map<int, int>();
    counter.reserve(n);

    // Loop all points
    int maxCount = 1;
    for (int i = 0; i < n; ++i) {
      counter.clear();
      int x1 = points[i][0], y1 = points[i][1];

      // no need to check previous points
      for (int j = i + 1; j < n; ++j) {
        int x2 = points[j][0], y2 = points[j][1];
        int dx = x2 - x1, dy = y2 - y1;
        int g = gcd(abs(dx), abs(dy));
        dx /= g, dy /= g;
        if (dx < 0) {
          dx = -dx;
          dy = -dy;
        } else if (dx == 0) {
          dy = 1;  // vertical
        } else if (dy == 0) {
          dx = 1;  // horizontal
        }

        int slope = (dx << 16) ^ dy;  // values are 16 bits
        maxCount = max(maxCount, ++counter[slope]);
      }
    }

    return maxCount + 1;  // add one for the anchor point
  }
};
