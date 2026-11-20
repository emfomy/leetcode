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
// Loop for all points triplets.
// Area(ABC)
// = 1/2 * abs(det [
//   1 x1 y1
//   1 x2 y2
//   1 x3 y3
// ])
// = abs(x1(y2-y3) + x2(y3-y1) + x3(y1-y2))/2
class Solution {
 public:
  double largestTriangleArea(const vector<vector<int>>& points) {
    const int n = points.size();

    // Get the parallelogram area, which is the double of the triangle area.
    auto getArea = [&points](int p1, int p2, int p3) -> int {
      int x1 = points[p1][0], y1 = points[p1][1];
      int x2 = points[p2][0], y2 = points[p2][1];
      int x3 = points[p3][0], y3 = points[p3][1];

      return abs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
    };

    // Find maximum parallelogram area
    int maxArea = 0;
    for (int p1 = 0; p1 < n; ++p1) {
      for (int p2 = 0; p2 < p1; ++p2) {
        for (int p3 = 0; p3 < p2; ++p3) {
          maxArea = max(maxArea, getArea(p1, p2, p3));
        }
      }
    }

    return double(maxArea * 0.5);
  }
};
