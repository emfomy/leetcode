# Source: https://leetcode.com/problems/search-in-rotated-sorted-array
# Title: Search in Rotated Sorted Array
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
#
# (i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).
#
# You are given a target value to search. If found in the array return its index, otherwise return -1.
#
# You may assume no duplicate exists in the array.
#
# Your algorithm's runtime complexity must be in the order of O(log n).
#
# Example 1:
#
#   Input: nums = [4,5,6,7,0,1,2], target = 0
#   Output: 4
#
# Example 2:
#
#   Input: nums = [4,5,6,7,0,1,2], target = 3
#   Output: -1
#
################################################################################################################################

class Solution:
    def search(self, nums: List[int], target: int) -> int:

        if not nums:
            return -1

        base = nums[0]

        def comp(a, b):
            if a < base and b >= base:
                return False
            if a >= base and b < base:
                return True
            return a < b

        return self.binary_search(nums, 0, len(nums), target, comp)


    def binary_search(self, arr, start, end, target, comp):
        idx = (start + end) // 2

        val = arr[idx]
        if val == target:
            return idx

        if start >= end-1:
            return -1

        if comp(target, val): # Less
            return self.binary_search(arr, start, idx, target, comp)
        else: # Greater
            return self.binary_search(arr, idx, end, target, comp)
