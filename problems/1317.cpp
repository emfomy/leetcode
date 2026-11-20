// Source: https://leetcode.com/problems/convert-integer-to-the-sum-of-two-no-zero-integers
// Title: Convert Integer to the Sum of Two No-Zero Integers
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// **No-Zero integer** is a positive integer that **does not contain any `0`** in its decimal representation.
//
// Given an integer `n`, return a list of two integers `[a, b]` where:
//
// - `a` and `b` are **No-Zero integers**.
// - `a + b = n`
//
// The test cases are generated so that there is at least one valid solution. If there are many valid solutions, you can return any of them.
//
// **Example 1:**
//
// ```
// Input: n = 2
// Output: [1,1]
// Explanation: Let a = 1 and b = 1.
// Both a and b are no-zero integers, and a + b = 2 = n.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 11
// Output: [2,9]
// Explanation: Let a = 2 and b = 9.
// Both a and b are no-zero integers, and a + b = 11 = n.
// Note that there are other valid answers as [8, 3] that can be accepted.
// ```
//
// **Constraints:**
//
// - `2 <= n <= 10^4`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> getNoZeroIntegers(int n) {
    auto hasZero = [](int x) -> bool {
      while (x > 0) {
        if (x % 10 == 0) return true;
        x /= 10;
      }
      return false;
    };

    for (auto a = 1; a < n; ++a) {
      auto b = n - a;
      if (!hasZero(a) && !hasZero(b)) return {a, b};
    }
    return {};
  }
};
