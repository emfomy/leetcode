// Source: https://leetcode.com/problems/valid-parenthesis-string
// Title: Valid Parenthesis String
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string `s` containing only three types of characters: `'('`, `')'` and `'*'`, return `true` if `s` is **valid**.
//
// The following rules define a **valid** string:
//
// - Any left parenthesis `'('` must have a corresponding right parenthesis `')'`.
// - Any right parenthesis `')'` must have a corresponding left parenthesis `'('`.
// - Left parenthesis `'('` must go before the corresponding right parenthesis `')'`.
// - `'*'` could be treated as a single right parenthesis `')'` or a single left parenthesis `'('` or an empty string `""`.
//
// **Example 1:**
//
// ```
// Input: s = "()"
// Output: true
// ```
//
// **Example 2:**
//
// ```
// Input: s = "(*)"
// Output: true
// ```
//
// **Example 3:**
//
// ```
// Input: s = "(*))"
// Output: true
// ```
//
// **Example 4:**
//
// ```
// Input: s = "("
// Output: false
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 100`
// - `s[i]` is `'('`, `')'` or `'*'`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <string>

using namespace std;

// Greedy
//
// Assume that s is a valid string.
// We assign each letter a depth value.
// Note that the depth must be positive.
// It is clear that s is valid iff the depth is all positive, and start/end with zero.
//
// Assume that s contains star.
// Say there are star at i and j, i < j, s[i] converts to close, s[j] converts to open.
// Note that i/j are not start/end.
// Now reassign s[i] to open and s[j] to close, then depth of [i, j] increases by 2.
// The new string is still valid since the depth is still positive,
// and the start/end does not change.
//
// Using above idea, we can convert star at the left to open, and star at the right to close.
class Solution {
 public:
  bool checkValidString(const string &s) {
    const int n = s.size();
    bool hasEmpty = n % 2;

    // Count
    int open = count(s.cbegin(), s.cend(), '(');
    int close = count(s.cbegin(), s.cend(), ')');
    if (open > n / 2 || close > n / 2) return false;

    // Greedy
    int depth = 0;
    for (char ch : s) {
      if (ch == '*') {
        if (open < n / 2) {
          ch = '(';
          ++open;
        } else if (hasEmpty) {
          hasEmpty = false;
          continue;  // skip empty letter
        } else {
          ch = ')';
        }
      }
      depth += (ch == '(') ? 1 : -1;
      if (depth < 0) return false;
    }

    return depth == 0;
  }
};

// Greedy
//
// Using the same depth idea.
//
// First we loop from left to right, assuming all star are open.
// We will overestimate the depth.
// However, if there the depth become negative (i.e. too many close), then it must be invalid.
//
// Next loop from right to left, assuming all star are close.
//
// If both loop passed, then it must be valid.
// (We can convert star at the left to open, and star at the right to close).
class Solution2 {
 public:
  bool checkValidString(const string &s) {
    const int n = s.size();

    // Left to right
    {
      int depth = 0;
      for (int i = 0; i < n; ++i) {
        depth += (s[i] != ')') ? 1 : -1;
        if (depth < 0) return false;
      }
    }

    // Right to left
    {
      int depth = 0;
      for (int i = n - 1; i >= 0; --i) {
        depth += (s[i] != '(') ? 1 : -1;
        if (depth < 0) return false;
      }
    }

    return true;
  }
};
