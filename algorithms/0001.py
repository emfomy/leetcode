# Source: https://leetcode.com/problems/two-sum/
# Title:  Two Sum
# Author: Mu Yang <muyang.pro>

################################################################################################################################
# Given an array of integers, return indices of the two numbers such that they add up to a specific target.
#
# You may assume that each input would have exactly one solution, and you may not use the same element twice.
#
# Example:
#
# Given nums = [2, 7, 11, 15], target = 9,
#
# Because nums[0] + nums[1] = 2 + 7 = 9,
# return [0, 1].
################################################################################################################################

class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        d = {}
        for i, n in enumerate(nums):
            if n in d:
                return [d[n], i]
            d[target-n] = i

class Solution2:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        idxs = sorted(range(len(nums)), key=lambda k: nums[k])
        i = 0
        j = len(nums)-1
        while True:
            s = nums[idxs[i]] + nums[idxs[j]]
            if s > target:
                j -= 1
            elif s < target:
                i += 1
            else:
                return [idxs[i], idxs[j]]
