// Source: https://leetcode.com/problems/max-area-of-island
// Title: Max Area of Island
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an `m x n` binary matrix `grid`. An island is a group of `1`'s (representing land) connected **4-directionally** (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.
//
// The **area** of an island is the number of cells with a value `1` in the island.
//
// Return the maximum **area** of an island in `grid`. If there is no island, return `0`.
//
// **Example 1:**
//
// https://assets.leetcode.com/uploads/2021/05/01/maxarea1-grid.jpg
//
// ```
// Input: grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]
// Output: 6
// Explanation: The answer is not 11, because the island must be connected 4-directionally.
// ```
//
// **Example 2:**
//
// ```
// Input: grid = [[0,0,0,0,0,0,0,0]]
// Output: 0
// ```
//
// **Constraints:**
//
// - `m == grid.length`
// - `n == grid[i].length`
// - `1 <= m, n <= 50`
// - `grid[i][j]` is either `0` or `1`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <vector>

using namespace std;

// BFS
//
// We overwrite the original grid. Use value 2 as visited.
class Solution {
  using Cell = pair<int, int>;

 public:
  int maxAreaOfIsland(vector<vector<int>>& grid) {
    const int m = grid.size(), n = grid[0].size();

    int maxCount = 0;
    auto que = queue<Cell>();
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] != 1) continue;

        // BFS
        int count = 1;
        que.push({i, j});
        grid[i][j] = 2;
        while (!que.empty()) {
          auto [r, c] = que.front();
          que.pop();

          if (r - 1 >= 0 && grid[r - 1][c] == 1) {
            ++count;
            que.push({r - 1, c});
            grid[r - 1][c] = 2;
          }
          if (r + 1 < m && grid[r + 1][c] == 1) {
            ++count;
            que.push({r + 1, c});
            grid[r + 1][c] = 2;
          }
          if (c - 1 >= 0 && grid[r][c - 1] == 1) {
            ++count;
            que.push({r, c - 1});
            grid[r][c - 1] = 2;
          }
          if (c + 1 < n && grid[r][c + 1] == 1) {
            ++count;
            que.push({r, c + 1});
            grid[r][c + 1] = 2;
          }
        }

        maxCount = max(maxCount, count);
      }
    }

    return maxCount;
  }
};
