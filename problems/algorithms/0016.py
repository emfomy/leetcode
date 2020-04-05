# Source: https://leetcode.com/problems/3sum-closest/
# Title: 3Sum Closest
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given an array nums of n integers and an integer target, find three integers in nums such that the sum is closest to target. Return the sum of the three integers. You may assume that each input would have exactly one solution.
#
# Example:
#
#   Given array nums = [-1, 2, 1, -4], and target = 1.
#
# The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
#
################################################################################################################################

class Solution:
    def threeSumClosest(self, nums: List[int], target: int) -> int:
        nums.sort()
        ans = None
        diff = float('Inf')
        n = len(nums)
        i = 0
        while i < n:
            ai = nums[i]
            if ai > 0 and ai > target + diff: # break when ai too large
                break

            j = i+1
            k = n-1
            while j < k:
                aj = nums[j]
                ak = nums[k]
                aijk = ai + aj + ak

                if aijk == target:
                    return target

                if aijk > target + diff:
                    k -= 1
                    while j < k and nums[k] == ak: # skip duplicate
                        k -= 1
                elif aijk < target - diff:
                    j += 1
                    while j < k and nums[j] == aj: # skip duplicate
                        j += 1
                else:
                    adiff = abs(aijk - target)
                    if adiff < diff:
                        diff = adiff
                        ans = aijk

                    if aijk > target:
                        k -= 1
                        while j < k and nums[k] == ak: # skip duplicate
                            k -= 1
                    else:
                        j += 1
                        while j < k and nums[j] == aj: # skip duplicate
                            j += 1

            i += 1
            while i < n and nums[i] == ai: # skip duplicate
                i += 1

        return ans
