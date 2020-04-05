# Source: https://leetcode.com/problems/reverse-integer/
# Title: Reverse Integer
# Difficulty: Easy
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given a 32-bit signed integer, reverse digits of an integer.
#
# Example 1:
#
#   Input: 123
#   Output: 321
#
# Example 2:
#
#   Input: -123
#   Output: -321
#
# Example 3:
#
#   Input: 120
#   Output: 21
#
# Note:
#   Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−2^31,  2^31 − 1]. For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.
################################################################################################################################

INT_MAX = 2**31-1
INT_MIN = -2**31

class Solution:
    def reverse(self, x: int) -> int:
        if x >= 0:
            ans = int(str(x)[::-1])
            return ans if ans < INT_MAX else 0
        else:
            ans = -int(str(-x)[::-1])
            return ans if ans > INT_MIN else 0
