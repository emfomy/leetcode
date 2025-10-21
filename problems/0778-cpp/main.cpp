// Source: https://leetcode.com/problems/swim-in-rising-water
// Title: Swim in Rising Water
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an `n x n` integer matrix `grid` where each value `grid[i][j]` represents the elevation at that point `(i, j)`.
//
// It starts raining, and water gradually rises over time. At time `t`, the water level is `t`, meaning **any** cell with elevation less than equal to `t` is submerged or reachable.
//
// You can swim from a square to another 4-directionally adjacent square if and only if the elevation of both squares individually are at most `t`. You can swim infinite distances in zero time. Of course, you must stay within the boundaries of the grid during your swim.
//
// Return the minimum time until you can reach the bottom right square `(n - 1, n - 1)` if you start at the top left square `(0, 0)`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/06/29/swim1-grid.jpg
//
// ```
// Input: grid = [[0,2],[1,3]]
// Output: 3
// Explanation:
// At time 0, you are in grid location (0, 0).
// You cannot go anywhere else because 4-directionally adjacent neighbors have a higher elevation than t = 0.
// You cannot reach point (1, 1) until time 3.
// When the depth of water is 3, we can swim anywhere inside the grid.
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2021/06/29/swim2-grid-1.jpg
//
// ```
// Input: grid = [[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]
// Output: 16
// Explanation: The final route is shown.
// We need to wait until time 16 so that (0, 0) and (4, 4) are connected.
// ```
//
// **Constraints:**
//
// - `n == grid.length`
// - `n == grid[i].length`
// - `1 <= n <= 50`
// - `0 <= grid[i][j] <n^2`
// - Each value `grid[i][j]` is **unique**.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

// BFS + Heap
class Solution {
  static constexpr const int INF = 10000;

  using Cell = tuple<int, int, int>;  // time, x, y

 public:
  int swimInWater(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();

    // Helper
    auto valid = [=](int x, int y) -> bool { return 0 <= x && x < m && 0 <= y && y < n; };

    // Prepare
    auto reach = vector(m, vector(n, INF));                 // min-time to reach
    auto heap = priority_queue(greater(), vector<Cell>());  // min-heap
    heap.push({grid[0][0], 0, 0});

    // BFS
    pair<int, int> dirs[4] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    while (!heap.empty()) {
      auto [t, x, y] = heap.top();
      heap.pop();
      if (t >= reach[x][y]) continue;
      reach[x][y] = t;

      if (x == m - 1 && y == n - 1) continue;

      for (auto [dx, dy] : dirs) {
        auto x2 = x + dx, y2 = y + dy;
        if (!valid(x2, y2)) continue;
        auto t2 = max(t, grid[x2][y2]);
        if (t2 >= reach[x2][y2]) continue;
        heap.push({t2, x2, y2});
      }
    }

    return reach[m - 1][n - 1];
  }
};

// BFS + Heap
class Solution2 {
  using Cell = tuple<int, int, int>;  // time, x, y

 public:
  int swimInWater(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();

    // Helper
    auto valid = [=](int x, int y) -> bool { return 0 <= x && x < m && 0 <= y && y < n; };

    // Prepare
    auto seen = vector(m, vector(n, false));
    auto heap = priority_queue(greater(), vector<Cell>());  // min-heap
    heap.push({grid[0][0], 0, 0});
    seen[0][0] = true;

    // BFS
    pair<int, int> dirs[4] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    auto ans = 0;
    while (!heap.empty()) {
      auto [t, x, y] = heap.top();
      heap.pop();
      ans = max(ans, t);

      if (x == m - 1 && y == n - 1) break;

      for (auto [dx, dy] : dirs) {
        auto x2 = x + dx, y2 = y + dy;
        if (valid(x2, y2) && !seen[x2][y2]) {
          heap.push({grid[x2][y2], x2, y2});
          seen[x2][y2] = true;
        }
      }
    }

    return ans;
  }
};
