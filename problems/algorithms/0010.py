# Source: https://leetcode.com/problems/regular-expression-matching/
# Title: Regular Expression Matching
# Difficulty: Hard
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*'.
#
# '.' Matches any single character.
# '*' Matches zero or more of the preceding element.
# The matching should cover the entire input string (not partial).
#
# Note:
#
#    s could be empty and contains only lowercase letters a-z.
#    p could be empty and contains only lowercase letters a-z, and characters like . or *.
#
# Example 1:
#
#   Input:
#   s = "aa"
#   p = "a"
#   Output: false
#   Explanation: "a" does not match the entire string "aa".
#
# Example 2:
#
#   Input:
#   s = "aa"
#   p = "a*"
#   Output: true
#   Explanation: '*' means zero or more of the preceding element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".
#
# Example 3:
#
#   Input:
#   s = "ab"
#   p = ".*"
#   Output: true
#   Explanation: ".*" means "zero or more (*) of any character (.)".
#
# Example 4:
#
#   Input:
#   s = "aab"
#   p = "c*a*b"
#   Output: true
#   Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore, it matches "aab".
#
# Example 5:
#
#   Input:
#   s = "mississippi"
#   p = "mis*is*p*."
#   Output: false
#
################################################################################################################################

class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        print(s, '|', p, sep='\t\t')
        if not p: # no pattern
            return not s

        pc = p[-1]
        if pc == '*': # multiple
            pc = p[-2]
            if self.isMatch(s, p[:-2]): # no char
                return True
            if not s:
                return False
            if pc == '.' or pc == s[-1]:
                return self.isMatch(s[:-1], p)
        else: # single
            if not s:
                return False
            if pc == '.' or pc == s[-1]:
                return self.isMatch(s[:-1], p[:-1])
        return False

################################################################################################################################

import re

class Solution2:
    def isMatch(self, s: str, p: str) -> bool:
        return bool(re.match(fr'^{p}$', s))
