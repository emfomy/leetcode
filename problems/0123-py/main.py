# Source: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii
# Title: Best Time to Buy and Sell Stock III
# Difficulty: Hard
# Author: Mu Yang <http://muyang.pro>

################################################################################################################################
# You are given an array `prices` where `prices[i]` is the price of a given stock on the `i^th` day.
#
# Find the maximum profit you can achieve. You may complete **at most two transactions**.
#
# **Note:** You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).
#
# **Example 1:**
#
# ```
# Input: prices = [3,3,5,0,0,3,1,4]
# Output: 6
# Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
# Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.
# ```
#
# **Example 2:**
#
# ```
# Input: prices = [1,2,3,4,5]
# Output: 4
# Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
# Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are engaging multiple transactions at the same time. You must sell before buying again.
# ```
#
# **Example 3:**
#
# ```
# Input: prices = [7,6,4,3,1]
# Output: 0
# Explanation: In this case, no transaction is done, i.e. max profit = 0.
# ```
#
# **Constraints:**
#
# - `1 <= prices.length <= 10^5`
# - `0 <= prices[i] <= 10^5`
#
################################################################################################################################


from typing import List


# Two way DP
#
# Left[i]  = max profit in [0, i)
# Right[i] = max profit in [i, n)
class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        n = len(prices)

        left = [0] * (n + 1)
        right = [0] * (n + 1)

        minPrice = int(1e5)
        for i in range(n):
            minPrice = min(minPrice, prices[i])
            left[i + 1] = max(left[i], prices[i] - minPrice)

        maxPrice = 0
        for i in reversed(range(n)):
            maxPrice = max(maxPrice, prices[i])
            right[i + 1] = max(right[i + 1], maxPrice - prices[i])

        ans = 0
        for i in range(n):
            ans = max(ans, left[i] + right[i + 1])

        return ans


# One Pass DP
class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        cost1 = int(1e5)
        cost2 = int(1e5)
        profit1 = 0
        profit2 = 0

        for price in prices:
            cost1 = min(cost1, price)
            profit1 = max(profit1, price - cost1)
            cost2 = min(cost2, price - profit1)
            profit2 = max(profit2, price - cost2)

        return profit2
