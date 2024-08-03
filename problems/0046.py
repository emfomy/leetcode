# Source: https://leetcode.com/problems/permutations
# Title: Permutations
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given a collection of distinct integers, return all possible permutations.
#
# Example:
#
#   Input: [1,2,3]
#   Output:
#   [
#     [1,2,3],
#     [1,3,2],
#     [2,1,3],
#     [2,3,1],
#     [3,1,2],
#     [3,2,1]
#   ]
#
################################################################################################################################

class Solution:
    """Heap's algorithm"""
    def permute(self, nums: List[int]) -> List[List[int]]:
        yield from self.permuteInner(nums, len(nums))

    def permuteInner(self, nums, k):
        if k == 1:
            yield list(nums)
        else:
            for i in range(k):
                yield from self.permuteInner(nums, k-1)
                if k % 2:
                    nums[i], nums[k-1] = nums[k-1], nums[i]
                else:
                    nums[0], nums[k-1] = nums[k-1], nums[0]

################################################################################################################################

class Solution2:
    def permute(self, nums: List[int]) -> List[List[int]]:
        yield from self.permuteInner([], nums)

    def permuteInner(self, prefix, nums):
        if not nums:
            yield prefix
        else:
            for i, n in enumerate(nums):
                yield from self.permuteInner(prefix+[n], nums[:i]+nums[i+1:])
