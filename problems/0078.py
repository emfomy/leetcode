# Source: https://leetcode.com/problems/subsets
# Title: Subsets
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given an integer array nums, return all possible subsets (the power set).
#
# The solution set must not contain duplicate subsets.
#
# Example 1:
#
#   Input: nums = [1,2,3]
#   Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
#
# Example 2:
#
#   Input: nums = [0]
#   Output: [[],[0]]
#
# Constraints:
#
#   1 <= nums.length <= 10
#   -10 <= nums[i] <= 10
#
################################################################################################################################

from collections import Counter

class Solution:
    def subsets(self, nums: List[int]) -> List[List[int]]:
        counter = Counter(nums)
        yield from self.subsetsInner(*counter.items())

    def subsetsInner(self, item, *items, res=[]):
        key, count = item
        if items:
            for i in range(count+1):
                yield from self.subsetsInner(*items, res=(res+[key]*i))
        else:
            for i in range(count+1):
                yield (res+[key]*i)
