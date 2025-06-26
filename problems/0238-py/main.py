# Source: https://leetcode.com/problems/product-of-array-except-self
# Title: Product of Array Except Self
# Difficulty: Medium
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# Given an integer array `nums`, return an array `answer` such that `answer[i]` is equal to the product of all the elements of `nums` except `nums[i]`.
#
# The product of any prefix or suffix of `nums` is **guaranteed** to fit in a **32-bit** integer.
#
# You must write an algorithm that runs in`O(n)`time and without using the division operation.
#
# **Example 1:**
#
# ```
# Input: nums = [1,2,3,4]
# Output: [24,12,8,6]
# ```
#
# **Example 2:**
#
# ```
# Input: nums = [-1,1,0,-3,3]
# Output: [0,0,9,0,0]
# ```
#
# **Constraints:**
#
# - `2 <= nums.length <= 10^5`
# - `-30 <= nums[i] <= 30`
# - The input is generated such that `answer[i]` is **guaranteed** to fit in a **32-bit** integer.
#
# **Follow up:**Can you solve the problem in `O(1)`extraspace complexity? (The output array **does not** count as extra space for space complexity analysis.)
#
################################################################################################################################


from typing import List


# First check if there is zero.
# If there is no zero, the answer is equal to the total product divides the number.
# If there is only one zero, the answer is zero except the zero item.
# If there are more zeros, the answer is always zero.
class Solution:
    def productExceptSelf(self, nums: List[int]) -> List[int]:
        n = len(nums)

        # Compute product and count zeros
        product = 1
        zeros = 0
        zeroIdx = -1
        for idx, num in enumerate(nums):
            if num == 0:
                zeros += 1
                zeroIdx = idx
            else:
                product *= num

        # Contains zeros
        if zeros > 0:
            ans = [0] * n
            if zeros == 1:
                ans[zeroIdx] = product
            return ans

        # No zero
        ans = [product // num for num in nums]
        return ans


# Two pass
# Prepare the answer list first, then product from both side.
class Solution2:
    def productExceptSelf(self, nums: List[int]) -> List[int]:
        n = len(nums)
        ans = [1] * n

        # Product from left
        product = 1
        for i in range(n):
            ans[i] *= product
            product *= nums[i]

        # Product from right
        product = 1
        for i in reversed(range(n)):
            ans[i] *= product
            product *= nums[i]

        return ans
