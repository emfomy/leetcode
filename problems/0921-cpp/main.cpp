// Source: https://leetcode.com/problems/minimum-add-to-make-parentheses-valid
// Title: Minimum Add to Make Parentheses Valid
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A parentheses string is valid if and only if:
//
// - It is the empty string,
// - It can be written as `AB` (`A` concatenated with `B`), where `A` and `B` are valid strings, or
// - It can be written as `(A)`, where `A` is a valid string.
//
// You are given a parentheses string `s`. In one move, you can insert a parenthesis at any position of the string.
//
// - For example, if `s = "()))"`, you can insert an opening parenthesis to be `"(**(**)))"` or a closing parenthesis to be `"())**)**)"`.
//
// Return the minimum number of moves required to make `s` valid.
//
// **Example 1:**
//
// ```
// Input: s = "())"
// Output: 1
// ```
//
// **Example 2:**
//
// ```
// Input: s = "((("
// Output: 3
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 1000`
// - `s[i]` is either `'('` or `')'`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>

using namespace std;

// Count
//
// Count the number of unclosed left parentheses.
// For each right parenthesis, decrease the count.
// If the count is already zero, then we need to add a left parenthesis.
//
// In the end, we also need to add the same number of right parentheses.
class Solution {
 public:
  int minAddToMakeValid(const string &s) {
    int ans = 0;
    int count = 0;
    for (char ch : s) {
      if (ch == '(') {
        ++count;
      } else {
        if (count == 0) {
          ++ans;
        } else {
          --count;
        }
      }
    }

    return ans + count;
  }
};
