// Source: https://leetcode.com/problems/circle-and-rectangle-overlapping
// Title: Circle and Rectangle Overlapping
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a circle represented as `(radius, xCenter, yCenter)` and an axis-aligned rectangle represented as `(x1, y1, x2, y2)`, where `(x1, y1)` are the coordinates of the bottom-left corner, and `(x2, y2)` are the coordinates of the top-right corner of the rectangle.
//
// Return `true` if the circle and rectangle are overlapped otherwise return `false`. In other words, check if there is **any** point `(x_i, y_i)` that belongs to the circle and the rectangle at the same time.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/02/20/sample_4_1728.png
//
// ```
// Input: radius = 1, xCenter = 0, yCenter = 0, x1 = 1, y1 = -1, x2 = 3, y2 = 1
// Output: true
// Explanation: Circle and rectangle share the point (1,0).
// ```
//
// **Example 2:**
//
// ```
// Input: radius = 1, xCenter = 1, yCenter = 1, x1 = 1, y1 = -3, x2 = 2, y2 = -1
// Output: false
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2020/02/20/sample_2_1728.png
//
// ```
// Input: radius = 1, xCenter = 0, yCenter = 0, x1 = -1, y1 = 0, x2 = 0, y2 = 1
// Output: true
// ```
//
// **Constraints:**
//
// - `1 <= radius <= 2000`
// - `-10^4 <= xCenter, yCenter <= 10^4`
// - `-10^4 <= x1 < x2 <= 10^4`
// - `-10^4 <= y1 < y2 <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>

using namespace std;

// Shift the circle to (0, 0).
// Now we check if there is a point (x, y) in the square such that x^2+y^2 <= r^2.
// Lets find the minimal x^2 for x1 <= x <= x2 and minimal y2 for y1 <= y <= y2.
//
// If x1 and x2 has the same sign, then min(x^2) = min(x1^2, x2^2).
// If x1 and x2 has different sign, then min(x^2) = 0.
// Similar to y.
class Solution {
 public:
  bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {
    // Normalize
    x1 -= xCenter, x2 -= xCenter;
    y1 -= yCenter, y2 -= yCenter;

    // Find min(x^2)
    int minXSq = x1 * x2 > 0 ? min(x1 * x1, x2 * x2) : 0;
    int minYSq = y1 * y2 > 0 ? min(y1 * y1, y2 * y2) : 0;
    return minXSq + minYSq <= radius * radius;
  }
};
