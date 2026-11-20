// Source: https://leetcode.com/problems/number-of-zigzag-arrays-i
// Title: Number of ZigZag Arrays I
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given three integers `n`, `l`, and `r`.
//
// A **ZigZag** array of length `n` is defined as follows:
//
// - Each element lies in the range `[l, r]`.
// - No **two** adjacent elements are equal.
// - No **three** consecutive elements form a **strictly increasing** or **strictly decreasing** sequence.
//
// Return the total number of valid **ZigZag** arrays.
//
// Since the answer may be large, return it **modulo** `10^9 + 7`.
//
// A **sequence** is said to be **strictly increasing** if each element is strictly greater than its previous one (if exists).
//
// A **sequence** is said to be **strictly decreasing** if each element is strictly smaller than its previous one (if exists).
//
// **Example 1:**
//
// ```
// Input: n = 3, l = 4, r = 5
// Output: 2
// Explanation:
// There are only 2 valid ZigZag arrays of length `n = 3` using values in the range `[4, 5]`:
// - `[4, 5, 4]`
// - `[5, 4, 5]`
// ```
//
// **Example 2:**
//
// ```
// Input: n = 3, l = 1, r = 3
// Output: 10
// Explanation:
// There are 10 valid ZigZag arrays of length `n = 3` using values in the range `[1, 3]`:
// - `[1, 2, 1]`, `[1, 3, 1]`, `[1, 3, 2]`
// - `[2, 1, 2]`, `[2, 1, 3]`, `[2, 3, 1]`, `[2, 3, 2]`
// - `[3, 1, 2]`, `[3, 1, 3]`, `[3, 2, 3]`
// All arrays meet the ZigZag conditions.
// ```
//
// **Constraints:**
//
// - `3 <= n <= 2000`
// - `1 <= l < r <= 2000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

// 2D-DP, O(mn)
//
// We first shift [l, r] to [0, r-l]. Define m = r-l.
//
// D[i][j] / U[i][j] is the number of length-i subarray,
// which end with j, and the last element goes down / up.
//
// Since D and U are summetric, we have U[i][j] = D[i][m-j]
// D[0][j] = 1
// D[i][j] = sum U[i-1][k] for k > j
//         = sum D[i-1][m-k] for k > j
//         = sum D[i-1][k] for k < m-j
class Solution {
  constexpr static int modulo = 1e9 + 7;

 public:
  int zigZagArrays(const int n, const int l, const int r) {
    const int m = r - l;

    auto dp = vector<vector<int>>(n, vector<int>(m + 1));
    for (int j = 0; j <= m; ++j) {
      dp[0][j] = 1;
    }
    for (int i = 1; i < n; ++i) {
      int sum = 0;
      for (int j = m; j >= 0; --j) {
        dp[i][j] = sum;
        sum = (sum + dp[i - 1][m - j]) % modulo;
      }
    }

    // Total
    int total = 0;
    for (int item : dp.back()) {
      total = (total + item) % modulo;
    }
    return (2 * total) % modulo;
  }
};

// 1D-DP, O(mn)
class Solution2 {
  constexpr static int modulo = 1e9 + 7;

 public:
  int zigZagArrays(const int n, const int l, const int r) {
    const int m = r - l;

    auto prev = vector<int>(m + 1);
    auto curr = vector<int>(m + 1, 1);  // initialized with all 1
    for (int i = 1; i < n; ++i) {
      swap(curr, prev);

      int sum = 0;
      for (int j = m; j >= 0; --j) {
        curr[j] = sum;
        sum = (sum + prev[m - j]) % modulo;
      }
    }

    // Total
    int total = 0;
    for (int item : curr) {
      total = (total + item) % modulo;
    }
    return (2 * total) % modulo;
  }
};
