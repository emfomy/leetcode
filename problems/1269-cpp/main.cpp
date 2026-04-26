// Source: https://leetcode.com/problems/number-of-ways-to-stay-in-the-same-place-after-some-steps
// Title: Number of Ways to Stay in the Same Place After Some Steps
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You have a pointer at index `0` in an array of size `arrLen`. At each step, you can move 1 position to the left, 1 position to the right in the array, or stay in the same place (The pointer should not be placed outside the array at any time).
//
// Given two integers `steps` and `arrLen`, return the number of ways such that your pointer is still at index `0` after **exactly** `steps` steps. Since the answer may be too large, return it **modulo** `10^9 + 7`.
//
// **Example 1:**
//
// ```
// Input: steps = 3, arrLen = 2
// Output: 4
// Explanation: There are 4 differents ways to stay at index 0 after 3 steps.
// Right, Left, Stay
// Stay, Right, Left
// Right, Stay, Left
// Stay, Stay, Stay
// ```
//
// **Example 2:**
//
// ```
// Input: steps = 2, arrLen = 4
// Output: 2
// Explanation: There are 2 differents ways to stay at index 0 after 2 steps
// Right, Left
// Stay, Stay
// ```
//
// **Example 3:**
//
// ```
// Input: steps = 4, arrLen = 2
// Output: 8
// ```
//
// **Constraints:**
//
// - `1 <= steps <= 500`
// - `1 <= arrLen <= 10^6`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <vector>

using namespace std;

// DP
//
// Store the ways of each position of each step.
// Let DP[i, j] be the number of ways to go to position i at step j.
// DP[1, 0] = 1,  DP[i, 0] = 0.
// DP[i, j] = DP[i-1, j-1] + DP[i, j-1] + DP[i+1, j-1]
class Solution {
  constexpr static int64_t modulo = 1e9 + 7;

  int64_t mod(int64_t x) {  //
    return x % modulo;
  }

 public:
  int numWays(int steps, int arrLen) {
    const int n = min(arrLen, steps + 1);  // we can't go beyond (steps+1)

    // Init
    auto prev = vector<int64_t>(n + 2);
    auto curr = vector<int64_t>(n + 2);
    curr[1] = 1;

    // Loop
    for (int step = 1; step <= steps; ++step) {
      swap(curr, prev);

      for (int i = 1; i <= n; ++i) {
        curr[i] = mod(prev[i - 1] + prev[i] + prev[i + 1]);
      }
    }

    return curr[1];
  }
};

// DP
//
// Say we go m steps.
// We focus on the number of ways in the halfway.
//
// DP[0, m] = sum_i DP[i, ceil(m/2)] DP[i, floor(m/2)]
// We go to halfway i in ceil(m/2) step, and go back in floor(m/2) step.
class Solution2 {
  constexpr static int64_t modulo = 1e9 + 7;

  int64_t mod(int64_t x) {  //
    return x % modulo;
  }

 public:
  int numWays(int steps, int arrLen) {
    const int n = min(arrLen, steps / 2 + 1);  // at most floor(m/2) steps far

    // Init
    auto prev = vector<int64_t>(n + 2);
    auto curr = vector<int64_t>(n + 2);
    curr[1] = 1;

    // Loop
    for (int step = 1; step <= (steps + 1) / 2; ++step) {  // ceil(m/2) steps
      swap(curr, prev);

      for (int i = 1; i <= n; ++i) {
        curr[i] = mod(prev[i - 1] + prev[i] + prev[i + 1]);
      }
    }

    // Sum
    int64_t ans = 0;
    if (steps % 2) {  // odd
      for (int i = 1; i <= n; ++i) {
        ans = mod(ans + curr[i] * prev[i]);
      }
    } else {  // even
      for (int i = 1; i <= n; ++i) {
        ans = mod(ans + curr[i] * curr[i]);
      }
    }

    return ans;
  }
};
