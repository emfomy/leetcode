// Source: https://leetcode.com/problems/find-all-possible-stable-binary-arrays-i
// Title: Find All Possible Stable Binary Arrays I
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given 3 positive integers `zero`, `one`, and `limit`.
//
// A **binary array** `arr` is called **stable** if:
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
// The two possible stable binary arrays are `[1,0]` and `[0,1]`, as both arrays have a single 0 and a single 1, and no subarray has a length greater than 2.
// ```
//
// **Example 2:**

// ```
// Input: zero = 1, one = 2, limit = 1
// Output: 1
// Explanation:
// The only possible stable binary array is `[1,0,1]`.
// Note that the binary arrays `[1,1,0]` and `[0,1,1]` have subarrays of length 2 with identical elements, hence, they are not stable.
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
// - `1 <= zero, one, limit <= 200`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <utility>
#include <vector>

using namespace std;

// 3D-DP
//
// Say we want total #zero zeros and #one ones.
//
// Let DP0[k, c, r] be the number of arrays,
// where k is the array length, c is the number of zeros, r is the number of trailing zeros.
// Let DP1[k, c, r] be the number of arrays,
// where k is the array length, c is the number of ones, r is the number of trailing ones.
//
// For DP0, the ranges are:
// 1 <= k <= #one + #zero;
// 1 <= c <= k; k-#one <= c <= #zero; (k-#zero <= c <= #one for DP1).
// 1 <= r <= c; 1 <= r <= limit.
//
// DP0[1, 1, 1] = DP1[1, 1, 1] = 1.
// DP0[k, c, 1] = sum DP1[k-1, k-c, :]
// DP1[k, c, 1] = sum DP0[k-1, k-c, :]
// DP0[k, c, r>1] = DP0[k-1, c-1, r-1]
// DP1[k, c, r>1] = DP1[k-1, c-1, r-1]
class Solution {
  constexpr static uint32_t modulo = 1e9 + 7;

 public:
  int numberOfStableArrays(int zero, int one, int limit) {
    const int n = zero + one;

    // Init DP
    auto dp0 = vector(n + 1, vector(zero + 1, vector<uint32_t>(limit + 1)));
    auto dp1 = vector(n + 1, vector(one + 1, vector<uint32_t>(limit + 1)));
    dp0[1][1][1] = 1;
    dp1[1][1][1] = 1;

    // Loop
    for (int k = 2; k <= n; ++k) {
      for (int c = max(1, k - one); c <= min(k, zero); ++c) {
        for (int i = 1; i <= min(k - c, limit); ++i) {  // r = 1
          dp0[k][c][1] = (dp0[k][c][1] + dp1[k - 1][k - c][i]) % modulo;
        }
        for (int r = 2; r <= min(c, limit); ++r) {  // r > 1
          dp0[k][c][r] = dp0[k - 1][c - 1][r - 1];
        }
      }
      for (int c = max(1, k - zero); c <= min(k, one); ++c) {
        for (int i = 1; i <= min(k - c, limit); ++i) {  // r = 1
          dp1[k][c][1] = (dp1[k][c][1] + dp0[k - 1][k - c][i]) % modulo;
        }
        for (int r = 2; r <= min(c, limit); ++r) {  // r > 1
          dp1[k][c][r] = dp1[k - 1][c - 1][r - 1];
        }
      }
    }

    uint32_t ans = 0;
    for (int r = 1; r <= min(zero, limit); ++r) {
      ans = (ans + dp0[n][zero][r]) % modulo;
    }
    for (int r = 1; r <= min(one, limit); ++r) {
      ans = (ans + dp1[n][one][r]) % modulo;
    }
    return ans;
  }
};

// 2D-DP
//
// DP0[1, 1, 1] = DP1[1, 1, 1] = 1.
// DP0[k, c, 1] = sum DP1[k-1, k-c, :]
// DP1[k, c, 1] = sum DP0[k-1, k-c, :]
// DP0[k, c, r>1] = DP0[k-1, c-1, r-1]
// DP1[k, c, r>1] = DP1[k-1, c-1, r-1]
class Solution2 {
  constexpr static uint32_t modulo = 1e9 + 7;

 public:
  int numberOfStableArrays(int zero, int one, int limit) {
    const int n = zero + one;

    // Init DP
    auto prev0 = vector(zero + 1, vector<uint32_t>(limit + 1));
    auto prev1 = vector(one + 1, vector<uint32_t>(limit + 1));
    auto curr0 = vector(zero + 1, vector<uint32_t>(limit + 1));
    auto curr1 = vector(one + 1, vector<uint32_t>(limit + 1));
    curr0[1][1] = 1;
    curr1[1][1] = 1;

    // Loop
    for (int k = 2; k <= n; ++k) {
      swap(curr0, prev0);
      swap(curr1, prev1);

      for (int c = max(1, k - one); c <= min(k, zero); ++c) {
        curr0[c][1] = 0;
        for (int i = 1; i <= min(k - c, limit); ++i) {  // r = 1
          curr0[c][1] = (curr0[c][1] + prev1[k - c][i]) % modulo;
        }
        for (int r = 2; r <= min(c, limit); ++r) {  // r > 1
          curr0[c][r] = prev0[c - 1][r - 1];
        }
      }
      for (int c = max(1, k - zero); c <= min(k, one); ++c) {
        curr1[c][1] = 0;
        for (int i = 1; i <= min(k - c, limit); ++i) {  // r = 1
          curr1[c][1] = (curr1[c][1] + prev0[k - c][i]) % modulo;
        }
        for (int r = 2; r <= min(c, limit); ++r) {  // r > 1
          curr1[c][r] = prev1[c - 1][r - 1];
        }
      }
    }

    uint32_t ans = 0;
    for (int r = 1; r <= min(zero, limit); ++r) {
      ans = (ans + curr0[zero][r]) % modulo;
    }
    for (int r = 1; r <= min(one, limit); ++r) {
      ans = (ans + curr1[one][r]) % modulo;
    }
    return ans;
  }
};

// 2D-DP + Prefix Sum
//
// Define Pre0[k, c, r] = sum DP0[k, c, i] for i <= r.
// Define Pre1[k, c, r] = sum DP1[k, c, i] for i <= r.
//
// Pre0[:, :, 0] = Pre1[:, :, 0] = 0
// Pre0[1, 1, 1] = Pre1[1, 1, 1] = 1
// Pre0[k, c, 1] = Pre1[k-1, k-c, min(k-c, limit)]
// Pre1[k, c, 1] = Pre0[k-1, k-c, min(k-c, limit)]
// Pre0[k, c, r>1] = Pre0[k, c, r-1] + Pre0[k-1, c-1, r-1] - Pre0[k-1, c-1, r-2]
// Pre1[k, c, r>1] = Pre1[k, c, r-1] + Pre1[k-1, c-1, r-1] - Pre1[k-1, c-1, r-2]
class Solution3 {
  constexpr static int64_t modulo = 1e9 + 7;

  inline int64_t mod(int64_t x) {  //
    return ((x % modulo) + modulo) % modulo;
  }

 public:
  int numberOfStableArrays(int zero, int one, int limit) {
    const int n = zero + one;

    // Init DP
    auto prev0 = vector(zero + 1, vector<int64_t>(limit + 1));
    auto prev1 = vector(one + 1, vector<int64_t>(limit + 1));
    auto curr0 = vector(zero + 1, vector<int64_t>(limit + 1));
    auto curr1 = vector(one + 1, vector<int64_t>(limit + 1));
    curr0[0][0] = curr1[0][0] = 0;
    curr0[1][1] = curr1[1][1] = 1;

    // Loop
    for (int k = 2; k <= n; ++k) {
      swap(curr0, prev0);
      swap(curr1, prev1);

      for (int c = max(1, k - one); c <= min(k, zero); ++c) {
        curr0[c][1] = prev1[k - c][min(k - c, limit)];
        for (int r = 2; r <= min(c, limit); ++r) {  // r > 1
          curr0[c][r] = mod(curr0[c][r - 1] + prev0[c - 1][r - 1] - prev0[c - 1][r - 2]);
        }
      }

      for (int c = max(1, k - zero); c <= min(k, one); ++c) {
        curr1[c][1] = prev0[k - c][min(k - c, limit)];
        for (int r = 2; r <= min(c, limit); ++r) {  // r > 1
          curr1[c][r] = mod(curr1[c][r - 1] + prev1[c - 1][r - 1] - prev1[c - 1][r - 2]);
        }
      }
    }

    return mod(curr0[zero][min(zero, limit)] + curr1[one][min(one, limit)]);
  }
};

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
class Solution4 {
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
