// Source: https://leetcode.com/problems/path-with-minimum-effort
// Title: Path With Minimum Effort
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are a hiker preparing for an upcoming hike. You are given `heights`, a 2D array of size `rows x columns`, where `heights[row][col]` represents the height of cell `(row, col)`. You are situated in the top-left cell, `(0, 0)`, and you hope to travel to the bottom-right cell, `(rows-1, columns-1)` (i.e.,**0-indexed**). You can move **up**, **down**, **left**, or **right**, and you wish to find a route that requires the minimum **effort**.
//
// A route's **effort** is the **maximum absolute difference** in heights between two consecutive cells of the route.
//
// Return the minimum **effort** required to travel from the top-left cell to the bottom-right cell.
//
// **Example 1:**
//
// https://assets.leetcode.com/uploads/2020/10/04/ex1.png
//
// ```
// Input: heights = [[1,2,2],[3,8,2],[5,3,5]]
// Output: 2
// Explanation: The route of [1,3,5,3,5] has a maximum absolute difference of 2 in consecutive cells.
// This is better than the route of [1,2,2,2,5], where the maximum absolute difference is 3.
// ```
//
// **Example 2:**
//
// https://assets.leetcode.com/uploads/2020/10/04/ex2.png
//
// ```
// Input: heights = [[1,2,3],[3,8,4],[5,3,5]]
// Output: 1
// Explanation: The route of [1,2,3,4,5] has a maximum absolute difference of 1 in consecutive cells, which is better than route [1,3,5,3,5].
// ```
//
// **Example 3:**
// https://assets.leetcode.com/uploads/2020/10/04/ex3.png
//
// ```
// Input: heights = [[1,2,1,1,1],[1,2,1,2,1],[1,2,1,2,1],[1,2,1,2,1],[1,1,1,2,1]]
// Output: 0
// Explanation: This route does not require any effort.
// ```
//
// **Constraints:**
//
// - `rows == heights.length`
// - `columns == heights[i].length`
// - `1 <= rows, columns <= 100`
// - `1 <= heights[i][j] <= 10^6`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <functional>
#include <queue>
#include <vector>

using namespace std;

// Dijkstra
class Solution {
  constexpr static pair<int, int> dirs[] = {
      {1, 0},
      {-1, 0},
      {0, 1},
      {0, -1},
  };

  using State = tuple<int, int, int>;  // cost, row, col

  using Heap = priority_queue<State, vector<State>, greater<>>;  // min-heap

 public:
  int minimumEffortPath(const vector<vector<int>>& heights) {
    const int m = heights.size(), n = heights[0].size();

    // Helper
    const auto valid = [m, n](int r, int c) -> bool {
      return 0 <= r && r < m && 0 <= c && c < n;  //
    };

    // Prepare
    auto costs = vector<vector<int>>(m, vector<int>(n, INT_MAX));
    Heap heap;
    costs[0][0] = 0;
    heap.push(State{0, 0, 0});

    // Loop
    while (!heap.empty()) {
      auto [cost, r, c] = heap.top();
      heap.pop();

      // Early Stop
      if (r == m - 1 && c == n - 1) return cost;

      // Relax
      if (costs[r][c] < cost) continue;

      // Traversal
      for (const auto [dr, dc] : dirs) {
        int nextR = r + dr, nextC = c + dc;
        if (!valid(nextR, nextC)) continue;

        int nextCost = max(cost, abs(heights[nextR][nextC] - heights[r][c]));
        if (costs[nextR][nextC] <= nextCost) continue;  // Relax
        costs[nextR][nextC] = nextCost;
        heap.push(State{nextCost, nextR, nextC});
      }
    }

    return -1;  // unreachable
  }
};
