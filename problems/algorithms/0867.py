# Source: https://leetcode.com/problems/transpose-matrix/
# Title: Transpose Matrix
# Difficulty: Easy
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given a 2D integer array matrix, return the transpose of matrix.
#
# The transpose of a matrix is the matrix flipped over its main diagonal, switching the matrix's row and column indices.
#
# Example 1:
#
#   Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
#   Output: [[1,4,7],[2,5,8],[3,6,9]]
#
# Example 2:
#
#   Input: matrix = [[1,2,3],[4,5,6]]
#   Output: [[1,4],[2,5],[3,6]]
#
# Constraints:
#
#   m == matrix.length
#   n == matrix[i].length
#   1 <= m, n <= 1000
#   1 <= m * n <= 10^5
#   -10^9 <= matrix[i][j] <= 10^9
#
################################################################################################################################

from typing import *

class Solution:
    def transpose(self, matrix: List[List[int]]) -> List[List[int]]:
        m = len(matrix)
        n = len(matrix[0])

        res = [[0] * m for _ in range(n)]

        for i, row in enumerate(matrix):
            for j, v in enumerate(row):
                res[j][i] = v

        return res

class Solution2:
    def transpose(self, matrix: List[List[int]]) -> List[List[int]]:
        return (col for col in zip(*matrix))
