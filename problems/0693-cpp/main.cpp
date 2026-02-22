// Source: https://leetcode.com/problems/binary-number-with-alternating-bits
// Title: Binary Number with Alternating Bits
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a positive integer, check whether it has alternating bits: namely, if two adjacent bits will always have different values.
//
// **Example 1:**
//
// ```
// Input: n = 5
// Output: true
// Explanation: The binary representation of 5 is: 101
// ```
//
// **Example 2:**
//
// ```
// Input: n = 7
// Output: false
// Explanation: The binary representation of 7 is: 111.```
//
// **Example 3:**
//
// ```
// Input: n = 11
// Output: false
// Explanation: The binary representation of 11 is: 1011.```
//
// **Constraints:**
//
// - `1 <= n <= 2^31 - 1`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

class Solution {
 public:
  bool hasAlternatingBits(unsigned int n) {
    unsigned int prevBit = n % 2;
    n /= 2;
    while (n > 0) {
      unsigned int bit = n % 2;
      if (prevBit == bit) return false;
      prevBit = bit;
      n /= 2;
    }
    return true;
  }
};
