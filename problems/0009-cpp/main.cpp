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
#include <string>

using namespace std;

// Convert to string
class Solution {
 public:
  bool isPalindrome(int x) {
    auto sx = to_string(x);
    auto sy = sx;
    reverse(sy.begin(), sy.end());
    return sx == sy;
  }
};

// Integer
class Solution2 {
 public:
  bool isPalindrome(int x) {
    if (x == 0) return true;
    if (x < 0 || x % 10 == 0) return false;

    auto y = 0;
    while (y < x) {
      y = 10 * y + x % 10;
      x /= 10;
    }
    return (x == y) || x == y / 10;  // compare to y/10 is length is odd
  }
};
