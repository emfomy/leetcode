// Source: https://leetcode.com/problems/check-if-there-is-a-valid-path-in-a-grid
// Title: Check if There is a Valid Path in a Grid
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an `m x n` `grid`. Each cell of `grid` represents a street. The street of `grid[i][j]` can be:
//
// - `1` which means a street connecting the left cell and the right cell.
// - `2` which means a street connecting the upper cell and the lower cell.
// - `3` which means a street connecting the left cell and the lower cell.
// - `4` which means a street connecting the right cell and the lower cell.
// - `5` which means a street connecting the left cell and the upper cell.
// - `6` which means a street connecting the right cell and the upper cell.
// https://assets.leetcode.com/uploads/2020/03/05/main.png
//
// You will initially start at the street of the upper-left cell `(0, 0)`. A valid path in the grid is a path that starts from the upper left cell `(0, 0)` and ends at the bottom-right cell `(m - 1, n - 1)`. **The path should only follow the streets**.
//
// **Notice** that you are **not allowed** to change any street.
//
// Return `true` if there is a valid path in the grid or `false` otherwise.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/03/05/e1.png
//
// ```
// Input: grid = [[2,4,3],[6,5,2]]
// Output: true
// Explanation: As shown you can start at cell (0, 0) and visit all the cells of the grid to reach (m - 1, n - 1).
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2020/03/05/e2.png
//
// ```
// Input: grid = [[1,2,1],[1,2,1]]
// Output: false
// Explanation: As shown you the street at cell (0, 0) is not connected with any street of any other cell and you will get stuck at cell (0, 0)
// ```
//
// **Example 3:**
//
// ```
// Input: grid = [[1,1,2]]
// Output: false
// Explanation: You will get stuck at cell (0, 1) and you cannot reach cell (0, 2).
// ```
//
// **Constraints:**
//
// - `m == grid.length`
// - `n == grid[i].length`
// - `1 <= m, n <= 300`
// - `1 <= grid[i][j] <= 6`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <utility>
#include <vector>

using namespace std;

// BFS
class Solution {
  using Bool = unsigned char;

  constexpr static Bool canUp[7] = {false, false, true, false, false, true, true};
  constexpr static Bool canDown[7] = {false, false, true, true, true, false, false};
  constexpr static Bool canLeft[7] = {false, true, false, true, false, true, false};
  constexpr static Bool canRight[7] = {false, true, false, false, true, false, true};

 public:
  bool hasValidPath(const vector<vector<int>>& grid) {
    const int m = grid.size(), n = grid[0].size();

    auto que = queue<pair<int, int>>();
    auto visited = vector<vector<Bool>>(m, vector<Bool>(n));
    que.emplace(0, 0);
    visited[0][0] = true;

    while (!que.empty()) {
      auto [i, j] = que.front();
      que.pop();

      // Found
      if (i == m - 1 && j == n - 1) return true;

      // up
      if (i > 0 && !visited[i - 1][j] && canUp[grid[i][j]] && canDown[grid[i - 1][j]]) {
        que.emplace(i - 1, j);
        visited[i - 1][j] = true;
      }

      // down
      if (i < m - 1 && !visited[i + 1][j] && canDown[grid[i][j]] && canUp[grid[i + 1][j]]) {
        que.emplace(i + 1, j);
        visited[i + 1][j] = true;
      }

      // left
      if (j > 0 && !visited[i][j - 1] && canLeft[grid[i][j]] && canRight[grid[i][j - 1]]) {
        que.emplace(i, j - 1);
        visited[i][j - 1] = true;
      }

      // right
      if (j < n - 1 && !visited[i][j + 1] && canRight[grid[i][j]] && canLeft[grid[i][j + 1]]) {
        que.emplace(i, j + 1);
        visited[i][j + 1] = true;
      }
    }

    return false;
  }
};

// DFS
//
// Since the path is a road without branching, we can use DFS instead.
class Solution2 {
  using Bool = unsigned char;

  enum Dir { DOWN = 0, UP = 1, RIGHT = 2, LEFT = 3, NONE = 4 };

  constexpr static pair<int, int> dirs[4] = {
      {1, 0},   // down
      {-1, 0},  // up
      {0, 1},   // right
      {0, -1},  // left
  };

  // Previous Dir x Cell -> Next Dir
  constexpr static Dir nextDir[4][7] = {
      {NONE, NONE, DOWN, NONE, NONE, LEFT, RIGHT},  // down
      {NONE, NONE, UP, LEFT, RIGHT, NONE, NONE},    // up
      {NONE, RIGHT, NONE, DOWN, NONE, UP, NONE},    // right
      {NONE, LEFT, NONE, NONE, DOWN, NONE, UP},     // left
  };

  // Next Dir x Next Cell
  constexpr static Bool canGo[4][7] = {
      {false, false, true, false, false, true, true},  // down
      {false, false, true, true, true, false, false},  // up
      {false, true, false, true, false, true, false},  // right
      {false, true, false, false, true, false, true},  // left
  };

 public:
  bool hasValidPath(const vector<vector<int>>& grid) {
    const int m = grid.size(), n = grid[0].size();

    // Helper
    const auto dfs = [&](Dir d) -> bool {
      int i = 0, j = 0;
      while (true) {
        // Found
        if (i == m - 1 && j == n - 1) return true;

        // Move
        i += dirs[d].first;
        j += dirs[d].second;
        if (i < 0 || i >= m || j < 0 || j >= n) return false;
        if (!canGo[d][grid[i][j]]) return false;

        // Cycle
        if (i == 0 && j == 0) return false;

        // Turn
        d = nextDir[d][grid[i][j]];
        if (d == NONE) return false;
      }
    };

    // Go right
    if (grid[0][0] == 1 || grid[0][0] == 4 || grid[0][0] == 6) {
      if (dfs(RIGHT)) return true;
    }

    // Go down
    if (grid[0][0] == 2 || grid[0][0] == 3 || grid[0][0] == 4) {
      if (dfs(DOWN)) return true;
    }

    return false;
  }
};
