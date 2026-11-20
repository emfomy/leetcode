// Source: Number of Substrings With Only 1s
// Title: https://leetcode.com/problems/number-of-substrings-with-only-1s
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a binary string `s`, return the number of substrings with all characters `1`'s. Since the answer may be too large, return it modulo `10^9 + 7`.
//
// **Example 1:**
//
// ```
// Input: s = "0110111"
// Output: 9
// Explanation: There are 9 substring in total with only 1's characters.
// "1" -> 5 times.
// "11" -> 3 times.
// "111" -> 1 time.```
//
// **Example 2:**
//
// ```
// Input: s = "101"
// Output: 2
// Explanation: Substring "1" is shown 2 times in s.
// ```
//
// **Example 3:**
//
// ```
// Input: s = "111111"
// Output: 21
// Explanation: Each substring contains only 1's characters.
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

class Solution {
  constexpr static int modulo = 1e9 + 7;

 public:
  int numSub(string s) {
    auto ans = 0;

    auto ones = 0;
    for (auto ch : s) {
      if (ch == '1') {
        ans = (ans + (++ones)) % modulo;
      } else {
        ones = 0;
      }
    }

    return ans;
  }
};
