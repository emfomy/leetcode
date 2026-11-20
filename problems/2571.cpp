// Source: https://leetcode.com/problems/minimum-operations-to-reduce-an-integer-to-0
// Title: Minimum Operations to Reduce an Integer to 0
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a positive integer `n`, you can do the following operation **any** number of times:
//
// - Add or subtract a **power** of `2` from `n`.
//
// Return the **minimum** number of operations to make `n` equal to `0`.
//
// A number `x` is power of `2` if `x == 2^i`where `i >= 0`.
//
// **Example 1:**
//
// ```
// Input: n = 39
// Output: 3
// Explanation: We can do the following operations:
// - Add 2^0 = 1 to n, so now n = 40.
// - Subtract 2^3 = 8 from n, so now n = 32.
// - Subtract 2^5 = 32 from n, so now n = 0.
// It can be shown that 3 is the minimum number of operations we need to make n equal to 0.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 54
// Output: 3
// Explanation: We can do the following operations:
// - Add 2^1 = 2 to n, so now n = 56.
// - Add 2^3 = 8 to n, so now n = 64.
// - Subtract 2^6 = 64 from n, so now n = 0.
// So the minimum number of operations is 3.
// ```
//
// **Constraints:**
//
// - `1 <= n <= 10^5`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <unordered_set>

using namespace std;

// BFS
class Solution {
 public:
  int minOperations(int n) {
    auto que = queue<pair<int, int>>();  // num, ops
    auto visited = unordered_set<int>();
    que.emplace(n, 0);
    visited.insert(n);

    while (!que.empty()) {
      auto [num, ops] = que.front();
      que.pop();

      int nextOps = ops + 1;
      for (int b = 1; b <= num; b *= 2) {
        int nextNum = num - b;
        if (nextNum == 0) return nextOps;
        if (!visited.contains(nextNum)) {
          visited.insert(nextNum);
          que.emplace(nextNum, nextOps);
        }

        nextNum = num + b;
        if (!visited.contains(nextNum)) {
          visited.insert(nextNum);
          que.emplace(nextNum, nextOps);
        }
      }
    }

    return -1;  // unreachable
  }
};

// Bit
//
// Focus on the bits of n. We can either:
// * set 1 to 0; (i.e. remove lowbit)
// * convert 011...11 to 100...00 (i.e. add lowbit)
//
// We start from the lowest bit (since op2 will affect higher bits).
class Solution2 {
 public:
  int minOperations(int n) {
    int ops = 0;
    while (n > 0) {
      // Find lowbit
      int b = (n & -n);
      ++ops;

      if (!(n & (b << 1))) {  // remove lowbit
        n -= b;
      } else {  // add lowbit
        n += b;
      }
    }

    return ops;
  }
};

// Bit
//
// Instead of finding lowbit and check if it is single bit,
// we shift right to remove zeros and check if the lowest bit are 01 or 11.
class Solution3 {
 public:
  int minOperations(const int n) {
    auto un = static_cast<unsigned>(n);
    int ops = 0;
    while (un > 0) {
      if ((un & 3u) == 3u) {  // add lowbit
        ++un;
        ++ops;
      } else if ((un & 1u) == 1u) {  // remove lowbit
        --un;
        ++ops;
      } else {  // remove trailing zero
        un >>= countr_zero(un);
      }
    }

    return ops;
  }
};
