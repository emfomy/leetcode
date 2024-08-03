# Source: https://leetcode.com/problems/jump-game-ii
# Title: Jump Game II
# Difficulty: Hard
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given an array of non-negative integers nums, you are initially positioned at the first index of the array.
#
# Each element in the array represents your maximum jump length at that position.
#
# Your goal is to reach the last index in the minimum number of jumps.
#
# You can assume that you can always reach the last index.
#
# Example 1:
#
#   Input: nums = [2,3,1,1,4]
#   Output: 2
#   Explanation: The minimum number of jumps to reach the last index is 2. Jump 1 step from index 0 to 1, then 3 steps to the last index.
#
# Example 2:
#
#   Input: nums = [2,3,0,1,4]
#   Output: 2
#
# Constraints:
#
#   1 <= nums.length <= 10^4
#   0 <= nums[i] <= 1000
#
################################################################################################################################

class Solution:
    def jump(self, nums: List[int]) -> int:

        l = len(nums)

        min_step = [None]*l
        min_step[0] = 0

        for i, n in enumerate(nums):
            next_step = min_step[i]+1
            for j in range(i+1, min(i+1+n, l)):
                if not min_step[j] or next_step < min_step[j]:
                    min_step[j] = next_step

        return min_step[-1]


################################################################################################################################

class Solution2:
    def jump(self, nums: List[int]) -> int:
        l = len(nums)-1
        if l <= 0:
            return 0

        step = 0
        cur_end = 0
        cur_max = 0
        for i, n in enumerate(nums):
            cur_max = max(cur_max, i+n)
            if i == cur_end:
                step += 1
                cur_end = cur_max
                if cur_end >= l:
                    break
        return step
