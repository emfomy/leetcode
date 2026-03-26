// Source: https://leetcode.com/problems/rotting-oranges
// Title: Rotting Oranges
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an `m x n` `grid` where each cell can have one of three values:
//
// - `0` representing an empty cell,
// - `1` representing a fresh orange, or
// - `2` representing a rotten orange.
//
// Every minute, any fresh orange that is **4-directionally adjacent** to a rotten orange becomes rotten.
//
// Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return `-1`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2019/02/16/oranges.png
//
// ```
// Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
// Output: 4
// ```
//
// **Example 2:**
//
// ```
// Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
// Output: -1
// Explanation: The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.
// ```
//
// **Example 3:**
//
// ```
// Input: grid = [[0,2]]
// Output: 0
// Explanation: Since there are already no fresh oranges at minute 0, the answer is just 0.
// ```
//
// **Constraints:**
//
// - `m == grid.length`
// - `n == grid[i].length`
// - `1 <= m, n <= 10`
// - `grid[i][j]` is `0`, `1`, or `2`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// BFS (Double Buffer Vector)
//
// Use a vector for rotten oranges.
// For each minutes, rot all neighbor fresh oranges,
// and put them into another vector of next minute.
class Solution {
 public:
  int orangesRotting(vector<vector<int>>& grid) {
    const auto m = grid.size(), n = grid[0].size();

    // Prepare
    auto curr = vector<pair<int, int>>();
    auto next = vector<pair<int, int>>();
    curr.reserve(m * n);
    next.reserve(m * n);

    // Initialize
    int freshes = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == 2) {
          curr.emplace_back(i, j);
        } else if (grid[i][j] == 1) {
          ++freshes;
        }
      }
    }
    if (freshes == 0) return 0;

    // BFS
    pair<int, int> dirs[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int minute = 0;
    while (!curr.empty() && freshes > 0) {
      ++minute;
      for (auto [i, j] : curr) {
        for (auto [di, dj] : dirs) {
          const int i2 = i + di, j2 = j + dj;
          if (0 <= i2 && i2 < m && 0 <= j2 && j2 < n && grid[i2][j2] == 1) {
            --freshes;
            grid[i2][j2] = 2;
            next.emplace_back(i2, j2);
          }
        }
      }
      curr.clear();
      swap(curr, next);
    }

    return freshes > 0 ? -1 : minute;
  }
};
