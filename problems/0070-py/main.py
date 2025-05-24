# Source: https://leetcode.com/problems/climbing-stairs
# Title: Climbing Stairs
# Difficulty: Easy
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# You are climbing a stair case. It takes n steps to reach to the top.
#
# Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
#
# Example 1:
#
#   Input: 2
#   Output: 2
#   Explanation: There are two ways to climb to the top.
#   1. 1 step + 1 step
#   2. 2 steps
#
# Example 2:
#
#   Input: 3
#   Output: 3
#   Explanation: There are three ways to climb to the top.
#   1. 1 step + 1 step + 1 step
#   2. 1 step + 2 steps
#   3. 2 steps + 1 step
#
# Constraints:
#
#   1 <= n <= 45
#
################################################################################################################################

from math import sqrt, pow
SQRT5 = sqrt(5.0)
PHI = (1+SQRT5)/2

class Solution:
    """Find (n+1)th Fibonacci number"""
    def climbStairs(self, n: int) -> int:
        return int(pow(PHI, n+1)/SQRT5+.5)

################################################################################################################################

class Solution2:
    """Find (n+1)th Fibonacci number"""
    def climbStairs(self, n: int) -> int:

        a = b = 1
        for i in range(n-1):
            a, b = a+b, a
        return a

################################################################################################################################

# Python 3.8+
# from math import comb
class Solution3:
    def climbStairs(self, n: int) -> int:

        ans = 0
        for n2 in range(n//2+1):  # num(2)
            m = n - n2  # num(1) + num(2)
            ans += comb(m, n2)

        return ans
