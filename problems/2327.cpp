// Source: https://leetcode.com/problems/number-of-people-aware-of-a-secret
// Title: Number of People Aware of a Secret
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// On day `1`, one person discovers a secret.
//
// You are given an integer `delay`, which means that each person will **share** the secret with a new person **every day**, starting from `delay` days after discovering the secret. You are also given an integer `forget`, which means that each person will **forget** the secret `forget` days after discovering it. A person **cannot** share the secret on the same day they forgot it, or on any day afterwards.
//
// Given an integer `n`, return the number of people who know the secret at the end of day `n`. Since the answer may be very large, return it **modulo** `10^9 + 7`.
//
// **Example 1:**
//
// ```
// Input: n = 6, delay = 2, forget = 4
// Output: 5
// Explanation:
// Day 1: Suppose the first person is named A. (1 person)
// Day 2: A is the only person who knows the secret. (1 person)
// Day 3: A shares the secret with a new person, B. (2 people)
// Day 4: A shares the secret with a new person, C. (3 people)
// Day 5: A forgets the secret, and B shares the secret with a new person, D. (3 people)
// Day 6: B shares the secret with E, and C shares the secret with F. (5 people)
// ```
//
// **Example 2:**
//
// ```
// Input: n = 4, delay = 1, forget = 3
// Output: 6
// Explanation:
// Day 1: The first person is named A. (1 person)
// Day 2: A shares the secret with B. (2 people)
// Day 3: A and B share the secret with 2 new people, C and D. (4 people)
// Day 4: A forgets the secret. B, C, and D share the secret with 3 new people. (6 people)
// ```
//
// **Constraints:**
//
// - `2 <= n <= 1000`
// - `1 <= delay < forget <= n`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// Use 2-D DP
//
// DP[i,j] is the number of people who have known the secret for exactly j days, at day i.
// DP[i,j] = DP[i-1,j-1], j > 0
// DP[i,0] = Sum DP[i-1,j-1] for j in [delay, forget)
class Solution {
  constexpr static int modulo = 1e9 + 7;

 public:
  int peopleAwareOfSecret(int n, int delay, int forget) {
    auto dp = vector(n + 1, vector(forget, 0));
    dp[1][0] = 1;

    for (auto i = 2; i <= n; ++i) {
      for (auto j = 1; j < forget; ++j) {
        dp[i][j] = dp[i - 1][j - 1];
      }
      for (auto j = delay; j < forget; ++j) {
        dp[i][0] = (dp[i][0] + dp[i - 1][j - 1]) % modulo;
      }
    }

    auto ans = 0;
    for (auto j = 0; j < forget; ++j) {
      ans = (ans + dp[n][j]) % modulo;
    }
    return ans;
  }
};

// Use 1-D DP
//
// DP[i,j] is the number of people who have known the secret for exactly j days, at day i.
// DP[i,j] = DP[i-1,j-1], j > 0
// DP[i,0] = Sum DP[i-1,j-1] for j in [delay, forget)
class Solution2 {
  constexpr static int modulo = 1e9 + 7;

 public:
  int peopleAwareOfSecret(int n, int delay, int forget) {
    auto curr = vector(forget, 0);
    auto prev = vector(forget, 0);
    curr[0] = 1;

    for (auto i = 2; i <= n; ++i) {
      swap(curr, prev);
      for (auto j = 1; j < forget; ++j) {
        curr[j] = prev[j - 1];
      }
      curr[0] = 0;
      for (auto j = delay; j < forget; ++j) {
        curr[0] = (curr[0] + prev[j - 1]) % modulo;
      }
    }

    auto ans = 0;
    for (auto j = 0; j < forget; ++j) {
      ans = (ans + curr[j]) % modulo;
    }
    return ans;
  }
};

// Use 1-D DP
//
// Let DP2[i-j] = DP[i,j] to avoid update for j > 0
class Solution3 {
  constexpr static int modulo = 1e9 + 7;

 public:
  int peopleAwareOfSecret(int n, int delay, int forget) {
    auto dp = vector(forget, 0);
    dp[1] = 1;

    for (auto i = 2; i <= n; ++i) {
      auto newbie = 0;
      for (auto j = delay; j < forget; ++j) {
        newbie = (newbie + dp[(i - j + forget) % forget]) % modulo;
      }
      dp[i % forget] = newbie;
    }

    auto ans = 0;
    for (auto j = 0; j < forget; ++j) {
      ans = (ans + dp[j]) % modulo;
    }
    return ans;
  }
};

// Use 1-D DP
//
// Use as extra variable to track the number of people that will tell the secret.
// S[i] = S[i-1] + DP[i-1,delay-1] - DP[i-1,forget-1]
class Solution4 {
  constexpr static int modulo = 1e9 + 7;

 public:
  int peopleAwareOfSecret(int n, int delay, int forget) {
    auto curr = vector(forget, 0);
    auto prev = vector(forget, 0);
    curr[0] = 1;
    auto snitches = 0;

    for (auto i = 2; i <= n; ++i) {
      swap(curr, prev);
      for (auto j = 1; j < forget; ++j) {
        curr[j] = prev[j - 1];
      }
      snitches = (snitches + prev[delay - 1]) % modulo;
      snitches = (snitches - prev[forget - 1] + modulo) % modulo;
      curr[0] = snitches;
    }

    auto ans = 0;
    for (auto j = 0; j < forget; ++j) {
      ans = (ans + curr[j]) % modulo;
    }
    return ans;
  }
};

// Use 1-D DP
//
// Use DP2[i-j].
// Use extra variable.
class Solution5 {
  constexpr static int modulo = 1e9 + 7;

 public:
  int peopleAwareOfSecret(int n, int delay, int forget) {
    auto dp = vector(forget, 0);
    dp[1] = 1;
    auto snitches = 0;

    for (auto i = 2; i <= n; ++i) {
      snitches = (snitches + dp[(i - delay + forget) % forget]) % modulo;
      snitches = (snitches - dp[i % forget] + modulo) % modulo;
      dp[i % forget] = snitches;
    }

    auto ans = 0;
    for (auto j = 0; j < forget; ++j) {
      ans = (ans + dp[j]) % modulo;
    }
    return ans;
  }
};
