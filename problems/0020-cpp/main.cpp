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

#include <string>
#include <vector>

using namespace std;

// Use stack
class Solution {
  constexpr static char match[128] = {
      [')'] = '(',
      [']'] = '[',
      ['}'] = '{',
  };

 public:
  bool isValid(const string &s) {
    const int n = s.size();

    auto st = vector<char>();
    st.reserve(n);

    for (char ch : s) {
      switch (ch) {
        case '(':
        case '[':
        case '{': {
          st.push_back(ch);
          break;
        }
        case ')':
        case ']':
        case '}': {
          if (st.empty() || st.back() != match[ch]) return false;
          st.pop_back();
          break;
        }
        default:
          return false;
      }
    }

    return st.empty();
  }
};
