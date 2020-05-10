# Source: https://leetcode.com/problems/3sum/
# Title: 3Sum
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.
#
# Note:
#
# The solution set must not contain duplicate triplets.
#
# Example:
#
#   Given array nums = [-1, 0, 1, 2, -1, -4],
#
#   A solution set is:
#   [
#     [-1, 0, 1],
#     [-1, -1, 2]
#   ]
#
################################################################################################################################

class Solution:
    def threeSum(self, nums: List[int]) -> List[List[int]]:
        nums.sort()
        n = len(nums)
        i = 0
        while i < n:
            ai = nums[i]
            if ai > 0: # break when numbers are all positive
                break
            j = i+1
            k = n-1
            while j < k:
                aj = nums[j]
                ak = nums[k]
                aijk = ai + aj + ak
                if aijk > 0:
                    k -= 1
                elif aijk < 0:
                    j += 1
                else:
                    yield (ai, aj, ak,) # use yield to save memory
                    j += 1
                    k -= 1
                    while j < k and nums[j] == aj: # skip duplicate
                        j += 1
                    while j < k and nums[k] == ak: # skip duplicate
                        k -= 1
            i += 1
            while i < n and nums[i] == ai: # skip duplicate
                i += 1
