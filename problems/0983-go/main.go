// Source: https://leetcode.com/problems/minimum-cost-for-tickets
// Title: Minimum Cost For Tickets
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You have planned some train traveling one year in advance. The days of the year in which you will travel are given as an integer array `days`. Each day is an integer from `1` to `365`.
//
// Train tickets are sold in **three different ways** :
//
// - a **1-day** pass is sold for `costs[0]` dollars,
// - a **7-day** pass is sold for `costs[1]` dollars, and
// - a **30-day** pass is sold for `costs[2]` dollars.
//
// The passes allow that many days of consecutive travel.
//
// - For example, if we get a **7-day** pass on day `2`, then we can travel for `7` days: `2`, `3`, `4`, `5`, `6`, `7`, and `8`.
//
// Return the minimum number of dollars you need to travel every day in the given list of days.
//
// **Example 1:**
//
// ```
// Input: days = [1,4,6,7,8,20], costs = [2,7,15]
// Output: 11
// Explanation: For example, here is one way to buy passes that lets you travel your travel plan:
// On day 1, you bought a 1-day pass for costs[0] = $2, which covered day 1.
// On day 3, you bought a 7-day pass for costs[1] = $7, which covered days 3, 4, ..., 9.
// On day 20, you bought a 1-day pass for costs[0] = $2, which covered day 20.
// In total, you spent $11 and covered all the days of your travel.
// ```
//
// **Example 2:**
//
// ```
// Input: days = [1,2,3,4,5,6,7,8,9,10,30,31], costs = [2,7,15]
// Output: 17
// Explanation: For example, here is one way to buy passes that lets you travel your travel plan:
// On day 1, you bought a 30-day pass for costs[2] = $15 which covered days 1, 2, ..., 30.
// On day 31, you bought a 1-day pass for costs[0] = $2 which covered day 31.
// In total, you spent $17 and covered all the days of your travel.
// ```
//
// **Constraints:**
//
// - `1 <= days.length <= 365`
// - `1 <= days[i] <= 365`
// - `days` is in strictly increasing order.
// - `costs.length == 3`
// - `1 <= costs[i] <= 1000`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"math"
	"slices"
)

// DP
func mincostTickets(days []int, costs []int) int {
	n := len(days)

	var prevDp map[int]int
	currDp := make(map[int]int, 30)

	getMinCost := func(dp map[int]int) int {
		res := math.MaxInt
		for _, v := range dp {
			res = min(res, v)
		}
		return res
	}

	{ // i = 0
		currDp[0] = costs[0]
		currDp[6] = costs[1]
		currDp[29] = costs[2]
	}

	for i := 1; i < n; i++ {
		prevDp = currDp
		currDp = make(map[int]int, 30)

		{
			prevCost := getMinCost(prevDp)
			currDp[0] = costs[0] + prevCost
			currDp[6] = costs[1] + prevCost
			currDp[29] = costs[2] + prevCost
		}

		dayDiff := days[i] - days[i-1]
		for rest, cost := range prevDp {
			if rest < dayDiff {
				continue
			}
			if val, ok := currDp[rest-dayDiff]; !ok {
				currDp[rest-dayDiff] = cost
			} else {
				currDp[rest-dayDiff] = min(val, cost)
			}
		}
	}

	return getMinCost(currDp)
}

// DP
func mincostTickets2(days []int, costs []int) int {
	lastDay := slices.Max(days)
	dp := make([]int, lastDay+1)

	i := 0
	for day := 1; day <= lastDay; day++ {
		if day < days[i] {
			dp[day] = dp[day-1]
			continue
		}

		i++
		dp[day] = min(
			dp[max(0, day-1)]+costs[0],
			dp[max(0, day-7)]+costs[1],
			dp[max(0, day-30)]+costs[2],
		)
	}

	return dp[lastDay]
}
