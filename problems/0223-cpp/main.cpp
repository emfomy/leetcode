// Source: https://leetcode.com/problems/rectangle-area
// Title: Rectangle Area
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given the coordinates of two **rectilinear** rectangles in a 2D plane, return the total area covered by the two rectangles.
//
// The first rectangle is defined by its **bottom-left** corner `(ax1, ay1)` and its **top-right** corner `(ax2, ay2)`.
//
// The second rectangle is defined by its **bottom-left** corner `(bx1, by1)` and its **top-right** corner `(bx2, by2)`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/05/08/rectangle-plane.png
//
// ```
// Input: ax1 = -3, ay1 = 0, ax2 = 3, ay2 = 4, bx1 = 0, by1 = -1, bx2 = 9, by2 = 2
// Output: 45
// ```
//
// **Example 2:**
//
// ```
// Input: ax1 = -2, ay1 = -2, ax2 = 2, ay2 = 2, bx1 = -2, by1 = -2, bx2 = 2, by2 = 2
// Output: 16
// ```
//
// **Constraints:**
//
// - `-10^4 <= ax1 <= ax2 <= 10^4`
// - `-10^4 <= ay1 <= ay2 <= 10^4`
// - `-10^4 <= bx1 <= bx2 <= 10^4`
// - `-10^4 <= by1 <= by2 <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>

using namespace std;

// Find the overlap range of x and y.
// The answer is the sum of the two area minus the overlapping area.
class Solution {
 public:
  int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
    auto cx1 = max(ax1, bx1), cy1 = max(ay1, by1), cx2 = min(ax2, bx2), cy2 = min(ay2, by2);

    auto aArea = (ax2 - ax1) * (ay2 - ay1);
    auto bArea = (bx2 - bx1) * (by2 - by1);
    auto cArea = ((cx2 - cx1) > 0 && (cy2 - cy1) > 0) ? (cx2 - cx1) * (cy2 - cy1) : 0;

    return aArea + bArea - cArea;
  }
};
