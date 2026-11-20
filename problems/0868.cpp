// Source: https://leetcode.com/problems/binary-gap
// Title: Binary Gap
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a positive integer `n`, find and return the **longest distance** between any two **adjacent** `1`'s in the binary representation of `n`. If there are no two adjacent `1`'s, return `0`.
//
// Two `1`'s are **adjacent** if there are only `0`'s separating them (possibly no `0`'s). The **distance** between two `1`'s is the absolute difference between their bit positions. For example, the two `1`'s in `"1001"` have a distance of 3.
//
// **Example 1:**
//
// ```
// Input: n = 22
// Output: 2
// Explanation: 22 in binary is "10110".
// The first adjacent pair of 1's is "10110" with a distance of 2.
// The second adjacent pair of 1's is "10110" with a distance of 1.
// The answer is the largest of these two distances, which is 2.
// Note that "10110" is not a valid pair since there is a 1 separating the two 1's underlined.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 8
// Output: 0
// Explanation: 8 in binary is "1000".
// There are not any adjacent pairs of 1's in the binary representation of 8, so we return 0.
// ```
//
// **Example 3:**
//
// ```
// Input: n = 5
// Output: 2
// Explanation: 5 in binary is "101".
// ```
//
// **Constraints:**
//
// - `1 <= n <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <bit>

using namespace std;

// Loop through all bits
class Solution {
 public:
  int binaryGap(unsigned int n) {
    int maxGap = 0;

    // Loop through all bits
    int prevBit = -1, bit = 0;
    while (n > 0) {
      if (n & 1u) {
        if (prevBit >= 0) {
          maxGap = max(maxGap, bit - prevBit);
        }
        prevBit = bit;
      }
      n >>= 1;
      ++bit;
    }

    return maxGap;
  }
};

// Bit trick
class Solution2 {
 public:
  int binaryGap(unsigned int n) {
    int maxGap = 0;

    // Edge case
    if (n == 0) return 0;

    // Find first bit
    int prevIdx = countr_zero(n);  // find lowbit
    n &= (n - 1);                  // remove lowbit

    // Find next bit
    while (n > 0) {
      int currIdx = countr_zero(n);  // find lowbit
      n &= (n - 1);                  // remove lowbit
      maxGap = max(maxGap, currIdx - prevIdx);
      prevIdx = currIdx;
    }

    return maxGap;
  }
};
