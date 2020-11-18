# Source: https://leetcode.com/problems/unique-paths/
# Title: Unique Paths
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
#
# The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).
#
# How many possible unique paths are there?
#
# Example 1:
#
#   Input: m = 3, n = 7
#   Output: 28
#
# Example 2:
#
#   Input: m = 3, n = 2
#   Output: 3
#   Explanation:
#   From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
#   1. Right -> Down -> Down
#   2. Down -> Down -> Right
#   3. Down -> Right -> Down
#
# Example 3:
#
#   Input: m = 7, n = 3
#   Output: 28
#
# Example 4:
#
#   Input: m = 3, n = 3
#   Output: 6
#
# Constraints:
#
#   1 <= m, n <= 100
#   It's guaranteed that the answer will be less than or equal to 2 * 10^9.
#
################################################################################################################################

# Python 3.8+
from math import comb
class Solution:
    def uniquePaths(self, m: int, n: int) -> int:
        return comb(m+n-2, m-1)

################################################################################################################################

class Solution:
    def uniquePaths(self, m: int, n: int) -> int:
        res = 1
        if m > n:
            m, n = n, m
        m -= 1
        n -= 1

        # C^{m+n}_m
        for i in range(m):
            res *= n+m-i
            res /= (i+1)

        return int(res)
