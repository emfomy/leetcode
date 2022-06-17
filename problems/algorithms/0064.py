# Source: https://leetcode.com/problems/minimum-path-sum/
# Title: Minimum Path Sum
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right, which minimizes the sum of all numbers along its path.
#
# Note: You can only move either down or right at any point in time.
#
# Example 1:
#
#   https://assets.leetcode.com/uploads/2020/11/05/minpath.jpg
#   Input: grid = [[1,3,1],[1,5,1],[4,2,1]]
#   Output: 7
#   Explanation: Because the path 1 → 3 → 1 → 1 → 1 minimizes the sum.
#
# Example 2:
#
#   Input: grid = [[1,2,3],[4,5,6]]
#   Output: 12
#
# Constraints:
#
#   m == grid.length
#   n == grid[i].length
#   1 <= m, n <= 200
#   0 <= grid[i][j] <= 100
#
################################################################################################################################

class Solution:
    def minPathSum(self, grid: List[List[int]]) -> int:
        m = len(grid)
        n = len(grid[0])

        # Create buffer
        tmp = [None]*m
        for i in range(m):
            tmp[i] = [0]*n

        tmp[0][0] = grid[0][0]
        for i in range(1, m):
            tmp[i][0] = tmp[i-1][0] + grid[i][0]
        for j in range(1, n):
            tmp[0][j] = tmp[0][j-1] + grid[0][j]


        for i in range(1, m):
            for j in range(1, n):
                tmp[i][j] = min(tmp[i-1][j], tmp[i][j-1]) + grid[i][j]

        return tmp[-1][-1]
