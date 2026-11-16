// Source: https://leetcode.com/problems/minimum-xor-path-in-a-grid
// Title: Minimum XOR Path in a Grid
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a 2D integer array `grid` of size `m * n`.
//
// You start at the **top-left** cell `(0, 0)` and want to reach the **bottom-right** cell `(m - 1, n - 1)`.
//
// At each step, you **may** move either **right or down**.
//
// The **cost** of a path is defined as the **bitwise XOR** of all the values in the cells along that path, **including** the start and end cells.
//
// Return the **minimum** possible XOR value among all valid paths from `(0, 0)` to `(m - 1, n - 1)`.
//
// **Example 1:**
//
// ```
// Input: grid = [[1,2],[3,4]]
// Output: 6
// Explanation:
// There are two valid paths:
// - `(0, 0) → (0, 1) → (1, 1)` with XOR: `1 XOR 2 XOR 4 = 7`
// - `(0, 0) → (1, 0) → (1, 1)` with XOR: `1 XOR 3 XOR 4 = 6`
// The minimum XOR value among all valid paths is 6.
// ```
//
// **Example 2:**
//
// ```
// Input: grid = [[6,7],[5,8]]
// Output: 9
// Explanation:
// There are two valid paths:
// - `(0, 0) → (0, 1) → (1, 1)` with XOR: `6 XOR 7 XOR 8 = 9`
// - `(0, 0) → (1, 0) → (1, 1)` with XOR: `6 XOR 5 XOR 8 = 11`
// The minimum XOR value among all valid paths is 9.
// ```
//
// **Example 3:**
//
// ```
// Input: grid = [[2,7,5]]
// Output: 0
// Explanation:
// There is only one valid path:
// - `(0, 0) → (0, 1) → (0, 2)` with XOR: `2 XOR 7 XOR 5 = 0`
// The XOR value of this path is 0, which is the minimum possible.
// ```
//
// **Constraints:**
//
// - `1 <= m == grid.length <= 1000`
// - `1 <= n == grid[i].length <= 1000`
// - `m * n <= 1000`
// - `0 <= grid[i][j] <= 1023`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

// 2D-DP
//
// Compute the possible XOR values for each cell.
// The possible values are 0~1023.
class Solution {
  static constexpr int V = 1024;
  using Values = array<bool, V>;

 public:
  int minCost(const vector<vector<int>>& grid) {
    const int m = grid.size(), n = grid[0].size();

    // DP
    auto dp = vector(m, vector<Values>(n));
    dp[0][0][grid[0][0]] = true;

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        // From top
        if (i > 0) {
          for (int v = 0; v < V; ++v) {
            if (dp[i - 1][j][v]) {
              dp[i][j][grid[i][j] ^ v] = true;
            }
          }
        }

        // From left
        if (j > 0) {
          for (int v = 0; v < V; ++v) {
            if (dp[i][j - 1][v]) {
              dp[i][j][grid[i][j] ^ v] = true;
            }
          }
        }
      }
    }

    // Answer
    const Values& last = dp.back().back();
    return find(last.cbegin(), last.cend(), true) - last.cbegin();
  }
};

// 1D-DP
class Solution2 {
  static constexpr int V = 1024;
  using Values = array<bool, V>;

 public:
  int minCost(const vector<vector<int>>& grid) {
    const int m = grid.size(), n = grid[0].size();

    // DP
    auto curr = vector<Values>(n);
    auto prev = vector<Values>(n);
    curr[0][0] = true;  // virtual row

    for (int i = 0; i < m; ++i) {
      swap(curr, prev);
      fill(curr.begin(), curr.end(), Values{});

      for (int j = 0; j < n; ++j) {
        // From top
        for (int v = 0; v < V; ++v) {
          if (prev[j][v]) {
            curr[j][grid[i][j] ^ v] = true;
          }
        }

        // From left
        if (j > 0) {
          for (int v = 0; v < V; ++v) {
            if (curr[j - 1][v]) {
              curr[j][grid[i][j] ^ v] = true;
            }
          }
        }
      }
    }

    // Answer
    const Values& last = curr.back();
    return find(last.cbegin(), last.cend(), true) - last.cbegin();
  }
};

// 1D-DP
class Solution3 {
  static constexpr int V = 1024;
  using Values = array<bool, V>;

 public:
  int minCost(const vector<vector<int>>& grid) {
    const int m = grid.size(), n = grid[0].size();

    // DP
    auto dp = vector<Values>(n);
    dp[0][0] = true;  // virtual row

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        Values tmp = {};

        // From top
        for (int v = 0; v < V; ++v) {
          if (dp[j][v]) {
            tmp[grid[i][j] ^ v] = true;
          }
        }

        // From left
        if (j > 0) {
          for (int v = 0; v < V; ++v) {
            if (dp[j - 1][v]) {
              tmp[grid[i][j] ^ v] = true;
            }
          }
        }

        dp[j] = tmp;
      }
    }

    // Answer
    const Values& last = dp.back();
    return find(last.cbegin(), last.cend(), true) - last.cbegin();
  }
};
