// Source: https://leetcode.com/problems/number-of-steps-to-reduce-a-number-to-zero
// Title: Number of Steps to Reduce a Number to Zero
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer num, return the number of steps to reduce it to zero.
//
// In one step, if the current number is even, you have to divide it by 2, otherwise, you have to subtract 1 from it.
//
// Example 1:
//
//   Input: num = 14
//   Output: 6
//   Explanation:
//   Step 1) 14 is even; divide by 2 and obtain 7.
//   Step 2) 7 is odd; subtract 1 and obtain 6.
//   Step 3) 6 is even; divide by 2 and obtain 3.
//   Step 4) 3 is odd; subtract 1 and obtain 2.
//   Step 5) 2 is even; divide by 2 and obtain 1.
//   Step 6) 1 is odd; subtract 1 and obtain 0.
//
// Example 2:
//
//   Input: num = 8
//   Output: 4
//   Explanation:
//   Step 1) 8 is even; divide by 2 and obtain 4.
//   Step 2) 4 is even; divide by 2 and obtain 2.
//   Step 3) 2 is even; divide by 2 and obtain 1.
//   Step 4) 1 is odd; subtract 1 and obtain 0.
//
// Example 3:
//
//   Input: num = 123
//   Output: 12
//
// Constraints:
//
//   0 <= num <= 10^6
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <bit>

using namespace std;

// If num is power of 2, then the result is log2(num).
// For any bit 1 below the highest digit in binary, we need and extra subtract.
// Therefore, the result is
//   log2(num) + number of 1 below the highest digit
// = (sizeof(num) * 8 - countl_zero(num)) + (popcount(num) - 1)
// Note: since num is sigend integer,
//   we need to substract 1 to the result for the sign bit.
class Solution {
 public:
  int numberOfSteps(int num) { return num ? sizeof(num) * 8 - __builtin_clz(num) + __builtin_popcount(num) - 1 : 0; }
};
