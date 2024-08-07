# Source: https://leetcode.com/problems/maximum-subarray
# Title: Maximum Subarray
# Difficulty: Easy
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.
#
# Follow up: If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.
#
# Example 1:
#
#   Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
#   Output: 6
#   Explanation: [4,-1,2,1] has the largest sum = 6.
#
# Example 2:
#
#   Input: nums = [1]
#   Output: 1
#
# Example 3:
#
#   Input: nums = [0]
#   Output: 0
#
# Example 4:
#
#   Input: nums = [-1]
#   Output: -1
#
# Example 5:
#
#   Input: nums = [-2147483647]
#   Output: -2147483647
#
# Constraints:
#
#   1 <= nums.length <= 2 * 10^4
#   -2^31 <= nums[i] <= 2^31 - 1
#
################################################################################################################################

class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        max_all = max_end = nums[0]
        for n in nums[1:]:
            max_end = max(max_end + n, n)
            max_all = max(max_all, max_end)
        return max_all
