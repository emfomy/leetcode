# Source: https://leetcode.com/problems/largest-rectangle-in-histogram
# Title: Largest Rectangle in Histogram
# Difficulty: Hard
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.
#
# Example:
#
#   Input: [2,1,5,6,2,3]
#   Output: 10
#
################################################################################################################################

class Solution:
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
