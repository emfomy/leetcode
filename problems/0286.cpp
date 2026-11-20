// Source: https://leetcode.com/problems/walls-and-gates
// Title: Walls and Gates
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an `m x n` grid `rooms`initialized with these three possible values.
//
// - `-1`A wall or an obstacle.
// - `0` A gate.
// - `INF` Infinity means an empty room. We use the value `2^31 - 1 = 2147483647` to represent `INF` as you may assume that the distance to a gate is less than `2147483647`.
//
// Fill each empty room with the distance to its nearest gate. If it is impossible to reach a gate, it should be filled with `INF`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/01/03/grid.jpg
//
// ```
// Input: rooms = [[2147483647,-1,0,2147483647],[2147483647,2147483647,2147483647,-1],[2147483647,-1,2147483647,-1],[0,-1,2147483647,2147483647]]
// Output: [[3,-1,0,1],[2,2,1,-1],[1,-1,2,-1],[0,-1,3,4]]
// ```
//
// **Example 2:**
//
// ```
// Input: rooms = [[-1]]
// Output: [[-1]]
// ```
//
// **Constraints:**
//
// - `m == rooms.length`
// - `n == rooms[i].length`
// - `1 <= m, n <= 250`
// - `rooms[i][j]` is `-1`, `0`, or `2^31 - 1`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <utility>
#include <vector>

using namespace std;

// BFS
class Solution {
  constexpr static int INF = 2147483647;

  using State = tuple<int, int, int>;  // col, row, dist

 public:
  void wallsAndGates(vector<vector<int>>& rooms) {
    int m = rooms.size(), n = rooms[0].size();
    auto visited = vector(m, vector<bool>(n));
    auto que = queue<State>();

    // Find gates
    for (auto i = 0; i < m; ++i) {
      for (auto j = 0; j < n; ++j) {
        if (rooms[i][j] == 0) que.emplace(i, j, 0);
        if (rooms[i][j] == -1) visited[i][j] = true;
      }
    }

    // BFS
    auto dirs = vector<pair<int, int>>({{0, -1}, {0, 1}, {-1, 0}, {1, 0}});
    while (!que.empty()) {
      auto [i, j, d] = que.front();
      que.pop();

      // Visited
      if (visited[i][j]) continue;
      visited[i][j] = true;
      rooms[i][j] = d;

      // Step
      ++d;
      for (auto [di, dj] : dirs) {
        auto i2 = i + di, j2 = j + dj;
        if (0 <= i2 && i2 < m && 0 <= j2 && j2 < n && !visited[i2][j2]) {
          rooms[i2][j2] = d;
          que.push({i2, j2, d});
        }
      }
    }
  }
};
