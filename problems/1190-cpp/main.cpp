// Source: https://leetcode.com/problems/reverse-substrings-between-each-pair-of-parentheses
// Title: Reverse Substrings Between Each Pair of Parentheses
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given a string `s` that consists of lower case English letters and brackets.
//
// Reverse the strings in each pair of matching parentheses, starting from the innermost one.
//
// Your result should **not** contain any brackets.
//
// **Example 1:**
//
// ```
// Input: s = "(abcd)"
// Output: "dcba"
// ```
//
// **Example 2:**
//
// ```
// Input: s = "(u(love)i)"
// Output: "iloveu"
// Explanation: The substring "love" is reversed first, then the whole string is reversed.
// ```
//
// **Example 3:**
//
// ```
// Input: s = "(ed(et(oc))el)"
// Output: "leetcode"
// Explanation: First, we reverse the substring "oc", then "etco", and finally, the whole string.
// ```
//
// **Constraints:**
//
// - `1 <= s.length <= 2000`
// - `s` only contains lower case English characters and parentheses.
// - It is guaranteed that all parentheses are balanced.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <stack>
#include <vector>

using namespace std;

class Solution {
 public:
  string reverseParentheses(string &s) {
    const int n = s.size();

    // Find parens
    auto st = stack<int>();
    for (int i = 0; i < n; ++i) {
      if (s[i] == '(') {
        st.push(i);
        continue;
      }

      if (s[i] == ')') {
        // Reverse
        reverse(s.begin() + st.top() + 1, s.begin() + i);
        st.pop();
      }
    }

    // Remove parens
    string ans;
    ans.reserve(n);
    for (int i = 0; i < n; ++i) {
      if (s[i] != '(' && s[i] != ')') ans.push_back(s[i]);
    }

    return ans;
  }
};

class Solution2 {
 public:
  string reverseParentheses(const string &s) {
    const int n = s.size();

    // Find parens
    auto parenMap = vector<int>(n);  // maps left to right and vice versa
    auto st = stack<int>();
    for (int i = 0; i < n; ++i) {
      if (s[i] == '(') {
        st.push(i);
        continue;
      }

      if (s[i] == ')') {
        parenMap[i] = st.top();
        parenMap[st.top()] = i;
        st.pop();
      }
    }

    // Construct
    string ans;
    ans.reserve(n);
    int i = 0, dir = 1;
    while (i < n) {
      if (s[i] == '(' || s[i] == ')') {  // jump to corresponding paren
        i = parenMap[i];
        dir = -dir;
      } else {
        ans.push_back(s[i]);
      }
      i += dir;
    }

    return ans;
  }
};
