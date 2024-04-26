// Source: https://leetcode.com/problems/minimum-falling-path-sum-ii
// Title: Minimum Falling Path Sum II
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an n x n integer matrix grid, return the minimum sum of a falling path with non-zero shifts.
//
// A falling path with non-zero shifts is a choice of exactly one element from each row of grid such that no two elements chosen in adjacent rows are in the same column.
//
// Example 1:
//
//   https://assets.leetcode.com/uploads/2021/08/10/falling-grid.jpg
//
//   Input: grid = [[1,2,3],[4,5,6],[7,8,9]]
//   Output: 13
//   Explanation:
//     The possible falling paths are:
//     [1,5,9], [1,5,7], [1,6,7], [1,6,8],
//     [2,4,8], [2,4,9], [2,6,7], [2,6,8],
//     [3,4,8], [3,4,9], [3,5,7], [3,5,9]
//     The falling path with the smallest sum is [1,5,7], so the answer is 13.
//
// Example 2:
//
//   Input: grid = [[7]]
//   Output: 7
//
// Constraints:
//
//   n == grid.length == grid[i].length
//   1 <= n <= 200
//   -99 <= grid[i][j] <= 99
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"math"
)

func minFallingPathSum(grid [][]int) int {
	n := len(grid)
	if n == 1 {
		return grid[0][0]
	}

	prev := make([]int, n)
	next := make([]int, n)

	for i, v := range grid[0] {
		prev[i] = v
	}

	for _, row := range grid[1:] {
		// Find the minimum and the second minimum
		prevMin, prevMin2 := math.MaxInt32, math.MaxInt32
		for _, v := range prev {
			if v < prevMin {
				prevMin, prevMin2 = v, prevMin
			} else if v < prevMin2 {
				prevMin2 = v
			}
		}

		// DP
		for i := 0; i < n; i++ {
			if prev[i] != prevMin {
				next[i] = prevMin + row[i]
			} else {
				next[i] = prevMin2 + row[i]
			}
		}

		prev, next = next, prev
	}

	res := math.MaxInt32
	for _, v := range prev {
		res = min(res, v)
	}

	return res
}
