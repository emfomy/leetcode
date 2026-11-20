// Source: https://leetcode.com/problems/equal-sum-grid-partition-i
// Title: Equal Sum Grid Partition I
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an `m x n` matrix `grid` of positive integers. Your task is to determine if it is possible to make **either one horizontal or one vertical cut** on the grid such that:
//
// - Each of the two resulting sections formed by the cut is **non-empty**.
// - The sum of the elements in both sections is **equal**.
//
// Return `true` if such a partition exists; otherwise return `false`.
//
// **Example 1:**
//
// ```
// Input: grid = [[1,4],[2,3]]
// Output: true
// Explanation:
// https://assets.leetcode.com/uploads/2025/03/30/lc.pnghttps://assets.leetcode.com/uploads/2025/03/30/lc.jpeg
// A horizontal cut between row 0 and row 1 results in two non-empty sections, each with a sum of 5. Thus, the answer is `true`.
// ```
//
// **Example 2:**
//
// ```
// Input: grid = [[1,3],[2,4]]
// Output: false
// Explanation:
// No horizontal or vertical cut results in two non-empty sections with equal sums. Thus, the answer is `false`.
// ```
//
// **Constraints:**
//
// - `1 <= m == grid.length <= 10^5`
// - `1 <= n == grid[i].length <= 10^5`
// - `2 <= m * n <= 10^5`
// - `1 <= grid[i][j] <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <vector>

using namespace std;

// Loop
//
// First Compute the total sum.
// Next loop row-wise and column-wise and check if the sum is half of the total sum.
class Solution {
 public:
  bool canPartitionGrid(const vector<vector<int>>& grid) {
    const int m = grid.size(), n = grid[0].size();

    // Total Sum
    int64_t totalSum = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        totalSum += grid[i][j];
      }
    }

    // Total is odd
    if (totalSum % 2) return false;

    // Row-wise
    int64_t rowSum = 0;
    for (int i = 0; i < m - 1; ++i) {  // exclude last row to avoid empty section
      for (int j = 0; j < n; ++j) {
        rowSum += grid[i][j];
      }
      if (2 * rowSum == totalSum) return true;
    }

    // Column-wise
    int64_t colSum = 0;
    for (int j = 0; j < n - 1; ++j) {  // exclude last column to avoid empty section
      for (int i = 0; i < m; ++i) {
        colSum += grid[i][j];
      }
      if (2 * colSum == totalSum) return true;
    }

    return false;
  }
};
