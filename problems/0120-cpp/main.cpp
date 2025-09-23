// Source: https://leetcode.com/problems/triangle
// Title: Triangle
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a `triangle` array, return the minimum path sum from top to bottom.
//
// For each step, you may move to an adjacent number of the row below. More formally, if you are on index `i` on the current row, you may move to either index `i` or index `i + 1` on the next row.
//
// **Example 1:**
//
// ```
// Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
// Output: 11
// Explanation: The triangle looks like:
//    2
//   3 4
//  6 5 7
// 4 1 8 3
// The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11 (underlined above).
// ```
//
// **Example 2:**
//
// ```
// Input: triangle = [[-10]]
// Output: -10
// ```
//
// **Constraints:**
//
// - `1 <= triangle.length <= 200`
// - `triangle[0].length == 1`
// - `triangle[i].length == triangle[i - 1].length + 1`
// - `-10^4 <= triangle[i][j] <= 10^4`
//
// **Follow up:** Could you do this using only `O(n)` extra space, where `n` is the total number of rows in the triangle?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Use DP
class Solution {
 public:
  int minimumTotal(vector<vector<int>>& triangle) {
    int n = triangle.size();

    // DP
    auto curr = vector<int>(n);
    auto prev = vector<int>(n);
    curr[0] = triangle[0][0];

    for (auto i = 1; i < n; ++i) {
      swap(curr, prev);
      curr[0] = prev[0] + triangle[i][0];
      for (auto j = 1; j < i; ++j) {
        curr[j] = min(prev[j - 1], prev[j]) + triangle[i][j];
      }
      curr[i] = prev[i - 1] + triangle[i][i];
    }

    auto ansIt = min_element(curr.cbegin(), curr.cend());
    return *ansIt;
  }
};
