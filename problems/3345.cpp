// Source: https://leetcode.com/problems/smallest-divisible-digit-product-i
// Title: Smallest Divisible Digit Product I
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given two integers `n` and `t`. Return the **smallest** number greater than or equal to `n` such that the **product of its digits** is divisible by `t`.
//
// **Example 1:**
//
// Input: n = 10, t = 2
//
// Output: 10
//
// Explanation:
//
// The digit product of 10 is 0, which is divisible by 2, making it the smallest number greater than or equal to 10 that satisfies the condition.
//
// **Example 2:**
//
// Input: n = 15, t = 3
//
// Output: 16
//
// Explanation:
//
// The digit product of 16 is 6, which is divisible by 3, making it the smallest number greater than or equal to 15 that satisfies the condition.
//
// **Constraints:**
//
// - `1 <= n <= 100`
// - `1 <= t <= 10`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

// Brute Force
//
// Note that a number with zero in it always fit the criteria.
// Therefore, we only need to check at most 10 numbers;
class Solution {
 public:
  int smallestNumber(int n, int t) {
    for (int m = n; m < n + 10; ++m) {
      if (digitProd(m) % t == 0) return m;
    }
    return -1;  // unreachable
  }

  int digitProd(int n) {
    int prod = 1;
    while (n > 0) {
      prod *= n % 10;
      n /= 10;
    }
    return prod;
  }
};
