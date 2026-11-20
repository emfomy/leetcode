# Source: https://leetcode.com/problems/rotate-array
# Title: Rotate Array
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given an integer array `nums`, rotate the array to the right by `k` steps, where `k` is non-negative.
#
# **Example 1:**
#
# ```
# Input: nums = [1,2,3,4,5,6,7], k = 3
# Output: [5,6,7,1,2,3,4]
# Explanation:
# rotate 1 steps to the right: [7,1,2,3,4,5,6]
# rotate 2 steps to the right: [6,7,1,2,3,4,5]
# rotate 3 steps to the right: [5,6,7,1,2,3,4]
# ```
#
# **Example 2:**
#
# ```
# Input: nums = [-1,-100,3,99], k = 2
# Output: [3,99,-1,-100]
# Explanation:
# rotate 1 steps to the right: [99,-1,-100,3]
# rotate 2 steps to the right: [3,99,-1,-100]
# ```
#
# **Constraints:**
#
# - `1 <= nums.length <= 10^5`
# - `-2^31 <= nums[i] <= 2^31 - 1`
# - `0 <= k <= 10^5`
#
# **Follow up:**
#
# - Try to come up with as many solutions as you can. There are at least **three** different ways to solve this problem.
# - Could you do it in-place with `O(1)` extra space?
#
################################################################################################################################


import math
from typing import List


# The rotation forms multiple chains
# 0 -> k   -> 2k   -> ... -> 0
# 1 -> k+1 -> 2k+1 -> ... -> 1
# ...
# If gcd(n, k) = 1, we only need to start from 0
# If gcd(n, k) = d > 1, we need to start from 0, 1, ..., d-1
class Solution:
    def rotate(self, nums: List[int], k: int) -> None:
        n = len(nums)
        k = k % n

        if k == 0 or n == 1:
            return

        d = math.gcd(n, k)
        for i in range(d):
            dst = i
            tmp = nums[i]
            while True:
                src = (dst + n - k) % n
                if src == i:
                    nums[dst] = tmp
                    break
                nums[dst] = nums[src]
                dst = src


# Similarity to above solution
# Instead of computing gcd, we count the rotated numbers
class Solution2:
    def rotate(self, nums: List[int], k: int) -> None:
        n = len(nums)
        k = k % n

        if k == 0 or n == 1:
            return

        count = 0
        start = 0
        while count < n:
            dst = start
            tmp = nums[start]
            while True:
                count += 1
                src = (dst + n - k) % n
                if src == start:
                    nums[dst] = tmp
                    break
                nums[dst] = nums[src]
                dst = src

            start += 1
