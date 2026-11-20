# Source: https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string
# Title: Find the Index of the First Occurrence in a String
# Difficulty: Easy
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given two strings `needle` and `haystack`, return the index of the first occurrence of `needle` in `haystack`, or `-1` if `needle` is not part of `haystack`.
#
# **Example 1:**
#
# ```
# Input: haystack = "sadbutsad", needle = "sad"
# Output: 0
# Explanation: "sad" occurs at index 0 and 6.
# The first occurrence is at index 0, so we return 0.
# ```
#
# **Example 2:**
#
# ```
# Input: haystack = "leetcode", needle = "leeto"
# Output: -1
# Explanation: "leeto" did not occur in "leetcode", so we return -1.
# ```
#
# **Constraints:**
#
# - `1 <= haystack.length, needle.length <= 10^4`
# - `haystack` and `needle` consist of only lowercase English characters.
#
################################################################################################################################


class Solution:
    def strStr(self, haystack: str, needle: str) -> int:
        return haystack.find(needle)


# Naive
class Solution:
    def strStr(self, haystack: str, needle: str) -> int:
        n = len(haystack)
        m = len(needle)
        if n < m:
            return -1

        for i in range(n - m + 1):
            if haystack[i : i + m] == needle:
                return i
        return -1


# Rabin-Karp Algorithm
#
# Use char sum as hash
class Solution:
    def strStr(self, haystack: str, needle: str) -> int:
        n = len(haystack)
        m = len(needle)
        if n < m:
            return -1

        needle_hash = sum((ord(ch) for ch in needle))
        curr_hash = sum((ord(ch) for ch in haystack[: m - 1]))

        for i in range(n - m + 1):
            curr_hash += ord(haystack[i + m - 1])
            if curr_hash == needle_hash:
                if haystack[i : i + m] == needle:
                    return i
            curr_hash -= ord(haystack[i])
        return -1


# KMP Algorithm
class Solution:
    def strStr(self, haystack: str, needle: str) -> int:
        n = len(haystack)
        m = len(needle)
        if n < m:
            return -1

        # LPS
        lps = [0] * m
        i, j = 1, 0
        while i < m:
            if needle[i] == needle[j]:
                j += 1
                lps[i] = j
                i += 1
            elif j > 0:
                j = lps[j - 1]
            else:
                lps[i] = 0
                i += 1

        # Search
        i, j = 0, 0
        while i < n:
            if haystack[i] == needle[j]:
                i += 1
                j += 1
                if j == m:
                    return i - m
            elif j > 0:
                j = lps[j - 1]
            else:
                i += 1

        return -1
