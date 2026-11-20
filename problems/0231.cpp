// Source: https://leetcode.com/problems/power-of-two
// Title: Power of Two
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an integer `n`, return `true` if it is a power of two. Otherwise, return `false`.
//
// An integer `n` is a power of two, if there exists an integer `x` such that `n == 2^x`.
//
// **Example 1:**
//
// ```
// Input: n = 1
// Output: true
// Explanation: 2^0 = 1
// ```
//
// **Example 2:**
//
// ```
// Input: n = 16
// Output: true
// Explanation: 2^4 = 16
// ```
//
// **Example 3:**
//
// ```
// Input: n = 3
// Output: false
// ```
//
// **Constraints:**
//
// - `-2^31 <= n <= 2^31 - 1`
//
// **Follow up:** Could you solve it without loops/recursion?
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <bit>
#include <cstdint>
#include <cstdlib>

using namespace std;

// Use Loop
class Solution {
 public:
  bool isPowerOfTwo(int n) {
    if (n <= 0) return false;

    for (; n > 1; n >>= 1) {
      if (n & 1) return false;
    }
    return true;
  }
};

// n & -n get the right most 1-bit
class Solution2 {
 public:
  bool isPowerOfTwo(int n) {  //
    return (n > 0) ? (n & (-n)) == n : false;
  }
};

// n & (n-1) removes right most 1-bit
class Solution3 {
 public:
  bool isPowerOfTwo(int n) {  //
    return (n > 0) ? (n & (n - 1)) == 0 : false;
  }
};

class Solution4 {
 public:
  bool isPowerOfTwo(int n) {  //
    return (n > 0) ? popcount(static_cast<uint32_t>(n)) == 1 : false;
  }
};

// Equal to (n & (n - 1)) == 0
class Solution5 {
 public:
  bool isPowerOfTwo(int n) {  //
    return (n > 0) ? has_single_bit(static_cast<uint32_t>(n)) : false;
  }
};
