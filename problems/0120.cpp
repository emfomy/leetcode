// Source: https://leetcode.com/problems/triangle
// Title: Triangle
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a `triangle` array, return the minimum path sum from top to bottom.
//
// For each step, you may move to an adjacent number of the row below. More formally, if you are on index `i` on the current row, you may move to either index `i` or index `i + 1` on the next row.
//
// **Example 1:**
//
// ```
// Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
// Output: 11
// Explanation: The triangle looks like:
//    2
//   3 4
//  6 5 7
// 4 1 8 3
// The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11 (underlined above).
// ```
//
// **Example 2:**
//
// ```
// Input: triangle = [[-10]]
// Output: -10
// ```
//
// **Constraints:**
//
// - `1 <= triangle.length <= 200`
// - `triangle[0].length == 1`
// - `triangle[i].length == triangle[i - 1].length + 1`
// - `-10^4 <= triangle[i][j] <= 10^4`
//
// **Follow up:** Could you do this using only `O(n)` extra space, where `n` is the total number of rows in the triangle?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

using namespace std;

// Use 2D-DP
// DP[i, j] = min(DP[i-1, j-1], DP[i-1, j]) + Val[i, j]
class Solution {
 public:
  int minimumTotal(vector<vector<int>>& triangle) {
    int n = triangle.size();
    auto dp = vector(n, vector(n, 0));

    dp[0][0] = triangle[0][0];
    for (auto i = 1; i < n; ++i) {
      dp[i][0] = dp[i - 1][0] + triangle[i][0];
      for (auto j = 1; j < i; ++j) {
        dp[i][j] = min(dp[i - 1][j - 1], dp[i - 1][j]) + triangle[i][j];
      }
      dp[i][i] = dp[i - 1][i - 1] + triangle[i][i];
    }

    return *min_element(dp[n - 1].cbegin(), dp[n - 1].cend());
  }
};

// Use 1D-DP (Top-Down)
// DP[i, j] = min(DP[i-1, j-1], DP[i-1, j]) + Val[i, j]
class Solution2 {
 public:
  int minimumTotal(vector<vector<int>>& triangle) {
    const int INF = 1e8;

    int n = triangle.size();

    auto curr = vector(n + 1, INF);
    auto prev = vector(n + 1, INF);
    curr[1] = triangle[0][0];
    for (auto i = 1; i < n; ++i) {
      swap(curr, prev);
      for (auto j = 0; j <= i; ++j) {
        curr[j + 1] = min(prev[j], prev[j + 1]) + triangle[i][j];
      }
    }

    return *min_element(curr.cbegin(), curr.cend());
  }
};

// Use 1D-DP (Bottom-Up)
// DP[i, j] = min(DP[i+1, j], DP[i+1, j+1]) + Val[i, j]
class Solution3 {
 public:
  int minimumTotal(vector<vector<int>>& triangle) {
    int n = triangle.size();

    auto curr = vector(n + 1, 0);
    auto prev = vector(n + 1, 0);
    for (auto i = n - 1; i >= 0; --i) {
      swap(curr, prev);
      for (auto j = 0; j <= i; ++j) {
        curr[j] = min(prev[j], prev[j + 1]) + triangle[i][j];
      }
    }

    return curr[0];
  }
};
