// Source: https://leetcode.com/problems/minimum-falling-path-sum/
// Title: Minimum Falling Path Sum
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Given an n x n array of integers matrix, return the minimum sum of any falling path through matrix.
//
// A falling path starts at any element in the first row and chooses the element in the next row that is either directly below or diagonally left/right. Specifically, the next element from position (row, col) will be (row + 1, col - 1), (row + 1, col), or (row + 1, col + 1).
//
// Example 1:
//
//   https://assets.leetcode.com/uploads/2021/11/03/failing1-grid.jpg
//   Input: matrix = [[2,1,3],[6,5,4],[7,8,9]]
//   Output: 13
//   Explanation: There are two falling paths with a minimum sum as shown.
//
// Example 2:
//
//   https://assets.leetcode.com/uploads/2021/11/03/failing2-grid.jpg
//   Input: matrix = [[-19,57],[-40,-5]]
//   Output: -59
//   Explanation: The falling path with a minimum sum is shown.
//
// Constraints:
//
//   n == matrix.length == matrix[i].length
//   1 <= n <= 100
//   -100 <= matrix[i][j] <= 100
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

package main

import (
	"math"
)

func minFallingPathSum(matrix [][]int) int {
	n := len(matrix)
	if n == 1 {
		return matrix[0][0]
	}

	prev := make([]int, n)
	next := make([]int, n)
	for i, v := range matrix[0] {
		prev[i] = v
	}

	for _, row := range matrix[1:] {
		next[0] = _min(prev[0], prev[1]) + row[0]
		for i := 1; i < n-1; i++ {
			next[i] = _min3(prev[i-1], prev[i], prev[i+1]) + row[i]
		}
		next[n-1] = _min(prev[n-2], prev[n-1]) + row[n-1]

		prev, next = next, prev
	}

	res := math.MaxInt32
	for _, v := range prev {
		res = _min(res, v)
	}

	return res
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
