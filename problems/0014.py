# Source: https://leetcode.com/problems/longest-common-prefix
# Title: Longest Common Prefix
# Difficulty: Easy
# Author: Mu Yang <http://muyang.pro>
#
################################################################################################################################
# Write a function to find the longest common prefix string amongst an array of strings.
#
# If there is no common prefix, return an empty string `""`.
#
# **Example 1:**
#
# ```
# Input: strs = ["flower","flow","flight"]
# Output: "fl"
# ```
#
# **Example 2:**
#
# ```
# Input: strs = ["dog","racecar","car"]
# Output: ""
# Explanation: There is no common prefix among the input strings.
# ```
#
# **Constraints:**
#
# - `1 <= strs.length <= 200`
# - `0 <= strs[i].length <= 200`
# - `strs[i]` consists of only lowercase English letters if it is non-empty.
#
################################################################################################################################


from typing import List


class Solution:
    def longestCommonPrefix(self, strs: List[str]) -> str:
        size = 0

        for chs in zip(*strs):
            if any((ch != chs[0] for ch in chs)):
                break
            size += 1

        return strs[0][:size]
