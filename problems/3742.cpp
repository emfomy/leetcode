// Source: https://leetcode.com/problems/maximum-path-score-in-a-grid
// Title: Maximum Path Score in a Grid
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an `m x n` grid where each cell contains one of the values 0, 1, or 2. You are also given an integer `k`.
//
// You start from the top-left corner `(0, 0)` and want to reach the bottom-right corner `(m - 1, n - 1)` by moving only **right** or **down**.
//
// Each cell contributes a specific score and incurs an associated cost, according to their cell values:
//
// - 0: adds 0 to your score and costs 0.
// - 1: adds 1 to your score and costs 1.
// - 2: adds 2 to your score and costs 1.
//
// Return the **maximum** score achievable without exceeding a total cost of `k`, or -1 if no valid path exists.
//
// **Note:** If you reach the last cell but the total cost exceeds `k`, the path is invalid.
//
// **Example 1:**
//
// ```
// Input: grid = [[0, 1],[2, 0]], k = 1
// Output: 2
// Explanation:
// The optimal path is:
// | Cell   | grid[i][j] | Score | Total Score | Cost | Total Cost |
// |--------|------------|-------|-------------|------|------------|
// | (0, 0) | 0          | 0     | 0           | 0    | 0          |
// | (1, 0) | 2          | 2     | 2           | 1    | 1          |
// | (1, 1) | 0          | 0     | 2           | 0    | 1          |
// Thus, the maximum possible score is 2.
// ```
//
// **Example 2:**
//
// ```
// Input: grid = [[0, 1],[1, 2]], k = 1
// Output: -1
// Explanation:
// There is no path that reaches cell `(1, 1)` without exceeding cost k. Thus, the answer is -1.
// ```
//
// **Constraints:**
//
// - `1 <= m, n <= 200`
// - `0 <= k <= 10^3`
// - `^grid[0][0] == 0`
// - `0 <= grid[i][j] <= 2`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// 3D-DP
//
// DP[i, j, t] is the max score to (i, j) with exact t cost.
class Solution {
 public:
  int maxPathScore(const vector<vector<int>>& grid, int k) {
    const int m = grid.size(), n = grid[0].size();

    // DP
    auto dp = vector<vector<vector<int>>>(m, vector<vector<int>>(n, vector<int>(k + 1, -1)));
    dp[0][0][0] = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        int cost = (grid[i][j] > 0);
        for (int t = cost; t <= k; ++t) {
          if (i > 0 && dp[i - 1][j][t - cost] > -1) {
            dp[i][j][t] = max(dp[i][j][t], dp[i - 1][j][t - cost] + grid[i][j]);
          }
          if (j > 0 && dp[i][j - 1][t - cost] > -1) {
            dp[i][j][t] = max(dp[i][j][t], dp[i][j - 1][t - cost] + grid[i][j]);
          }
        }
      }
    }

    // Answer
    return *max_element(dp.back().back().cbegin(), dp.back().back().cend());
  }
};

// 2D-DP
//
// DP[i, j, t] is the max score to (i, j) with exact t cost.
class Solution2 {
 public:
  int maxPathScore(const vector<vector<int>>& grid, int k) {
    const int m = grid.size(), n = grid[0].size();

    // DP
    auto prev = vector<vector<int>>(n, vector<int>(k + 1));
    auto curr = vector<vector<int>>(n, vector<int>(k + 1));
    for (int i = 0; i < m; ++i) {
      swap(curr, prev);
      for (auto& row : curr) fill(row.begin(), row.end(), -1);
      if (i == 0) curr[0][0] = 0;

      for (int j = 0; j < n; ++j) {
        int cost = (grid[i][j] > 0);
        for (int t = cost; t <= k; ++t) {
          if (i > 0 && prev[j][t - cost] > -1) {
            curr[j][t] = max(curr[j][t], prev[j][t - cost] + grid[i][j]);
          }
          if (j > 0 && curr[j - 1][t - cost] > -1) {
            curr[j][t] = max(curr[j][t], curr[j - 1][t - cost] + grid[i][j]);
          }
        }
      }
    }

    // Answer
    return *max_element(curr.back().cbegin(), curr.back().cend());
  }
};

// 2D-DP
//
// DP[i, j, t] is the max score to (i, j) with exact t cost.
//
// Note that the maximum path length is m+n-2,
// therefore we don't need to handle t greater then this value.
class Solution3 {
 public:
  int maxPathScore(const vector<vector<int>>& grid, int k) {
    const int m = grid.size(), n = grid[0].size();

    // Cap k
    k = min(k, m + n - 2);

    // DP
    auto prev = vector<vector<int>>(n, vector<int>(k + 1));
    auto curr = vector<vector<int>>(n, vector<int>(k + 1));
    for (int i = 0; i < m; ++i) {
      swap(curr, prev);
      for (auto& row : curr) fill(row.begin(), row.end(), -1);
      if (i == 0) curr[0][0] = 0;

      for (int j = 0; j < n; ++j) {
        int cost = (grid[i][j] > 0);
        for (int t = cost; t <= min(k, i + j); ++t) {  // cost at most i+j to reach (i, j)
          if (i > 0 && prev[j][t - cost] > -1) {
            curr[j][t] = max(curr[j][t], prev[j][t - cost] + grid[i][j]);
          }
          if (j > 0 && curr[j - 1][t - cost] > -1) {
            curr[j][t] = max(curr[j][t], curr[j - 1][t - cost] + grid[i][j]);
          }
        }
      }
    }

    // Answer
    return *max_element(curr.back().cbegin(), curr.back().cend());
  }
};
