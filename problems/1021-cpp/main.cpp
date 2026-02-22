// Source: https://leetcode.com/problems/remove-outermost-parentheses
// Title: Remove Outermost Parentheses
// Difficulty: Easy
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A valid parentheses string is either empty `""`, `"(" + A + ")"`, or `A + B`, where `A` and `B` are valid parentheses strings, and `+` represents string concatenation.
//
// - For example, `""`, `"()"`, `"(())()"`, and `"(()(()))"` are all valid parentheses strings.
//
// A valid parentheses string `s` is primitive if it is nonempty, and there does not exist a way to split it into `s = A + B`, with `A` and `B` nonempty valid parentheses strings.
//
// Given a valid parentheses string `s`, consider its primitive decomposition: `s = P_1 + P_2 + ... + P_k`, where `P_i` are primitive valid parentheses strings.
//
// Return `s` after removing the outermost parentheses of every primitive string in the primitive decomposition of `s`.
//
// **Example 1:**
//
// ```
// Input: s = "(()())(())"
// Output: "()()()"
// Explanation:
// The input string is "(()())(())", with primitive decomposition "(()())" + "(())".
// After removing outer parentheses of each part, this is "()()" + "()" = "()()()".
// ```
//
// **Example 2:**
//
// ```
// Input: s = "(()())(())(()(()))"
// Output: "()()()()(())"
// Explanation:
// The input string is "(()())(())(()(()))", with primitive decomposition "(()())" + "(())" + "(()(()))".
// After removing outer parentheses of each part, this is "()()" + "()" + "()(())" = "()()()()(())".
// ```
//
// **Example 3:**
//
// ```
// Input: s = "()()"
// Output: ""
// Explanation:
// The input string is "()()", with primitive decomposition "()" + "()".
// After removing outer parentheses of each part, this is "" + "" = "".
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 10^5`
// - `s[i]` is either `'('` or `')'`.
// - `s` is a valid parentheses string.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <string_view>

using namespace std;

// Counter
class Solution {
 public:
  string removeOuterParentheses(const string_view &s) {
    const int n = s.size();

    if (n == 0) return "";

    // Prepare ans
    string ans;
    ans.reserve(n);

    // Prepare counter
    int counter = 0;
    int prevIdx = 0;
    for (int i = 1; i <= n; ++i) {  // end index
      counter += (s[i - 1] == '(') ? 1 : -1;
      if (counter == 0) {
        ans += s.substr(prevIdx + 1, i - prevIdx - 2);
        prevIdx = i;
      }
    }

    // Counter must be 0 at the end since s is valid

    return ans;
  }
};
