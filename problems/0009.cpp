// Source: https://leetcode.com/problems/palindrome-number
// Title: Palindrome Number
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer `x`, return `true` if `x` is a **palindrome**, and `false` otherwise.
//
// An integer is a **palindrome** when it reads the same forward and backward.
//
// **Example 1:**
//
// ```
// Input: x = 121
// Output: true
// Explanation: 121 reads as 121 from left to right and from right to left.
// ```
//
// **Example 2:**
//
// ```
// Input: x = -121
// Output: false
// Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.
// ```
//
// **Example 3:**
//
// ```
// Input: x = 10
// Output: false
// Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
// ```
//
// **Constraints:**
//
// - `-2^31<= x <= 2^31- 1`
//
// **Follow up:** Could you solve it without converting the integer to a string?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cstdint>
#include <string>

using namespace std;

// Convert to string
class Solution {
 public:
  bool isPalindrome(int x) {
    string sx = to_string(x);
    return equal(sx.cbegin(), sx.cend(), sx.rbegin());
  }
};

// Integer Division
class Solution2 {
 public:
  bool isPalindrome(const int x) {
    if (x == 0) return true;                 // trivial
    if (x < 0 || x % 10 == 0) return false;  // reverse is not number

    int64_t y = 0;
    int64_t tmp = x;
    while (tmp > 0) {
      y = y * 10 + tmp % 10;
      tmp /= 10;
    }
    return x == y;
  }
};

// Integer Division
class Solution3 {
 public:
  bool isPalindrome(int x) {
    if (x == 0) return true;                 // trivial
    if (x < 0 || x % 10 == 0) return false;  // reverse is not number

    int y = 0;
    while (y < x) {
      y = y * 10 + x % 10;
      x /= 10;
    }
    return (x == y) || x == y / 10;  // compare x to y/10 when length is odd
  }
};
