// Source: https://leetcode.com/problems/minimum-cost-path-with-teleportations
// Title: Minimum Cost Path with Teleportations
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a `m x n` 2D integer array `grid` and an integer `k`. You start at the top-left cell `(0, 0)` and your goal is to reach the bottom‐right cell `(m - 1, n - 1)`.
//
// There are two types of moves available:
// - **Normal move**: You can move right or down from your current cell `(i, j)`, i.e. you can move to `(i, j + 1)` (right) or `(i + 1, j)` (down). The cost is the value of the destination cell.
// - **Teleportation**: You can teleport from any cell `(i, j)`, to any cell `(x, y)` such that `grid[x][y] <= grid[i][j]`; the cost of this move is 0. You may teleport at most `k` times.
//
// Return the **minimum** total cost to reach cell `(m - 1, n - 1)` from `(0, 0)`.
//
// **Example 1:**
//
// ```
// Input: grid = [[1,3,3],[2,5,4],[4,3,5]], k = 2
// Output: 7
// Explanation:
// Initially we are at (0, 0) and cost is 0.
//
// | Current Position | Move       | New Position | Total Cost |
// |------------------|------------|--------------|------------|
// | (0, 0)           | Move Down  | (1, 0)       | 0 + 2 = 2  |
// | (1, 0)           | Move Right | (1, 1)       | 2 + 5 = 7  |
// | (1, 1)           | Teleport   | (2, 2)       | 7 + 0 = 7  |
//
// The minimum cost to reach bottom-right cell is 7.
// ```
//
// **Example 2:**
//
// ```
// Input: grid = [[1,2],[2,3],[3,4]], k = 1
// Output: 9
// Explanation:
// Initially we are at (0, 0) and cost is 0.
//
// | Current Position | Move       | New Position | Total Cost |
// |------------------|------------|--------------|------------|
// | (0, 0)           | Move Down  | (1, 0)       | 0 + 2 = 2  |
// | (1, 0)           | Move Right | (1, 1)       | 2 + 3 = 5  |
// | (1, 1)           | Move Down  | (2, 1)       | 5 + 4 = 9  |
//
// The minimum cost to reach bottom-right cell is 9.
// ```
//
// **Constraints:**
//
// - `2 <= m, n <= 80`
// - `m == grid.length`
// - `n == grid[i].length`
// - `0 <= grid[i][j] <= 10^4`
// - `0 <= k <= 10`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <map>
#include <vector>

using namespace std;

// DP + Sort
//
// We do k+1 rounds.
// In each round, go from top left to button right and compute the minimal costs.
//
// Next sort all cell by its weight (decreasing) and cost (increasing).
// For each cell, we would like to teleport from a higher weight with minimal cost.
class Solution {
  using Cell = tuple<int, int, int, int>;  // -weight, cost, row, col

 public:
  int minCost(vector<vector<int>>& grid, int k) {
    int m = grid.size(), n = grid[0].size();

    auto cells = vector<Cell>();
    cells.reserve(m * n);

    auto costs = vector(m, vector(n, INT_MAX));
    costs[0][0] = 0;

    // Loop
    for (auto t = 0; t <= k; ++t) {
      // DP
      for (auto i = 0; i < m; ++i) {
        for (auto j = 0; j < n; ++j) {
          if (i > 0) costs[i][j] = min(costs[i][j], costs[i - 1][j] + grid[i][j]);
          if (j > 0) costs[i][j] = min(costs[i][j], costs[i][j - 1] + grid[i][j]);
        }
      }

      // Teleport
      if (t < k) {
        cells.clear();
        for (auto i = 0; i < m; ++i) {
          for (auto j = 0; j < n; ++j) {
            cells.push_back({-grid[i][j], costs[i][j], i, j});
          }
        }
        sort(cells.begin(), cells.end());

        auto minCost = INT_MAX;
        for (auto [_, c, i, j] : cells) {
          costs[i][j] = min(costs[i][j], minCost);
          minCost = min(minCost, c);
        }
      }
    }

    return costs[m - 1][n - 1];
  }
};

// DP + Sort
//
// Instead of sorting by weight and cost, we sort by weight only at the beginning.
// In the teleportation loop, we scan all cells with the same weights,
// find the minimal cost and update the them together.
class Solution2 {
  using Cell = pair<int, int>;  // row, col

 public:
  int minCost(vector<vector<int>>& grid, int k) {
    int m = grid.size(), n = grid[0].size();

    auto cellMap = map<int, vector<Cell>>();
    for (auto i = 0; i < m; ++i) {
      for (auto j = 0; j < n; ++j) {
        cellMap[-grid[i][j]].push_back({i, j});
      }
    }
    auto cellGroups = vector<vector<Cell>>();
    for (auto& [_, cell] : cellMap) {
      cellGroups.push_back(std::move(cell));
    }

    auto costs = vector(m, vector(n, INT_MAX));
    costs[0][0] = 0;

    // Loop
    for (auto t = 0; t <= k; ++t) {
      // DP
      for (auto i = 0; i < m; ++i) {
        for (auto j = 0; j < n; ++j) {
          if (i > 0) costs[i][j] = min(costs[i][j], costs[i - 1][j] + grid[i][j]);
          if (j > 0) costs[i][j] = min(costs[i][j], costs[i][j - 1] + grid[i][j]);
        }
      }

      // Teleport
      if (t < k) {
        auto minCost = INT_MAX;
        for (auto& cells : cellGroups) {
          for (auto [i, j] : cells) {
            minCost = min(minCost, costs[i][j]);
          }
          for (auto [i, j] : cells) {
            costs[i][j] = min(costs[i][j], minCost);
          }
        }
      }
    }

    return costs[m - 1][n - 1];
  }
};
