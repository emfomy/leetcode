// Source: https://leetcode.com/problems/minimum-changes-to-make-alternating-binary-string
// Title: Minimum Changes To Make Alternating Binary String
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string `s` consisting only of the characters `'0'` and `'1'`. In one operation, you can change any `'0'` to `'1'` or vice versa.
//
// The string is called alternating if no two adjacent characters are equal. For example, the string `"010"` is alternating, while the string `"0100"` is not.
//
// Return the **minimum** number of operations needed to make `s` alternating.
//
// **Example 1:**
//
// ```
// Input: s = "0100"
// Output: 1
// Explanation: If you change the last character to '1', s will be "0101", which is alternating.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "10"
// Output: 0
// Explanation: s is already alternating.
// ```
//
// **Example 3:**
//
// ```
// Input: s = "1111"
// Output: 2
// Explanation: You need two operations to reach "0101" or "1010".
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 10^4`
// - `s[i]` is either `'0'` or `'1'`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>

using namespace std;

// Try both cases.
class Solution {
 public:
  int minOperations(const string &s) {
    const int n = s.size();

    int op0 = 0;  // start from 0
    int op1 = 0;  // start from 1

    for (int i = 0; i < n; ++i) {
      if ((s[i] & 1) != (i & 1)) {
        ++op0;
      } else {
        ++op1;
      }
    }

    return min(op0, op1);
  }
};

// Say op0 is the minimal operations needed to make s alternating starting from 0.
// Say op1 is the minimal operations needed to make s alternating starting from 1.
// It is clear that op0 + op1 = len(s).
//
// Therefore we only need to compute op0.
class Solution2 {
 public:
  int minOperations(const string &s) {
    const int n = s.size();
    int ops = 0;
    for (int i = 0; i < n; ++i) {
      ops += ((s[i] ^ i) & 1);
    }
    return min(ops, n - ops);
  }
};
