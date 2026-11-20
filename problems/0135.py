# Source: https://leetcode.com/problems/candy
# Title: Candy
# Difficulty: Hard
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# There are `n` children standing in a line. Each child is assigned a rating value given in the integer array `ratings`.
#
# You are giving candies to these children subjected to the following requirements:
#
# - Each child must have at least one candy.
# - Children with a higher rating get more candies than their neighbors.
#
# Return the minimum number of candies you need to have to distribute the candies to the children.
#
# **Example 1:**
#
# ```
# Input: ratings = [1,0,2]
# Output: 5
# Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.
# ```
#
# **Example 2:**
#
# ```
# Input: ratings = [1,2,2]
# Output: 4
# Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
# The third child gets 1 candy because it satisfies the above two conditions.
# ```
#
# **Constraints:**
#
# - `n == ratings.length`
# - `1 <= n <= 2 * 10^4`
# - `0 <= ratings[i] <= 2 * 10^4`
#
################################################################################################################################


from typing import List


# Traverse from both direction
class Solution:
    def candy(self, ratings: List[int]) -> int:
        n = len(ratings)

        candies = [1] * n

        # From left to right
        for i in range(1, n):
            print(i, ratings[i] > ratings[i - 1])
            if ratings[i] > ratings[i - 1]:
                candies[i] = max(candies[i], candies[i - 1] + 1)

        # From right to left
        for i in reversed(range(n - 1)):
            print(i, ratings[i] > ratings[i + 1])
            if ratings[i] > ratings[i + 1]:
                candies[i] = max(candies[i], candies[i + 1] + 1)

        return sum(candies)
