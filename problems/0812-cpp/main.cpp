// Source: https://leetcode.com/problems/largest-triangle-area
// Title: Largest Triangle Area
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an array of points on the **X-Y** plane `points` where `points[i] = [x_i, y_i]`, return the area of the largest triangle that can be formed by any three different points. Answers within `10^-5` of the actual answer will be accepted.
//
// **Example 1:**
// https://s3-lc-upload.s3.amazonaws.com/uploads/2018/04/04/1027.png
//
// ```
// Input: points = [[0,0],[0,1],[1,0],[0,2],[2,0]]
// Output: 2.00000
// Explanation: The five points are shown in the above figure. The red triangle is the largest.
// ```
//
// **Example 2:**
//
// ```
// Input: points = [[1,0],[0,0],[0,1]]
// Output: 0.50000
// ```
//
// **Constraints:**
//
// - `3 <= points.length <= 50`
// - `-50 <= x_i, y_i <= 50`
// - All the given points are **unique**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Brute-Force
//
// Use cross product for triangle area
// 2Area = |AB x AC|
//       = |(x2-x1, y2-y1) x (x3-x1, y3-y1)|
//       = |(x2-x1)(y3-y1) - (x3-x1)(y2-y1)|
//       = |x1(y2-y3) + x2(y3-y1) + x3(y1-y2)|
class Solution {
 public:
  double largestTriangleArea(vector<vector<int>>& points) {
    int n = points.size();

    auto getArea = [&](int i, int j, int k) {
      auto x1 = points[i][0], y1 = points[i][1];
      auto x2 = points[j][0], y2 = points[j][1];
      auto x3 = points[k][0], y3 = points[k][1];
      return abs(0.5 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)));
    };

    auto ans = 0.0;
    for (auto i = 0; i < n; ++i) {
      for (auto j = i + 1; j < n; ++j) {
        for (auto k = j + 1; k < n; ++k) {
          ans = max(ans, getArea(i, j, k));
        }
      }
    }

    return ans;
  }
};
