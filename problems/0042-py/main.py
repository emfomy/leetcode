# Source: https://leetcode.com/problems/trapping-rain-water
# Title: Trapping Rain Water
# Difficulty: Hard
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given `n` non-negative integers representing an elevation map where the width of each bar is `1`, compute how much water it can trap after raining.
#
# **Example 1:**
# https://assets.leetcode.com/uploads/2018/10/22/rainwatertrap.png
#
# ```
# Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
# Output: 6
# Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.
# ```
#
# **Example 2:**
#
# ```
# Input: height = [4,2,0,3,2,5]
# Output: 9
# ```
#
# **Constraints:**
#
# - `n == height.length`
# - `1 <= n <= 2 * 10^4`
# - `0 <= height[i] <= 10^5`
#
################################################################################################################################

from typing import List


# Use two pointer
class Solution:
    def trap(self, height: List[int]) -> int:
        n = len(height)

        left, right = 0, n - 1
        left_max, right_max = height[left], height[right]
        ans = 0

        while left < right:
            if height[left] < height[right]:  # shrink from left
                left += 1
                left_max = max(left_max, height[left])
                ans += left_max - height[left]
            else:  # shrink right
                right -= 1
                right_max = max(right_max, height[right])
                ans += right_max - height[right]

        return ans
