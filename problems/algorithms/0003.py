# Source: https://leetcode.com/problems/longest-substring-without-repeating-characters/
# Title: Longest Substring Without Repeating Characters
# Difficulty: Medium

__author__  = 'Mu Yang <http://muyang.pro>'

################################################################################################################################
# Given a string, find the length of the longest substring without repeating characters.
#
# Example 1:
#
#   Input: "abcabcbb"
#   Output: 3
#   Explanation: The answer is "abc", with the length of 3.
#
# Example 2:
#
#   Input: "bbbbb"
#   Output: 1
#   Explanation: The answer is "b", with the length of 1.
#
# Example 3:
#
#   Input: "pwwkew"
#   Output: 3
#   Explanation: The answer is "wke", with the length of 3.
#                Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
#
################################################################################################################################

class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        pool = set()
        max_len = 0
        i = 0
        j = 0
        n = len(s)
        while j < n:
            if s[j] not in pool:
                pool.add(s[j])
                j += 1
                max_len = max(max_len, j-i)
            else:
                pool.remove(s[i])
                i += 1
        return max_len
