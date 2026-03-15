// Source: https://leetcode.com/problems/find-all-possible-stable-binary-arrays-ii
// Title: Find All Possible Stable Binary Arrays II
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given 3 positive integers `zero`, `one`, and `limit`.
//
// A binary array `arr` is called **stable** if:
//
// - The number of occurrences of 0 in `arr` is **exactly **`zero`.
// - The number of occurrences of 1 in `arr` is **exactly** `one`.
// - Each subarray of `arr` with a size greater than `limit` must contain **both **0 and 1.
//
// Return the total number of **stable** binary arrays.
//
// Since the answer may be very large, return it **modulo** `10^9 + 7`.
//
// **Example 1:**
//
// ```
// Input: zero = 1, one = 1, limit = 2
// Output: 2
// Explanation:
// The two possible stable binary arrays are `[1,0]` and `[0,1]`.
// ```
//
// **Example 2:**
//
// ```
// Input: zero = 1, one = 2, limit = 1
// Output: 1
// Explanation:
// The only possible stable binary array is `[1,0,1]`.
// ```
//
// **Example 3:**
//
// ```
// Input: zero = 3, one = 3, limit = 2
// Output: 14
// Explanation:
// All the possible stable binary arrays are `[0,0,1,0,1,1]`, `[0,0,1,1,0,1]`, `[0,1,0,0,1,1]`, `[0,1,0,1,0,1]`, `[0,1,0,1,1,0]`, `[0,1,1,0,0,1]`, `[0,1,1,0,1,0]`, `[1,0,0,1,0,1]`, `[1,0,0,1,1,0]`, `[1,0,1,0,0,1]`, `[1,0,1,0,1,0]`, `[1,0,1,1,0,0]`, `[1,1,0,0,1,0]`, and `[1,1,0,1,0,0]`.
// ```
//
// **Constraints:**
//
// - `1 <= zero, one, limit <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <vector>

using namespace std;

// 2D-DP
//
// Let DP0[i][j] be the the number of arrays with i ones and j zeros, and end with 0.
// Let DP1[i][j] be the the number of arrays with i ones and j zeros, and end with 1.
//
// Therefore two ways to construct arrays for DP0[i][j].
// We may either append DP0[i-1][j] or DP1[i-1][j].
// However, to exclude all the results end with (limit+1) copies of 0.
// That is all arrays of DP1[i-limit-1][j] with trailing `0`*(limit+1).
// Note that we only need to exclude the results with exactly (limit+1) copies of 0.,
// since if the number is greater then limit, then it is already invalid in DP0[i-1][j].
//
// DP0[t][:] = DP1[:][t] = 0, t <= 0
// DP0[t][0] = DP1[0][t] = 1, 1 < t <= limit
// DP0[t][0] = DP1[0][t] = 0, limit < t
//
// DP0[i][j] = DP[i-1][j] + DP1[i-1][j] - DP1[i-limit-1][j]
// DP1[i][j] = DP[i][j-1] + DP1[i][j-1] - DP0[i][j-limit-1]
class Solution {
  constexpr static int64_t modulo = 1e9 + 7;

  inline int64_t mod(int64_t x) {  //
    return ((x % modulo) + modulo) % modulo;
  }

 public:
  int numberOfStableArrays(int zero, int one, int limit) {
    const int n = zero + one;

    auto dp0 = vector(zero + 1, vector<int64_t>(one + 1, 0));
    auto dp1 = vector(zero + 1, vector<int64_t>(one + 1, 0));
    for (int i = 1; i <= min(zero, limit); ++i) {
      dp0[i][0] = 1;
    }
    for (int j = 1; j <= min(one, limit); ++j) {
      dp1[0][j] = 1;
    }

    // Loop
    for (int i = 1; i <= zero; ++i) {
      for (int j = 1; j <= one; ++j) {
        dp0[i][j] = mod(dp0[i - 1][j] + dp1[i - 1][j]);
        if (i > limit) {
          dp0[i][j] = mod(dp0[i][j] - dp1[i - limit - 1][j]);
        }

        dp1[i][j] = mod(dp1[i][j - 1] + dp0[i][j - 1]);
        if (j > limit) {
          dp1[i][j] = mod(dp1[i][j] - dp0[i][j - limit - 1]);
        }
      }
    }

    return mod(dp0[zero][one] + dp1[zero][one]);
  }
};
