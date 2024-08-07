# Source: https://leetcode.com/problems/roman-to-integer
# Title: Roman to Integer
# Difficulty: Easy
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.
#
#   Symbol       Value
#   I             1
#   V             5
#   X             10
#   L             50
#   C             100
#   D             500
#   M             1000
#
# For example, two is written as II in Roman numeral, just two one's added together. Twelve is written as, XII, which is simply X + II. The number twenty seven is written as XXVII, which is XX + V + II.
#
# Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not IIII. Instead, the number four is written as IV. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as IX. There are six instances where subtraction is used:
#
# - I can be placed before V (5) and X (10) to make 4 and 9.
# - X can be placed before L (50) and C (100) to make 40 and 90.
# - C can be placed before D (500) and M (1000) to make 400 and 900.
#
# Given a roman numeral, convert it to an integer. Input is guaranteed to be within the range from 1 to 3999.
#
# Example 1:
#
#   Input: "III"
#   Output: 3
#
# Example 2:
#
#   Input: "IV"
#   Output: 4
#
# Example 3:
#
#   Input: "IX"
#   Output: 9
#
# Constraints:
#
#   1 <= s.length <= 15
#   s contains only the characters ('I', 'V', 'X', 'L', 'C', 'D', 'M').
#   It is guaranteed that s is a valid roman numeral in the range [1, 3999].
#
################################################################################################################################

ROMANS = {
    'I': 1,
    'V': 5,
    'X': 10,
    'L': 50,
    'C': 100,
    'D': 500,
    'M': 1000,
}

class Solution:
    def romanToInt(self, s: str) -> int:
        l = map(ROMANS.get, s)
        ans = 0
        cur = next(l)
        for nxt in l:
            if cur < nxt:
                ans -= cur
            else:
                ans += cur
            cur = nxt
        ans += cur
        return ans

class Solution2:
    def romanToInt(self, s: str) -> int:
        ans = 0
        cur = ROMANS[s[0]]
        for c in s[1:]:
            nxt = romans[c]
            if cur < nxt:
                ans -= cur
            else:
                ans += cur
            cur = nxt
        ans += cur
        return ans
