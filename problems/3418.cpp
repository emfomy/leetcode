// Source: https://leetcode.com/problems/maximum-amount-of-money-robot-can-earn
// Title: Maximum Amount of Money Robot Can Earn
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an `m x n` grid. A robot starts at the top-left corner of the grid `(0, 0)` and wants to reach the bottom-right corner `(m - 1, n - 1)`. The robot can move either right or down at any point in time.
//
// The grid contains a value `coins[i][j]` in each cell:
//
// - If `coins[i][j] >= 0`, the robot gains that many coins.
// - If `coins[i][j] < 0`, the robot encounters a robber, and the robber steals the **absolute** value of `coins[i][j]` coins.
//
// The robot has a special ability to **neutralize robbers** in at most **2 cells** on its path, preventing them from stealing coins in those cells.
//
// **Note:** The robot's total coins can be negative.
//
// Return the **maximum** profit the robot can gain on the route.
//
// **Example 1:**
//
// ```
// Input: coins = [[0,1,-1],[1,-2,3],[2,-3,4]]
// Output: 8
// Explanation:
// An optimal path for maximum coins is:
// - Start at `(0, 0)` with `0` coins (total coins = `0`).
// - Move to `(0, 1)`, gaining `1` coin (total coins = `0 + 1 = 1`).
// - Move to `(1, 1)`, where there's a robber stealing `2` coins. The robot uses one neutralization here, avoiding the robbery (total coins = `1`).
// - Move to `(1, 2)`, gaining `3` coins (total coins = `1 + 3 = 4`).
// - Move to `(2, 2)`, gaining `4` coins (total coins = `4 + 4 = 8`).
// ```
//
// **Example 2:**
//
// ```
// Input: coins = [[10,10,10],[10,10,10]]
// Output: 40
// Explanation:
// An optimal path for maximum coins is:
// - Start at `(0, 0)` with `10` coins (total coins = `10`).
// - Move to `(0, 1)`, gaining `10` coins (total coins = `10 + 10 = 20`).
// - Move to `(0, 2)`, gaining another `10` coins (total coins = `20 + 10 = 30`).
// - Move to `(1, 2)`, gaining the final `10` coins (total coins = `30 + 10 = 40`).
// ```
//
// **Constraints:**
//
// - `m == coins.length`
// - `n == coins[i].length`
// - `1 <= m, n <= 500`
// - `-1000 <= coins[i][j] <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <climits>
#include <utility>
#include <vector>

using namespace std;

// 3D-DP
//
// DP[i][j][t] be the maximum profit at grid[i][j] with neutralize t robbers.
// We initialize DP as -INF.
// For each (i, j, t), updates (i+1, j, t), (i, j+1, t), (i+1, j, t+1), (i, j+1, t+1)
class Solution {
  constexpr static int T = 2;  // max neutralize count

  constexpr static int NINF = INT_MIN / 2;  // negative infinity; smaller that min-profit 500*500*1000

 public:
  int maximumAmount(const vector<vector<int>>& coins) {
    const auto m = coins.size(), n = coins[0].size();

    auto dp = vector<vector<vector<int>>>(m, vector<vector<int>>(n, vector<int>(T + 1, NINF)));
    dp[0][0][0] = coins[0][0];
    for (int t = 1; t <= T; ++t) {
      dp[0][0][t] = 0;
    }

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        for (int t = 0; t <= T; ++t) {
          if (i + 1 < m) {
            dp[i + 1][j][t] = max(dp[i + 1][j][t], dp[i][j][t] + coins[i + 1][j]);
            if (t + 1 <= T) {
              dp[i + 1][j][t + 1] = max(dp[i + 1][j][t + 1], dp[i][j][t]);
            }
          }
          if (j + 1 < n) {
            dp[i][j + 1][t] = max(dp[i][j + 1][t], dp[i][j][t] + coins[i][j + 1]);
            if (t + 1 <= T) {
              dp[i][j + 1][t + 1] = max(dp[i][j + 1][t + 1], dp[i][j][t]);
            }
          }
        }
      }
    }

    return *max_element(dp[m - 1][n - 1].cbegin(), dp[m - 1][n - 1].cend());
  }
};

// 3D-DP
//
// Reverse indices.
class Solution2 {
  constexpr static int T = 2;  // max neutralize count

  constexpr static int NINF = INT_MIN / 2;  // negative infinity; smaller that min-profit 500*500*1000

 public:
  int maximumAmount(const vector<vector<int>>& coins) {
    const auto m = coins.size(), n = coins[0].size();

    auto dp = vector<vector<vector<int>>>(m + 1, vector<vector<int>>(n + 1, vector<int>(T + 2, NINF)));
    for (int t = 0; t <= T; ++t) {
      dp[m - 1][n][t] = 0;
      dp[m][n - 1][t] = 0;
    }

    for (int i = m - 1; i >= 0; --i) {
      for (int j = n - 1; j >= 0; --j) {
        for (int t = T; t >= 0; --t) {
          dp[i][j][t] = max({
              dp[i + 1][j][t] + coins[i][j],
              dp[i][j + 1][t] + coins[i][j],
              dp[i + 1][j][t + 1],
              dp[i][j + 1][t + 1],
          });
        }
      }
    }

    return *max_element(dp[0][0].cbegin(), dp[0][0].cend());
  }
};

// 2D-DP
class Solution3 {
  constexpr static int T = 2;  // max neutralize count

  constexpr static int NINF = INT_MIN / 2;  // negative infinity; smaller that min-profit 500*500*1000

 public:
  int maximumAmount(const vector<vector<int>>& coins) {
    const auto m = coins.size(), n = coins[0].size();

    auto prevDp = vector<vector<int>>(n + 1, vector<int>(T + 2, NINF));
    auto currDp = vector<vector<int>>(n + 1, vector<int>(T + 2, NINF));
    fill(currDp[n - 1].begin(), currDp[n - 1].end() - 1, 0);
    for (int i = m - 1; i >= 0; --i) {
      swap(currDp, prevDp);

      int fillVal = (i == m - 1) ? 0 : NINF;
      fill(currDp[n].begin(), currDp[n].end() - 1, fillVal);

      for (int j = n - 1; j >= 0; --j) {
        for (int t = T; t >= 0; --t) {
          currDp[j][t] = max({
              prevDp[j][t] + coins[i][j],
              currDp[j + 1][t] + coins[i][j],
              prevDp[j][t + 1],
              currDp[j + 1][t + 1],
          });
        }
      }
    }

    return *max_element(currDp[0].cbegin(), currDp[0].cend());
  }
};
