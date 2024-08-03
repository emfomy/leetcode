// Source: https://leetcode.com/problems/maximal-square
// Title: Maximal Square
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an m x n binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.
//
// Example 1:
//
//   https://assets.leetcode.com/uploads/2020/11/26/max1grid.jpg
//
//   Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
//   Output: 4
//
// Example 2:
//
//   https://assets.leetcode.com/uploads/2020/11/26/max2grid.jpg
//
//   Input: matrix = [["0","1"],["1","0"]]
//   Output: 1
//
// Example 3:
//
//   Input: matrix = [["0"]]
//   Output: 0
//
// Constraints:
//
//   m == matrix.length
//   n == matrix[i].length
//   1 <= m, n <= 300
//   matrix[i][j] is '0' or '1'.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

func maximalSquare(matrix [][]byte) int {
	m := len(matrix)
	n := len(matrix[0])

	dp := make([][]int, m)
	for i := 0; i < m; i++ {
		dp[i] = make([]int, n)
		for j := 0; j < n; j++ {
			if matrix[i][j] == '1' {
				dp[i][j] = 1
			} else {
				dp[i][j] = 0
			}
		}
	}

	for i := 1; i < m; i++ {
		for j := 1; j < n; j++ {
			if dp[i][j] == 1 {
				dp[i][j] = _min3(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1
			} else {
				dp[i][j] = 0
			}
		}
	}

	res := 0
	for _, row := range dp {
		for _, v := range row {
			res = _max(res, v)
		}
	}

	return res * res
}

func _max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func _min3(a, b, c int) int {
	return _min(_min(a, b), c)
}

func _min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
