// Source: https://leetcode.com/problems/trapping-rain-water-ii
// Title: Trapping Rain Water II
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an `m x n` integer matrix `heightMap` representing the height of each unit cell in a 2D elevation map, return the volume of water it can trap after raining.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/04/08/trap1-3d.jpg
//
// ```
// Input: heightMap = [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]
// Output: 4
// Explanation: After the rain, water is trapped between the blocks.
// We have two small ponds 1 and 3 units trapped.
// The total volume of water trapped is 4.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/04/08/trap2-3d.jpg
//
// ```
// Input: heightMap = [[3,3,3,3,3],[3,2,2,2,3],[3,2,1,2,3],[3,2,2,2,3],[3,3,3,3,3]]
// Output: 10
// ```
//
// **Constraints:**
//
// - `m == heightMap.length`
// - `n == heightMap[i].length`
// - `1 <= m, n <= 200`
// - `0 <= heightMap[i][j] <= 2 * 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <queue>
#include <vector>

using namespace std;

// BFS + Queue
//
// First full the whole grid with infinity water.
//
// Use a queue for the cells to be updated.
// We first set all border cells to the ground height and put them into the queue (since they will flow out).
// For each updating cell, reduce its height to the lowest neighbor.
// Next put all higher neighbor into the queue.
class Solution {
  using Cell = pair<int, int>;

 public:
  int trapRainWater(vector<vector<int>>& heightMap) {  //
    const int INF = 1e5;
    int m = heightMap.size(), n = heightMap[0].size();

    auto waterMap = vector(m + 2, vector(n + 2, INF));
    auto getHeight = [&](int i, int j) -> int { return heightMap[i - 1][j - 1]; };

    // Set border to zero
    for (auto i = 0; i < m + 2; ++i) {
      waterMap[i][0] = 0;
      waterMap[i][n + 1] = 0;
    }
    for (auto j = 1; j <= n; ++j) {
      waterMap[0][j] = 0;
      waterMap[m + 1][j] = 0;
    }

    // Prepare queue
    auto que = queue<Cell>();
    for (auto i = 1; i <= m; ++i) {
      que.push({i, 1});
      que.push({i, n});
    }
    for (auto j = 2; j <= n - 1; ++j) {
      que.push({1, j});
      que.push({m, j});
    }

    // BFS
    pair<int, int> dirs[4] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    while (!que.empty()) {
      auto [x, y] = que.front();
      auto w = waterMap[x][y];
      auto h = getHeight(x, y);
      que.pop();

      // Find minimal neighbor
      auto minW = INF;
      for (auto [dx, dy] : dirs) {
        auto x2 = x + dx, y2 = y + dy;
        minW = min(minW, waterMap[x2][y2]);
      }
      if (minW >= w) continue;

      // Update
      waterMap[x][y] = w = max(minW, h);
      for (auto [dx, dy] : dirs) {
        auto x2 = x + dx, y2 = y + dy;
        if (waterMap[x2][y2] > w) que.push({x2, y2});
      }
    }

    // Answer
    auto ans = 0;
    for (auto i = 1; i <= m; ++i) {
      for (auto j = 1; j <= n; ++j) {
        ans += waterMap[i][j] - getHeight(i, j);
      }
    }

    return ans;
  }
};
