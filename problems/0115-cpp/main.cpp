// Source: https://leetcode.com/problems/distinct-subsequences
// Title: Distinct Subsequences
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two strings s and t, return **the number of distinct subsequences of s which equals t**.
//
// The test cases are generated so that the answer fits on a 32-bit signed integer.
//
// **Example 1:**
//
// ```
// Input: s = "rabbbit", t = "rabbit"
// Output: 3
// Explanation:
// As shown below, there are 3 ways you can generate "rabbit" from s.
// `**rabb**b**it**`
// `**ra**b**bbit**`
// `**rab**b**bit**`
// ```
//
// **Example 2:**
//
// ```
// Input: s = "babgbag", t = "bag"
// Output: 5
// Explanation:
// As shown below, there are 5 ways you can generate "bag" from s.
// `**ba**b**g**bag`
// `**ba**bgba**g**`
// `**b**abgb**ag**`
// `ba**b**gb**ag**`
// `babg**bag**````
//
// **Constraints:**
//
// - `1 <= s.length, t.length <= 1000`
// - `s` and `t` consist of English letters.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

using namespace std;

// 2D DP
//
// Say len(t) = m, len(s) = n.
// DP[i][j] is the number of subsequences of s[:j] which is equal to t[:i].
//
// DP[0][j]     = 1
// DP[i+1][j+1] = DP[i+1][j]            if s[j] != t[i] (skip s[j])
// DP[i+1][j+1] = DP[i+1][j] + DP[i][j] if s[j] != t[i] (extend using s[j])
//
// Note that although the answer fit in 32 bit integer,
// the intermediate state might not.
// However, since we don't care about these states,
// we use unsigned integer to avoid overflow errors.
class Solution {
 public:
  int numDistinct(const string& s, const string& t) {
    const int m = t.size(), n = s.size();
    if (m > n) return 0;  // edge case

    auto dp = vector(m + 1, vector<unsigned int>(n + 1));
    fill(dp[0].begin(), dp[0].end(), 1);
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        dp[i + 1][j + 1] = dp[i + 1][j] + dp[i][j] * (s[j] == t[i]);
      }
    }

    return dp.back().back();
  }
};

// 1D DP
class Solution2 {
 public:
  int numDistinct(const string& s, const string& t) {
    const int m = t.size(), n = s.size();

    auto curr = vector<unsigned int>(n + 1, 1);  // DP[0][:] = 1
    auto prev = vector<unsigned int>(n + 1);
    for (int i = 0; i < m; ++i) {
      swap(curr, prev);
      curr[0] = 0;
      for (int j = 0; j < n; ++j) {
        curr[j + 1] = curr[j] + prev[j] * (s[j] == t[i]);
      }
    }

    return curr.back();
  }
};

// 1D DP
//
// Note that we don't need to compute DP[i][j] j < i and for j-i > n-m.
// That is, we only care about the ranges j in [i, i+n-m].
// Let j = i+k, k in [0, n-m].
//
// DP[i+1][j+1] = DP[i+1][j]   + DP[i][j]
// DP[i+1][k]   = DP[i+1][k-1] + DP[i][k]
//
// Note that k-1 might be -1, we need to shift one in the program.
class Solution3 {
 public:
  int numDistinct(const string& s, const string& t) {
    const int m = t.size(), n = s.size();

    auto curr = vector<unsigned int>(n - m + 2, 1);  // DP[0][:] = 1
    auto prev = vector<unsigned int>(n - m + 2);
    for (int i = 0; i < m; ++i) {
      swap(curr, prev);
      curr[0] = 0;
      for (int k = 0; k <= n - m; ++k) {
        curr[k + 1] = curr[k] + prev[k + 1] * (s[i + k] == t[i]);
      }
    }

    return curr.back();
  }
};
