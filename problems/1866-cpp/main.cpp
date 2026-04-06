// Source: https://leetcode.com/problems/number-of-ways-to-rearrange-sticks-with-k-sticks-visible
// Title: Number of Ways to Rearrange Sticks With K Sticks Visible
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There are `n` uniquely-sized sticks whose lengths are integers from `1` to `n`. You want to arrange the sticks such that **exactly** `k`sticks are **visible** from the left. A stickis **visible** from the left if there are no **longer**sticks to the **left** of it.
//
// - For example, if the sticks are arranged `[1,3,2,5,4]`, then the sticks with lengths `1`, `3`, and `5` are visible from the left.
//
// Given `n` and `k`, return the **number** of such arrangements. Since the answer may be large, return it **modulo** `10^9 + 7`.
//
// **Example 1:**
//
// ```
// Input: n = 3, k = 2
// Output: 3
// Explanation: [1,3,2], [2,3,1], and [2,1,3] are the only arrangements such that exactly 2 sticks are visible.
// The visible sticks are underlined.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 5, k = 5
// Output: 1
// Explanation: [1,2,3,4,5] is the only arrangement such that all 5 sticks are visible.
// The visible sticks are underlined.
// ```
//
// **Example 3:**
//
// ```
// Input: n = 20, k = 11
// Output: 647427950
// Explanation: There are 647427950 (mod 10^9 + 7) ways to rearrange the sticks such that exactly 11 sticks are visible.
// ```
//
// **Constraints:**
//
// - `1 <= n <= 1000`
// - `1 <= k <= n`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <array>
#include <cstdint>
#include <vector>

using namespace std;

// 2D-DP, TLE
//
// Let R(n, k) be the number of arrangements.
// Define R(n, k) = 0 for k > n (impossible).
// R(n, 0) = 0 (impossible).
// R(0, 0) = 1 (empty).
//
// The tallest stick must be visible.
// All other visible sticks are at its left.
// The left sticks must have k-1 visible ones, and right sticks has no constraint.
// Say we put this stick at position i (0-indexed).
// There are C(n-1, i) ways to choose i sticks to be at lest,
// There are R(i, k-1) cases for left sticks and (n-i-1)! for right sticks.
// That is,
// R(n, k) = sum R(i, k-1) * (n-i-1)! * Binom(n-1, i) for i=0~(n-1).
class Solution {
  constexpr static int64_t modulo = 1e9 + 7;
  constexpr static int64_t mod(int64_t x) { return x % modulo; }

 public:
  int rearrangeSticks(int N, int K) {
    // Compute binomials
    auto binoms = vector<vector<int64_t>>(N + 1, vector<int64_t>(N + 1));
    for (int n = 0; n <= N; ++n) {
      binoms[n][0] = 1;
      for (int i = 1; i <= n; ++i) {
        binoms[n][i] = mod(binoms[n - 1][i - 1] + binoms[n - 1][i]);
      }
    }

    // Compute factorials
    auto facts = vector<int64_t>(N + 1);
    facts[0] = 1;
    for (int i = 1; i <= N; ++i) {
      facts[i] = mod(facts[i - 1] * i);
    }

    auto dp = vector<vector<int64_t>>(N + 1, vector<int64_t>(K + 1));
    dp[0][0] = 1;
    for (int n = 1; n <= N; ++n) {
      for (int k = 1; k <= min(n, K); ++k) {
        for (int i = k - 1; i < n; ++i) {
          dp[n][k] = mod(dp[n][k] + mod(dp[i][k - 1] * facts[n - i - 1]) * binoms[n - 1][i]);
        }
      }
    }

    return dp[N][K];
  }
};

// 2D-DP
//
// R(n, k) = sum R(i, k-1) * (n-i-1)! * Binom(n-1, i) for i=0~(n-1).
//
// Binom(n-1, i) = (n-1)! / i! (n-1-i)!
// (n-i-1)! * Binom(n-1, i) = (n-1)!/i!
//
// R(n, k) = sum R(i, k-1) * (n-1)!/i! for i = 0~(n-1)
//         = R(n-1, k-1) + sum R(i, k-1) * (n-1)!/i! for i = 0~(n-2)
//         = R(n-1, k-1) + (n-1) * [sum R(i, k-1) * (n-2)!/i! for i = 0~(n-2)]
//         = R(n-1, k-1) + (n-1) R(n-1, k)
class Solution2 {
  constexpr static int64_t modulo = 1e9 + 7;
  constexpr static int64_t mod(int64_t x) { return x % modulo; }

 public:
  int rearrangeSticks(int N, int K) {
    auto dp = vector<vector<int64_t>>(N + 1, vector<int64_t>(K + 1));
    dp[0][0] = 1;
    for (int n = 1; n <= N; ++n) {
      for (int k = 1; k <= min(n, K); ++k) {
        dp[n][k] = mod(dp[n - 1][k - 1] + (n - 1) * dp[n - 1][k]);
      }
    }

    return dp[N][K];
  }
};

// 1D-DP
class Solution3 {
  constexpr static int64_t modulo = 1e9 + 7;
  constexpr static int64_t mod(int64_t x) { return x % modulo; }

 public:
  int rearrangeSticks(int N, int K) {
    auto prevDp = vector<int64_t>(K + 1);
    auto currDp = vector<int64_t>(K + 1);
    currDp[0] = 1;
    for (int n = 1; n <= N; ++n) {
      swap(currDp, prevDp);
      currDp[0] = 0;
      for (int k = 1; k <= min(n, K); ++k) {
        currDp[k] = mod(prevDp[k - 1] + (n - 1) * prevDp[k]);
      }
    }

    return currDp[K];
  }
};

// 1D-DP
class Solution4 {
  constexpr static int64_t modulo = 1e9 + 7;
  constexpr static int64_t mod(int64_t x) { return x % modulo; }

 public:
  int rearrangeSticks(int N, int K) {
    auto dp = vector<int64_t>(K + 1);
    dp[0] = 1;
    for (int n = 1; n <= N; ++n) {
      for (int k = min(n, K); k >= 1; --k) {
        dp[k] = mod(dp[k - 1] + (n - 1) * dp[k]);
      }
      dp[0] = 0;
    }

    return dp[K];
  }
};

// Precompute 2D-DP
class Solution5 {
  constexpr static int M = 1000;  // maximum n

  constexpr static int64_t modulo = 1e9 + 7;
  constexpr static int64_t mod(int64_t x) { return x % modulo; }

  using Matrix = array<array<int64_t, M + 1>, M + 1>;
  inline const static Matrix dp = []() {
    Matrix dp = {};
    dp[0][0] = 1;
    for (int n = 1; n <= M; ++n) {
      for (int k = 1; k <= min(n, M); ++k) {
        dp[n][k] = mod(dp[n - 1][k - 1] + (n - 1) * dp[n - 1][k]);
      }
    }
    return dp;
  }();

 public:
  int rearrangeSticks(int n, int k) { return dp[n][k]; }
};
