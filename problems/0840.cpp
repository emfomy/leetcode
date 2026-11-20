// Source: https://leetcode.com/problems/magic-squares-in-grid
// Title: Magic Squares In Grid
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A `3 x 3` **magic square** is a `3 x 3` grid filled with distinct numbers **from **1** to **9 such that each row, column, and both diagonals all have the same sum.
//
// Given a `row x col` `grid` of integers, how many `3 x 3` magic square subgrids are there?
//
// Note: while a magic square can only contain numbers from 1 to 9, `grid` may contain numbers up to 15.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/09/11/magic_main.jpg
//
// ```
// Input: grid = [[4,3,8,4],[9,5,1,9],[2,7,6,2]]
// Output: 1
// Explanation:
// The following subgrid is a 3 x 3 magic square:
// https://assets.leetcode.com/uploads/2020/09/11/magic_valid.jpg
// while this one is not:
// https://assets.leetcode.com/uploads/2020/09/11/magic_invalid.jpg
// In total, there is only one magic square inside the given grid.
// ```
//
// **Example 2:**
//
// ```
// Input: grid = [[8]]
// Output: 0
// ```
//
// **Constraints:**
//
// - `row == grid.length`
// - `col == grid[i].length`
// - `1 <= row, col <= 10`
// - `0 <= grid[i][j] <= 15`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <array>
#include <vector>

using namespace std;

// Scan
class Solution {
 public:
  int numMagicSquaresInside(vector<vector<int>>& grid) {
    auto m = grid.size(), n = grid[0].size();
    if (m < 3 || n < 3) return 0;

    auto ans = 0;
    for (auto row = 0; row <= m - 3; ++row) {
      for (auto col = 0; col <= n - 3; ++col) {
        ans += isMagic(grid, row, col);
      }
    }

    return ans;
  }

  bool isMagic(vector<vector<int>>& grid, int row, int col) {
    // Numbers
    auto seen = array<bool, 10>();
    for (auto r = row; r < row + 3; ++r) {
      for (auto c = col; c < col + 3; ++c) {
        if (grid[r][c] >= 10 || grid[r][c] == 0 || seen[grid[r][c]]) return false;
        seen[grid[r][c]] = true;
      }
    }

    return (grid[row + 0][col + 0] + grid[row + 0][col + 1] + grid[row + 0][col + 2] == 15 &&
            grid[row + 1][col + 0] + grid[row + 1][col + 1] + grid[row + 1][col + 2] == 15 &&
            grid[row + 2][col + 0] + grid[row + 2][col + 1] + grid[row + 2][col + 2] == 15 &&
            grid[row + 0][col + 0] + grid[row + 1][col + 0] + grid[row + 2][col + 0] == 15 &&
            grid[row + 0][col + 1] + grid[row + 1][col + 1] + grid[row + 2][col + 1] == 15 &&
            grid[row + 0][col + 2] + grid[row + 1][col + 2] + grid[row + 2][col + 2] == 15 &&
            grid[row + 0][col + 0] + grid[row + 1][col + 1] + grid[row + 2][col + 2] == 15 &&
            grid[row + 0][col + 2] + grid[row + 1][col + 1] + grid[row + 2][col + 0] == 15);
  }
};

// Scan
//
// There are only 8 possible magic square.
// The center must be 5.
// The outer must be one of the followings: (start from top left and go clockwise)
// 81672943, 67294381, 29438167, 43816729,
// 83492761, 61834927, 27618349, 49276183.
class Solution2 {
  const vector<vector<int>> patterns = {
      {2, 7, 6, 1, 8, 3, 4, 9},  //
      {2, 9, 4, 3, 8, 1, 6, 7},  //
      {4, 3, 8, 1, 6, 7, 2, 9},  //
      {4, 9, 2, 7, 6, 1, 8, 3},  //
      {6, 1, 8, 3, 4, 9, 2, 7},  //
      {6, 7, 2, 9, 4, 3, 8, 1},  //
      {8, 3, 4, 9, 2, 7, 6, 1},  //
      {8, 1, 6, 7, 2, 9, 4, 3},  //
  };

 public:
  int numMagicSquaresInside(vector<vector<int>>& grid) {
    auto m = grid.size(), n = grid[0].size();
    if (m < 3 || n < 3) return 0;

    // Scan
    auto ans = 0;
    for (auto row = 1; row < m - 1; ++row) {
      for (auto col = 1; col < n - 1; ++col) {
        if (grid[row][col] == 5) ans += isMagic(grid, row, col);
      }
    }
    return ans;
  }

  bool isMagic(vector<vector<int>>& grid, int row, int col) {
    for (auto& pattern : patterns) {
      if (grid[row - 1][col - 1] == pattern[0] && grid[row - 1][col + 0] == pattern[1] &&
          grid[row - 1][col + 1] == pattern[2] && grid[row + 0][col + 1] == pattern[3] &&
          grid[row + 1][col + 1] == pattern[4] && grid[row + 1][col + 0] == pattern[5] &&
          grid[row + 1][col - 1] == pattern[6] && grid[row + 0][col - 1] == pattern[7])
        return true;
    }

    return false;
  }
};
