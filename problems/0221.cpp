// Source: https://leetcode.com/problems/maximal-square
// Title: Maximal Square
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an `m x n` binary `matrix` filled with `0`'s and `1`'s, find the largest square containing only `1`'s and return its area.
//
// **Example 1:**
//
// https://assets.leetcode.com/uploads/2020/11/26/max1grid.jpg
//
// ```
// Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
// Output: 4
// ```
//
// **Example 2:**
//
// https://assets.leetcode.com/uploads/2020/11/26/max2grid.jpg
//
// ```
// Input: matrix = [["0","1"],["1","0"]]
// Output: 1
// ```
//
// **Example 3:**
//
// ```
// Input: matrix = [["0"]]
// Output: 0
// ```
//
// **Constraints:**
//
// - `m == matrix.length`
// - `n == matrix[i].length`
// - `1 <= m, n <= 300`
// - `matrix[i][j]` is `'0'` or `'1'`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// 2D-DP
//
// Let DP[i, j] be the maximum size with (i, j) as top-left corner.
// We loop from bottom-right to compute the values.
//
// DP[i, j] = 0                                             if matrix[i, j] = 0
// DP[i, j] = min(DP[i+1, j], DP[i, j+1], DP[i+1, j+1]) + 1 if matrix[i, j] = 1
class Solution {
 public:
  int maximalSquare(const vector<vector<char>>& matrix) {
    const int m = matrix.size(), n = matrix[0].size();

    int maxSize = 0;
    auto dp = vector<vector<int>>(m + 1, vector<int>(n + 1, 0));
    for (int i = m - 1; i >= 0; --i) {
      for (int j = n - 1; j >= 0; --j) {
        dp[i][j] = (matrix[i][j] == '0') ? 0 : (min({dp[i][j + 1], dp[i + 1][j], dp[i + 1][j + 1]}) + 1);
        maxSize = max(maxSize, dp[i][j]);
      }
    }

    return maxSize * maxSize;
  }
};

// 1D-DP
class Solution2 {
 public:
  int maximalSquare(const vector<vector<char>>& matrix) {
    const int m = matrix.size(), n = matrix[0].size();

    int maxSize = 0;
    auto prev = vector<int>(n + 1, 0);
    auto curr = vector<int>(n + 1, 0);
    for (int i = m - 1; i >= 0; --i) {
      swap(curr, prev);
      for (int j = n - 1; j >= 0; --j) {
        curr[j] = (matrix[i][j] == '0') ? 0 : (min({curr[j + 1], prev[j], prev[j + 1]}) + 1);
        maxSize = max(maxSize, curr[j]);
      }
    }

    return maxSize * maxSize;
  }
};
