// Source: https://leetcode.com/problems/largest-magic-square
// Title: Largest Magic Square
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A `k x k` **magic square** is a `k x k` grid filled with integers such that every row sum, every column sum, and both diagonal sums are **all equal**. The integers in the magic square **do not have to be distinct**. Every `1 x 1` grid is trivially a **magic square**.
//
// Given an `m x n` integer `grid`, return the **size** (i.e., the side length `k`) of the **largest magic square** that can be found within this grid.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/05/29/magicsquare-grid.jpg
//
// ```
// Input: grid = [[7,1,4,5,6],[2,5,1,6,4],[1,5,4,3,2],[1,2,7,3,4]]
// Output: 3
// Explanation: The largest magic square has a size of 3.
// Every row sum, column sum, and diagonal sum of this magic square is equal to 12.
// - Row sums: 5+1+6 = 5+4+3 = 2+7+3 = 12
// - Column sums: 5+5+2 = 1+4+7 = 6+3+3 = 12
// - Diagonal sums: 5+4+3 = 6+4+2 = 12
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/05/29/magicsquare2-grid.jpg
//
// ```
// Input: grid = [[5,1,3,1],[9,3,3,1],[1,3,3,8]]
// Output: 2
// ```
//
// **Constraints:**
//
// - `m == grid.length`
// - `n == grid[i].length`
// - `1 <= m, n <= 50`
// - `1 <= grid[i][j] <= 10^6`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// DP
//
// Let prerow[i][j] be the row prefix sum end at (i, j).
// Let precol[i][j] be the column prefix sum end at (i, j).
//
// We compute the diagonal directly since it has less overlap.
class Solution {
 public:
  int largestMagicSquare(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    auto mn = min(m, n);

    auto prerow = vector(m, vector(n + 1, 0));
    auto precol = vector(m + 1, vector(n, 0));
    for (auto i = 0; i < m; ++i) {
      for (auto j = 0; j < n; ++j) {
        prerow[i][j + 1] = prerow[i][j] + grid[i][j];
        precol[i + 1][j] = precol[i][j] + grid[i][j];
      }
    }

    // Helper, check square [i, i+k) x [j, j+k)
    auto check = [&](const int i, const int j, const int k) -> bool {
      // rows
      auto sum = prerow[i][j + k] - prerow[i][j];
      for (auto ii = i + 1; ii < i + k; ++ii) {
        if (prerow[ii][j + k] - prerow[ii][j] != sum) return false;
      }

      // cols
      for (auto jj = j; jj < j + k; ++jj) {
        if (precol[i + k][jj] - precol[i][jj] != sum) return false;
      }

      // diag
      auto d1 = 0, d2 = 0;
      for (auto l = 0; l < k; ++l) {
        d1 += grid[i + l][j + l];
        d2 += grid[i + l][j + k - l - 1];
      }
      return (d1 == sum && d2 == sum);
    };

    // k = 1 must be magic square
    for (auto k = mn; k >= 2; --k) {
      for (auto i = 0; i <= m - k; ++i) {
        for (auto j = 0; j <= n - k; ++j) {
          if (check(i, j, k)) return k;
        }
      }
    }
    return 1;
  }
};
