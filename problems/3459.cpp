// Source: https://leetcode.com/problems/length-of-longest-v-shaped-diagonal-segment
// Title: Length of Longest V-Shaped Diagonal Segment
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a 2D integer matrix `grid` of size `n x m`, where each element is either `0`, `1`, or `2`.
//
// A **V-shaped diagonal segment** is defined as:
//
// - The segment starts with `1`.
// - The subsequent elements follow this infinite sequence: `2, 0, 2, 0, ...`.
// - The segment:
//
// - Starts **along** a diagonal direction (top-left to bottom-right, bottom-right to top-left, top-right to bottom-left, or bottom-left to top-right).
// - Continues the** sequence** in the same diagonal direction.
// - Makes** at most one clockwise 90-degree** ** turn** to another diagonal direction while **maintaining** the sequence.
//
// https://assets.leetcode.com/uploads/2025/01/11/length_of_longest3.jpg
//
// Return the **length** of the **longest** **V-shaped diagonal segment** . If no valid segment exists, return 0.
//
// **Example 1:**
//
// ```
// Input: grid = [[2,2,1,2,2],[2,0,2,2,0],[2,0,1,1,0],[1,0,2,2,2],[2,0,0,2,2]]
// Output: 5
// Explanation:
// https://assets.leetcode.com/uploads/2024/12/09/matrix_1-2.jpg
// The longest V-shaped diagonal segment has a length of 5 and follows these coordinates: `(0,2) → (1,3) → (2,4)`, takes a **90-degree clockwise turn** at `(2,4)`, and continues as `(3,3) → (4,2)`.
// ```
//
// **Example 2:**
//
// ```
// Input: grid = [[2,2,2,2,2],[2,0,2,2,0],[2,0,1,1,0],[1,0,2,2,2],[2,0,0,2,2]]
// Output: 4
// Explanation:
// **https://assets.leetcode.com/uploads/2024/12/09/matrix_2.jpg
// The longest V-shaped diagonal segment has a length of 4 and follows these coordinates: `(2,3) → (3,2)`, takes a **90-degree clockwise turn** at `(3,2)`, and continues as `(2,1) → (1,0)`.
// ```
//
// **Example 3:**
//
// ```
// Input: grid = [[1,2,2,2,2],[2,2,2,2,0],[2,0,0,0,0],[0,0,2,2,2],[2,0,0,2,0]]
// Output: 5
// Explanation:
// **https://assets.leetcode.com/uploads/2024/12/09/matrix_3.jpg
// The longest V-shaped diagonal segment has a length of 5 and follows these coordinates: `(0,0) → (1,1) → (2,2) → (3,3) → (4,4)`.
// ```
//
// **Example 4:**
//
// ```
// Input: grid = [[1]]
// Output: 1
// Explanation:
// The longest V-shaped diagonal segment has a length of 1 and follows these coordinates: `(0,0)`.
// ```
//
// **Constraints:**
//
// - `n == grid.length`
// - `m == grid[i].length`
// - `1 <= n, m <= 500`
// - `grid[i][j]` is either `0`, `1` or `2`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <vector>

using namespace std;

// Use DFS + DP
class Solution {
 public:
  int lenOfVDiagonal(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    auto dirs = vector<pair<int, int>>({{1, 1}, {1, -1}, {-1, -1}, {-1, 1}});
    auto memo = vector<int>(m * n * 4 * 2, -1);

    function<int(int, int, int, bool, int)> dfs = [&](int i, int j, int dir, bool turned, int target) -> int {
      auto [di, dj] = dirs[dir];
      i += di;
      j += dj;
      auto memoKey = i * n * 4 * 2 + j * 4 * 2 + dir * 2 + turned;

      if (!(0 <= i && i < m && 0 <= j && j < n && grid[i][j] == target)) return 0;
      if (memo[memoKey] != -1) return memo[memoKey];

      int ret = dfs(i, j, dir, turned, 2 - target);
      if (!turned) {
        ret = max(ret, dfs(i, j, (dir + 1) % 4, true, 2 - target));
      }

      memo[memoKey] = ret + 1;
      return ret + 1;
    };

    auto ans = 0;
    for (auto i = 0; i < m; i++) {
      for (auto j = 0; j < n; j++) {
        if (grid[i][j] == 1) {
          for (auto dir = 0; dir < 4; dir++) {
            ans = max(ans, dfs(i, j, dir, false, 2) + 1);
          }
        }
      }
    }

    return ans;
  }
};
