// Source: https://leetcode.com/problems/longest-valid-parentheses
// Title: Longest Valid Parentheses
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string containing just the characters `'('` and `')'`, return the length of the longest valid (well-formed) parentheses substring.
//
// **Example 1:**
//
// ```
// Input: s = "(()"
// Output: 2
// Explanation: The longest valid parentheses substring is "()".
// ```
//
// **Example 2:**
//
// ```
// Input: s = ")()())"
// Output: 4
// Explanation: The longest valid parentheses substring is "()()".
// ```
//
// **Example 3:**
//
// ```
// Input: s = ""
// Output: 0
// ```
//
// **Constraints:**
//
// - `0 <= s.length <= 3 * 10^4`
// - `s[i]` is `'('`, or `')'`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <stack>
#include <string>

using namespace std;

// Two pointer
//
// Scan from left to right.
// Whenever there are more right paren than left paren,
// we shrink the substring from the left.
//
// We also do the same again from right to left.
class Solution {
 public:
  int longestValidParentheses(const string& s) {
    const int n = s.size();

    // Left to right
    int ans = 0;
    int i = 0;     // [i, j]
    int diff = 0;  // left - right
    for (int j = 0; j < n; ++j) {
      diff += (s[j] == '(') ? 1 : -1;
      if (diff == 0) {
        ans = max(ans, j - i + 1);
      }
      while (diff < 0) {
        diff -= (s[i] == '(') ? 1 : -1;
        ++i;
      }
    }

    // Right to left
    i = n - 1;  // [i, j]
    diff = 0;   // right - left
    for (int j = n - 1; j >= 0; --j) {
      diff += (s[j] == ')') ? 1 : -1;
      if (diff == 0) {
        ans = max(ans, i - j + 1);
      }
      while (diff < 0) {
        diff -= (s[i] == ')') ? 1 : -1;
        --i;
      }
    }

    return ans;
  }
};
