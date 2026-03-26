// Source: https://leetcode.com/problems/maximum-non-negative-product-in-a-matrix
// Title: Maximum Non Negative Product in a Matrix
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a `m x n` matrix `grid`. Initially, you are located at the top-left corner `(0, 0)`, and in each step, you can only **move right or down** in the matrix.
//
// Among all possible paths starting from the top-left corner `(0, 0)` and ending in the bottom-right corner `(m - 1, n - 1)`, find the path with the **maximum non-negative product**. The product of a path is the product of all integers in the grid cells visited along the path.
//
// Return the maximum non-negative product **modulo** `10^9 + 7`. If the maximum product is **negative**, return `-1`.
//
// Notice that the modulo is performed after getting the maximum product.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/12/23/product1.jpg
//
// ```
// Input: grid = [[-1,-2,-3],[-2,-3,-3],[-3,-3,-2]]
// Output: -1
// Explanation: It is not possible to get non-negative product in the path from (0, 0) to (2, 2), so return -1.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/12/23/product2.jpg
//
// ```
// Input: grid = [[1,-2,1],[1,-2,1],[3,-4,1]]
// Output: 8
// Explanation: Maximum non-negative product is shown (1 * 1 * -2 * -4 * 1 = 8).
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2021/12/23/product3.jpg
//
// ```
// Input: grid = [[1,3],[0,-4]]
// Output: 0
// Explanation: Maximum non-negative product is shown (1 * 0 * -4 = 0).
// ```
//
// **Constraints:**
//
// - `m == grid.length`
// - `n == grid[i].length`
// - `1 <= m, n <= 15`
// - `-4 <= grid[i][j] <= 4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cstdint>
#include <vector>

using namespace std;

// 2D-DP
//
// Max[i][j] is the maximum product to (i, j)
// Min[i][j] is the minimum product to (i, j)
class Solution {
  constexpr static int64_t modulo = 1e9 + 7;

 public:
  int maxProductPath(const vector<vector<int>>& grid) {
    const int m = grid.size(), n = grid[0].size();

    // Init DP
    auto maxDp = vector<vector<int64_t>>(m, vector<int64_t>(n));
    auto minDp = vector<vector<int64_t>>(m, vector<int64_t>(n));
    maxDp[0][0] = grid[0][0];
    minDp[0][0] = grid[0][0];

    // i = 0
    maxDp[0][0] = grid[0][0];
    minDp[0][0] = grid[0][0];
    for (int j = 1; j < n; ++j) {
      auto [minProd, maxProd] = minmax({
          maxDp[0][j - 1] * grid[0][j],
          minDp[0][j - 1] * grid[0][j],
      });
      maxDp[0][j] = maxProd;
      minDp[0][j] = minProd;
    }

    // i > 0
    for (int i = 1; i < m; ++i) {
      // j = 0
      auto [minProd, maxProd] = minmax({
          maxDp[i - 1][0] * grid[i][0],
          minDp[i - 1][0] * grid[i][0],
      });
      maxDp[i][0] = maxProd;
      minDp[i][0] = minProd;

      // j > 0
      for (int j = 1; j < n; ++j) {
        auto [minProd, maxProd] = minmax({
            maxDp[i][j - 1] * grid[i][j],
            maxDp[i - 1][j] * grid[i][j],
            minDp[i][j - 1] * grid[i][j],
            minDp[i - 1][j] * grid[i][j],
        });
        maxDp[i][j] = maxProd;
        minDp[i][j] = minProd;
      }
    }

    return max(static_cast<int>(maxDp[m - 1][n - 1] % modulo), -1);
  }
};

// 1D-DP
//
// Max[i][j] is the maximum product to (i, j)
// Min[i][j] is the minimum product to (i, j)
class Solution2 {
  constexpr static int64_t modulo = 1e9 + 7;

 public:
  int maxProductPath(const vector<vector<int>>& grid) {
    const int m = grid.size(), n = grid[0].size();

    // Init DP
    auto maxPrev = vector<int64_t>(n);
    auto maxCurr = vector<int64_t>(n);
    auto minPrev = vector<int64_t>(n);
    auto minCurr = vector<int64_t>(n);

    // i = 0
    maxCurr[0] = grid[0][0];
    minCurr[0] = grid[0][0];
    for (int j = 1; j < n; ++j) {
      auto [minProd, maxProd] = minmax({
          maxCurr[j - 1] * grid[0][j],
          minCurr[j - 1] * grid[0][j],
      });
      maxCurr[j] = maxProd;
      minCurr[j] = minProd;
    }

    // i > 0
    for (int i = 1; i < m; ++i) {
      swap(maxCurr, maxPrev);
      swap(minCurr, minPrev);

      // j = 0
      auto [minProd, maxProd] = minmax({
          maxPrev[0] * grid[i][0],
          minPrev[0] * grid[i][0],
      });
      maxCurr[0] = maxProd;
      minCurr[0] = minProd;

      // j > 0
      for (int j = 1; j < n; ++j) {
        auto [minProd, maxProd] = minmax({
            maxCurr[j - 1] * grid[i][j],
            maxPrev[j] * grid[i][j],
            minCurr[j - 1] * grid[i][j],
            minPrev[j] * grid[i][j],
        });
        maxCurr[j] = maxProd;
        minCurr[j] = minProd;
      }
    }

    return max(static_cast<int>(maxCurr[n - 1] % modulo), -1);
  }
};
