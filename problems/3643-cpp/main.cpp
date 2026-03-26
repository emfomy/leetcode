// Source: https://leetcode.com/problems/flip-square-submatrix-vertically
// Title: Flip Square Submatrix Vertically
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an `m x n` integer matrix `grid`, and three integers `x`, `y`, and `k`.
//
// The integers `x` and `y` represent the row and column indices of the **top-left** corner of a **square** submatrix and the integer `k` represents the size (side length) of the square submatrix.
//
// Your task is to flip the submatrix by reversing the order of its rows vertically.
//
// Return the updated matrix.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2025/07/20/gridexmdrawio.png
//
// ```
// Input: grid = [[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]], x = 1, y = 0, k = 3
// Output: [[1,2,3,4],[13,14,15,8],[9,10,11,12],[5,6,7,16]]
// Explanation:
// The diagram above shows the grid before and after the transformation.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2025/07/20/gridexm2drawio.png
//
// ```
// Input: grid = [[3,4,2,3],[2,3,4,2]], x = 0, y = 2, k = 2
// Output: [[3,4,4,2],[2,3,2,3]]
// Explanation:
// The diagram above shows the grid before and after the transformation.
// ```
//
// **Constraints:**
//
// - `m == grid.length`
// - `n == grid[i].length`
// - `1 <= m, n <= 50`
// - `1 <= grid[i][j] <= 100`
// - `0 <= x < m`
// - `0 <= y < n`
// - `1 <= k <= min(m - x, n - y)`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> reverseSubmatrix(      //
      vector<vector<int>>& grid,             //
      const int x, const int y, const int k  //
  ) {
    for (int i = 0; i < k / 2; ++i) {
      for (int j = 0; j < k; ++j) {
        swap(grid[x + i][y + j], grid[x + k - i - 1][y + j]);
      }
    }

    return grid;
  }
};
