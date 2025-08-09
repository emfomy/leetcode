# Source: https://leetcode.com/problems/sqrtx
# Title: Sqrt(x)
# Difficulty: Easy
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given a non-negative integer `x`, return the square root of `x` rounded down to the nearest integer. The returned integer should be **non-negative** as well.
#
# You **must not use** any built-in exponent function or operator.
#
# - For example, do not use `pow(x, 0.5)` in c++ or `x ** 0.5` in python.
#
# **Example 1:**
#
# ```
# Input: x = 4
# Output: 2
# Explanation: The square root of 4 is 2, so we return 2.
# ```
#
# **Example 2:**
#
# ```
# Input: x = 8
# Output: 2
# Explanation: The square root of 8 is 2.82842..., and since we round it down to the nearest integer, 2 is returned.
# ```
#
# **Constraints:**
#
# - `0 <= x <= 2^31 - 1`
#
################################################################################################################################


# Binary search
class Solution:
    def mySqrt(self, x: int) -> int:
        # check(lo-1)=false, check(lo=hi)=true
        lo, hi = 0, (2 << 16)
        while lo < hi:
            mid = lo + (hi - lo) // 2
            if mid * mid > x:
                hi = mid
            else:
                lo = mid + 1

        return lo - 1
