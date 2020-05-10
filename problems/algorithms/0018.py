# Source: https://leetcode.com/problems/4sum/
# Title: 4Sum
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given an array nums of n integers and an integer target, are there elements a, b, c, and d in nums such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.
#
# Note:
#
# The solution set must not contain duplicate quadruplets.
#
# Example:
#
#   Given array nums = [1, 0, -1, 0, -2, 2], and target = 0.
#
#   A solution set is:
#   [
#     [-1,  0, 0, 1],
#     [-2, -1, 1, 2],
#     [-2,  0, 0, 2]
#   ]
#
################################################################################################################################

class Solution:
    def fourSum(self, nums: List[int], target: int) -> List[List[int]]:
        nums.sort()
        n = len(nums)
        i = 0
        while i < n:
            ai = nums[i]
            if ai > target//4: # break when avg of numbers is larger than avg of target
                break
            j = i+1
            while j < n:
                aj = nums[j]
                aij = ai+aj
                if aij > target//2: # break when avg of numbers is larger than avg of target
                    break

                k = j+1
                l = n-1
                while k < l:
                    ak = nums[k]
                    al = nums[l]
                    aijkl = aij + ak + al
                    if aijkl > target:
                        l -= 1
                    elif aijkl < target:
                        k += 1
                    else:
                        yield (ai, aj, ak, al,) # use yield to save memory
                        k += 1
                        l -= 1
                        while k < l and nums[k] == ak: # slip duplicate
                            k += 1
                        while k < l and nums[l] == al: # slip duplicate
                            l -= 1

                j += 1
                while j < n and nums[j] == aj: # skip duplicate
                    j += 1

            i += 1
            while i < n and nums[i] == ai: # skip duplicate
                i += 1
