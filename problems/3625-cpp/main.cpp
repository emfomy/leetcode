// Source: https://leetcode.com/problems/count-number-of-trapezoids-ii
// Title: Count Number of Trapezoids II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a 2D integer array `points` where `points[i] = [x_i, y_i]` represents the coordinates of the `i^th` point on the Cartesian plane.
//
// Return the number of unique trapezoids that can be formed by choosing any four distinct points from `points`.
//
// A **trapezoid** is a convex quadrilateral with <strong data-end="496" data-start="475">at least one pair** of parallel sides. Two lines are parallel if and only if they have the same slope.
//
// **Example 1:**
//
// ```
// Input: points = [[-3,2],[3,0],[2,3],[3,2],[2,-3]]
// Output: 2
// Explanation:
// https://assets.leetcode.com/uploads/2025/04/29/desmos-graph-4.png
//
// There are two distinct ways to pick four points that form a trapezoid:
// - The points `[-3,2], [2,3], [3,2], [2,-3]` form one trapezoid.
// - The points `[2,3], [3,2], [3,0], [2,-3]` form another trapezoid.
// ```
//
// **Example 2:**
//
// ```
// Input: points = [[0,0],[1,0],[0,1],[2,1]]
// Output: 1
// Explanation:
// https://assets.leetcode.com/uploads/2025/04/29/desmos-graph-5.png
// There is only one trapezoid which can be formed.
// ```
//
// **Constraints:**
//
// - `4 <= points.length <= 500`
// - `–1000 <= x_i, y_i <= 1000`
// - All points are pairwise distinct.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <unordered_map>
#include <vector>

using namespace std;

// Math
//
// Loop for all pairs of points.
// Group them by their slopes. (Use a really large number for vertical)
// For each slope, it can be paired with all other slopes in the same group,
// except those in the same line
//
// In order to check if two slops are in the same line,
// we compute where the line intercept the y axis (x for vertical slopes).
//
// Define a line (assume dx != 0)
// (y-y0)dx = (x-x0)dy
// y dx - y0 dx = x dy - x0 dy
// let x = 0 to find the intercept point
// y = (y0 dx - x0 dy) / dx
//
// Note that we need to minus parallelograms since they will be count twice.
// Find the mid points of each pairs.
// If two pairs has the same mid points, they should form a parallelogram,
// except those in the same slope.
class Solution {
 public:
  int countTrapezoids(vector<vector<int>>& points) {
    int n = points.size();
    float INF = 1e9 + 7;

    // Groups
    auto midGroup = unordered_map<int, unordered_map<float, int>>();
    auto slopeGroup = unordered_map<float, unordered_map<float, int>>();
    for (auto i = 0; i < n; ++i) {
      auto x1 = points[i][0], y1 = points[i][1];
      for (auto j = 0; j < i; ++j) {
        auto x2 = points[j][0], y2 = points[j][1];
        float dx = x1 - x2, dy = y1 - y2;
        float slope = (dx == 0) ? INF : (dy / dx);
        float bias = (dx == 0) ? x1 : (y1 * dx - x1 * dy) / dx;
        auto mid = (x1 + x2) * 10000 + (y1 + y2);
        ++midGroup[mid][slope];
        ++slopeGroup[slope][bias];
      }
    }

    // Trapezoid
    auto ans = 0;
    for (auto& [_, subGroup] : slopeGroup) {
      auto prevCount = 0;
      for (auto [_, count] : subGroup) {
        ans += (count * prevCount);
        prevCount += count;
      }
    }

    // Parallelogram
    for (auto& [_, subGroup] : midGroup) {
      auto prevCount = 0;
      for (auto [_, count] : subGroup) {
        ans -= (count * prevCount);
        prevCount += count;
      }
    }

    return ans;
  }
};
