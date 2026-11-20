// Source: https://leetcode.com/problems/minimum-number-of-flips-to-make-the-binary-string-alternating
// Title: Minimum Number of Flips to Make the Binary String Alternating
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a binary string `s`. You are allowed to perform two types of operations on the string in any sequence:
//
// - **Type-1: Remove** the character at the start of the string `s` and **append** it to the end of the string.
// - **Type-2: Pick** any character in `s` and **flip** its value, i.e., if its value is `'0'` it becomes `'1'` and vice-versa.
//
// Return the **minimum** number of **type-2** operations you need to perform such that `s` becomes **alternating**.
//
// The string is called **alternating** if no two adjacent characters are equal.
//
// - For example, the strings `"010"` and `"1010"` are alternating, while the string `"0100"` is not.
//
// **Example 1:**
//
// ```
// Input: s = "111000"
// Output: 2
// Explanation
// : Use the first operation two times to make s = "100011".
// Then, use the second operation on the third and sixth elements to make s = "101010".
// ```
//
// **Example 2:**
//
// ```
// Input: s = "010"
// Output: 0
// Explanation
// : The string is already alternating.
// ```
//
// **Example 3:**
//
// ```
// Input: s = "1110"
// Output: 1
// Explanation
// : Use the second operation on the second element to make s = "1010".
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 10^5`
// - `s[i]` is either `'0'` or `'1'`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>

using namespace std;

// DP
//
// For len(s) even, we don't need type-1.
// For len(s) odd, we are allowed to have a pair of same adjacent element.
//
// b is 0 or 1.
// Let DP[i, b] = minimal flips of s[:i] if we want s[i] = b.
// Let DPA[i, b] = minimal flips of s[:i] if we want s[i] = b, and allowing same adjacent element.
//
// DP[0, b] = DPA[0, b] = 0 (since s[:0] is empty)
// DP[i, b]  = DP[i-1, !b] + int(s[i] != b).
// DPA[i, b] = min(DPA[i-1, !b], DP[i-1, b]) + int(s[i] != b).
//
// We only use the result of DPA is len(s) is odd.
class Solution {
 public:
  int minFlips(const string &s) {
    const int n = s.size();

    int dp0 = 0;   // s[k] = 0
    int dp1 = 0;   // s[k] = 1
    int dp0A = 0;  // s[k] = 0, allowing adjacent
    int dp1A = 0;  // s[k] = 1, allowing adjacent

    for (char ch : s) {
      const int cost0 = !(ch & 1);  // cost to flip s[i] to 0
      const int cost1 = (ch & 1);   // cost to flip s[i] to 1

      int nextDP0 = dp1 + cost0;
      int nextDP1 = dp0 + cost1;
      int nextDP0A = min(dp1A, dp0) + cost0;
      int nextDP1A = min(dp0A, dp1) + cost1;

      dp0 = nextDP0;
      dp1 = nextDP1;
      dp0A = nextDP0A;
      dp1A = nextDP1A;
    }

    int dp = min(dp0, dp1);
    int dpA = min(dp0A, dp1A);

    return (n & 1) ? min(dp, dpA) : dp;
  }
};

// DP, inplace
//
// For len(s) even, we don't need type-1.
// For len(s) odd, we are allowed to have a pair of same adjacent element.
//
// b is 0 or 1.
// Let DP[i, b]  = minimal flips of s[:i] if we want s[0] = b.
// Let DPA[i, b] = minimal flips of s[:i] if we want s[0] = b, and allowing same adjacent element.
//
// Therefore,
// DP[i, b]  wants s[i] = b is i is even, s[i] = !b is i is odd;
// DPA[i, b] wants s[i] = b is i is odd, s[i] = !b is i is even;
//
// DP[0, b] = DPA[0, b] = 0 (since s[:0] is empty)
// DP[i, b]  = DP[i-1, b] + (need flip?)
// DPA[i, b] = min(DPA[i-1, b], DP[i-1, b]) + (need flip?)
//
// We only use the result of DPA is len(s) is odd.
class Solution2 {
 public:
  int minFlips(const string &s) {
    const int n = s.size();

    int dp0 = 0;   // start from 0
    int dp1 = 0;   // start from 1
    int dp0A = 0;  // start from 0, allowing adjacent
    int dp1A = 0;  // start from 1, allowing adjacent

    for (int i = 0; i < n; ++i) {
      const int need0 = (s[i] ^ i) & 1;     // cost to flip s[i] for dp0
      const int need1 = !((s[i] ^ i) & 1);  // cost to flip s[i] for dp1

      dp0A = min(dp0A, dp0) + need1;
      dp1A = min(dp1A, dp1) + need0;
      dp0 += need0;
      dp1 += need1;
    }

    int dp = min(dp0, dp1);
    int dpA = min(dp0A, dp1A);

    return (n & 1) ? min(dp, dpA) : dp;
  }
};
