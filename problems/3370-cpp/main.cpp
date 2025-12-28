// Source: https://leetcode.com/problems/smallest-number-with-all-set-bits
// Title: Smallest Number With All Set Bits
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a positive number `n`.
//
// Return the **smallest** number `x` **greater than** or **equal to** `n`, such that the binary representation of `x` contains only <button type="button" aria-haspopup="dialog" aria-expanded="false" aria-controls="radix-:r1n:" data-state="closed" class="">set bits</button>
//
// **Example 1:**
//
// ```
// Input: n = 5
// Output: 7
// Explanation:
// The binary representation of 7 is `"111"`.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 10
// Output: 15
// Explanation:
// The binary representation of 15 is `"1111"`.
// ```
//
// **Example 3:**
//
// ```
// Input: n = 3
// Output: 3
// Explanation:
// The binary representation of 3 is `"11"`.
// ```
//
// **Constraints:**
//
// - `1 <= n <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <bit>

using namespace std;

class Solution {
 public:
  int smallestNumber(int n) {  //
    return bit_ceil(static_cast<unsigned int>(n + 1)) - 1;
  }
};
