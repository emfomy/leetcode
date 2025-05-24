// Source: https://leetcode.com/problems/coin-change
// Title: Coin Change
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.
//
// Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.
//
// You may assume that you have an infinite number of each kind of coin.
//
// Example 1:
//
//   Input: coins = [1,2,5], amount = 11
//   Output: 3
//   Explanation: 11 = 5 + 5 + 1
//
// Example 2:
//
//   Input: coins = [2], amount = 3
//   Output: -1
//
// Example 3:
//
//   Input: coins = [1], amount = 0
//   Output: 0
//
// Constraints:
//
//   1 <= coins.length <= 12
//   1 <= coins[i] <= 2^31 - 1
//   0 <= amount <= 10^4
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"math"
	"sort"
)

const maxNum = math.MaxInt32 - 1

func coinChange(coins []int, amount int) int {
	sort.Ints(coins)

	dp := make([]int, amount+1) // number of coins for amount=i

	for i := 1; i <= amount; i++ {
		dp[i] = maxNum
		for _, coin := range coins {
			if coin > i {
				break
			}
			dp[i] = _min(dp[i], dp[i-coin]+1)
		}
	}

	if dp[amount] == maxNum {
		return -1
	}
	return dp[amount]
}

func _min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
