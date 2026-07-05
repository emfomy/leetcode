// Source: https://leetcode.com/problems/find-a-safe-walk-through-a-grid
// Title: Find a Safe Walk Through a Grid
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an `m x n` binary matrix `grid` and an integer `health`.
//
// You start on the upper-left corner `(0, 0)` and would like to get to the lower-right corner `(m - 1, n - 1)`.
//
// You can move up, down, left, or right from one cell to another adjacent cell as long as your health remains **positive**.
//
// Cells `(i, j)` with `grid[i][j] = 1` are considered **unsafe** and reduce your health by 1.
//
// Return `true` if you can reach the final cell with a health value of 1 or more, and `false` otherwise.
//
// **Example 1:**
//
// ```
// Input: grid = [[0,1,0,0,0],[0,1,0,1,0],[0,0,0,1,0]], health = 1
// Output: true
// Explanation:
// The final cell can be reached safely by walking along the gray cells below.
// https://assets.leetcode.com/uploads/2024/08/04/3868_examples_1drawio.png
// ```
//
// **Example 2:**
//
// ```
// Input: grid = [[0,1,1,0,0,0],[1,0,1,0,0,0],[0,1,1,1,0,1],[0,0,1,0,1,0]], health = 3
// Output: false
// Explanation:
// A minimum of 4 health points is needed to reach the final cell safely.
// https://assets.leetcode.com/uploads/2024/08/04/3868_examples_2drawio.png
// ```
//
// **Example 3:**
//
// ```
// Input: grid = [[1,1,1],[1,0,1],[1,1,1]], health = 5
// Output: true
// Explanation:
// The final cell can be reached safely by walking along the gray cells below.
// https://assets.leetcode.com/uploads/2024/08/04/3868_examples_3drawio.png
// Any path that does not go through the cell `(1, 1)` is unsafe since your health will drop to 0 when reaching the final cell.
// ```
//
// **Constraints:**
//
// - `m == grid.length`
// - `n == grid[i].length`
// - `1 <= m, n <= 50`
// - `2 <= m * n`
// - `1 <= health <= m + n`
// - `grid[i][j]` is either 0 or 1.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <queue>
#include <vector>

using namespace std;

// BFS (Dijkstra)
class Solution {
  using Bool = unsigned char;

  using Dir = pair<int, int>;          // x, y
  using State = tuple<int, int, int>;  // cost, x, y

  using Heap = priority_queue<State, vector<State>, greater<>>;  // min-heap

 public:
  bool findSafeWalk(const vector<vector<int>>& grid, int health) {
    const int m = grid.size(), n = grid[0].size();

    // Helper
    auto dirs = vector<Dir>({{0, -1}, {0, 1}, {-1, 0}, {1, 0}});
    auto checkIdx = [m, n](int x, int y) -> bool {  //
      return 0 <= x && x < m && 0 <= y && y < n;
    };

    // BFS
    auto costs = vector<vector<int>>(m, vector<int>(n, INT_MAX));
    Heap heap;
    costs[0][0] = grid[0][0];
    heap.push(State{grid[0][0], 0, 0});

    while (!heap.empty()) {
      auto [cost, x, y] = heap.top();
      heap.pop();

      // Early stop
      if (x == m - 1 && y == n - 1) return true;

      // Relax
      if (costs[x][y] < cost) continue;

      for (auto [dx, dy] : dirs) {
        auto x2 = x + dx, y2 = y + dy;
        if (!checkIdx(x2, y2)) continue;
        int nextCost = cost + grid[x2][y2];
        if (nextCost >= health) continue;         // No more health
        if (costs[x2][y2] <= nextCost) continue;  // Relax
        costs[x2][y2] = nextCost;
        heap.push(State{nextCost, x2, y2});
      }
    }

    return false;
  }
};

// 0-1 BFS
class Solution2 {
  using Dir = pair<int, int>;          // x, y
  using State = tuple<int, int, int>;  // cost, x, y

  using Queue = deque<State>;

 public:
  bool findSafeWalk(const vector<vector<int>>& grid, int health) {
    const int m = grid.size(), n = grid[0].size();

    // Helper
    auto dirs = vector<Dir>({{0, -1}, {0, 1}, {-1, 0}, {1, 0}});
    auto checkIdx = [m, n](int x, int y) -> bool {  //
      return 0 <= x && x < m && 0 <= y && y < n;
    };

    // BFS
    auto costs = vector<vector<int>>(m, vector<int>(n, INT_MAX));
    Queue que;
    costs[0][0] = grid[0][0];
    que.push_back(State{grid[0][0], 0, 0});

    while (!que.empty()) {
      auto [cost, x, y] = que.front();
      que.pop_front();

      // Early stop
      if (x == m - 1 && y == n - 1) return true;

      for (auto [dx, dy] : dirs) {
        auto x2 = x + dx, y2 = y + dy;
        if (!checkIdx(x2, y2)) continue;
        int nextCost = cost + grid[x2][y2];
        if (nextCost >= health) continue;         // No more health
        if (costs[x2][y2] <= nextCost) continue;  // Relax
        costs[x2][y2] = nextCost;
        if (grid[x2][y2]) {
          que.push_back(State{nextCost, x2, y2});
        } else {
          que.push_front(State{nextCost, x2, y2});
        }
      }
    }

    return costs.back().back() < health;
  }
};
