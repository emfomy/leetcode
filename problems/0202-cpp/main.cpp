// Source: https://leetcode.com/problems/happy-number
// Title: Happy Number
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Write an algorithm to determine if a number `n` is happy.
//
// A **happy number** is a number defined by the following process:
//
// - Starting with any positive integer, replace the number by the sum of the squares of its digits.
// - Repeat the process until the number equals 1 (where it will stay), or it **loops endlessly in a cycle** which does not include 1.
// - Those numbers for which this process **ends in 1** are happy.
//
// Return `true` if `n` is a happy number, and `false` if not.
//
// **Example 1:**
//
// ```
// Input: n = 19
// Output: true
// Explanation:
// 1^2 + 9^2 = 82
// 8^2 + 2^2 = 68
// 6^2 + 8^2 = 100
// 1^2 + 0^2 + 0^2 = 1
// ```
//
// **Example 2:**
//
// ```
// Input: n = 2
// Output: false
// ```
//
// **Constraints:**
//
// - `1 <= n <= 2^31 - 1`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <unordered_set>

using namespace std;

// Use hash map
class Solution {
 public:
  bool isHappy(int n) {
    unordered_set<int> seen;

    auto getNext = [=](int x) -> int {
      int y = 0;
      for (; x > 0; x /= 10) {
        y += (x % 10) * (x % 10);
      }
      return y;
    };

    for (; n != 1; n = getNext(n)) {
      if (seen.count(n)) return false;
      seen.insert(n);
    }

    return true;
  }
};

// Use fast slow pointer
class Solution2 {
 public:
  bool isHappy(int n) {
    auto getNext = [=](int x) -> int {
      int y = 0;
      for (; x > 0; x /= 10) {
        y += (x % 10) * (x % 10);
      }
      return y;
    };

    auto slow = n;
    auto fast = getNext(n);

    while (slow != 1) {
      if (slow == fast) return false;
      slow = getNext(slow);
      fast = getNext(getNext(fast));
    }

    return true;
  }
};
