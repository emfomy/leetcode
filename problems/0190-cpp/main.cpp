// Source: https://leetcode.com/problems/reverse-bits
// Title: Reverse Bits
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reverse bits of a given 32 bits signed integer.
//
// **Example 1:**
//
// ```
// Input: n = 43261596
// Output: 964176192
// Explanation:
// * 43261596: 00000010100101000001111010011100
// * 964176192: 00111001011110000010100101000000
// ```
//
// **Example 2:**
//
// ```
// Input: n = 2147483644
// Output: 1073741822
// Explanation:
// * 2147483644: 01111111111111111111111111111100
// * 1073741822: 00111111111111111111111111111110
// ```
//
// **Constraints:**
//
// - `0 <= n <= 2^31 - 2`
// - `n` is even.
//
// **Follow up:** If this function is called many times, how would you optimize it?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
using namespace std;

// Shift Loop
class Solution {
 public:
  int reverseBits(uint32_t n) {
    auto ans = 0;
    for (auto i = 0; i < 32; i++) {
      ans <<= 1;
      ans += n % 2;
      n >>= 1;
    }

    return ans;
  }
};

// Bit Mask
class Solution2 {
 public:
  uint32_t reverseBits(uint32_t n) {
    n = (n << 16) | (n >> 16);
    // n = ((0x0000FFFFu & n) << 16) | ((0xFFFF0000u & n) >> 16);
    n = ((0x00FF00FFu & n) << 8) | ((0xFF00FF00u & n) >> 8);
    n = ((0x0F0F0F0Fu & n) << 4) | ((0xF0F0F0F0u & n) >> 4);
    n = ((0x33333333u & n) << 2) | ((0xCCCCCCCCu & n) >> 2);
    n = ((0x55555555u & n) << 1) | ((0xAAAAAAAAu & n) >> 1);
    return n;
  }
};

// Builtin
class Solution3 {
 public:
  int reverseBits(uint32_t n) {  //
    return __builtin_bitreverse32(n);
  }
};
