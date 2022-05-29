# Source: https://leetcode.com/problems/longest-palindromic-substring/
# Title: Longest Palindromic Substring
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.
#
# Example 1:
#
#   Input: "babad"
#   Output: "bab"
#   Note: "aba" is also a valid answer.
#
# Example 2:
#
#   Input: "cbbd"
#   Output: "bb"
#
# Constraints:
#
#   1 <= s.length <= 1000
#   s consist of only digits and English letters.
#
################################################################################################################################

class Solution:
    def longestPalindrome(self, s: str) -> str:
        ans = ''
        n = len(s)
        for i in range(n):
            j = 0
            while i-j >= 0 and i+j < n:
                if s[i-j] == s[i+j]:
                    if 2*j+1 > len(ans):
                        ans = s[i-j:i+j+1]
                else:
                    break
                j += 1
        for i in range(n-1):
            if s[i] != s[i+1]:
                continue
            j = 0
            while i-j >= 0 and i+j+1 < n:
                if s[i-j] == s[i+j+1]:
                    if 2*j+2 > len(ans):
                        ans = s[i-j:i+j+2]
                else:
                    break
                j += 1
        return ans
