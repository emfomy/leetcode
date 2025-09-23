// Source: https://leetcode.com/problems/maximum-area-of-longest-diagonal-rectangle
// Title: Maximum Area of Longest Diagonal Rectangle
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a 2D **0-indexed** integer array `dimensions`.
//
// For all indices `i`, `0 <= i < dimensions.length`, `dimensions[i][0]` represents the length and `dimensions[i][1]` represents the width of the rectangle `i`.
//
// Return the **area** of the rectangle having the **longest** diagonal. If there are multiple rectangles with the longest diagonal, return the area of the rectangle having the **maximum** area.
//
// **Example 1:**
//
// ```
// Input: dimensions = [[9,3],[8,6]]
// Output: 48
// Explanation:
// For index = 0, length = 9 and width = 3. Diagonal length = sqrt(9 * 9 + 3 * 3) = sqrt(90) ≈ 9.487.
// For index = 1, length = 8 and width = 6. Diagonal length = sqrt(8 * 8 + 6 * 6) = sqrt(100) = 10.
// So, the rectangle at index 1 has a greater diagonal length therefore we return area = 8 * 6 = 48.
// ```
//
// **Example 2:**
//
// ```
// Input: dimensions = [[3,4],[4,3]]
// Output: 12
// Explanation: Length of diagonal is the same for both which is 5, so maximum area = 12.
// ```
//
// **Constraints:**
//
// - `1 <= dimensions.length <= 100`
// - `dimensions[i].length == 2`
// - `1 <= dimensions[i][0], dimensions[i][1] <= 100`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

class Solution {
 public:
  int areaOfMaxDiagonal(vector<vector<int>>& dimensions) {
    auto maxDiag2 = 0;
    auto maxArea = 0;

    for (auto& rect : dimensions) {
      auto diag2 = rect[0] * rect[0] + rect[1] * rect[1];
      auto area = rect[0] * rect[1];
      if (maxDiag2 < diag2) {
        maxDiag2 = diag2;
        maxArea = area;
      } else if (maxDiag2 == diag2) {
        maxDiag2 = diag2;
        maxArea = max(maxArea, rect[0] * rect[1]);
      }
    }

    return maxArea;
  }
};
