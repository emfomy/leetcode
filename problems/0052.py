# Source: https://leetcode.com/problems/n-queens-ii
# Title: N-Queens II
# Difficulty: Hard
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# The **n-queens** puzzle is the problem of placing `n` queens on an `n x n` chessboard such that no two queens attack each other.
#
# Given an integer `n`, return the number of distinct solutions to the**n-queens puzzle**.
#
# **Example 1:**
# https://assets.leetcode.com/uploads/2020/11/13/queens.jpg
#
# ```
# Input: n = 4
# Output: 2
# Explanation: There are two distinct solutions to the 4-queens puzzle as shown.
# ```
#
# **Example 2:**
#
# ```
# Input: n = 1
# Output: 1
# ```
#
# **Constraints:**
#
# - `1 <= n <= 9`
#
################################################################################################################################


class Solution:
    def totalNQueens(self, n: int) -> int:
        def dfs(*queens: int) -> int:
            if len(queens) == n:
                return 1

            ans = 0
            j = len(queens)
            for qj in range(n):
                if all(
                    qj != qi and qj - qi != j - i and qi - qj != j - i
                    for i, qi in enumerate(queens)
                ):
                    ans += dfs(*queens, qj)

            return ans

        return dfs()
