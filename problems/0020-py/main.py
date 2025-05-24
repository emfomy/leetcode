# Source: https://leetcode.com/problems/valid-parentheses
# Title: Valid Parentheses
# Difficulty: Easy
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
#
# An input string is valid if:
#
# 1. Open brackets must be closed by the same type of brackets.
# 2. Open brackets must be closed in the correct order.
#
# Note that an empty string is also considered valid.
#
# Example 1:
#
#   Input: "()"
#   Output: true
#
# Example 2:
#
#   Input: "()[]{}"
#   Output: true
#
# Example 3:
#
#   Input: "(]"
#   Output: false
#
# Example 4:
#
#   Input: "([)]"
#   Output: false
#
# Example 5:
#
#   Input: "{[]}"
#   Output: true
#
################################################################################################################################

BRACK_MAP = {
    '(': ')',
    '[': ']',
    '{': '}',
}

class Solution:
    def isValid(self, s: str) -> bool:
        stack = []
        for c in s:
            if c in BRACK_MAP:
                stack.append(BRACK_MAP[c])
            else:
                if not stack:
                    return False
                if c != stack.pop():
                    return False
        return not stack
