// Source: https://leetcode.com/problems/maximum-product-of-two-digits
// Title: Maximum Product of Two Digits
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a positive integer `n`.
//
// Return the **maximum** product of any two digits in `n`.
//
// **Note:** You may use the **same** digit twice if it appears more than once in `n`.
//
// **Example 1:**
//
// ```
// Input: n = 31
// Output: 3
// Explanation:
// - The digits of `n` are `[3, 1]`.
// - The possible products of any two digits are: `3 * 1 = 3`.
// - The maximum product is 3.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 22
// Output: 4
// Explanation:
// - The digits of `n` are `[2, 2]`.
// - The possible products of any two digits are: `2 * 2 = 4`.
// - The maximum product is 4.
// ```
//
// **Example 3:**
//
// ```
// Input: n = 124
// Output: 8
// Explanation:
// - The digits of `n` are `[1, 2, 4]`.
// - The possible products of any two digits are: `1 * 2 = 2`, `1 * 4 = 4`, `2 * 4 = 8`.
// - The maximum product is 8.
// ```
//
// **Constraints:**
//
// - `10 <= n <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
using namespace std;

// Compare
class Solution {
 public:
  int maxProduct(int n) {
    int d1 = 0, d2 = 0;  // largest two digits
    while (n > 0) {
      int d = n % 10;
      n /= 10;
      if (d > d1) {
        d2 = d1;
        d1 = d;
      } else if (d > d2) {
        d2 = d;
      }
    }

    return d1 * d2;
  }
};

// Swap
class Solution2 {
 public:
  int maxProduct(int n) {
    int d1 = 0, d2 = 0;  // largest two digits
    while (n > 0) {
      int d = n % 10;
      n /= 10;
      if (d > d1) swap(d, d1);
      if (d > d2) swap(d, d2);
    }

    return d1 * d2;
  }
};

// DP (slower)
class Solution3 {
 public:
  int maxProduct(int n) {
    int m1 = 0;  // max digit
    int m2 = 0;  // max product
    while (n > 0) {
      int d = n % 10;
      n /= 10;
      m2 = max(m2, m1 * d);
      m1 = max(m1, d);
    }

    return m2;
  }
};
