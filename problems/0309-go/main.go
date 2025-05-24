// Source: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown
// Title: Best Time to Buy and Sell Stock with Cooldown
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an array prices where prices[i] is the price of a given stock on the ith day.
//
// Find the maximum profit you can achieve. You may complete as many transactions as you like (i.e., buy one and sell one share of the stock multiple times) with the following restrictions:
//
//   After you sell your stock, you cannot buy stock on the next day (i.e., cooldown one day).
//
// Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).
//
// Example 1:
//
//   Input: prices = [1,2,3,0,2]
//   Output: 3
//   Explanation: transactions = [buy, sell, cooldown, buy, sell]
//
// Example 2:
//
//   Input: prices = [1]
//   Output: 0
//
// Constraints:
//
//   1 <= prices.length <= 5000
//   0 <= prices[i] <= 1000
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"math"
)

// There are three actions:
//
//	Buy (buy stock or keep bought stock), sell, cooldown (do nothing after sell)
//
// Denote these actions as B, S, C.
// Only the following action transactions are allowed:
//
//	B -> B, B -> S
//	S -> C
//	C -> C, C -> B
func maxProfit(prices []int) int {
	bPrev := math.MinInt32
	sPrev := math.MinInt32
	cPrev := 0

	for _, price := range prices {
		bCurr := _max(bPrev, cPrev-price)
		sCurr := bPrev + price
		cCurr := _max(sPrev, cPrev)
		bPrev, sPrev, cPrev = bCurr, sCurr, cCurr
	}

	return _max(sPrev, cPrev)
}

func _max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
