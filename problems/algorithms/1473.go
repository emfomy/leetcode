// Source: https://leetcode.com/problems/paint-house-iii/
// Title: Paint House III
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// There is a row of m houses in a small city, each house must be painted with one of the n colors (labeled from 1 to n), some houses that have been painted last summer should not be painted again.
//
// A neighborhood is a maximal group of continuous houses that are painted with the same color.
//
//   For example: houses = [1,2,2,3,3,2,1,1] contains 5 neighborhoods [{1}, {2,2}, {3,3}, {2}, {1,1}].
//
// Given an array houses, an m x n matrix cost and an integer target where:
//
//   houses[i]: is the color of the house i, and 0 if the house is not painted yet.
//   cost[i][j]: is the cost of paint the house i with the color j + 1.
//
// Return the minimum cost of painting all the remaining houses in such a way that there are exactly target neighborhoods. If it is not possible, return -1.
//
// Example 1:
//
//   Input: houses = [0,0,0,0,0], cost = [[1,10],[10,1],[10,1],[1,10],[5,1]], m = 5, n = 2, target = 3
//   Output: 9
//   Explanation:
//     Paint houses of this way [1,2,2,1,1]
//     This array contains target = 3 neighborhoods, [{1}, {2,2}, {1,1}].
//     Cost of paint all houses (1 + 1 + 1 + 1 + 5) = 9.
//
// Example 2:
//
//   Input: houses = [0,2,1,2,0], cost = [[1,10],[10,1],[10,1],[1,10],[5,1]], m = 5, n = 2, target = 3
//   Output: 11
//   Explanation:
//     Some houses are already painted, Paint the houses of this way [2,2,1,2,2]
//     This array contains target = 3 neighborhoods, [{2,2}, {1}, {2,2}].
//     Cost of paint the first and last house (10 + 1) = 11.
//
// Example 3:
//
//   Input: houses = [3,1,2,3], cost = [[1,1,1],[1,1,1],[1,1,1],[1,1,1]], m = 4, n = 3, target = 3
//   Output: -1
//   Explanation: Houses are already painted with a total of 4 neighborhoods [{3},{1},{2},{3}] different of target = 3.
//
// Constraints:
//
//   m == houses.length == cost.length
//   n == cost[i].length
//   1 <= m <= 100
//   1 <= n <= 20
//   1 <= target <= m
//   0 <= houses[i] <= n
//   1 <= cost[i][j] <= 10^4
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"math"
)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Use 3D DP
// dp[i][j][k] = the minimum cost where we have (k+1) neighborhoods in the first i house
//   and the i-th house is painted with the color j.
func minCost(houses []int, cost [][]int, m int, n int, target int) int {
	dp := make([][][]int, m)
	for i := 0; i < m; i++ {
		dp[i] = make([][]int, n)
		for j := 0; j < n; j++ {
			dp[i][j] = make([]int, m)
			for k := 0; k < m; k++ {
				dp[i][j][k] = math.MaxInt32
			}
		}
	}

	// First house
	if houses[0] != 0 { // already painted
		j := houses[0] - 1
		dp[0][j][0] = 0
	} else {
		for j := 0; j < n; j++ {
			dp[0][j][0] = cost[0][j]
		}
	}

	for i := 1; i < m; i++ {
		if houses[i] != 0 { // already painted
			j := houses[i] - 1
			for j2 := 0; j2 < n; j2++ {
				if j == j2 { // same color as the previous house
					for k := 0; k < i; k++ {
						dp[i][j][k] = _min(dp[i][j][k], dp[i-1][j2][k])
					}
				} else { // different color
					for k := 1; k <= i; k++ {
						dp[i][j][k] = _min(dp[i][j][k], dp[i-1][j2][k-1])
					}
				}
			}
		} else {
			for j := 0; j < n; j++ { // loop for colors for this house
				for j2 := 0; j2 < n; j2++ { // loop for colors for previous house
					if j == j2 { // same color
						for k := 0; k < i; k++ {
							dp[i][j][k] = _min(dp[i][j][k], cost[i][j]+dp[i-1][j2][k])
						}
					} else { // different color
						for k := 1; k <= i; k++ {
							dp[i][j][k] = _min(dp[i][j][k], cost[i][j]+dp[i-1][j2][k-1])
						}
					}
				}
			}
		}
	}

	res := math.MaxInt32
	for j := 0; j < n; j++ {
		res = _min(res, dp[m-1][j][target-1])
	}

	if res >= math.MaxInt32 {
		return -1
	}
	return res
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Use 2D DP
// dp[i][j][k] = the minimum cost where we have (k+1) neighborhoods in the first i house
//   and the i-th house is painted with the color j.
// We reuse the first dimension (i.e. remove i)
func minCost2(houses []int, cost [][]int, m int, n int, target int) int {
	prev := make([][]int, n)
	curr := make([][]int, n)
	for j := 0; j < n; j++ {
		prev[j] = make([]int, m)
		curr[j] = make([]int, m)
	}

	// Init
	for j := 0; j < n; j++ {
		prev[j][0] = math.MaxInt32
	}

	// First house
	if houses[0] != 0 { // already painted
		j := houses[0] - 1
		prev[j][0] = 0
	} else {
		for j := 0; j < n; j++ {
			prev[j][0] = cost[0][j]
		}
	}

	// Loop
	for i := 1; i < m; i++ {
		// Clear
		for j := 0; j < n; j++ {
			for k := 0; k <= i; k++ {
				curr[j][k] = math.MaxInt32
			}
		}

		// DP
		if houses[i] != 0 { // already painted
			j := houses[i] - 1
			for j2 := 0; j2 < n; j2++ {
				if j == j2 { // same color as the previous house
					for k := 0; k < i; k++ {
						curr[j][k] = _min(curr[j][k], prev[j2][k])
					}
				} else { // different color
					for k := 1; k <= i; k++ {
						curr[j][k] = _min(curr[j][k], prev[j2][k-1])
					}
				}
			}
		} else {
			for j := 0; j < n; j++ { // loop for colors for this house
				for j2 := 0; j2 < n; j2++ { // loop for colors for previous house
					if j == j2 { // same color
						for k := 0; k < i; k++ {
							curr[j][k] = _min(curr[j][k], cost[i][j]+prev[j2][k])
						}
					} else { // different color
						for k := 1; k <= i; k++ {
							curr[j][k] = _min(curr[j][k], cost[i][j]+prev[j2][k-1])
						}
					}
				}
			}
		}

		prev, curr = curr, prev
	}

	res := math.MaxInt32
	for j := 0; j < n; j++ {
		res = _min(res, prev[j][target-1])
	}

	if res >= math.MaxInt32 {
		return -1
	}
	return res
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

func _min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
