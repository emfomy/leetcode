// Source: https://leetcode.com/problems/minimum-insertions-to-balance-a-parentheses-string
// Title: Minimum Insertions to Balance a Parentheses String
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a parentheses string `s` containing only the characters `'('` and `')'`. A parentheses string is **balanced** if:
//
// - Any left parenthesis `'('` must have a corresponding two consecutive right parenthesis `'))'`.
// - Left parenthesis `'('` must go before the corresponding two consecutive right parenthesis `'))'`.
//
// In other words, we treat `'('` as an opening parenthesis and `'))'` as a closing parenthesis.
//
// - For example, `"())"`, `"())(())))"` and `"(())())))"` are balanced, `")()"`, `"()))"` and `"(()))"` are not balanced.
//
// You can insert the characters `'('` and `')'` at any position of the string to balance it if needed.
//
// Return the minimum number of insertions needed to make `s` balanced.
//
// **Example 1:**
//
// ```
// Input: s = "(()))"
// Output: 1
// Explanation: The second '(' has two matching '))', but the first '(' has only ')' matching. We need to add one more ')' at the end of the string to be "(())))" which is balanced.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "())"
// Output: 0
// Explanation: The string is already balanced.
// ```
//
// **Example 3:**
//
// ```
// Input: s = "))())("
// Output: 3
// Explanation: Add '(' to match the first '))', Add '))' to match the last '('.
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 10^5`
// - `s` consists of `'('` and `')'` only.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>

using namespace std;

// Count
//
// Tracking the score.
// Open has 2 scores, close has -1 score.
// When score is negative, insert an open.
// When encounter odd close, insert a close
class Solution {
 public:
  int minInsertions(const string &s) {
    int ans = 0, score = 0, close = 0;
    for (const char ch : s) {
      if (ch == '(') {
        score += 2;
        if (close % 2) {
          ++ans;  // insert )
          --score;
          close = 0;
        }
      } else {
        --score;
        ++close;
      }

      if (score < 0) {
        ++ans;  // insert (
        score += 2;
      }
    }
    ans += score;  // insert )

    return ans;
  }
};
