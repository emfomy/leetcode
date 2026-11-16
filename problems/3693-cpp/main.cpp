// Source: https://leetcode.com/problems/climbing-stairs-ii
// Title: Climbing Stairs II
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are climbing a staircase with `n + 1` steps, numbered from 0 to `n`.
//
// You are also given a **1-indexed** integer array `costs` of length `n`, where `costs[i]` is the cost of step `i`.
//
// From step `i`, you can jump **only** to step `i + 1`, `i + 2`, or `i + 3`. The cost of jumping from step `i` to step `j` is defined as: `costs[j] + (j - i)^2`
//
// You start from step 0 with `cost = 0`.
//
// Return the **minimum** total cost to reach step `n`.
//
// **Example 1:**
//
// ```
// Input: n = 4, costs = [1,2,3,4]
// Output: 13
// Explanation:
// One optimal path is `0 → 1 → 2 → 4`
// | Jump  | Cost Calculation             | Cost |
// |-------|------------------------------|------|
// | 0 → 1 | costs[1] + (1 - 0)^2 = 1 + 1 | 2    |
// | 1 → 2 | costs[2] + (2 - 1)^2 = 2 + 1 | 3    |
// | 2 → 4 | costs[4] + (4 - 2)^2 = 4 + 4 | 8    |
// Thus, the minimum total cost is `2 + 3 + 8 = 13`
// ```
//
// **Example 2:**
//
// ```
// Input: n = 4, costs = [5,1,6,2]
// Output: 11
// Explanation:
// One optimal path is `0 → 2 → 4`
// | Jump  | Cost Calculation             | Cost |
// |-------|------------------------------|------|
// | 0 → 2 | costs[2] + (2 - 0)^2 = 1 + 4 | 5    |
// | 2 → 4 | costs[4] + (4 - 2)^2 = 4 + 4 | 6    |
// <table><tbody><tr><th>Jump</th><th>Cost Calculation</th><th>Cost</th></tr></tbody><tbody><tr><td>0 → 2</td><td>`costs[2] + (2 - 0)^2 = 1 + 4`</td><td>5</td></tr><tr><td>2 → 4</td><td>`costs[4] + (4 - 2)^2 = 2 + 4`</td><td>6</td></tr></tbody></table>
// Thus, the minimum total cost is `5 + 6 = 11`
// ```
//
// **Example 3:**
//
// ```
// Input: n = 3, costs = [9,8,3]
// Output: 12
// Explanation:
// The optimal path is `0 → 3` with total cost = `costs[3] + (3 - 0)^2 = 3 + 9 = 12`
// ```
//
// **Constraints:**
//
// - `1 <= n == costs.length <= 10^5`
// - `1 <= costs[i] <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <vector>

using namespace std;

// 1D-DP
class Solution {
 public:
  int climbStairs(int n, const vector<int>& costs) {
    auto dp = vector<int>(n + 1, INT_MAX);
    dp[0] = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j <= i + 3 && j <= n; ++j) {
        dp[j] = min(dp[j], dp[i] + costs[j - 1] + (j - i) * (j - i));
      }
    }

    return dp.back();
  }
};

// 1D-DP
class Solution2 {
 public:
  int climbStairs(int n, const vector<int>& costs) {
    auto dp = vector<int>(n + 1, INT_MAX);
    dp[0] = 0;
    for (int j = 1; j <= n; ++j) {
      for (int i = max(0, j - 3); i < j; ++i) {
        dp[j] = min(dp[j], dp[i] + costs[j - 1] + (j - i) * (j - i));
      }
    }

    return dp.back();
  }
};

// 1D-DP
class Solution3 {
 public:
  int climbStairs(int n, const vector<int>& costs) {
    auto dp = vector<int>(n + 1, INT_MAX);
    dp[0] = 0;
    for (int j = 1; j <= n; ++j) {
      for (int i = max(0, j - 3); i < j; ++i) {
        dp[j] = min(dp[j], dp[i] + costs[j - 1] + (j - i) * (j - i));
      }
    }

    return dp.back();
  }
};

// 0D-DP
class Solution4 {
 public:
  int climbStairs(int n, const vector<int>& costs) {
    // a=dp[j-3], b=dp[j-2], c=dp[j-1], d=dp[j]
    int a = 0, b = 0, c = 0;
    for (int j = 1; j <= n; ++j) {
      int d = min({a + 9, b + 4, c + 1}) + costs[j - 1];
      a = b;
      b = c;
      c = d;
    }

    return c;
  }
};
