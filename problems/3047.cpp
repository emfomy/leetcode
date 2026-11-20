// Source: https://leetcode.com/problems/find-the-largest-area-of-square-inside-two-rectangles
// Title: Find the Largest Area of Square Inside Two Rectangles
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There exist `n` rectangles in a 2D plane with edges parallel to the x and y axis. You are given two 2D integer arrays`bottomLeft` and `topRight`where `bottomLeft[i] = [a_i, b_i]` and `topRight[i] = [c_i, d_i]` representthe **bottom-left** and **top-right** coordinates of the `i^th` rectangle, respectively.
//
// You need to find the **maximum** area of a **square** that can fit inside the intersecting region of at least two rectangles. Return `0` if such a square does not exist.
//
// **Example 1:**
//
// https://assets.leetcode.com/uploads/2024/01/05/example12.png
//
// ```
// Input: bottomLeft = [[1,1],[2,2],[3,1]], topRight = [[3,3],[4,4],[6,6]]
// Output: 1
// Explanation:
// A square with side length 1 can fit inside either the intersecting region of rectangles 0 and 1 or the intersecting region of rectangles 1 and 2. Hence the maximum area is 1. It can be shown that a square with a greater side length can not fit inside any intersecting region of two rectangles.
// ```
//
// **Example 2:**
//
// https://assets.leetcode.com/uploads/2024/07/15/diag.png
//
// ```
// Input: bottomLeft = [[1,1],[1,3],[1,5]], topRight = [[5,5],[5,7],[5,9]]
// Output: 4
// Explanation:
// A square with side length 2 can fit inside either the intersecting region of rectangles 0 and 1 or the intersecting region of rectangles 1 and 2. Hence the maximum area is `2 * 2 = 4`. It can be shown that a square with a greater side length can not fit inside any intersecting region of two rectangles.
// ```
//
// **Example 3:**
//
// https://assets.leetcode.com/uploads/2024/01/04/rectanglesexample2.png
//
// ```
// Input: bottomLeft = [[1,1],[2,2],[1,2]], topRight = [[3,3],[4,4],[3,4]]
// Output: 1
// Explanation:
// A square with side length 1 can fit inside the intersecting region of any two rectangles. Also, no larger square can, so the maximum area is 1. Note that the region can be formed by the intersection of more than 2 rectangles.
// ```
//
// **Example 4:**
//
// https://assets.leetcode.com/uploads/2024/01/04/rectanglesexample3.png
//
// ```
// Input: bottomLeft = [[1,1],[3,3],[3,1]], topRight = [[2,2],[4,4],[4,2]]
// Output: 0
// Explanation:
// No pair of rectangles intersect, hence, the answer is 0.
// ```
//
// **Constraints:**
//
// - `n == bottomLeft.length == topRight.length`
// - `2 <= n <= 10^3`
// - `bottomLeft[i].length == topRight[i].length == 2`
// - `1 <= bottomLeft[i][0], bottomLeft[i][1] <= 10^7`
// - `1 <= topRight[i][0], topRight[i][1] <= 10^7`
// - `bottomLeft[i][0] < topRight[i][0]`
// - `bottomLeft[i][1] < topRight[i][1]`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Loop through all rectangle pairs. Check the size of its intersection.
class Solution {
 public:
  long long largestSquareArea(vector<vector<int>>& bottomLeft, vector<vector<int>>& topRight) {
    int n = bottomLeft.size();

    auto size = 0;
    for (auto i = 0; i < n; ++i) {
      for (auto j = 0; j < i; ++j) {
        auto ix1 = bottomLeft[i][0], iy1 = bottomLeft[i][1], ix2 = topRight[i][0], iy2 = topRight[i][1];
        auto jx1 = bottomLeft[j][0], jy1 = bottomLeft[j][1], jx2 = topRight[j][0], jy2 = topRight[j][1];
        auto x1 = max(ix1, jx1), y1 = max(iy1, jy1), x2 = min(ix2, jx2), y2 = min(iy2, jy2);
        size = max(size, min(x2 - x1, y2 - y1));
      }
    }

    return 1LL * size * size;
  }
};
