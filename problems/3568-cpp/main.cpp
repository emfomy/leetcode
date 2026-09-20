// Source: https://leetcode.com/problems/minimum-moves-to-clean-the-classroom
// Title: Minimum Moves to Clean the Classroom
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an `m x n` grid `classroom` where a student volunteer is tasked with cleaning up litter scattered around the room. Each cell in the grid is one of the following:
//
// - `'S'`: Starting position of the student
// - `'L'`: Litter that must be collected (once collected, the cell becomes empty)
// - `'R'`: Reset area that restores the student's energy to full capacity, regardless of their current energy level (can be used multiple times)
// - `'X'`: Obstacle the student cannot pass through
// - `'.'`: Empty space
//
// You are also given an integer `energy`, representing the student's maximum energy capacity. The student starts with this energy from the starting position `'S'`.
//
// Each move to an adjacent cell (up, down, left, or right) costs 1 unit of energy. If the energy reaches 0, the student can only continue if they are on a reset area `'R'`, which resets the energy to its **maximum** capacity `energy`.
//
// Return the **minimum** number of moves required to collect all litter items, or `-1` if it's impossible.
//
// **Example 1:**
//
// ```
// Input: classroom = ["S.", "XL"], energy = 2
// Output: 2
// Explanation:
// - The student starts at cell `(0, 0)` with 2 units of energy.
// - Since cell `(1, 0)` contains an obstacle 'X', the student cannot move directly downward.
// - A valid sequence of moves to collect all litter is as follows:
//   - Move 1: From `(0, 0)` → `(0, 1)` with 1 unit of energy and 1 unit remaining.
//   - Move 2: From `(0, 1)` → `(1, 1)` to collect the litter `'L'`.
// - The student collects all the litter using 2 moves. Thus, the output is 2.
// ```
//
// **Example 2:**
//
// ```
// Input: classroom = ["LS", "RL"], energy = 4
// Output: 3
// Explanation:
// - The student starts at cell `(0, 1)` with 4 units of energy.
// - A valid sequence of moves to collect all litter is as follows:
//   - Move 1: From `(0, 1)` → `(0, 0)` to collect the first litter `'L'` with 1 unit of energy used and 3 units remaining.
//   - Move 2: From `(0, 0)` → `(1, 0)` to `'R'` to reset and restore energy back to 4.
//   - Move 3: From `(1, 0)` → `(1, 1)` to collect the second litter `'L'`.
// - The student collects all the litter using 3 moves. Thus, the output is 3.
// ```
//
// **Example 3:**
//
// ```
// Input: classroom = ["L.S", "RXL"], energy = 3
// Output: -1
// Explanation:
// No valid path collects all `'L'`.
// ```
//
// **Constraints:**
//
// - `1 <= m == classroom.length <= 20`
// - `1 <= n == classroom[i].length <= 20`
// - `classroom[i][j]` is one of `'S'`, `'L'`, `'R'`, `'X'`, or `'.'`
// - `1 <= energy <= 50`
// - There is exactly **one** `'S'` in the grid.
// - There are **at most** 10 `'L'` cells in the grid.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <string>
#include <vector>

using namespace std;

// BFS
class Solution {
  using Bool = unsigned char;

  struct State {
    int x;
    int y;
    int cap;   // energy on student
    int mask;  // remaining litters.
    int step;  // moves of student
  };

 public:
  int minMoves(const vector<string>& classroom, int energy) {
    const int m = classroom.size();
    const int n = classroom[0].size();
    const pair<int, int> dirs[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    // Prepare litter bit mask
    auto id = vector(m, vector(n, 0));
    int sx, sy, cnt = 0;
    for (int x = 0; x < m; ++x) {
      for (int y = 0; y < n; ++y) {
        if (classroom[x][y] == 'S') {
          sx = x, sy = y;
        } else if (classroom[x][y] == 'L') {
          id[x][y] = 1 << (cnt++);
        }
      }
    }
    const int fullMask = (1 << cnt) - 1;

    // BFS
    auto bestCap = vector(m, vector(n, vector(fullMask + 1, -1)));
    auto que = queue<State>();
    bestCap[sx][sy][0] = energy;
    que.push({sx, sy, energy, 0, 0});
    while (!que.empty()) {
      auto [x, y, cap, mask, step] = que.front();
      que.pop();

      // Finished
      if (mask == fullMask) return step;

      // Out of energy
      if (cap == 0) continue;

      for (const auto [dx, dy] : dirs) {
        int nx = x + dx, ny = y + dy;
        if (nx < 0 || nx >= m || ny < 0 || ny >= n || classroom[nx][ny] == 'X') continue;

        int nCap = classroom[nx][ny] == 'R' ? energy : cap - 1;
        int nMask = mask | id[nx][ny];

        if (bestCap[nx][ny][nMask] < nCap) {
          bestCap[nx][ny][nMask] = nCap;
          que.push(State{nx, ny, nCap, nMask, step + 1});
        }
      }
    }

    return -1;
  }
};
