// Source: https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings
// Title: Minimum ASCII Delete Sum for Two Strings
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two strings `s1` and`s2`, return the lowest **ASCII** sum of deleted characters to make two strings equal.
//
// **Example 1:**
//
// ```
// Input: s1 = "sea", s2 = "eat"
// Output: 231
// Explanation: Deleting "s" from "sea" adds the ASCII value of "s" (115) to the sum.
// Deleting "t" from "eat" adds 116 to the sum.
// At the end, both strings are equal, and 115 + 116 = 231 is the minimum sum possible to achieve this.
// ```
//
// **Example 2:**
//
// ```
// Input: s1 = "delete", s2 = "leet"
// Output: 403
// Explanation: Deleting "dee" from "delete" to turn the string into "let",
// adds 100[d] + 101[e] + 101[e] to the sum.
// Deleting "e" from "leet" adds 101[e] to the sum.
// At the end, both strings are equal to "let", and the answer is 100+101+101+101 = 403.
// If instead we turned both strings into "lee" or "eet", we would get answers of 433 or 417, which are higher.
// ```
//
// **Constraints:**
//
// - `1 <= s1.length, s2.length <= 1000`
// - `s1` and `s2` consist of lowercase English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// 2D-DP
//
// It a sequence alignment problem.
// Let DP[i][j] be the minimum score where of substring s1[:i] and s2[:j].
// DP[i][j] =
//   DP[i-1][j-1]                 // if s1[i] = s2[j]
//   DP[i-1][j-1] + s1[i] + s2[j] // if s1[i] != s2[j]
//   DP[i-1][j]   + s1[i]         // skip s1[i]
//   DP[i][j-1]   + s2[j]         // skip s2[j]
class Solution {
 public:
  int minimumDeleteSum(string s1, string s2) {
    int m = s1.size(), n = s2.size();
    auto dp = vector(m + 1, vector(n + 1, 0));

    for (auto i = 0; i < m; ++i) {
      dp[i + 1][0] = dp[i][0] + s1[i];
    }
    for (auto j = 0; j < n; ++j) {
      dp[0][j + 1] = dp[0][j] + s2[j];
    }
    for (auto i = 0; i < m; ++i) {
      for (auto j = 0; j < n; ++j) {
        int c1 = s1[i], c2 = s2[j];
        if (c1 == c2) {
          dp[i + 1][j + 1] = dp[i][j];
        } else {
          dp[i + 1][j + 1] = min(dp[i][j + 1] + c1, dp[i + 1][j] + c2);
        }
      }
    }

    return dp[m][n];
  }
};

// 1D-DP
//
// It a sequence alignment problem.
// Let DP[i][j] be the minimum score where of substring s1[:i] and s2[:j].
// DP[i][j] =
//   DP[i-1][j-1]                 // if s1[i] = s2[j]
//   DP[i-1][j-1] + s1[i] + s2[j] // if s1[i] != s2[j]
//   DP[i-1][j]   + s1[i]         // skip s1[i]
//   DP[i][j-1]   + s2[j]         // skip s2[j]
class Solution2 {
 public:
  int minimumDeleteSum(string s1, string s2) {
    int m = s1.size(), n = s2.size();
    auto curr = vector(n + 1, 0);
    auto prev = vector(n + 1, 0);

    for (auto j = 0; j < n; ++j) {
      curr[j + 1] = curr[j] + s2[j];
    }
    for (auto i = 0; i < m; ++i) {
      swap(curr, prev);
      curr[0] = prev[0] + s1[i];
      for (auto j = 0; j < n; ++j) {
        int c1 = s1[i], c2 = s2[j];
        if (c1 == c2) {
          curr[j + 1] = prev[j];
        } else {
          curr[j + 1] = min(prev[j + 1] + c1, curr[j] + c2);
        }
      }
    }

    return curr[n];
  }
};
