# Source: https://leetcode.com/problems/longest-valid-parentheses
# Title: Longest Valid Parentheses
# Difficulty: Hard
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.
#
# Example 1:
#
#   Input: "(()"
#   Output: 2
#   Explanation: The longest valid parentheses substring is "()"
#
# Example 2:
#
#   Input: ")()())"
#   Output: 4
#   Explanation: The longest valid parentheses substring is "()()"
#
################################################################################################################################

class Solution:
    def longestValidParentheses(self, s: str) -> int:
        return max(
            self.longestValidParenthesesInner(s, d=1),
            self.longestValidParenthesesInner(s, d=-1),
        )

    def longestValidParenthesesInner(self, s, d=1):
        val = 0
        min_idx = 0
        min_val = 0
        max_len = 0

        for i, c in enumerate(s[::d], 1):
            if c == '(':
                val += d
            else:
                val -= d
            if val < min_val:
                min_val = val
                min_idx = i
            elif val == min_val:
                max_len = max(max_len, i-min_idx)
        return max_len
