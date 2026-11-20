// Source: https://leetcode.com/problems/reordered-power-of-2
// Title: Reordered Power of 2
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer `n`. We reorder the digits in any order (including the original order) such that the leading digit is not zero.
//
// Return `true` if and only if we can do this so that the resulting number is a power of two.
//
// **Example 1:**
//
// ```
// Input: n = 1
// Output: true
// ```
//
// **Example 2:**
//
// ```
// Input: n = 10
// Output: false
// ```
//
// **Constraints:**
//
// - `1 <= n <= 10^9`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <array>

using namespace std;

// First find the digits of n.
// Check all power of 2 and check if the digits distribution is equal.
class Solution {
 public:
  bool reorderedPowerOf2(int n) {
    auto count = [](int x) -> array<int, 10> {
      auto ret = array<int, 10>();
      while (x > 0) {
        ret[x % 10]++;
        x /= 10;
      }
      return ret;
    };

    auto digits = count(n);
    for (auto p = 0; p < 31; p++) {
      if (digits == count(1 << p)) {
        return true;
      }
    }
    return false;
  }
};
