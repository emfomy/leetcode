// Source: https://leetcode.com/problems/number-of-1-bits
// Title: Number of 1 Bits
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a positive integer `n`, write a function that returns the number of **set bits** in its binary representation (also known as the **Hamming weight** https://en.wikipedia.org/wiki/Hamming_weight).
//
// A **set bit** refers to a bit in the binary representation of a number that has a value of 1.
//
// **Example 1:**
//
// ```
// Input: n = 11
// Output: 3
// Explanation:
// The input binary string **1011** has a total of three set bits.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 128
// Output: 1
// Explanation:
// The input binary string **10000000** has a total of one set bit.
// ```
//
// **Example 3:**
//
// ```
// Input: n = 2147483645
// Output: 30
// Explanation:
// The input binary string **1111111111111111111111111111101** has a total of thirty set bits.
// ```
//
// **Constraints:**
//
// - `1 <= n <= 2^31 - 1`
//
// **Follow up:** If this function is called many times, how would you optimize it?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <bit>
#include <cstdint>

using namespace std;

// Shift Loop
class Solution {
 public:
  int hammingWeight(int n) {
    auto ans = 0;
    for (; n > 0; n >>= 1) {
      ans += n % 2;
    }
    return ans;
  }
};

// Bit Mask
class Solution2 {
 public:
  int hammingWeight(uint32_t n) {
    n = ((0xAAAAAAAAu & n) >> 1) + (0x55555555u & n);
    n = ((0xCCCCCCCCu & n) >> 2) + (0x33333333u & n);
    n = ((0xF0F0F0F0u & n) >> 4) + (0x0F0F0F0Fu & n);
    n = ((0xFF00FF00u & n) >> 8) + (0x00FF00FFu & n);
    n = ((0xFFFF0000u & n) >> 16) + (0x0000FFFFu & n);
    return n;
  }
};

// Builtin
class Solution3 {
 public:
  int hammingWeight(uint32_t n) {  //
    return popcount(n);
  }
};
