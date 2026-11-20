// Source: https://leetcode.com/problems/sum-of-two-integers
// Title: Sum of Two Integers
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two integers `a` and `b`, return the sum of the two integers without using the operators `+` and `-`.
//
// **Example 1:**
//
// ```
// Input: a = 1, b = 2
// Output: 3
// ```
//
// **Example 2:**
//
// ```
// Input: a = 2, b = 3
// Output: 5
// ```
//
// **Constraints:**
//
// - `-1000 <= a, b <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include <tuple>

using namespace std;

// ALU
//
// Let x = abs(a) and y = abs(b), we compute to x+y or x-y for non-negative integers.
// WLOG, assume x >= y.
//
// We use the following recursion to solve.
// For addition,     we have x+y = x^y + (x&y << 1). (x&y are carry bits)
// For substraction, we have x-y = x^y - ((~x)&y << 1) ((~x)&y are the borrow bits)
class Solution {
 public:
  int getSum(int a, int b) {
    int x = abs(a), y = abs(b);

    // Ensure x >= y
    if (x < y) {
      swap(a, b);
      swap(x, y);
    }

    if (a * b >= 0) {  // same sign, x+y
      while (y) {
        tie(x, y) = forward_as_tuple(x ^ y, (x & y) << 1);
      }
    } else {  // different sign, x-y
      while (y) {
        tie(x, y) = forward_as_tuple(x ^ y, ((~x) & y) << 1);
      }
    }

    return a >= 0 ? x : -x;
  }
};

// ALU
//
// Since we are using C++, we dan't need to care about the sign.
class Solution2 {
 public:
  int getSum(int a, int b) {
    while (b) {
      tie(a, b) = forward_as_tuple(a ^ b, (a & b) << 1);
    }
    return a;
  }
};
