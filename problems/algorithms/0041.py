# Source: https://leetcode.com/problems/first-missing-positive/
# Title: First Missing Positive
# Difficulty: Hard
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given an unsorted integer array nums, find the smallest missing positive integer.
#
# Follow up: Could you implement an algorithm that runs in O(n) time and uses constant extra space.?
#
# Example 1:
#
#   Input: nums = [1,2,0]
#   Output: 3
#
# Example 2:
#
#   Input: nums = [3,4,-1,1]
#   Output: 2
#
# Example 3:
#
#   Input: nums = [7,8,9,11,12]
#   Output: 1
#
# Constraints:
#
#   0 <= nums.length <= 300
#   -2^31 <= nums[i] <= 2^31 - 1
#
################################################################################################################################

class Solution:
    """
        Idea:
            1. let l be the length of the array
            2. the missing value must be in [1, l]
            3. use this array to store if each value is exist (+: not exist, -: exist)
    """
    def firstMissingPositive(self, nums: List[int]) -> int:

        # Get length
        l = len(nums)

        # Set all negative to l+1 (should be ignored)
        for i, n in enumerate(nums):
            if n <= 0:
                nums[i] = l+1

        # Flip signs
        for i, n in enumerate(nums):
            an = abs(n)
            if an <= l:
                nums[an-1] = -abs(nums[an-1])

        # Find index of the positive value
        for i, n in enumerate(nums):
            if n > 0:
                return i+1

        return l+1
