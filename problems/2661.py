# Source: https://leetcode.com/problems/first-completely-painted-row-or-column
# Title: First Completely Painted Row or Column
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# You are given a **0-indexed** integer array `arr`, and an `m x n` integer **matrix** `mat`. `arr` and `mat` both contain **all** the integers in the range `[1, m * n]`.
#
# Go through each index `i` in `arr` starting from index `0` and paint the cell in `mat` containing the integer `arr[i]`.
#
# Return the smallest index `i` at which either a row or a column will be completely painted in `mat`.
#
# **Example 1:**
# https://assets.leetcode.com/uploads/2023/01/18/grid1.jpg
#
# ```
# Input: arr = [1,3,4,2], mat = [[1,4],[2,3]]
# Output: 2
# Explanation: The moves are shown in order, and both the first row and second column of the matrix become fully painted at arr[2].
# ```
#
# **Example 2:**
# https://assets.leetcode.com/uploads/2023/01/18/grid2.jpg
#
# ```
# Input: arr = [2,8,7,4,1,3,5,6,9], mat = [[3,2,5],[1,4,6],[8,7,9]]
# Output: 3
# Explanation: The second column becomes fully painted at arr[3].
# ```
#
# **Constraints:**
#
# - `m == mat.length`
# - `n = mat[i].length`
# - `arr.length == m * n`
# - `1 <= m, n <= 10^5`
# - `1 <= m * n <= 10^5`
# - `1 <= arr[i], mat[r][c] <= m * n`
# - All the integers of `arr` are **unique**.
# - All the integers of `mat` are **unique**.
#
################################################################################################################################


class Solution:
    def firstCompleteIndex(self, arr: list[int], mat: list[list[int]]) -> int:
        m, n = len(mat), len(mat[0])
        rowMap = {num: i for i, row in enumerate(mat) for num in row}
        colMap = {num: j for row in mat for j, num in enumerate(row)}

        rowCount = [0] * m
        colCount = [0] * n
        for idx, num in enumerate(arr):
            rowCount[rowMap[num]] += 1
            colCount[colMap[num]] += 1
            if rowCount[rowMap[num]] == n or colCount[colMap[num]] == m:
                return idx
        return -1


class Solution2:
    def firstCompleteIndex(self, arr: list[int], mat: list[list[int]]) -> int:
        m, n = len(mat), len(mat[0])
        idxMap = {num: idx for idx, num in enumerate(arr)}

        return min(
            min(
                (  # first finished row
                    max((idxMap[mat[i][j]] for j in range(n)))  # last index of row
                    for i in range(m)
                )
            ),
            min(
                (  # first finished column
                    max((idxMap[mat[i][j]] for i in range(m)))  # last index of column
                    for j in range(n)
                )
            ),
        )
