# Source: https://leetcode.com/problems/container-with-most-water/
# Title: Container With Most Water
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given n non-negative integers a1, a2, ..., an , where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.
#
# Note: You may not slant the container and n is at least 2.
#
# https://s3-lc-upload.s3.amazonaws.com/uploads/2018/07/17/question_11.jpg
#
# The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.
#
# Example:
#
#   Input: [1,8,6,2,5,4,8,3,7]
#   Output: 49
#
################################################################################################################################

class Solution:
    def maxArea(self, height: List[int]) -> int:
        i = 0
        j = len(height)-1
        ans = 0
        while i < j:
            ans = max(ans, min(height[i], height[j]) * (j-i))
            if height[i] < height[j]:
                i += 1
            else:
                j -= 1

        return ans
