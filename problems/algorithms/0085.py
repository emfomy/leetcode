# Source: https://leetcode.com/problems/maximal-rectangle/
# Title: Maximal Rectangle
# Difficulty: Hard
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given a rows x cols binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.
#
# Example1:
#
#   Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
#   Output: 6
#   Explanation: The maximal rectangle is shown in the above picture.
#
# Example 2:
#
#   Input: matrix = []
#   Output: 0
#
# Example 3:
#
#   Input: matrix = [["0"]]
#   Output: 0
#
# Example 4:
#
#   Input: matrix = [["1"]]
#   Output: 1
#
# Example 5:
#
#   Input: matrix = [["0","0"]]
#   Output: 0
#
# Constraints:
#
#   rows == matrix.length
#   cols == matrix[0].length
#   0 <= row, cols <= 200
#   matrix[i][j] is '0' or '1'.
#
################################################################################################################################

class Solution:
    """Based on largest rectangle area"""
    def maximalRectangle(self, matrix: List[List[str]]) -> int:

        rows = len(matrix)
        if not rows:
            return 0
        cols = len(matrix[0])
        if not cols:
            return 0

        # Create height matrix
        heights = [None] * rows
        heights[0] = [0] * cols
        for i, row in enumerate(matrix):
            heights[i] = [0] * cols
            for j, value in enumerate(row):
                if int(value):
                    heights[i][j] = 1 + (heights[i-1][j] if i else 0)

        # Call largest rectangle area by rows
        ans = 0
        for row in heights:
            ans = max(ans, self.largestRectangleArea(row))
        return ans

    def largestRectangleArea(self, heights: List[int]) -> int:

        n = len(heights)

        left_index = [0]*n
        right_index = [n]*n

        # Find right index
        stack = []
        for i in range(n):
            while stack and heights[stack[-1]] > heights[i]:
                right_index[stack.pop()] = i
            stack.append(i)

        # Find left index
        stack = []
        for i in range(n-1, -1, -1):
            while stack and heights[stack[-1]] > heights[i]:
                left_index[stack.pop()] = i+1
            stack.append(i)

        # Compute area
        ans = 0
        for i, height in enumerate(heights):
            area = height * (right_index[i] - left_index[i])
            ans = max(ans, area)

        return ans
