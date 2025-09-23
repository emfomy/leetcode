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

// Use 2D-DP
//
// dp[i, j] is the size of the largest square with (i, j) as top-left corner.
// If matrix[i, j] = 1, then dp[i, j] = min(dp[i+1,j+1], dp[i+1,j], dp[i,j+1])+1
class Solution {
 public:
  int maximalSquare(vector<vector<char>>& matrix) {
    int m = matrix.size(), n = matrix[0].size();

    // DP
    auto ans = 0;
    auto dp = vector(m + 1, vector(n + 1, 0));
    for (auto i = m - 1; i >= 0; --i) {
      for (auto j = n - 1; j >= 0; --j) {
        if (matrix[i][j] == '1') {
          dp[i][j] = min({dp[i + 1][j + 1], dp[i + 1][j], dp[i][j + 1]}) + 1;
          ans = max(ans, dp[i][j]);
        }
      }
    }

    return ans * ans;
  }
};

// Use 1D-DP
class Solution2 {
 public:
  int maximalSquare(vector<vector<char>>& matrix) {
    int m = matrix.size(), n = matrix[0].size();

    // DP
    auto ans = 0;
    auto curr = vector(n + 1, 0);
    auto prev = vector(n + 1, 0);
    for (auto i = m - 1; i >= 0; --i) {
      swap(curr, prev);
      for (auto j = n - 1; j >= 0; --j) {
        curr[j] = (matrix[i][j] == '0') ? 0 : min({prev[j + 1], prev[j], curr[j + 1]}) + 1;
        ans = max(ans, curr[j]);
      }
    }

    return ans * ans;
  }
};
