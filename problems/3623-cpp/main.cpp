// Source: https://leetcode.com/problems/count-number-of-trapezoids-i
// Title: Count Number of Trapezoids I
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a 2D integer array `points`, where `points[i] = [x_i, y_i]` represents the coordinates of the `i^th` point on the Cartesian plane.
//
// A **horizontal** **trapezoid** is a convex quadrilateral with **at least one pair** of horizontal sides (i.e. parallel to the x-axis). Two lines are parallel if and only if they have the same slope.
//
// Return the <em> number of unique **horizontal trapezoids** that can be formed by choosing any four distinct points from `points`.
//
// Since the answer may be very large, return it **modulo** `10^9 + 7`.
//
// **Example 1:**
//
// ```
// Input: points = [[1,0],[2,0],[3,0],[2,2],[3,2]]
// Output: 3
// Explanation:
// https://assets.leetcode.com/uploads/2025/05/01/desmos-graph-6.png" style="width: 250px; height: 250px;"> <img alt="" src="https://assets.leetcode.com/uploads/2025/05/01/desmos-graph-7.png" style="width: 250px; height: 250px;"> <img alt="" src="https://assets.leetcode.com/uploads/2025/05/01/desmos-graph-8.png
//
// There are three distinct ways to pick four points that form a horizontal trapezoid:
// - Using points `[1,0]`, `[2,0]`, `[3,2]`, and `[2,2]`.
// - Using points `[2,0]`, `[3,0]`, `[3,2]`, and `[2,2]`.
// - Using points `[1,0]`, `[3,0]`, `[3,2]`, and `[2,2]`.
// ```
//
// **Example 2:**
//
// ```
// Input: points = [[0,0],[1,0],[0,1],[2,1]]
// Output: 1
// Explanation:
// https://assets.leetcode.com/uploads/2025/04/29/desmos-graph-5.png
// There is only one horizontal trapezoid that can be formed.
// ```
//
// **Constraints:**
//
// - `4 <= points.length <= 10^5`
// - `–10^8 <= x_i, y_i <= 10^8`
// - All points are pairwise distinct.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <unordered_map>
#include <vector>

using namespace std;

// Math
//
// Group the points by y axis.
class Solution {
  constexpr static int modulo = 1e9 + 7;

 public:
  int countTrapezoids(vector<vector<int>>& points) {
    // Groups
    auto sizes = unordered_map<int, int>();
    for (auto& point : points) ++sizes[point[1]];

    // Count answer
    auto ans = 0;
    for (auto it1 = sizes.cbegin(); it1 != sizes.cend(); ++it1) {
      for (auto it2 = sizes.cbegin(); it2 != it1; ++it2) {
        ans = (ans + it1->second * (it1->second - 1) * it2->second * (it2->second - 1) / 4) % modulo;
      }
    }

    return ans;
  }
};

// Math
//
// Group the points by y axis.
class Solution2 {
  constexpr static int modulo = 1e9 + 7;

 public:
  int countTrapezoids(vector<vector<int>>& points) {
    // Groups
    auto sizes = unordered_map<int, int>();
    for (auto& point : points) ++sizes[point[1]];

    // Count answer
    int64_t ans = 0;
    auto prevPairs = 0;
    for (auto [_, size] : sizes) {
      auto pairs = int64_t(size) * (size - 1) / 2;
      ans = (ans + pairs * prevPairs) % modulo;
      prevPairs += pairs;
    }

    return ans;
  }
};
