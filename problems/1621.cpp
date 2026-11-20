// Source: https://leetcode.com/problems/number-of-sets-of-k-non-overlapping-line-segments
// Title: Number of Sets of K Non-Overlapping Line Segments
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given `n` points on a 1-D plane, where the `i^th` point (from `0` to `n-1`) is at `x = i`, find the number of ways we can draw **exactly** `k` **non-overlapping** line segments such that each segment covers two or more points. The endpoints of each segment must have **integral coordinates**. The `k` line segments **do not** have to cover all `n` points, and they are **allowed** to share endpoints.
//
// Return the number of ways we can draw `k` non-overlapping line segments. Since this number can be huge, return it **modulo** `10^9 + 7`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2020/09/07/ex1.png
//
// ```
// Input: n = 4, k = 2
// Output: 5
// Explanation: The two line segments are shown in red and blue.
// The image above shows the 5 different ways {(0,2),(2,3)}, {(0,1),(1,3)}, {(0,1),(2,3)}, {(1,2),(2,3)}, {(0,1),(1,2)}.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 3, k = 1
// Output: 3
// Explanation: The 3 ways are {(0,1)}, {(0,2)}, {(1,2)}.
// ```
//
// **Example 3:**
//
// ```
// Input: n = 30, k = 7
// Output: 796297179
// Explanation: The total number of possible ways to draw 7 line segments is 3796297200. Taking this number modulo 10^9 + 7 gives us 796297179.
// ```
//
// **Constraints:**
//
// - `2 <= n <= 1000`
// - `1 <= k <= n-1`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <vector>
using namespace std;

// 2D-DP
//
// Let DP[i, j] be the number of ways to have i segments for first j points.
// For each step, we either
// 1. extend a segment,
// 2. create a new segment,
// 3. leave empty.
//
// In order to know whether we can extend a segment or not,
// we use two DP variable instead:
// DP0 means the end is not a segment,
// DP1 means the end is a segment.
//
// DP0[0, j] = 1
// DP1[0, j] = 0
// DP0[i, +] = 0
// DP1[i, +] = 0
//
// DP0[i, j] = DP0[i, j-1] + DP1[i, j-1]                   // leave empty
// DP1[i, j] = DP1[i, j-1] + DP1[i-1, j-1] + DP0[i-1, j-1] // extend or create new
class Solution {
  static constexpr int modulo = 1e9 + 7;

  inline int mod(int x) { return (x % modulo + modulo) % modulo; }

 public:
  int numberOfSets(int n, int k) {
    auto dp0 = vector(k + 1, vector<int>(n));
    auto dp1 = vector(k + 1, vector<int>(n));

    // Loop
    fill(dp0.front().begin(), dp0.front().end(), 1);
    for (int i = 1; i <= k; ++i) {
      for (int j = 1; j < n; ++j) {
        dp0[i][j] = mod(dp0[i][j - 1] + dp1[i][j - 1]);
        dp1[i][j] = mod(dp1[i][j - 1] + mod(dp1[i - 1][j - 1] + dp0[i - 1][j - 1]));
      }
    }

    return mod(dp0.back().back() + dp1.back().back());
  }
};

// 1D-DP
class Solution2 {
  static constexpr int modulo = 1e9 + 7;

  inline int mod(int x) { return (x % modulo + modulo) % modulo; }

 public:
  int numberOfSets(int n, int k) {
    auto curr0 = vector<int>(n);
    auto curr1 = vector<int>(n);
    auto prev0 = vector<int>(n);
    auto prev1 = vector<int>(n);

    // Loop
    fill(curr0.begin(), curr0.end(), 1);
    for (int i = 1; i <= k; ++i) {
      swap(curr0, prev0);
      swap(curr1, prev1);
      curr0[0] = 0;
      for (int j = 1; j < n; ++j) {
        curr0[j] = mod(curr0[j - 1] + curr1[j - 1]);
        curr1[j] = mod(curr1[j - 1] + mod(prev1[j - 1] + prev0[j - 1]));
      }
    }

    return mod(curr0.back() + curr1.back());
  }
};

// Math
//
// Let l[i] and r[i] be the left and right point of segment i.
// We have 0 <= l1 < r1 <= l2 < r2 <= ... <= lk < rk < n.
//
// Let's make above all non-equal be shifting the numbers right:
// L[i] = l[i] + (i-1), R[i] = r[i] + (i-1)
// Now we have 0 <= L1 < R1 < ... < Lk < Rk < n+k-1.
//
// Now the problem becomes selection 2k numbers in [0, n+k-1).
// The answer is comb(n+k-1, 2k).
class Solution3 {
  static constexpr int modulo = 1e9 + 7;
  static constexpr int N = 1000;

  static inline int C[2 * N][2 * N];
  static void init() {
    if (C[0][0] != 0) return;

    for (int i = 0; i < 2 * N; ++i) {
      C[i][0] = 1;
      for (int j = 1; j <= i; ++j) {
        C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % modulo;
      }
    }
  }

 public:
  int numberOfSets(int n, int k) {
    init();
    return C[n + k - 1][2 * k];
  }
};
