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
#include <vector>

using namespace std;

// DP
//
// We use a stack to store the index of left parentheses.
// After each right parenthesis, pop the stack.
//
// Let DP[i]=j means [j, i) is the longest valid substring end at i.
//
// For each ')', if it is the end of a valid substring,
// then it must be either A() or `A((...))`, where A is a valid substring.
// For case (), use DP[i-1] to find the start of A.
// For case `A((...))`, first use DP[i]=j to find `A?(...))` (the index of '?' is j-1).
// '?' must be '(' in order to get a valid substring.
// And use DP[j-1] to find the start of A.
class Solution {
 public:
  int longestValidParentheses(const string& s) {
    const int n = s.size();

    auto dp = vector<int>(n + 1, 0);

    for (int i = 0; i < n; ++i) {
      dp[i + 1] = i + 1;
      if (i == 0 || s[i] == '(') {
        continue;
      }

      if (s[i - 1] == '(') {
        dp[i + 1] = dp[i - 1];
        continue;
      }

      int j = dp[i];
      if (j == 0 || s[j - 1] == ')') {
        continue;
      }
      dp[i + 1] = dp[j - 1];
    }

    // Find max
    int maxLen = 0;
    for (int i = 0; i <= n; ++i) {
      maxLen = max(maxLen, i - dp[i]);
    }

    return maxLen;
  }
};

// Stack
//
// We put the index each parenthesis in the stack.
// We also put the starting index `-1` into the stack as a sentinel.
//
// After each right parenthesis, pop the stack.
// If the stack become empty after popping (i.e. the sentinel is removed), we insert a new sentinel.
// Otherwise, the distance between current index and the top index is current valid substring.
class Solution2 {
 public:
  int longestValidParentheses(const string& s) {
    const int n = s.size();

    auto st = stack<int>();
    st.push(-1);  // sentinel

    int maxLen = 0;
    for (int i = 0; i < n; ++i) {
      // Push
      if (s[i] == '(') {
        st.push(i);
        continue;
      }

      // Pop
      st.pop();

      if (st.empty()) {
        st.push(i);  // new sentinel
        continue;
      }

      // Get length
      maxLen = max(maxLen, i - st.top());
    }

    return maxLen;
  }
};

// Two pass
class Solution3 {
 public:
  int longestValidParentheses(const string& s) {
    const int n = s.size();
    int maxLen = 0;

    // Loop
    {
      int left = 0, right = 0;
      for (int i = 0; i < n; ++i) {
        if (s[i] == '(') {
          ++left;
        } else {
          ++right;
        }

        if (left == right) {
          maxLen = max(maxLen, 2 * left);
        } else if (right > left) {
          left = 0, right = 0;
        }
      }
    }

    // Reverse loop
    {
      int left = 0, right = 0;
      for (int i = n - 1; i >= 0; --i) {
        if (s[i] == '(') {
          ++left;
        } else {
          ++right;
        }

        if (left == right) {
          maxLen = max(maxLen, 2 * left);
        } else if (right < left) {
          left = 0, right = 0;
        }
      }
    }

    return maxLen;
  }
};
