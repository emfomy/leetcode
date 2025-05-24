# Source: https://leetcode.com/problems/longest-common-prefix
# Title: Longest Common Prefix
# Difficulty: Easy
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Write a function to find the longest common prefix string amongst an array of strings.
#
# If there is no common prefix, return an empty string "".
#
# Example 1:
#
#   Input: ["flower","flow","flight"]
#   Output: "fl"
#
# Example 2:
#
#   Input: ["dog","racecar","car"]
#   Output: ""
#   Explanation: There is no common prefix among the input strings.
#
# Note:
#
#   All given inputs are in lowercase letters a-z.
#
################################################################################################################################

class Solution:
    def longestCommonPrefix(self, strs: List[str]) -> str:
        ans = ''
        for cs in zip(*strs):
            if any(c != cs[0] for c in cs[1:]):
                break
            ans += cs[0]
        return ans
