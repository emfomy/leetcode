// Source: https://leetcode.com/problems/island-perimeter
// Title: Island Perimeter
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given `row x col` `grid` representing a map where `grid[i][j] = 1` representsland and `grid[i][j] = 0` represents water.
//
// Grid cells are connected **horizontally/vertically** (not diagonally). The `grid` is completely surrounded by water, and there is exactly one island (i.e., one or more connected land cells).
//
// The island doesn't have "lakes", meaning the water inside isn't connected to the water around the island. One cell is a square with side length 1. The grid is rectangular, width and height don't exceed 100. Determine the perimeter of the island.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2018/10/12/island.png
//
// ```
// Input: grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
// Output: 16
// Explanation: The perimeter is the 16 yellow stripes in the image above.
// ```
//
// **Example 2:**
//
// ```
// Input: grid = [[1]]
// Output: 4
// ```
//
// **Example 3:**
//
// ```
// Input: grid = [[1,0]]
// Output: 4
// ```
//
// **Constraints:**
//
// - `row == grid.length`
// - `col == grid[i].length`
// - `1 <= row, col <= 100`
// - `grid[i][j]` is `0` or `1`.
// - There is exactly one island in `grid`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Counting
//
// Loop through all cell, and check its border.
class Solution {
 public:
  int islandPerimeter(const vector<vector<int>>& grid) {
    const int m = grid.size(), n = grid[0].size();

    int perimeter = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == 0) continue;
        if (i == 0 || grid[i - 1][j] == 0) ++perimeter;
        if (i == m - 1 || grid[i + 1][j] == 0) ++perimeter;
        if (j == 0 || grid[i][j - 1] == 0) ++perimeter;
        if (j == n - 1 || grid[i][j + 1] == 0) ++perimeter;
      }
    }

    return perimeter;
  }
};

// Improved Counting
//
// For each land:
// if it is connected to a land at top, then there is no additional horizontal border;
// if it is connected to a land at left, then there is no additional vertical border.
class Solution2 {
 public:
  int islandPerimeter(const vector<vector<int>>& grid) {
    const int m = grid.size(), n = grid[0].size();

    int perimeter = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == 0) continue;
        if (i == 0 || grid[i - 1][j] == 0) perimeter += 2;
        if (j == 0 || grid[i][j - 1] == 0) perimeter += 2;
      }
    }

    return perimeter;
  }
};
