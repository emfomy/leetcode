// Source: https://leetcode.com/problems/find-the-safest-path-in-a-grid
// Title: Find the Safest Path in a Grid
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a **0-indexed** 2D matrix `grid` of size `n x n`, where `(r, c)` represents:
//
// - A cell containing a thief if `grid[r][c] = 1`
// - An empty cell if `grid[r][c] = 0`
//
// You are initially positioned at cell `(0, 0)`. In one move, you can move to any adjacent cell in the grid, including cells containing thieves.
//
// The **safeness factor** of a path on the grid is defined as the **minimum** manhattan distance from any cell in the path to any thief in the grid.
//
// Return the **maximum safeness factor** of all paths leading to cell `(n - 1, n - 1)`.
//
// An **adjacent** cell of cell `(r, c)`, is one of the cells `(r, c + 1)`, `(r, c - 1)`, `(r + 1, c)` and `(r - 1, c)` if it exists.
//
// The **Manhattan distance** between two cells `(a, b)` and `(x, y)` is equal to `|a - x| + |b - y|`, where `|val|` denotes the absolute value of val.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2023/07/02/example1.png
//
// ```
// Input: grid = [[1,0,0],[0,0,0],[0,0,1]]
// Output: 0
// Explanation: All paths from (0, 0) to (n - 1, n - 1) go through the thieves in cells (0, 0) and (n - 1, n - 1).
// ```
//
// **Example 2:**
// https://assets.leetcode.com/uploads/2023/07/02/example2.png
//
// ```
// Input: grid = [[0,0,1],[0,0,0],[0,0,0]]
// Output: 2
// Explanation: The path depicted in the picture above has a safeness factor of 2 since:
// - The closest cell of the path to the thief at cell (0, 2) is cell (0, 0). The distance between them is | 0 - 0 | + | 0 - 2 | = 2.
// It can be shown that there are no other paths with a higher safeness factor.
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2023/07/02/example3.png
//
// ```
// Input: grid = [[0,0,0,1],[0,0,0,0],[0,0,0,0],[1,0,0,0]]
// Output: 2
// Explanation: The path depicted in the picture above has a safeness factor of 2 since:
// - The closest cell of the path to the thief at cell (0, 3) is cell (1, 2). The distance between them is | 0 - 1 | + | 3 - 2 | = 2.
// - The closest cell of the path to the thief at cell (3, 0) is cell (3, 2). The distance between them is | 3 - 3 | + | 0 - 2 | = 2.
// It can be shown that there are no other paths with a higher safeness factor.
// ```
//
// **Constraints:**
//
// - `1 <= grid.length == n <= 400`
// - `grid[i].length == n`
// - `grid[i][j]` is either `0` or `1`.
// - There is at least one thief in the `grid`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <queue>
#include <vector>

using namespace std;

// BFS
//
// First use BFS to find the safeness of each cell.
// Next use BFS to find the maximum path.
class Solution {
  using Bool = unsigned char;

  using Dir = pair<int, int>;          // x, y
  using State = tuple<int, int, int>;  // score, x, y

  using Heap = priority_queue<State, vector<State>, less<>>;  // max-heap

 public:
  int maximumSafenessFactor(const vector<vector<int>>& grid) {
    const int m = grid.size(), n = grid[0].size();

    // Helper
    auto dirs = vector<Dir>({{0, -1}, {0, 1}, {-1, 0}, {1, 0}});
    auto checkIdx = [m, n](int x, int y) -> bool {  //
      return 0 <= x && x < m && 0 <= y && y < n;
    };

    // BFS cell score
    auto scores = vector<vector<int>>(m, vector<int>(n, m + n));
    {
      auto seen = vector<vector<Bool>>(m, vector<Bool>(n));
      auto que = queue<State>();
      for (int x = 0; x < m; ++x) {
        for (int y = 0; y < n; ++y) {
          if (grid[x][y] == 1) {
            scores[x][y] = 0;
            seen[x][y] = true;
            que.push({0, x, y});
          }
        }
      }
      while (!que.empty()) {
        auto [score, x, y] = que.front();
        que.pop();
        ++score;

        for (auto [dx, dy] : dirs) {
          auto x2 = x + dx, y2 = y + dy;
          if (!checkIdx(x2, y2)) continue;
          if (seen[x2][y2]) continue;  // relax
          seen[x2][y2] = true;
          scores[x2][y2] = score;
          que.push({score, x2, y2});
        }
      }
    }

    // BFS Max Path
    {
      auto seen = vector<vector<Bool>>(m, vector<Bool>(n));
      auto heap = Heap();
      seen[0][0] = true;
      heap.push({scores[0][0], 0, 0});
      while (!heap.empty()) {
        auto [score, x, y] = heap.top();
        heap.pop();

        if (x == m - 1 && y == n - 1) return score;

        for (auto [dx, dy] : dirs) {
          auto x2 = x + dx, y2 = y + dy;
          if (!checkIdx(x2, y2)) continue;
          if (seen[x2][y2]) continue;  // relax
          seen[x2][y2] = true;
          heap.push({min(score, scores[x2][y2]), x2, y2});
        }
      }
    }

    return -1;  // unreachable
  }
};
