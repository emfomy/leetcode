# Source: https://leetcode.com/problems/rotate-image/
# Title: Rotate Image
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).
#
# You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.
#
# Example 1:
#
#   Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
#   Output: [[7,4,1],[8,5,2],[9,6,3]]
#
# Example 2:
#
#   Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
#   Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
#
# Example 3:
#
#   Input: matrix = [[1]]
#   Output: [[1]]
#
# Example 4:
#
#   Input: matrix = [[1,2],[3,4]]
#   Output: [[3,1],[4,2]]
#
# Constraints:
#
#   matrix.length == n
#   matrix[i].length == n
#   1 <= n <= 20
#   -1000 <= matrix[i][j] <= 1000
#
################################################################################################################################

class Solution:
    def rotate(self, matrix: List[List[int]]) -> None:
        """
        Do not return anything, modify matrix in-place instead.
        """

        n = len(matrix)
        nn = n-1
        m1 = (n+1)//2
        m2 = n//2

        for i1 in range(m1):
            for j1 in range(m2):
                i2, j2 = nn-j1, i1
                i3, j3 = nn-i1, nn-j1
                i4, j4 = j1, nn-i1

                (
                    matrix[i1][j1], matrix[i2][j2], matrix[i3][j3], matrix[i4][j4]
                ) = (
                    matrix[i2][j2], matrix[i3][j3], matrix[i4][j4], matrix[i1][j1]
                )
