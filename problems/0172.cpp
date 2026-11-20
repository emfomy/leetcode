// Source: https://leetcode.com/problems/factorial-trailing-zeroes
// Title: Factorial Trailing Zeroes
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer `n`, return the number of trailing zeroes in `n!`.
//
// Note that `n! = n * (n - 1) * (n - 2) * ... * 3 * 2 * 1`.
//
// **Example 1:**
//
// ```
// Input: n = 3
// Output: 0
// Explanation: 3! = 6, no trailing zero.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 5
// Output: 1
// Explanation: 5! = 120, one trailing zero.
// ```
//
// **Example 3:**
//
// ```
// Input: n = 0
// Output: 0
// ```
//
// **Constraints:**
//
// - `0 <= n <= 10^4`
//
// **Follow up:** Could you write a solution that works in logarithmic time complexity?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Consider the prime factorization of n!.
// Since there are more 2 than 5, we just compute the number of 5s.
class Solution {
 public:
  int trailingZeroes(int n) {
    int zeros = 0;  // trailing zeros

    int fivePow = 5;  // power of 5
    while (fivePow <= n) {
      zeros += n / fivePow;
      fivePow *= 5;
    }

    return zeros;
  }
};

class Solution2 {
 public:
  int trailingZeroes(int n) {
    int zeros = 0;  // trailing zeros

    while (n > 0) {
      n /= 5;
      zeros += n;
    }

    return zeros;
  }
};
