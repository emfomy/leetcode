// Source: https://leetcode.com/problems/sqrtx
// Title: Sqrt(x)
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a non-negative integer `x`, return the square root of `x` rounded down to the nearest integer. The returned integer should be **non-negative** as well.
//
// You **must not use** any built-in exponent function or operator.
//
// - For example, do not use `pow(x, 0.5)` in c++ or `x ** 0.5` in python.
//
// **Example 1:**
//
// ```
// Input: x = 4
// Output: 2
// Explanation: The square root of 4 is 2, so we return 2.
// ```
//
// **Example 2:**
//
// ```
// Input: x = 8
// Output: 2
// Explanation: The square root of 8 is 2.82842..., and since we round it down to the nearest integer, 2 is returned.
// ```
//
// **Constraints:**
//
// - `0 <= x <= 2^31 - 1`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <cstdlib>

using namespace std;

// Binary Search
class Solution {
 public:
  int mySqrt(int x) {
    int64_t lo = 0, hi = 2 << 16;  // [lo, hi) unknown
    while (lo < hi) {
      auto mid = lo + (hi - lo) / 2;
      if (mid * mid <= x) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }
    // (lo-1) <= sqrt(x), lo=hi > sqrt(x)

    return lo - 1;
  }
};

// Newton's method
//
// f(y) = y^2 -x = 0
// f'(y) = 2y
//
// y <- y - f(y)/f'(y)
//    = y - (y^2-x)/2y
//    = (y + x / y) / 2
class Solution2 {
 public:
  int mySqrt(int x) {
    if (x == 0) return 0;

    double x0 = x, x1 = x;
    do {
      x0 = x1;
      x1 = (x0 + x / x0) / 2.0;
    } while (abs(x1 - x0) >= 1);
    return int(x1);
  }
};
