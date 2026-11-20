// Source: https://leetcode.com/problems/smallest-integer-divisible-by-k
// Title: Smallest Integer Divisible by K
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a positive integer `k`, you need to find the **length** of the **smallest** positive integer `n` such that `n` is divisible by `k`, and `n` only contains the digit `1`.
//
// Return the **length** of `n`. If there is no such `n`, return -1.
//
// **Note:** `n` may not fit in a 64-bit signed integer.
//
// **Example 1:**
//
// ```
// Input: k = 1
// Output: 1
// Explanation: The smallest answer is n = 1, which has length 1.
// ```
//
// **Example 2:**
//
// ```
// Input: k = 2
// Output: -1
// Explanation: There is no such positive integer n divisible by 2.
// ```
//
// **Example 3:**
//
// ```
// Input: k = 3
// Output: 3
// Explanation: The smallest answer is n = 111, which has length 3.
// ```
//
// **Constraints:**
//
// - `1 <= k <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <unordered_set>
using namespace std;

// Hash Map
class Solution {
 public:
  int smallestRepunitDivByK(int k) {
    auto visited = unordered_set<int>();
    int i = 1, n = (1 % k);
    visited.insert(n);
    while (n != 0) {
      n = (n * 10 + 1) % k;
      ++i;
      auto [_, ok] = visited.insert(n);
      if (!ok) return -1;  // loop detected
    }
    return i;
  }
};

// Math
//
// In previous approach, we use a hash map to detect loop.
// However, in mod k ring, the maximum loop is size k.
// Therefore, we can simply run the loop for k times without checkint the loop.
class Solution2 {
 public:
  int smallestRepunitDivByK(int k) {
    int n = (1 % k);
    for (int i = 1; i <= k; ++i) {
      if (n == 0) return i;
      n = (n * 10 + 1) % k;
    }
    return -1;
  }
};

// Math
//
// Answer exists iff. gcd(10, k) = 1.
class Solution3 {
 public:
  int smallestRepunitDivByK(int k) {
    if (k % 2 == 0 || k % 5 == 0) return -1;
    int n = (1 % k);
    for (int i = 1; i <= k; ++i) {
      if (n == 0) return i;
      n = (n * 10 + 1) % k;
    }
    return -1;  // unreachable
  }
};
