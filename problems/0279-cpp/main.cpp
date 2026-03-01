// Source: https://leetcode.com/problems/perfect-squares
// Title: Perfect Squares
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer `n`, return the least number of perfect square numbers that sum to `n`.
//
// A **perfect square** is an integer that is the square of an integer; in other words, it is the product of some integer with itself. For example, `1`, `4`, `9`, and `16` are perfect squares while `3` and `11` are not.
//
// **Example 1:**
//
// ```
// Input: n = 12
// Output: 3
// Explanation: 12 = 4 + 4 + 4.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 13
// Output: 2
// Explanation: 13 = 4 + 9.
// ```
//
// **Constraints:**
//
// - `1 <= n <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include <numeric>
#include <vector>

using namespace std;

// DP
//
// DP[i] be the result that sum to i.
// For each i, we try all perfect square to get next DP value.
//
// Note that we can initialize DP[i] = i since we can use all 1.
class Solution {
 public:
  int numSquares(const int n) {
    // Init DP[i] = i
    auto dp = vector<int>(n + 1);
    iota(dp.begin(), dp.end(), 0);

    // Loop
    for (int i = 0; i < n; ++i) {
      for (int x = 1; i + x * x <= n; ++x) {
        dp[i + x * x] = min(dp[i + x * x], dp[i] + 1);
      }
    }

    return dp[n];
  }
};

// DP
//
// Furthermore, we can record the maximum square we used in DP[i] to speed up processing.
class Solution2 {
 public:
  int numSquares(const int n) {
    // Init DP[i] = i
    auto dp = vector<int>(n + 1);
    auto maxX = vector<int>(n + 1, 2);  // maximum x seen
    iota(dp.begin(), dp.end(), 0);

    // Loop
    for (int i = 0; i < n; ++i) {
      for (int x = maxX[i]; i + x * x <= n; ++x) {
        int j = i + x * x;
        if (dp[j] > dp[i] + 1 || dp[j] == dp[i] + 1 && maxX[j] > x) {
          dp[j] = dp[i] + 1;
          maxX[j] = x;
        }
      }
    }

    return dp[n];
  }
};

// Math
//
// By Lagrange's four-square theorem, the result should be 1, 2, 3, 4.
// By Legendre's three-square theorem, the result is 4 iff. n = 4^a(8b+7) for a, b >= 0.
//
// We first apply three-square theorem to check if answer is 4.
// Note that if n is divided by 4^a, say m = n/4^a is also an integer.
// Since 4^a is a square, therefore the result of m is equal to n.
class Solution3 {
  bool isSquare(int x) {
    int sq = sqrt(x);
    return sq * sq == x;
  }

 public:
  int numSquares(int n) {
    // Check Legendre's three-square theorem, try if n = 4^a(8b+7)
    while (n % 4 == 0) n %= 4;
    if (n % 8 == 7) return 4;

    // Check is n is square
    if (isSquare(n)) return 1;

    // Check if result is 2
    for (int i = 1; i * i < n; ++i) {
      if (isSquare(n - i * i)) return 2;
    }

    return 3;
  }
};
