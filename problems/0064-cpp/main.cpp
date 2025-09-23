// Source: https://leetcode.com/problems/minimum-path-sum
// Title: Minimum Path Sum
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a `m x n` `grid` filled with non-negative numbers, find a path from top left to bottom right, which minimizes the sum of all numbers along its path.
//
// **Note:** You can only move either down or right at any point in time.
//
// **Example 1:**
//
// https://assets.leetcode.com/uploads/2020/11/05/minpath.jpg
//
// ```
// Input: grid = [[1,3,1],[1,5,1],[4,2,1]]
// Output: 7
// Explanation: Because the path 1 → 3 → 1 → 1 → 1 minimizes the sum.
// ```
//
// **Example 2:**
//
// ```
// Input: grid = [[1,2,3],[4,5,6]]
// Output: 12
// ```
//
// **Constraints:**
//
// - `m == grid.length`
// - `n == grid[i].length`
// - `1 <= m, n <= 200`
// - `0 <= grid[i][j] <= 200`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Use DP
//
// dp[i, j] = min(dp[i, j-1], dp[i-1, j]) + grid[i, j]
class Solution {
 public:
  int minPathSum(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();

    // First row
    auto curr = vector<int>(n);
    curr[0] = grid[0][0];
    for (auto j = 1; j < n; ++j) {
      curr[j] = curr[j - 1] + grid[0][j];
    }

    // Other Rows
    auto prev = vector<int>(n);
    for (auto i = 1; i < m; ++i) {
      swap(curr, prev);
      curr[0] = prev[0] + grid[i][0];
      for (auto j = 1; j < n; ++j) {
        curr[j] = min(curr[j - 1], prev[j]) + grid[i][j];
      }
    }

    return curr[n - 1];
  }
};
