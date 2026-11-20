// Source: https://leetcode.com/problems/score-of-parentheses
// Title: Score of Parentheses
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a balanced parentheses string `s`, return the **score** of the string.
//
// The **score** of a balanced parentheses string is based on the following rule:
//
// - `"()"` has score `1`.
// - `AB` has score `A + B`, where `A` and `B` are balanced parentheses strings.
// - `(A)` has score `2 * A`, where `A` is a balanced parentheses string.
//
// **Example 1:**
//
// ```
// Input: s = "()"
// Output: 1
// ```
//
// **Example 2:**
//
// ```
// Input: s = "(())"
// Output: 2
// ```
//
// **Example 3:**
//
// ```
// Input: s = "()()"
// Output: 2
// ```
//
// **Constraints:**
//
// - `2 <= s.length <= 50`
// - `s` consists of only `'('` and `')'`.
// - `s` is a balanced parentheses string.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stack>
#include <string>

using namespace std;

// Stack
//
// We use stack to store the score of each depth.
//
// When encounter `(`, push the stack with empty score.
// When encounter `)`, pop the stack, double it, and add to to its parent.
// However, if the top is empty, then add 1 instead.
class Solution {
 public:
  int scoreOfParentheses(const string &s) {
    auto st = stack<int>();
    st.push(0);

    for (const char ch : s) {
      if (ch == '(') {
        st.push(0);
      } else {
        int top = st.top();
        st.pop();
        st.top() += (top != 0) ? 2 * top : 1;
      }
    }

    return st.top();
  }
};

// Counter
//
// Only `()` gives scores. Each gives a score equal to 2^depth.
class Solution2 {
 public:
  int scoreOfParentheses(const string &s) {
    const int n = s.size();
    int score = 0, depth = 0;

    for (int i = 0; i < n; ++i) {
      if (s[i] == '(') {
        ++depth;
      } else {
        --depth;
        if (s[i - 1] == '(') {  // found ()
          score += 1 << depth;
        }
      }
    }

    return score;
  }
};
