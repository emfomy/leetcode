// Source: https://leetcode.com/problems/pacific-atlantic-water-flow
// Title: Pacific Atlantic Water Flow
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There is an `m x n` rectangular island that borders both the **Pacific Ocean** and **Atlantic Ocean**. The **Pacific Ocean** touches the island's left and top edges, and the **Atlantic Ocean** touches the island's right and bottom edges.
//
// The island is partitioned into a grid of square cells. You are given an `m x n` integer matrix `heights` where `heights[r][c]` represents the **height above sea level** of the cell at coordinate `(r, c)`.
//
// The island receives a lot of rain, and the rain water can flow to neighboring cells directly north, south, east, and west if the neighboring cell's height is **less than or equal to** the current cell's height. Water can flow from any cell adjacent to an ocean into the ocean.
//
// Return a **2D list** of grid coordinates `result` where `result[i] = [r_i, c_i]` denotes that rain water can flow from cell `(r_i, c_i)` to **both** the Pacific and Atlantic oceans.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/06/08/waterflow-grid.jpg
//
// ```
// Input: heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
// Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
// Explanation: The following cells can flow to the Pacific and Atlantic oceans, as shown below:
// [0,4]: [0,4] -> Pacific Ocean
//       [0,4] -> Atlantic Ocean
// [1,3]: [1,3] -> [0,3] -> Pacific Ocean
//       [1,3] -> [1,4] -> Atlantic Ocean
// [1,4]: [1,4] -> [1,3] -> [0,3] -> Pacific Ocean
//       [1,4] -> Atlantic Ocean
// [2,2]: [2,2] -> [1,2] -> [0,2] -> Pacific Ocean
//       [2,2] -> [2,3] -> [2,4] -> Atlantic Ocean
// [3,0]: [3,0] -> Pacific Ocean
//       [3,0] -> [4,0] -> Atlantic Ocean
// [3,1]: [3,1] -> [3,0] -> Pacific Ocean
//       [3,1] -> [4,1] -> Atlantic Ocean
// [4,0]: [4,0] -> Pacific Ocean
//        [4,0] -> Atlantic Ocean
// Note that there are other possible paths for these cells to flow to the Pacific and Atlantic oceans.
// ```
//
// **Example 2:**
//
// ```
// Input: heights = [[1]]
// Output: [[0,0]]
// Explanation: The water can flow from the only cell to the Pacific and Atlantic oceans.
// ```
//
// **Constraints:**
//
// - `m == heights.length`
// - `n == heights[r].length`
// - `1 <= m, n <= 200`
// - `0 <= heights[r][c] <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <vector>

using namespace std;

// BFS
class Solution {
 public:
  vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
    int m = heights.size(), n = heights[0].size();

    auto pacific = vector(m, vector(n, false));
    auto atlantic = vector(m, vector(n, false));

    auto que = queue<pair<int, int>>();
    pair<int, int> dirs[4] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    auto valid = [=](int r, int c) -> bool { return 0 <= r && r < m && 0 <= c && c < n; };

    // Prepare pacific
    for (auto r = 0; r < m; ++r) que.push({r, 0});
    for (auto c = 0; c < n; ++c) que.push({0, c});

    // BFS pacific
    while (!que.empty()) {
      auto [r, c] = que.front();
      auto h = heights[r][c];
      que.pop();

      if (pacific[r][c]) continue;
      pacific[r][c] = true;

      for (auto [dx, dy] : dirs) {
        auto x2 = r + dx, y2 = c + dy;
        if (valid(x2, y2) && !pacific[x2][y2] && heights[x2][y2] >= h) {
          que.push({x2, y2});
        }
      }
    }

    // Prepare atlantic
    for (auto r = 0; r < m; ++r) que.push({r, n - 1});
    for (auto c = 0; c < n; ++c) que.push({m - 1, c});

    // BFS atlantic
    while (!que.empty()) {
      auto [r, c] = que.front();
      auto h = heights[r][c];
      que.pop();

      if (atlantic[r][c]) continue;
      atlantic[r][c] = true;

      for (auto [dx, dy] : dirs) {
        auto x2 = r + dx, y2 = c + dy;
        if (valid(x2, y2) && !atlantic[x2][y2] && heights[x2][y2] >= h) {
          que.push({x2, y2});
        }
      }
    }

    // Answer
    auto ans = vector<vector<int>>();
    for (auto r = 0; r < m; ++r) {
      for (auto c = 0; c < n; ++c) {
        if (pacific[r][c] && atlantic[r][c]) ans.push_back({r, c});
      }
    }

    return ans;
  }
};
