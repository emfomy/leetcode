// Source: https://leetcode.com/problems/minimum-one-bit-operations-to-make-integers-zero
// Title: Minimum One Bit Operations to Make Integers Zero
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer `n`, you must transform it into `0` using the following operations any number of times:
//
// - Change the rightmost (`0^th`) bit in the binary representation of `n`.
// - Change the `i^th` bit in the binary representation of `n` if the `(i-1)^th` bit is set to `1` and the `(i-2)^th` through `0^th` bits are set to `0`.
//
// Return the minimum number of operations to transform `n` into `0`.
//
// **Example 1:**
//
// ```
// Input: n = 3
// Output: 2
// Explanation: The binary representation of 3 is "11".
// "11" -> "01" with the 2^nd operation since the 0^th bit is 1.
// "01" -> "00" with the 1^st operation.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 6
// Output: 4
// Explanation: The binary representation of 6 is "110".
// "110" -> "010" with the 2^nd operation since the 1^st bit is 1 and 0^th through 0^th bits are 0.
// "010" -> "011" with the 1^st operation.
// "011" -> "001" with the 2^nd operation since the 0^th bit is 1.
// "001" -> "000" with the 1^st operation.
// ```
//
// **Constraints:**
//
// - `0 <= n <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <bit>
#include <cstdint>

using namespace std;

// Let X be a bit, Y be !X.
//
// Denote the operations:
// F: change 0th bit: X -> Y
// G(i): change left of rightmost one bit: X10..0 -> Y10..0 (length i)
//
// Define H(i): change the rightmost bit: X0..0 -> Y0..0 (length i)
//
// Use recursion to implement H
// H(0) = F
// H(i): X00..0 -> H(i-1) -> X10..0 -> G(i) -> Y10..0 -> H(i-1) -> Y00..0
// #H(0) = 1
// #H(k) = 2*#H(k-1)+1 = 2^(k+1)-1
//
// Note that these operations are self-inverse:
// F & F = 0, G(i) & G(i) = 0, H(i) & G(i) = 0
//
// Then for any number, we can use H to remove rightmost `1` bit one by one.
//
// However, say the operations are H(i1) H(i2) H(i3) ..., where i1 < i2 < i3
// It is easy to find out that H(i1) is in H(i2) and H(i2) is in H(i3)
//
// Therefore, for any n, find the top bit 2^k and apply H(k).
// Now compute the n-2^k (remaining bits) and subtract by the number of operations.
class Solution {
 public:
  int minimumOneBitOperations(int n) {
    if (n == 0) return 0;
    auto b = bit_floor(uint32_t(n));  // find top bit
    return 2 * b - 1 - minimumOneBitOperations(n - b);
  }
};

// Use gray code
//
// These operations are exact the gray codes.
// We need to convert gray to binary
class Solution2 {
 public:
  int minimumOneBitOperations(int n) {
    auto ans = n;
    while (n) {
      n >>= 1;
      ans ^= n;
    }
    return ans;
  }
};

// Use gray code
class Solution3 {
 public:
  int minimumOneBitOperations(int n) {
    int ans = n;
    ans ^= ans >> 16;
    ans ^= ans >> 8;
    ans ^= ans >> 4;
    ans ^= ans >> 2;
    ans ^= ans >> 1;
    return ans;
  }
};
