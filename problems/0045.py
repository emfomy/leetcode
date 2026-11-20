# Source: https://leetcode.com/problems/jump-game-ii
# Title: Jump Game II
# Difficulty: Hard
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# You are given a **0-indexed** array of integers `nums` of length `n`. You are initially positioned at `nums[0]`.
#
# Each element `nums[i]` represents the maximum length of a forward jump from index `i`. In other words, if you are at `nums[i]`, you can jump to any `nums[i + j]` where:
#
# - `0 <= j <= nums[i]` and
# - `i + j < n`
#
# Return the minimum number of jumps to reach `nums[n - 1]`. The test cases are generated such that you can reach `nums[n - 1]`.
#
# **Example 1:**
#
# ```
# Input: nums = [2,3,1,1,4]
# Output: 2
# Explanation: The minimum number of jumps to reach the last index is 2. Jump 1 step from index 0 to 1, then 3 steps to the last index.
# ```
#
# **Example 2:**
#
# ```
# Input: nums = [2,3,0,1,4]
# Output: 2
# ```
#
# **Constraints:**
#
# - `1 <= nums.length <= 10^4`
# - `0 <= nums[i] <= 1000`
# - It's guaranteed that you can reach `nums[n - 1]`.
#
################################################################################################################################


from typing import List


# Use DP
class Solution:
    def jump(self, nums: List[int]) -> int:
        n = len(nums)
        dp = [n] * n  # steps to reach this index
        dp[0] = 0

        for i, num in enumerate(nums):
            for j in range(i + 1, min(i + num + 1, n)):
                dp[j] = min(dp[j], dp[i] + 1)

        return dp[n - 1]


# Use BFS
class Solution2:
    def jump(self, nums: List[int]) -> int:
        ans = 0  # steps
        currMax, nextMax = 0, 0

        for i, num in enumerate(nums):
            if i > currMax:
                currMax = nextMax
                ans += 1
            nextMax = max(nextMax, i + num)

        return ans
