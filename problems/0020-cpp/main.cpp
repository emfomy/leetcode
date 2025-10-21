// Source: https://leetcode.com/problems/valid-parentheses
// Title: Valid Parentheses
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string `s` containing just the characters `'('`, `')'`, `'{'`, `'}'`, `'['` and `']'`, determine if the input string is valid.
//
// An input string is valid if:
//
// - Open brackets must be closed by the same type of brackets.
// - Open brackets must be closed in the correct order.
// - Every close bracket has a corresponding open bracket of the same type.
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
// Input: s = "()[]{}"
// Output: true
// ```
//
// **Example 3:**
//
// ```
// Input: s = "(]"
// Output: false
// ```
//
// **Example 4:**
//
// ```
// Input: s = "([])"
// Output: true
// ```
//
// **Example 5:**
//
// ```
// Input: s = "([)]"
// Output: false
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 10^4`
// - `s` consists of parentheses only `'()[]{}'`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stack>
#include <string>
#include <unordered_map>

using namespace std;

// Use stack
class Solution {
 public:
  bool isValid(string s) {
    static const unordered_map<char, char> parenMap = {{'(', ')'}, {'[', ']'}, {'{', '}'}};

    auto st = stack<int>();
    st.push(' ');  // push empty char to avoid null check on stack.

    for (auto ch : s) {
      switch (ch) {
        case '(':
        case '[':
        case '{':
          st.push(parenMap.at(ch));
          break;
        case ')':
        case ']':
        case '}':
          if (st.top() != ch) return false;
          st.pop();
          break;
      }
    }

    return st.size() == 1;
  }
};
