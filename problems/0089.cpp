// Source: https://leetcode.com/problems/gray-code
// Title: Gray Code
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// An **n-bit gray code sequence** is a sequence of `2^n` integers where:
//
// - Every integer is in the **inclusive** range `[0, 2^n - 1]`,
// - The first integer is `0`,
// - An integer appears **no more than once** in the sequence,
// - The binary representation of every pair of **adjacent** integers differs by **exactly one bit**, and
// - The binary representation of the **first** and **last** integers differs by **exactly one bit**.
//
// Given an integer `n`, return any valid **n-bit gray code sequence**.
//
// **Example 1:**
//
// ```
// Input: n = 2
// Output: [0,1,3,2]
// Explanation:
// The binary representation of [0,1,3,2] is [00,01,11,10].
// - 00 and 01 differ by one bit
// - 01 and 11 differ by one bit
// - 11 and 10 differ by one bit
// - 10 and 00 differ by one bit
// [0,2,3,1] is also a valid gray code sequence, whose binary representation is [00,10,11,01].
// - 00 and 10 differ by one bit
// - 10 and 11 differ by one bit
// - 11 and 01 differ by one bit
// - 01 and 00 differ by one bit
// ```
//
// **Example 2:**
//
// ```
// Input: n = 1
// Output: [0,1]
// ```
//
// **Constraints:**
//
// - `1 <= n <= 16`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>
using namespace std;

// Recursion
//
// Say we have gray code of n bits.
// We reverse ordering them, set the nth bit to 1, and append to the end.
// Now we have gray code of n+1 bits.
//
// Let m = 2^n.
// We know that G(m) = G(m-1) + high bit, so they differs by exactly one bit.
// We know that G(2m-1) = G(0) + high bit, so they differs by exactly one bit.
class Solution {
 public:
  vector<int> grayCode(const int n) {
    // Guard
    if (n <= 0) return {};

    // Init
    const int m = 1 << n;
    auto grays = vector<int>(m);
    grays[0] = 0;
    grays[1] = 1;

    // Loop
    for (int k = 2; k < m; k <<= 1) {
      for (int i = 0; i < k; ++i) {
        grays[2 * k - 1 - i] = grays[i] | k;
      }
    }

    return grays;
  }
};

// Iteration
//
// G(x) = x ^ (x >> 1)
//
// Prove by induction.
// Let 0 <= x < m, m = 2^n.
// Let m <= y < 2m, y = 2m-1-x.
//
// By recursion,
// G(y) = m | G(x) = m | (x ^ (x>>1))
//
// We only consider the lowest n+1 bits.
// We can rewrite y = ~x => x = ~y.
// G(y) = m | ((~y) ^ ((~y)>>1))
//
// Note that (~y)>>= ~(y>>1), (~a) ^ (~b) = a ^ b
// G(y) = m | ((~y) ^ (~(y>>1)))
//      = m | (y ^ (y>>1))
//
// Note that y > m and (y>>1) < m,
// we know that (y ^ (y>>1)) contains the n-th bit (i.e. value of m).
// Therefore, G(y) = y ^ (y>>1)
class Solution2 {
 public:
  vector<int> grayCode(const int n) {
    // Guard
    if (n <= 0) return {};

    // Init
    const int m = 1 << n;
    auto grays = vector<int>(m);
    for (int i = 0; i < m; ++i) {
      grays[i] = i ^ (i >> 1);
    }

    return grays;
  }
};
