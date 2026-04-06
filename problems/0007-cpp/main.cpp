// Source: https://leetcode.com/problems/reverse-integer
// Title: Reverse Integer
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a signed 32-bit integer `x`, return `x` with its digits reversed. If reversing `x` causes the value to go outside the signed 32-bit integer range `[-2^31, 2^31 - 1]`, then return `0`.
//
// **Assume the environment does not allow you to store 64-bit integers (signed or unsigned).**
//
// **Example 1:**
//
// ```
// Input: x = 123
// Output: 321
// ```
//
// **Example 2:**
//
// ```
// Input: x = -123
// Output: -321
// ```
//
// **Example 3:**
//
// ```
// Input: x = 120
// Output: 21
// ```
//
// **Constraints:**
//
// - `-2^31 <= x <= 2^31 - 1`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <cstdint>
#include <cstdlib>
#include <string>

using namespace std;

// String
class Solution {
 public:
  int reverse(int x) {
    int64_t xx = static_cast<int64_t>(x);
    int64_t sign = (xx >= 0) ? 1 : -1;
    string s = to_string(abs(xx));
    std::reverse(s.begin(), s.end());
    int64_t y = sign * stoll(s);
    return (y > INT_MAX || y < INT_MIN) ? 0 : y;
  }
};

// Integer Division
class Solution2 {
 public:
  int reverse(int x) {
    int64_t y = 0;
    while (x != 0) {
      y = y * 10 + x % 10;
      x /= 10;
    }

    return (y > INT_MAX || y < INT_MIN) ? 0 : y;
  }
};

// Integer Division
class Solution3 {
 public:
  int reverse(int x) {
    int64_t y = 0;
    while (x != 0) {
      if (y > INT_MAX / 10 || y < INT_MIN / 10) return 0;  // out of range
      y = y * 10 + x % 10;
      x /= 10;
    }
    return y;
  }
};
