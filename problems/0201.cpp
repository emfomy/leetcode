// Source: https://leetcode.com/problems/bitwise-and-of-numbers-range
// Title: Bitwise AND of Numbers Range
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given two integers `left` and `right` that represent the range `[left, right]`, return the bitwise AND of all numbers in this range, inclusive.
//
// **Example 1:**
//
// ```
// Input: left = 5, right = 7
// Output: 4
// ```
//
// **Example 2:**
//
// ```
// Input: left = 0, right = 0
// Output: 0
// ```
//
// **Example 3:**
//
// ```
// Input: left = 1, right = 2147483647
// Output: 0
// ```
//
// **Constraints:**
//
// - `0 <= left <= right <= 2^31 - 1`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
using namespace std;

// Brute-Force (TLE)
class Solution {
 public:
  int rangeBitwiseAnd(uint32_t left, uint32_t right) {
    auto ans = right;
    for (auto i = left; i < right; ++i) {
      ans &= i;
    }
    return ans;
  }
};

// Check each bit
class Solution2 {
 public:
  uint32_t rangeBitwiseAnd(uint32_t left, uint32_t right) {
    auto ans = 0u;

    for (auto i = 0; i < 32; ++i) {
      auto bit = 1u << i;
      if ((left & bit) && (right & bit) && (right - left) < bit) {
        ans |= bit;
      }
    }

    return ans;
  }
};

// Common Prefix
//
// The problem is equal to finding the common prefix of left and right.
// We can shift left and right until they are equal.
class Solution3 {
 public:
  uint32_t rangeBitwiseAnd(uint32_t left, uint32_t right) {
    auto shift = 0;

    while (left < right) {
      left >>= 1;
      right >>= 1;
      ++shift;
    }

    return left << shift;
  }
};
