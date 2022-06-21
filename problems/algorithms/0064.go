// Source: https://leetcode.com/problems/minimum-path-sum/
// Title: Minimum Path Sum
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right, which minimizes the sum of all numbers along its path.
//
// Note: You can only move either down or right at any point in time.
//
// Example 1:
//
//   https://assets.leetcode.com/uploads/2020/11/05/minpath.jpg
//
//   Input: grid = [[1,3,1],[1,5,1],[4,2,1]]
//   Output: 7
//   Explanation: Because the path 1 → 3 → 1 → 1 → 1 minimizes the sum.
//
// Example 2:
//
//   Input: grid = [[1,2,3],[4,5,6]]
//   Output: 12
//
// Constraints:
//
//   m == grid.length
//   n == grid[i].length
//   1 <= m, n <= 200
//   0 <= grid[i][j] <= 100
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

func minPathSum(grid [][]int) int {
	m := len(grid)
	n := len(grid[0])

	dp := make([]int, n)

	dp[0] = grid[0][0]
	for j := 1; j < n; j++ {
		dp[j] = dp[j-1] + grid[0][j]
	}

	for i := 1; i < m; i++ {
		dp[0] += grid[i][0]
		for j := 1; j < n; j++ {
			dp[j] = _min(dp[j-1], dp[j]) + grid[i][j]
		}
	}

	return dp[n-1]
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Mofidy the grid
func minPathSum2(grid [][]int) int {
	m := len(grid)
	n := len(grid[0])

	for j := 1; j < n; j++ {
		grid[0][j] += grid[0][j-1]
	}

	for i := 1; i < m; i++ {
		grid[i][0] += grid[i-1][0]
	}

	for i := 1; i < m; i++ {
		for j := 1; j < n; j++ {
			grid[i][j] += _min(grid[i-1][j], grid[i][j-1])
		}
	}

	return grid[m-1][n-1]
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

func _min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
