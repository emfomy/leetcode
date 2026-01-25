// Source: https://leetcode.com/problems/sum-of-square-numbers
// Title: Sum of Square Numbers
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a non-negative integer `c`, decide whether there're two integers `a` and `b` such that `a^2 + b^2 = c`.
//
// **Example 1:**
//
// ```
// Input: c = 5
// Output: true
// Explanation: 1 * 1 + 2 * 2 = 5
// ```
//
// **Example 2:**
//
// ```
// Input: c = 3
// Output: false
// ```
//
// **Constraints:**
//
// - `0 <= c <= 2^31 - 1`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include <cstdint>

using namespace std;

class Solution {
 public:
  bool judgeSquareSum(int64_t c) {
    for (auto a = 0; a <= c; ++a) {
      auto a2 = a * a;
      if (a2 > c) return false;

      int b = sqrt(c - a2);
      if (a2 + b * b == c) return true;
      if (b <= a) return false;
    }
    return false;
  }
};

// Two pointer
//
// Let a = 0 and b = sqrt(c).
// Move a and b depends the relation between a^2 + b^2 and c
class Solution2 {
 public:
  bool judgeSquareSum(int64_t c) {
    int64_t a = 0, b = sqrt(c);
    while (a <= b) {
      auto sum = a * a + b * b;
      if (sum == c) return true;

      if (sum < c) {
        ++a;
      } else {
        --b;
      }
    }

    return false;
  }
};
