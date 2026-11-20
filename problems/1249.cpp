// Source: https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses
// Title: Minimum Remove to Make Valid Parentheses
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a string s of `'('` , `')'` and lowercase English characters.
//
// Your task is to remove the minimum number of parentheses ( `'('` or `')'`, in any positions ) so that the resulting parentheses string is valid and return **any** valid string.
//
// Formally, a parentheses string is valid if and only if:
//
// - It is the empty string, contains only lowercase characters, or
// - It can be written as `AB` (`A` concatenated with `B`), where `A` and `B` are valid strings, or
// - It can be written as `(A)`, where `A` is a valid string.
//
// **Example 1:**
//
// ```
// Input: s = "lee(t(c)o)de)"
// Output: "lee(t(c)o)de"
// Explanation: "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.
// ```
//
// **Example 2:**
//
// ```
// Input: s = "a)b(c)d"
// Output: "ab(c)d"
// ```
//
// **Example 3:**
//
// ```
// Input: s = "))(("
// Output: ""
// Explanation: An empty string is also valid.
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 10^5`
// - `s[i]` is either`'('` , `')'`, or lowercase English letter.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stack>
#include <string>
#include <vector>

using namespace std;

// Stack
//
// Scan from left to right. Skip all english letters.
// For `(`, put its index into the stack.
// For `)`, pop the stack if possible.
// If the stack is empty, then we should delete this `)`.
// After the scan, delete all remaining `(` in the stack.
//
// We use a boolean array to mark deletions.
class Solution {
  using Bool = unsigned char;

 public:
  string minRemoveToMakeValid(const string &s) {
    const int n = s.size();

    // Loop
    auto st = stack<int>();      // indices of `(`
    auto del = vector<Bool>(n);  // delete indices
    for (int i = 0; i < n; ++i) {
      if (s[i] == '(') {
        st.push(i);
        continue;
      }

      if (s[i] == ')') {
        if (!st.empty()) {
          st.pop();
        } else {
          del[i] = true;
        }
      }
    }

    // Clear stack
    while (!st.empty()) {
      del[st.top()] = true;
      st.pop();
    }

    // Answer
    string ans;
    ans.reserve(n);
    for (int i = 0; i < n; ++i) {
      if (!del[i]) ans.push_back(s[i]);
    }

    return ans;
  }
};
